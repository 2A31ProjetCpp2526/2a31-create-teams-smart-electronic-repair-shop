#include "qrcodechai.h"
#include "ui_qrcodechai.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>
#include <QPainter>


#include "connexion.h"    // Connexion::db()
#include "qrcodogen.h"    // librairie QR Nayuki

using namespace qrcodegen;   // pour QrCode

qrcodechai::qrcodechai(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qrcodechai)
{
    ui->setupUi(this);
}

qrcodechai::~qrcodechai()
{
    delete ui;
}

// -----------------------------------------------------------------------
// BOUTON : Générer le QR Code
// -----------------------------------------------------------------------
void qrcodechai::on_pushButton_generate_clicked()
{
    QString id = ui->lineEdit_1->text().trimmed();   // champ ID dans ton dialog

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID client.");
        return;
        ui->label_QRCode->setScaledContents(false);
    }

    // Récupérer les données du client
    QString clientData = getClientDataByID(id);

    if (clientData.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucun client trouvé avec cet ID.");
        return;
    }

    // Générer le QR code
    QPixmap qrPixmap = generateQRCode(clientData);

    // Afficher le QR code dans le label
    ui->label_QRCode->setPixmap(qrPixmap);
    ui->label_QRCode->setScaledContents(true);
}

// -----------------------------------------------------------------------
// RÉCUPÉRER LES DONNÉES DU CLIENT PAR ID
// -----------------------------------------------------------------------
QString qrcodechai::getClientDataByID(const QString &id)
{
    QSqlQuery query(Connexion::db());

    query.prepare(
        "SELECT ID_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL "
        "FROM SYSTEM.GS_CLIENT1 "
        "WHERE ID_CLIENT = :id"
        );
    query.bindValue(":id", id.toInt());

    if (!query.exec()) {
        QMessageBox::critical(
            this,
            "Erreur SQL",
            "Erreur lors de la récupération des données : " + query.lastError().text()
            );
        return QString();
    }

    if (query.next()) {
        QString clientData = QString(
                                 "ID: %1\n"
                                 "Nom: %2\n"
                                 "Prénom: %3\n"
                                 "Téléphone: %4\n"
                                 "Email: %5"
                                 )
                                 .arg(query.value("ID_CLIENT").toString())
                                 .arg(query.value("NOM").toString())
                                 .arg(query.value("PRENOM").toString())
                                 .arg(query.value("TELEPHONE").toString())
                                 .arg(query.value("EMAIL").toString());

        return clientData;
    }

    return QString();  // aucun client trouvé
}

// -----------------------------------------------------------------------
// GÉNÉRATION DU QR CODE
// -----------------------------------------------------------------------
QPixmap qrcodechai::generateQRCode(const QString &data)
{
    // --- Génération QR (lib Nayuki) ---
    QrCode qr = QrCode::encodeText(data.toUtf8().constData(), QrCode::Ecc::LOW);
    int qrSize = qr.getSize();  // ex: 33

    // --- Paramètres d'amélioration ---
    const int moduleSize = 10;   // chaque pixel QR = carré 10x10 -> HD
    const int border = 4;        // marge blanche autour (modules)

    int imgSize = (qrSize + border * 2) * moduleSize;

    // --- Image haute résolution ---
    QImage image(imgSize, imgSize, QImage::Format_RGB888);
    image.fill(Qt::white);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);

    // --- Dessiner chaque module ---
    for (int y = 0; y < qrSize; ++y) {
        for (int x = 0; x < qrSize; ++x) {
            if (qr.getModule(x, y)) {
                painter.drawRect(
                    (x + border) * moduleSize,
                    (y + border) * moduleSize,
                    moduleSize,
                    moduleSize
                    );
            }
        }
    }

    painter.end();

    // --- Adapter au QLabel SANS lissage ---
    QImage scaled = image.scaled(
        ui->label_QRCode->size(),
        Qt::KeepAspectRatio,
        Qt::FastTransformation   // ✔️ AUCUN flou
        );

    return QPixmap::fromImage(scaled);
}
