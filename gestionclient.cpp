#include "gestionclient.h"
#include "ui_gestionclient.h"
#include "client.h"
#include "connexion.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QDateTime>
#include <QPagedPaintDevice>
#include <QPageSize>
#include <QDialog>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include "qrcodechai.h"
#include <QTimer>
#include "qrcodogen.h"
using namespace qrcodegen;




#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>




gestionclient::gestionclient(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::GestionClient),
    speech(new QTextToSpeech(this)),
    voiceCombo(nullptr)
{
    ui->setupUi(this);
    remplirTable();
    // 🔊 INITIALISATION SYNTHÈSE VOCALE
    speech = new QTextToSpeech(this);

    // 🔊 (optionnel) si tu as une comboBox_voice dans le groupBox Speech

    voiceCombo = this->findChild<QComboBox*>("comboBox_voice");
    if (!voiceCombo) {
        qWarning("Impossible de trouver comboBox_voice (QComboBox) dans l'UI.");
    } else {
        const auto voices = speech->availableVoices();
        for (const QVoice &v : voices) {
            voiceCombo->addItem(v.name());
        }
        if (!speech->availableVoices().isEmpty()) {
            speech->setVoice(speech->availableVoices().first());
        }
        connect(ui->lineEdit, &QLineEdit::textChanged,
                this, [this](const QString &) {
                    on_pushButton_2_clicked();   // réutilise ton slot existant
                });

        remplirTable();

        remplirTable();
    }


    // Navigation vers la fenêtre principale
    connect(ui->pushButton_ToEmployes, &QPushButton::clicked,
            this, &gestionclient::goTomainwindow);

    // Validators
    ui->lineEdit_tel->setValidator(new QRegularExpressionValidator(
        QRegularExpression(R"(^[0-9+\s\-\(\)]{0,20}$)"), ui->lineEdit_tel));

    ui->lineEdit_email->setValidator(new QRegularExpressionValidator(
        QRegularExpression(R"(^[A-Z0-9._%+\-]+@[A-Z0-9.\-]+\.[A-Z]{2,}$)",
                           QRegularExpression::CaseInsensitiveOption),
        ui->lineEdit_email));


}

gestionclient::~gestionclient()
{
    delete ui;
}

bool gestionclient::verifTelephone(QString* msg) const
{
    QString tel = ui->lineEdit_tel->text().trimmed();
    if (tel.isEmpty()) { if (msg) *msg = "Téléphone obligatoire."; return false; }
    bool ok = false; tel.toLongLong(&ok);
    if (!ok) { if (msg) *msg = "Téléphone doit être numérique (colonne NUMBER)."; return false; }
    return true;
}

void gestionclient::remplirTable()
{
    QSqlQueryModel *model = Client::afficher();   // suppose retourner un QSqlQueryModel*
    if (!model) return;

    const int rows = model->rowCount();
    const int cols = model->columnCount();

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(rows);
    ui->tableWidget->setColumnCount(cols);

    // En-têtes
    QStringList headers;
    for (int c = 0; c < cols; ++c)
        headers << model->headerData(c, Qt::Horizontal).toString();
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Données
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            ui->tableWidget->setItem(
                r, c, new QTableWidgetItem(model->data(model->index(r, c)).toString()));

    delete model; // libère le modèle récupéré
}

void gestionclient::on_pushButton_1_clicked()   // AJOUT
{
    QString msg;
    // Tu peux choisir l’un des deux: verifTelephone (simple) OU verifTelephoneTN (Tunisie)
    // if (!verifTelephone(&msg)) { QMessageBox::warning(this, "Téléphone", msg); return; }
    if (!verifTelephoneTN(&msg)) { QMessageBox::warning(this, "Téléphone", msg); return; }
    if (!verifEmail(&msg))       { QMessageBox::warning(this, "Email", msg); return; }

    Client c;
    c.id_client = ui->lineEdit_id->text().toInt();
    c.nom       = ui->lineEdit_nom->text().trimmed();
    c.prenom    = ui->lineEdit_prenom->text().trimmed();
    c.telephone = ui->lineEdit_tel->text().trimmed();
    c.email     = ui->lineEdit_email->text().trimmed();

    if (c.ajouter()) {
        QMessageBox::information(this, "Succès", "Ajout effectué.");
        remplirTable();   // pas de clear (selon ta demande)
    } else {
        QMessageBox::critical(this, "Erreur", "Ajout non effectué.");
    }
}

void gestionclient::on_pushButton_modifier_clicked()   // MODIFIER
{
    QString msg;
    // if (!verifTelephone(&msg)) { QMessageBox::warning(this, "Téléphone", msg); return; }
    if (!verifTelephoneTN(&msg)) { QMessageBox::warning(this, "Téléphone", msg); return; }
    if (!verifEmail(&msg))       { QMessageBox::warning(this, "Email", msg); return; }

    int id = ui->lineEdit_id->text().toInt();
    if (id <= 0) {
        QMessageBox::warning(this, "Modifier", "ID_CLIENT invalide.");
        return;
    }

    Client c;
    c.id_client = id;
    c.nom       = ui->lineEdit_nom->text().trimmed();
    c.prenom    = ui->lineEdit_prenom->text().trimmed();
    c.telephone = ui->lineEdit_tel->text().trimmed();
    c.email     = ui->lineEdit_email->text().trimmed();

    if (c.modifier()) {
        QMessageBox::information(this, "Modifier", "Mise à jour effectuée.");
        remplirTable();
    } else {
        QMessageBox::critical(this, "Modifier", "Mise à jour non effectuée.");
    }
}

void gestionclient::on_pushButton_supprimer_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    if (id <= 0) {
        QMessageBox::warning(this, "Supprimer", "ID_CLIENT invalide.");
        return;
    }

    if (Client::supprimer(id)) {
        QMessageBox::information(this, "Supprimer", "Suppression effectuée.");
        remplirTable();
        // Clear uniquement à la suppression (comme demandé)
        ui->lineEdit_id->clear();
        ui->lineEdit_nom->clear();
        ui->lineEdit_prenom->clear();
        ui->lineEdit_tel->clear();
        ui->lineEdit_email->clear();
        ui->tableWidget->clearSelection();
    } else {
        QMessageBox::critical(this, "Supprimer", "Suppression non effectuée.");
    }
}

void gestionclient::goTomainwindow()
{
    MainWindow *Me = new MainWindow(this);
    Me->show();
    this->hide();
}

// =========================
// Helpers / Validations
// =========================

QString gestionclient::normalizePhone(const QString& raw)
{
    QString s = raw.trimmed();
    QString out; out.reserve(s.size());
    for (QChar ch : s) {
        if (ch.isDigit() || ch == '+') out.append(ch);
    }
    return out;
}

// Tunisie : +216XXXXXXXX ou 8 chiffres
bool gestionclient::verifTelephoneTN(QString* msg) const
{
    QString raw = ui->lineEdit_tel->text();
    if (raw.trimmed().isEmpty()) {
        if (msg) *msg = "Téléphone obligatoire.";
        return false;
    }

    QString phone = normalizePhone(raw);

    static const QRegularExpression rxIntl(R"(^\+216\d{8}$)");
    static const QRegularExpression rxNat (R"(^\d{8}$)");

    if (rxIntl.match(phone).hasMatch() || rxNat.match(phone).hasMatch())
        return true;

    if (msg) *msg = "Numéro invalide. Formats acceptés : +216XXXXXXXX ou 8 chiffres.";
    return false;
}

bool gestionclient::verifEmail(QString* msg) const
{
    QString e = ui->lineEdit_email->text().trimmed();
    if (e.isEmpty()) {
        if (msg) *msg = "Email obligatoire.";
        return false;
    }

    static const QRegularExpression rxMail(
        R"(^[A-Z0-9._%+\-]+@[A-Z0-9.\-]+\.[A-Z]{2,}$)",
        QRegularExpression::CaseInsensitiveOption
        );

    if (rxMail.match(e).hasMatch())
        return true;

    if (msg) *msg = "Email invalide. Exemple : nom.prenom@example.com";
    return false;
}
// =====================================================
// =====================================================
// === AJOUT : Fonction de RECHERCHE par ID (préfixe) ====
// =====================================================
void gestionclient::on_pushButton_2_clicked()
{
    // Si le champ est déjà vide → on recharge juste la table
    if (ui->lineEdit->text().trimmed().isEmpty()) {
        remplirTable();
        return;
    }

    // Sinon on efface le texte : ça déclenchera on_lineEdit_textChanged("")
    ui->lineEdit->clear();   // <- déclenche on_lineEdit_textChanged
}

void gestionclient::on_lineEdit_textChanged(const QString &text)
{
    QString searchText = text.trimmed();

    if (searchText.isEmpty()) {
        remplirTable();
        return;
    }

    // on ne garde que les chiffres
    for (QChar ch : searchText) {
        if (!ch.isDigit()) {
            return; // si ce n’est pas numérique, on ne filtre pas
        }
    }

    QSqlQueryModel *model = Client::rechercherParIdPrefix(searchText);
    if (!model) return;

    ui->tableWidget->setRowCount(model->rowCount());
    ui->tableWidget->setColumnCount(model->columnCount());

    // en-têtes
    for (int col = 0; col < model->columnCount(); ++col) {
        ui->tableWidget->setHorizontalHeaderItem(
            col,
            new QTableWidgetItem(model->headerData(col, Qt::Horizontal).toString())
            );
    }

    // données
    for (int row = 0; row < model->rowCount(); ++row)
        for (int col = 0; col < model->columnCount(); ++col)
            ui->tableWidget->setItem(
                row, col,
                new QTableWidgetItem(model->data(model->index(row, col)).toString())
                );

    delete model;
}

QImage generateSmallQR(const QString &text, int size = 90)
{
    QrCode qr = QrCode::encodeText(text.toUtf8().constData(), QrCode::Ecc::LOW);
    int qrSize = qr.getSize();

    QImage img(qrSize, qrSize, QImage::Format_RGB32);
    img.fill(Qt::white);

    for (int y = 0; y < qrSize; y++)
        for (int x = 0; x < qrSize; x++)
            img.setPixelColor(x, y, qr.getModule(x, y) ? Qt::black : Qt::white);

    // Agrandir proprement pour le PDF
    return img.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}




void gestionclient::on_pushButton_pdf_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(
        this, "Enregistrer sous", "clients_list.pdf", "PDF Files (*.pdf)");
    if (filePath.isEmpty())
        return;

    QPdfWriter pdf(filePath);
    QPageLayout layout(QPageSize(QPageSize::A4),
                       QPageLayout::Landscape,
                       QMarginsF(10, 10, 10, 10));
    pdf.setPageLayout(layout);
    pdf.setResolution(300);

    QPainter painter(&pdf);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier PDF !");
        return;
    }

    // === Marges & dimensions ===
    const int LM = 70, TM = 150, RM = 70, BM = 100;
    const int pageW = pdf.width();
    const int pageH = pdf.height();
    const int contentW = pageW - LM - RM;
    const int spacing = 20;
    const int rowH = 90;

    // === Largeurs des colonnes ===
    const int wID     = 160;
    const int wNom    = 260;
    const int wPrenom = 260;
    const int wTel    = 260;
    const int wQR     = 120;   // 🔹 dernière colonne QR

    int wMail = contentW - (wID + wNom + wPrenom + wTel + wQR) - 5 * spacing;
    if (wMail < 300) wMail = 300;

    // === Polices ===
    QFont titleFont("Arial", 26, QFont::Bold);
    QFont headerFont("Arial", 16, QFont::Bold);
    QFont dataFont("Arial", 15);

    int y = TM;

    // === Titre ===
    painter.setFont(titleFont);
    painter.drawText(LM, y,
                     QString("Liste des Clients - %1")
                         .arg(QDateTime::currentDateTime()
                                  .toString("yyyy-MM-dd HH:mm:ss")));
    y += 130;

    // === Fonctions utilitaires ===
    painter.setFont(headerFont);

    auto rectsAtY = [&](int yy) {
        QRect rID  (LM, yy, wID, rowH);
        QRect rNom (rID.right()   + spacing, yy, wNom, rowH);
        QRect rPre (rNom.right()  + spacing, yy, wPrenom, rowH);
        QRect rTel (rPre.right()  + spacing, yy, wTel, rowH);
        QRect rMail(rTel.right()  + spacing, yy, wMail, rowH);
        QRect rQR  (rMail.right() + spacing, yy, wQR, rowH);
        return std::array<QRect, 6>{rID, rNom, rPre, rTel, rMail, rQR};
    };

    auto drawHeaderCell = [&](const QRect &r, const QString &txt) {
        painter.fillRect(r, QColor(200, 200, 255)); // bleu clair
        painter.drawRect(r);
        painter.drawText(r.adjusted(20, 0, -20, 0),
                         Qt::AlignLeft | Qt::AlignVCenter, txt);
    };

    // === Ligne d’en-têtes ===
    auto H = rectsAtY(y);
    drawHeaderCell(H[0], "ID");
    drawHeaderCell(H[1], "Nom");
    drawHeaderCell(H[2], "Prénom");
    drawHeaderCell(H[3], "Téléphone");
    drawHeaderCell(H[4], "Email");
    drawHeaderCell(H[5], "QR");
    y += rowH + 25;

    // === Données ===
    QSqlQueryModel *model = Client::afficher();
    if (!model || model->rowCount() == 0) {
        QMessageBox::information(this, "PDF", "Aucun client à exporter !");
        painter.end();
        return;
    }

    painter.setFont(dataFont);

    auto newPage = [&]() {
        pdf.newPage();
        y = TM;
        painter.setFont(headerFont);
        auto HH = rectsAtY(y);
        drawHeaderCell(HH[0], "ID");
        drawHeaderCell(HH[1], "Nom");
        drawHeaderCell(HH[2], "Prénom");
        drawHeaderCell(HH[3], "Téléphone");
        drawHeaderCell(HH[4], "Email");
        drawHeaderCell(HH[5], "QR");
        y += rowH + 25;
        painter.setFont(dataFont);
    };

    for (int r = 0; r < model->rowCount(); ++r) {
        if (y + rowH > pageH - BM)
            newPage();

        auto R = rectsAtY(y);

        // Alternance de couleur de fond
        if (r % 2 == 1)
            painter.fillRect(QRect(LM, y, contentW, rowH),
                             QColor(245, 245, 245));

        QString id     = model->data(model->index(r, 0)).toString();
        QString nom    = model->data(model->index(r, 1)).toString();
        QString prenom = model->data(model->index(r, 2)).toString();
        QString tel    = model->data(model->index(r, 3)).toString();
        QString mail   = model->data(model->index(r, 4)).toString();

        // Bordures des cellules
        for (const QRect &rc : R)
            painter.drawRect(rc);

        // === Texte des colonnes ===
        painter.drawText(R[0].adjusted(20, 0, -20, 0),
                         Qt::AlignLeft | Qt::AlignVCenter, id);
        painter.drawText(R[1].adjusted(20, 0, -20, 0),
                         Qt::AlignLeft | Qt::AlignVCenter, nom);
        painter.drawText(R[2].adjusted(20, 0, -20, 0),
                         Qt::AlignLeft | Qt::AlignVCenter, prenom);
        painter.drawText(R[3].adjusted(20, 0, -20, 0),
                         Qt::AlignLeft | Qt::AlignVCenter, tel);

        painter.save();
        painter.drawText(R[4].adjusted(20, 10, -20, -10),
                         Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap, mail);
        painter.restore();

        // === QR Code (dernière colonne) ===
        // === QR Code (dernière colonne) ===
        // On encode toutes les infos principales du client
        QString qrText = QString(
                             "ID: %1\nNom: %2\nPrénom: %3\nTéléphone: %4\nEmail: %5"
                             ).arg(id, nom, prenom, tel, mail);

        QImage qrImg = generateSmallQR(qrText, rowH - 10);
        QRect qrRect = R[5].adjusted(10, 10, -10, -10);
        painter.drawImage(qrRect, qrImg);

        y += rowH + 25;
    }

    painter.end();
    QMessageBox::information(this, "PDF",
                             "PDF sauvegardé avec succès à : " + filePath);
}

class PieChartWidget : public QWidget
{
public:
    PieChartWidget(const QMap<QString,int>& stats, QWidget *parent = nullptr)
        : QWidget(parent),
        m_stats(stats),
        m_progress(0.0)     // 0 = vide, 1 = disque complet
    {
        // Timer d’animation : ~60 FPS
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this, timer]() {

            m_progress += 0.03;   // vitesse de remplissage (≈ 1 sec)
            if (m_progress >= 1.0) {
                m_progress = 1.0;
                timer->stop();
                timer->deleteLater();
            }

            update(); // redessiner => apparition en LIVE
        });

        timer->start(16); // 16 ms ≈ 60 FPS
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        if (m_stats.isEmpty())
            return;

        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        int diameter = qMin(width(), height()) * 0.55;
        int centerX  = (width()  - diameter) / 2 - 60; // décalé pour la légende
        int centerY  = (height() - diameter) / 2;

        QRectF rect(centerX, centerY, diameter, diameter);

        // Total
        int total = 0;
        for (auto v : m_stats)
            total += v;
        if (total == 0) return;

        // Couleurs
        QList<QColor> colors = {
            QColor(255, 153, 153),
            QColor(153, 204, 255),
            QColor(255, 204, 153),
            QColor(194, 214, 214),
            QColor(217, 179, 255)
        };

        // ==== CAMEMBERT AVEC APPARITION DANS UN SEUL SENS ====
        double maxAngleToDraw = 360.0 * m_progress; // angle total actuellement visible
        double currentStart   = 0.0;                // on part toujours du même sens
        int index = 0;

        for (auto it = m_stats.begin(); it != m_stats.end(); ++it) {
            int value = it.value();
            if (value <= 0) continue;

            double sliceAngle = 360.0 * value / total;
            double sliceEnd   = currentStart + sliceAngle;

            // Si tout ce secteur est au-delà de la zone visible -> on arrête
            if (currentStart >= maxAngleToDraw)
                break;

            // Angle effectivement à dessiner pour ce secteur
            double visibleEnd = qMin(sliceEnd, maxAngleToDraw);
            double visibleAngle = visibleEnd - currentStart;
            if (visibleAngle <= 0.0) {
                currentStart = sliceEnd;
                index++;
                continue;
            }

            p.setBrush(colors[index % colors.size()]);
            p.setPen(Qt::black);
            p.drawPie(rect,
                      int(currentStart * 16),
                      int(visibleAngle * 16));

            currentStart = sliceEnd;
            index++;
        }

        // ==== LÉGENDE (fixe) ====
        int y = 50;
        index = 0;
        for (auto it = m_stats.begin(); it != m_stats.end(); ++it) {
            int value = it.value();
            if (value <= 0) continue;

            double percent = (double(value) / total) * 100.0;

            p.setBrush(colors[index % colors.size()]);
            p.drawRect(width() - 150, y, 15, 15);

            p.drawText(width() - 130, y + 12,
                       QString("%1 — %2% (%3)")
                           .arg(it.key())
                           .arg(QString::number(percent, 'f', 1)) // arrondi 1 chiffre
                           .arg(value));

            y += 28;
            index++;
        }
    }

private:
    QMap<QString,int> m_stats;
    double m_progress;   // 0 → 1 : progression de l’apparition
};





void gestionclient::on_pushButton_stat_clicked()
{
    QMap<QString, int> stats = Client::getEmailDomainStats();

    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée disponible.");
        return;
    }

    QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle("Statistiques des emails");
    dlg->resize(700, 500);

    QVBoxLayout *layout = new QVBoxLayout(dlg);
    PieChartWidget *pie = new PieChartWidget(stats, dlg);
    layout->addWidget(pie);

    dlg->setLayout(layout);
    dlg->exec();
}



// =====================================================
//  Bouton statistiques : affiche le camembert
// =====================================================
void gestionclient::on_pushButton_trier_clicked()
{
    QString critere = ui->comboBox->currentText();

    QSqlQueryModel *model = nullptr;

    if (critere == "Nom") {
        model = Client::trierParNom();
    }
    else if (critere == "Prenom") {
        model = Client::trierParPrenom();
    }
    else {
        QMessageBox::warning(this, "Erreur", "Veuillez choisir un critère !");
        return;
    }

    if (!model || model->rowCount() == 0) {
        QMessageBox::information(this, "Tri", "Aucun client trouvé !");
        delete model;
        return;
    }

    // Remplir le tableau
    ui->tableWidget->setRowCount(model->rowCount());
    ui->tableWidget->setColumnCount(model->columnCount());

    for (int col = 0; col < model->columnCount(); col++) {
        ui->tableWidget->setHorizontalHeaderItem(
            col,
            new QTableWidgetItem(model->headerData(col, Qt::Horizontal).toString())
            );
    }

    for (int row = 0; row < model->rowCount(); row++)
        for (int col = 0; col < model->columnCount(); col++)
            ui->tableWidget->setItem(
                row, col,
                new QTableWidgetItem(model->data(model->index(row, col)).toString())
                );

    delete model;
}

void gestionclient::on_pushButton_qr_clicked()
{
    qrcodechai dialog(this);                 // Créer le dialog QR
    dialog.setWindowTitle("QR Code Client"); // Titre de la fenêtre
    dialog.exec();                           // Affichage modal
}
void gestionclient::on_pushButton_speech_clicked()
{
    if (!speech) {
        QMessageBox::warning(this, "Speech", "Le moteur de synthèse vocale n'est pas initialisé.");
        return;
    }

    int row = ui->tableWidget->currentRow();
    if (row < 0) {
        speech->say("Veuillez sélectionner un client dans la liste.");
        return;
    }

    QString id        = ui->tableWidget->item(row, 0) ? ui->tableWidget->item(row, 0)->text() : "";
    QString nom       = ui->tableWidget->item(row, 1) ? ui->tableWidget->item(row, 1)->text() : "";
    QString prenom    = ui->tableWidget->item(row, 2) ? ui->tableWidget->item(row, 2)->text() : "";
    QString telephone = ui->tableWidget->item(row, 3) ? ui->tableWidget->item(row, 3)->text() : "";
    QString email     = ui->tableWidget->item(row, 4) ? ui->tableWidget->item(row, 4)->text() : "";

    // Appliquer la voix choisie
    if (voiceCombo) {
        int voiceIndex = voiceCombo->currentIndex();
        const auto voices = speech->availableVoices();
        if (voiceIndex >= 0 && voiceIndex < voices.size()) {
            speech->setVoice(voices.at(voiceIndex));
        }
    }

    QString texte = QString(
                        "Client numéro %1. Nom : %2. Prénom : %3. Téléphone : %4. Email : %5."
                        ).arg(id, nom, prenom, telephone, email);

    speech->say(texte);
}






MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Remplir la ComboBox Type
    ui->cb_type->addItems({"PC", "Smartphone", "Tablette"});

    // Initialiser le tableau
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << "Type" << "Marque/Modèle" << "Date dépôt" << "Description" << "État");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    // permet modifier la cellule par double-clic
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    // connect auto (si slot nommé on_tableWidget_cellChanged, Qt auto-connect fonctionne),
    // sinon connect explicitement :
    //connect(ui->tableWidget, &QTableWidget::cellChanged, this, &MainWindow::on_tableWidget_cellChanged);


    refreshTable();
    // Quand l'utilisateur clique sur une cellule -> sélection de la ligne entière et remplissage du formulaire
    connect(ui->tableWidget, &QTableWidget::cellClicked, this, [this](int row, int /*col*/){
        if (row < 0) return;
        // Protéger contre items nuls
        QTableWidgetItem *itId = ui->tableWidget->item(row, 0);
        if (!itId) return;

        // Remplir les champs du formulaire avec les valeurs de la ligne
        ui->le_id->setText(itId->text());
        if (ui->tableWidget->item(row, 1)) ui->cb_type->setCurrentText(ui->tableWidget->item(row, 1)->text());
        if (ui->tableWidget->item(row, 2)) ui->le_marque->setText(ui->tableWidget->item(row, 2)->text());
        if (ui->tableWidget->item(row, 3)) {
            QString dateText = ui->tableWidget->item(row, 3)->text();
            QDate d = QDate::fromString(dateText, "dd/MM/yyyy");
            if (d.isValid()) ui->date_depot->setDate(d);
        }
        if (ui->tableWidget->item(row, 4)) ui->te_desc->setPlainText(ui->tableWidget->item(row, 4)->text());
        // Stocker la ligne sélectionnée si besoin
        ui->tableWidget->selectRow(row);
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

// Fonction pour recharger le contenu du QTableWidget
void MainWindow::refreshTable()
{
    ui->tableWidget->blockSignals(true);
    QSqlQuery query;
    // Un SELECT explicite, vérifier les noms de colonnes exacts
    if (!query.exec("SELECT ID, TYPE, MARQUEMODELE, DATEDEPOT, DESCRIPTION_PANNE, ETAT FROM EQUIPEMENT ORDER BY ID")) {
        qDebug() << "refreshTable SELECT error:" << query.lastError().text();
        QMessageBox::critical(this, "Erreur SQL", "Impossible de lire la table :\n" + query.lastError().text());
        ui->tableWidget->blockSignals(false);
        return;
    }

    ui->tableWidget->clearContents();

    ui->tableWidget->setRowCount(0);
    int row = 0;
    while (query.next()) {
        ui->tableWidget->insertRow(row);

        QTableWidgetItem *it0 = new QTableWidgetItem(query.value("ID").toString());
        it0->setFlags(it0->flags() & ~Qt::ItemIsEditable); // ID non editable
        ui->tableWidget->setItem(row, 0, it0);
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("TYPE").toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("MARQUEMODELE").toString()));

        // DATEDEPOT peut être renvoyé sous forme de QDate ou QString via ODBC :
        QVariant v = query.value("DATEDEPOT");
        QString dateText;
        if (v.canConvert<QDate>()) dateText = v.toDate().toString("yyyy-MM-dd");
        else dateText = v.toString();
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(dateText));

        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("DESCRIPTION_PANNE").toString()));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("ETAT").toString()));
        row++;
    }
}
void MainWindow::clearForm()
{
    ui->le_id->clear();
    ui->le_marque->clear();
    ui->te_desc->clear();
    ui->date_depot->setDate(QDate::currentDate());
    ui->cb_type->setCurrentIndex(0);
}

// ➕ Ajouter
void MainWindow::on_btn_ajouter_clicked()
{
    int id = ui->le_id->text().toInt();
    QString type = ui->cb_type->currentText();
    QString marque = ui->le_marque->text();
    QString desc = ui->te_desc->toPlainText();
    QDate date = ui->date_depot->date();
    QString etat = "en cours"; // valeur par défaut

    if (id <= 0 || marque.isEmpty() || desc.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires !");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO EQUIPEMENT "
                  "(ID, TYPE, MARQUEMODELE, DATEDEPOT, DESCRIPTION_PANNE, ETAT) "
                  "VALUES (:id, :type, :marque, :date, :desc, :etat)");
    query.bindValue(":id", id);
    query.bindValue(":type", type);
    query.bindValue(":marque", marque);
    query.bindValue(":date", date);
    query.bindValue(":desc", desc);
    query.bindValue(":etat", etat);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Équipement ajouté !");
        refreshTable();
        clearForm();
    } else {
        QMessageBox::critical(this, "Erreur SQL",
                              "Échec de l’ajout : " + query.lastError().text());
    }
}

// ✏️ Modifier
void MainWindow::on_btn_modifier_clicked()
{
    // 🔹 Vérifier qu’une ligne est bien sélectionnée
    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner une ligne à modifier !");
        return;
    }

    int row = ui->tableWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Erreur", "Aucune ligne sélectionnée !");
        return;
    }

    // 🔹 Récupérer les données depuis le tableau (pas depuis les lineEdits)
    QString id = ui->tableWidget->item(row, 0)->text();
    QString type = ui->tableWidget->item(row, 1)->text();
    QString marque = ui->tableWidget->item(row, 2)->text();
    QString dateStr = ui->tableWidget->item(row, 3)->text();
    QString desc = ui->tableWidget->item(row, 4)->text();
    QString etat = ui->tableWidget->item(row, 5)->text();

    // Vérifier que la date est valide
    QDate date = QDate::fromString(dateStr, "yyyy-MM-dd");
    if (!date.isValid()) {
        QMessageBox::warning(this, "Date invalide", "Format de date invalide (utilise yyyy-MM-dd)");
        return;
    }

    // 🔹 Créer la requête de mise à jour
    QSqlQuery query;
    query.prepare("UPDATE EQUIPEMENT SET TYPE = :type, MARQUEMODELE = :marque, "
                  "DATEDEPOT = TO_DATE(:date, 'YYYY-MM-DD'), "
                  "DESCRIPTION_PANNE = :desc, ETAT = :etat WHERE ID = :id");
    query.bindValue(":type", type);
    query.bindValue(":marque", marque);
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":desc", desc);
    query.bindValue(":etat", etat);
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", "Échec de la mise à jour :\n" + query.lastError().text());
        qDebug() << "❌ Erreur SQL :" << query.lastError().text();
        return;
    }

    // 🔹 Commit pour Oracle (nécessaire parfois avec ODBC)
    QSqlDatabase::database().commit();

    QMessageBox::information(this, "Succès", "✅ Modification enregistrée avec succès !");
    qDebug() << "✅ Ligne ID" << id << "mise à jour dans Oracle.";

    // 🔹 Recharger le tableau pour afficher les nouvelles données
    refreshTable();
}



// ---------- SUPPRIMER ----------
void MainWindow::on_btn_supprimer_clicked()
{
    int id = ui->le_id->text().toInt();  // Récupère l’ID de la zone de texte
    bool test = eqTmp.supprimer(id);      // Appel de la méthode du modèle

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée.\nClick Cancel to exit."),
                                 QMessageBox::Cancel);
        refreshTable();
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }
}



// 🔄 Actualiser
void MainWindow::on_btn_actualiser_clicked()
{
    refreshTable();
}



