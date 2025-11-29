#include "smartelectronic.h"
#include "ui_smartelectronic.h"
#include "equipement.h"
#include "client.h"
#include "connection.h"
#include "qrcodechai.h"
#include "qrcodogen.h"

#include <QMessageBox>
#include <QTableWidgetItem>
#include <QSqlQueryModel>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>


#include <QTimer>
#include <QMenu>

#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>

#include <QGraphicsOpacityEffect>
#include <QVBoxLayout>
#include <QLabel>
#include <QColor>

#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QApplication>
#include <QScreen>

#include <QPieSeries>
#include <QPieSlice>
#include <QChartView>
#include <QChart>
#include <iostream>

#include <QPdfWriter>
#include <QPainter>
#include <QDateTime>
#include <QPagedPaintDevice>
#include <QPageSize>
#include <QDialog>

using namespace qrcodegen;

SmartElectronic:: SmartElectronic(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::SmartElectronic),
    speech(new QTextToSpeech(this)),
    voiceCombo(nullptr)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->PageEquipement);
    ui->date_depot->setDate(QDate::currentDate());
    ui->date_limite->setDate(QDate::currentDate());

    afficherStatEtatPie();

    historiqueNotif = new QListWidget(this);
    historiqueNotif->hide();
    QTimer::singleShot(200, this, &SmartElectronic::chargerNotifications);

    timerNotif = new QTimer(this);
    connect(timerNotif, &QTimer::timeout, this, &SmartElectronic::chargerNotifications);
    timerNotif->start(30000);

    connect(ui->btnClient, &QPushButton::clicked,
            this, &SmartElectronic::on_btnClient_clicked);

    connect(ui->btnEquipement, &QPushButton::clicked,
            this, &SmartElectronic::on_btnEquipement_clicked);


    // Définir le nombre de colonnes
    ui->EquipementTableWidget->setColumnCount(8);
    ui->EquipementTableWidget->setIconSize(QSize(80, 80));
    ui->widget_notifications->setVisible(false);

    // Donner un nom aux colonnes
    ui->EquipementTableWidget->setHorizontalHeaderLabels(
        QStringList() << "ID" << "Type" << "Marque/Modèle"
                      << "Date Dépôt" << "État" << "Description panne"<<"image"<<"Date Limite"
        );

    remplirEquipementTable();
    connect(ui->EquipementTableWidget, &QTableWidget::cellClicked,
            this, &SmartElectronic::on_EquipementTableWidget_cellClicked);

    //gestion client
    remplirClientTable();
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

        remplirClientTable();

        remplirClientTable();
    }

    // Validators
    ui->lineEdit_tel->setValidator(new QRegularExpressionValidator(
        QRegularExpression(R"(^[0-9+\s\-\(\)]{0,20}$)"), ui->lineEdit_tel));

    ui->lineEdit_email->setValidator(new QRegularExpressionValidator(
        QRegularExpression(R"(^[A-Z0-9._%+\-]+@[A-Z0-9.\-]+\.[A-Z]{2,}$)",
                           QRegularExpression::CaseInsensitiveOption),
        ui->lineEdit_email));


}
SmartElectronic:: ~SmartElectronic()
{
    delete ui;
}
void SmartElectronic::remplirEquipementTable()
{
    QSqlQuery query = Etmp.afficher();

    // Effacer les anciennes lignes
    ui->EquipementTableWidget->setRowCount(0);

    int row = 0;
    while (query.next()) {

        ui->EquipementTableWidget->insertRow(row);

        ui->EquipementTableWidget->setItem(row, 0, new QTableWidgetItem(query.value("ID_EQUIPEMENT").toString()));
        ui->EquipementTableWidget->setItem(row, 1, new QTableWidgetItem(query.value("TYPE").toString()));
        ui->EquipementTableWidget->setItem(row, 2, new QTableWidgetItem(query.value("MARQUE_MODELE").toString()));
        ui->EquipementTableWidget->setItem(row, 3, new QTableWidgetItem(query.value("DATE_DEPOT").toString()));
        ui->EquipementTableWidget->setItem(row, 4, new QTableWidgetItem(query.value("ETAT").toString()));
        ui->EquipementTableWidget->setItem(row, 5, new QTableWidgetItem(query.value("DESCRIPTION_PANNE").toString()));
         ui->EquipementTableWidget->setItem(row, 7, new QTableWidgetItem(query.value("DATE_LIMITE").toString()));
        QString imgPath = query.value("IMAGE_PATH").toString();

        QTableWidgetItem *imgItem = new QTableWidgetItem();

        // Vérifier si l’image existe
        if (QFile::exists(imgPath))
        {
            QPixmap pix(imgPath);
            imgItem->setIcon(QIcon(pix.scaled(100, 100, Qt::KeepAspectRatio)));
            ui->EquipementTableWidget->setRowHeight(row, 80);
        }
        else
        {
            imgItem->setText("Aucune image");
        }

        ui->EquipementTableWidget->setItem(row, 6, imgItem);


        row++;
    }
}
void SmartElectronic::on_EquipementTableWidget_cellClicked(int row, int column)
{
    // Récupération des valeurs du tableau
    QString id = ui->EquipementTableWidget->item(row, 0)->text();
    QString type = ui->EquipementTableWidget->item(row, 1)->text();
    QString marque = ui->EquipementTableWidget->item(row, 2)->text();
    QString date = ui->EquipementTableWidget->item(row, 3)->text();
    QString etat = ui->EquipementTableWidget->item(row, 4)->text();
    QString description = ui->EquipementTableWidget->item(row, 5)->text();
    QString img = ui->EquipementTableWidget->item(row, 6)->text();
    QString datel = ui->EquipementTableWidget->item(row, 7)->text();
    // Affectation dans les champs du formulaire
    ui->le_id->setText(id);
    ui->cb_type->setCurrentText(type);
    ui->le_marque->setText(marque);
    ui->date_depot->setDate(QDate::fromString(date, "yyyy-MM-dd"));
    ui->date_limite->setDate(QDate::fromString(datel, "yyyy-MM-dd"));
    ui->cb_etat->setCurrentText(etat);
    ui->te_desc->setPlainText(description);
    ui->le_image->setText(img);

    if (!img.isEmpty())
        ui->label_image->setPixmap(QPixmap(img).scaled(180,180,Qt::KeepAspectRatio));
}

void SmartElectronic::on_btn_ajouter_clicked()
{
    int id = ui->le_id->text().toInt();
    QString type = ui->cb_type->currentText();
    QString marque = ui->le_marque->text();
    QDate dateDepot = ui->date_depot->date();
    QString etat = ui->cb_etat->currentText();
    QString description = ui->te_desc->toPlainText();
    QString image_path = ui->le_image->text();
    QDate date_limite = ui->date_limite->date();

    Equipement e(id, type, marque, dateDepot,date_limite, etat, description,image_path);

    if(e.ajouter())
    {
        remplirEquipementTable();
        QMessageBox::information(this, "Succès", "Équipement ajouté !");
        afficherStatEtatPie();
        etat = etat.trimmed().toLower();
        etat[0] = etat[0].toUpper();
        chargerNotifications();



    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Ajout échoué.");
    }
}



void SmartElectronic::on_btn_modifier_clicked()
{
    int id = ui->le_id->text().toInt();
    QString type = ui->cb_type->currentText();
    QString marque = ui->le_marque->text();
    QDate dateDepot = ui->date_depot->date();
    QString etat = ui->cb_etat->currentText();
    QString description = ui->te_desc->toPlainText();
    QString image_path = ui->le_image->text();
    QDate date_limite = ui->date_limite->date();

    Equipement e(id, type, marque, dateDepot,date_limite, etat, description,image_path);

    if(e.modifier())
    {
        remplirEquipementTable();
        QMessageBox::information(this, "Succès", "Équipement modifié !");
        etat = etat.trimmed().toLower();
        etat[0] = etat[0].toUpper();



    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Modification échouée.");
    }
}

void SmartElectronic::on_btn_supprimer_clicked()
{
    int id = ui->le_id->text().toInt();

    if(Etmp.supprimer(id))
    {
        remplirEquipementTable();
        QMessageBox::information(this, "Succès", "Équipement supprimé !");
        afficherStatEtatPie();

    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Suppression échouée.");
    }
}
void SmartElectronic::on_btn_pdf_clicked()
{
    // 1️⃣ Vérifier si la BD est ouverte
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::warning(this, "Erreur", "Base de données non connectée !");
        return;
    }

    // 2️⃣ Choisir emplacement du PDF
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Enregistrer le fichier PDF",
        "",
        "Fichiers PDF (*.pdf)"
        );

    if (fileName.isEmpty())
        return;

    // 3️⃣ Charger les données SQL dans un modèle
    QSqlQueryModel model;
    model.setQuery("SELECT ID_EQUIPEMENT, TYPE, MARQUE_MODELE, DATE_DEPOT, ETAT, DESCRIPTION_PANNE,IMAGE_PATH,DATE_LIMITE "
                   "FROM EQUIPEMENT");

    if (model.rowCount() == 0) {
        QMessageBox::information(this, "Info", "Aucune donnée trouvée dans la table EQUIPEMENT.");
        return;
    }

    // 4️⃣ Construire le HTML pour PDF
    QString html;
    html += "<html><head><style>"
            "body { font-family: Arial; margin: 20px; }"
            "table { width: 100%; border-collapse: collapse; }"
            "th, td { border: 1px solid #000; padding: 6px; text-align: center; }"
            "th { background-color: #f2f2f2; }"
            "</style></head><body>";

    html += "<h2 align='center'>Liste des Équipements</h2><br>";
    html += "<table><tr>";

    // En-têtes
    for (int col = 0; col < model.columnCount(); col++) {
        html += "<th>" + model.headerData(col, Qt::Horizontal).toString() + "</th>";
    }
    html += "</tr>";

    // Données
    for (int row = 0; row < model.rowCount(); row++) {
        html += "<tr>";
        for (int col = 0; col < model.columnCount(); col++) {
            html += "<td>" + model.data(model.index(row, col)).toString() + "</td>";
        }
        html += "</tr>";
    }

    html += "</table></body></html>";

    // 5️⃣ Conversion PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(html);
    doc.print(&printer);

    QMessageBox::information(this, "Succès", "Le fichier PDF a été généré avec succès !");
}
void SmartElectronic::on_btn_recherche_clicked()
{
    QString cle = ui->le_recherche->text();


    if (cle.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez saisir un mot-clé !");
        remplirEquipementTable();
        return;
    }

    QSqlQuery query;

    query.prepare(
        "SELECT ID_EQUIPEMENT, TYPE, MARQUE_MODELE, DATE_DEPOT, ETAT, DESCRIPTION_PANNE, IMAGE_PATH, DATE_LIMITE "
        "FROM EQUIPEMENT "
        "WHERE "
        "TO_CHAR(ID_EQUIPEMENT) LIKE :cle "
        "OR UPPER(TYPE) LIKE UPPER(:cle2) "
        "OR UPPER(MARQUE_MODELE) LIKE UPPER(:cle2) "
        "OR UPPER(DATE_DEPOT) LIKE UPPER(:cle2) "
        "OR UPPER(ETAT) LIKE UPPER(:cle2) "
        "OR UPPER(DESCRIPTION_PANNE) LIKE UPPER(:cle2)"
        );

    query.bindValue(":cle", "%" + cle + "%");
    query.bindValue(":cle2", "%" + cle + "%");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
        return;
    }

    ui->EquipementTableWidget->setRowCount(0);

    int row = 0;

    while (query.next()) {
        ui->EquipementTableWidget->insertRow(row);

        ui->EquipementTableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->EquipementTableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->EquipementTableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->EquipementTableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->EquipementTableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        ui->EquipementTableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
        ui->EquipementTableWidget->setItem(row, 7, new QTableWidgetItem(query.value(7).toString()));


        QString imgPath = query.value("IMAGE_PATH").toString();

        QTableWidgetItem *imgItem = new QTableWidgetItem();

        // Vérifier si l’image existe
        if (QFile::exists(imgPath))
        {
            QPixmap pix(imgPath);
            imgItem->setIcon(QIcon(pix.scaled(100, 100, Qt::KeepAspectRatio)));
            ui->EquipementTableWidget->setRowHeight(row, 80);
        }
        else
        {
            imgItem->setText("Aucune image");
        }

        ui->EquipementTableWidget->setItem(row, 6, imgItem);

        row++;
    }

    if (row == 0)
        QMessageBox::information(this, "Recherche", "Aucun équipement trouvé !");
}
void SmartElectronic::on_btn_tri_clicked()
{
    QString critere = ui->cb_tri->currentText();

    QString queryText;

    // 🟦 Tri par TYPE
    if (critere == "TYPE") {
        queryText =
            "SELECT ID_EQUIPEMENT, TYPE, MARQUE_MODELE, DATE_DEPOT, ETAT, DESCRIPTION_PANNE, IMAGE_PATH, DATE_LIMITE"
            " FROM EQUIPEMENT"
            " ORDER BY TYPE ASC";
    }

    // 🟨 Tri par ÉTAT
    else if (critere == "ETAT") {
        queryText =
            "SELECT ID_EQUIPEMENT, TYPE, MARQUE_MODELE, DATE_DEPOT, ETAT, DESCRIPTION_PANNE, IMAGE_PATH, DATE_LIMITE"
            " FROM EQUIPEMENT "
            " ORDER BY ETAT ASC";
    }

    QSqlQuery query;

    if (!query.exec(queryText)) {
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
        return;
    }

    // Nettoyer tableau
    ui->EquipementTableWidget->setRowCount(0);
    int row = 0;

    while (query.next()) {
        ui->EquipementTableWidget->insertRow(row);

        ui->EquipementTableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->EquipementTableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->EquipementTableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->EquipementTableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->EquipementTableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        ui->EquipementTableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
        ui->EquipementTableWidget->setItem(row, 7, new QTableWidgetItem(query.value(7).toString()));

        QString imgPath = query.value("IMAGE_PATH").toString();

        QTableWidgetItem *imgItem = new QTableWidgetItem();

        // Vérifier si l’image existe
        if (QFile::exists(imgPath))
        {
            QPixmap pix(imgPath);
            imgItem->setIcon(QIcon(pix.scaled(100, 100, Qt::KeepAspectRatio)));
            ui->EquipementTableWidget->setRowHeight(row, 80);
        }
        else
        {
            imgItem->setText("Aucune image");
        }

        ui->EquipementTableWidget->setItem(row, 6, imgItem);

        row++;
    }

    QMessageBox::information(this, "Tri réalisé",
                             "Tri effectué par : " + critere);
}
// Fonction pour effacer les anciens widgets dans un layout
void clearLayout(QLayout *layout)
{
    if (!layout) return;

    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater(); // Supprime le widget proprement
        }
        if (QLayout *childLayout = item->layout()) {
            clearLayout(childLayout); // Supprimer récursivement
        }
        delete item;
    }
}

/*// Fonction principale pour afficher le graphique en secteurs par état
void SmartElectronic::afficherStatEtatPie()
{
    // 1️⃣ Récupérer ou créer le layout du widget_stat
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->widget_stat->layout());
    if (!layout) {
        layout = new QVBoxLayout(ui->widget_stat);
        layout->setContentsMargins(0, 0, 0, 0);
        ui->widget_stat->setLayout(layout);
    } else {
        clearLayout(layout); // Supprimer les anciens widgets
    }

    // 2️⃣ Récupérer les statistiques depuis la base de données
    QSqlQuery query("SELECT UPPER(ETAT), COUNT(*) FROM EQUIPEMENT GROUP BY UPPER(ETAT)");


    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0); // Pas de donut, graphique plein

    while (query.next()) {
        QString etat = query.value(0).toString().toLower();
        etat[0] = etat[0].toUpper();   // Mise en forme propre du texte

        int count = query.value(1).toInt();

        // Ajouter une tranche au pie chart
        QPieSlice *slice = series->append(etat + " (" + QString::number(count) + ")", count);
        slice->setLabelVisible(true);
        slice->setLabelColor(Qt::black);
        slice->setLabelPosition(QPieSlice::LabelOutside);
    }

    // 3️⃣ Créer le chart et le configurer
    QChart *chart = new QChart();
    chart->setMinimumHeight(250);
    chart->addSeries(series);
    chart->setTitle("État des équipements");
    chart->legend()->setAlignment(Qt::AlignBottom);

    // 4️⃣ Créer le ChartView pour l’afficher
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 5️⃣ Ajouter le ChartView au layout existant
    layout->addWidget(chartView);
}*/
void SmartElectronic::on_btn_image_clicked()
{
    QString file = QFileDialog::getOpenFileName(
        this,
        "Choisir une image",
        "",
        "Images (*.png *.jpg *.jpeg *.bmp)"
        );

    if (file.isEmpty()) return;

    ui->le_image->setText(file);
    ui->label_image->setPixmap(QPixmap(file).scaled(180,180, Qt::KeepAspectRatio));
}
void SmartElectronic::afficherStatEtatPie()
{
    // 1) Récupérer ou créer le layout
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->widget_stat->layout());
    if (!layout) {
        layout = new QVBoxLayout(ui->widget_stat);
        layout->setContentsMargins(0, 0, 0, 0);
        ui->widget_stat->setLayout(layout);
    } else {
        clearLayout(layout);
    }

    // ----------- 2) Récupérer les données -----------
    QSqlQuery query("SELECT UPPER(ETAT), COUNT(*) FROM EQUIPEMENT GROUP BY UPPER(ETAT)");

    QMap<QString, int> data;
    int total = 0;

    while (query.next()) {
        QString etat = query.value(0).toString().toLower();
        etat[0] = etat[0].toUpper();  // Exemple : "repare" → "Repare"

        int count = query.value(1).toInt();
        data[etat] = count;
        total += count;
    }

    if (total == 0) return;

    // ----------- 3) Créer la série Pie -----------
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0);

    for (auto it = data.begin(); it != data.end(); ++it) {
        double percent = (double(it.value()) / total) * 100.0;
        QString label = QString("%1 : %2%")
                            .arg(it.key())
                            .arg(QString::number(percent, 'f', 1)); // 1 décimale

        QPieSlice *slice = series->append(label, it.value());
        slice->setLabelVisible(true);
        slice->setLabelColor(Qt::black);
        slice->setLabelPosition(QPieSlice::LabelOutside);
    }

    // ----------- 4) Chart -----------
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("État des équipements (%)");
    chart->legend()->setAlignment(Qt::AlignBottom);

    // ----------- 5) View -----------
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView);
}








void SmartElectronic::showSimpleNotification(const QString &title,
                                        const QString &message,
                                        const QString &icon,
                                        QColor color,
                                        int duration)
{
    // --- Création du widget notification ---
    QWidget *notifWidget = new QWidget(this);   // IMPORTANT : parent = SmartElectronic
    notifWidget->setWindowFlags(Qt::FramelessWindowHint);
    notifWidget->setAttribute(Qt::WA_TranslucentBackground);

    QWidget *container = new QWidget(notifWidget);
    container->setObjectName("notifContainer");

    QVBoxLayout *mainLayout = new QVBoxLayout(notifWidget);
    mainLayout->addWidget(container);
    mainLayout->setContentsMargins(10,10,10,10);

    // --- Header ---
    QHBoxLayout *header = new QHBoxLayout();

    QLabel *iconLabel = new QLabel(icon);
    iconLabel->setStyleSheet(QString("font-size: 22px; color: %1;").arg(color.name()));

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet(QString("font-weight: bold; font-size: 14px; color: %1;").arg(color.name()));

    QPushButton *closeButton = new QPushButton("✕");
    closeButton->setFixedSize(20,20);
    closeButton->setStyleSheet("border: none; background: transparent; font-size: 14px;");

    header->addWidget(iconLabel);
    header->addWidget(titleLabel, 1);
    header->addWidget(closeButton);

    // --- Message ---
    QLabel *messageLabel = new QLabel(message);
    messageLabel->setWordWrap(true);

    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->addLayout(header);
    containerLayout->addWidget(messageLabel);
    containerLayout->setContentsMargins(15,15,15,15);

    // --- Style ---
    container->setStyleSheet(QString(
                                 "QWidget#notifContainer {"
                                 " background: white;"
                                 " border-left: 4px solid %1;"
                                 " border-radius: 8px;"
                                 " }"
                                 ).arg(color.name()));

    notifWidget->setFixedWidth(330);

    notifWidget->adjustSize();


    // ✔ Position DANS la fenêtre (pas écran)
    QRect area = this->rect();

    int x = area.width() - notifWidget->width() - 20;
    int endY   = area.height() - notifWidget->height() - 20;
    int startY = area.height() + notifWidget->height();

    notifWidget->move(x, startY);
    notifWidget->show();

    // --- Animation slide ---
    QPropertyAnimation *slide = new QPropertyAnimation(notifWidget, "pos");
    slide->setDuration(500);
    slide->setStartValue(QPoint(x, startY));
    slide->setEndValue(QPoint(x, endY));
    slide->setEasingCurve(QEasingCurve::OutCubic);
    slide->start();

    // --- Animation fade ---
    QPropertyAnimation *fade = new QPropertyAnimation(notifWidget, "windowOpacity");
    fade->setDuration(500);
    fade->setStartValue(0);
    fade->setEndValue(1);

    //--- Timer autoclose ---
    QTimer *timer = new QTimer(notifWidget);
    timer->setSingleShot(true);

    if (duration > 0)
        timer->start(duration);

    connect(timer, &QTimer::timeout, [=]() {
        fade->setStartValue(1.0);
        fade->setEndValue(0.0);
        fade->start();

        connect(fade, &QPropertyAnimation::finished, [=]() {
            notifWidget->deleteLater();
        });
    });

    //--- Bouton fermer ---
    connect(closeButton, &QPushButton::clicked, [=]() {
        notifWidget->deleteLater();
    });
}



void SmartElectronic::chargerNotifications()
{
    notifications.clear();
    QSqlQuery q("SELECT ID_EQUIPEMENT, MARQUE_MODELE, DATE_LIMITE FROM EQUIPEMENT");

    QDate today = QDate::currentDate();
    int delay = 0; // pour espacer les notifications


    while (q.next()) {

        QVariant dateVar = q.value("DATE_LIMITE");
        QDate dateLimite = dateVar.toDate();


        if (!dateLimite.isValid())
            continue;

        int joursRestants = today.daysTo(dateLimite);

        // Alerte uniquement si 0..3 jours
        if (joursRestants < 0 || joursRestants > 3)
            continue;

        QString nom = q.value("MARQUE_MODELE").toString();
        QString id = q.value("ID_EQUIPEMENT").toString();
        QString uniqueKey = id + "_" + dateLimite.toString("yyyyMMdd");

        if (notificationsVues.contains(uniqueKey))
            continue;   // déjà vue → on ne l'affiche plus

        notificationsVues.insert(uniqueKey);


        QString titre, icon;
        QColor color;

        if (joursRestants == 0) {
            titre = "🚨 LIMITE ATTEINTE AUJOURD'HUI !";
            icon = "✖";
            color = QColor("#F44336"); // rouge
        }
        else if (joursRestants == 1) {
            titre = "⚠ LIMITE DEMAIN";
            icon = "⚠";
            color = QColor("#FF9800"); // orange
        }
        else if (joursRestants == 2) {
            titre = "⚠ Limite dans 2 jours";
            icon = "⚠";
            color = QColor("#FFC107"); // jaune
        }
        else { // 3 jours
            titre = "📅 Limite dans 3 jours";
            icon = "ℹ";
            color = QColor("#2196F3"); // bleu info
        }

        QString message = QString(
                              "Équipement : %1\n"
                              "ID : %2\n"
                              "Date limite : %3\n\n"
                              "Il reste %4 jour(s).")
                              .arg(nom)
                              .arg(id)
                              .arg(dateLimite.toString("dd/MM/yyyy"))
                              .arg(joursRestants);

        if (historiqueNotif)
            historiqueNotif->addItem(titre + "\n" + message + "\n----------------");

        QString msg = QString(
                          "Équipement : %1\n"
                          "ID : %2\n"
                          "Date limite : %3\n\n"
                          "Il reste %4 jour(s).")
                          .arg(nom)
                          .arg(id)
                          .arg(dateLimite.toString("dd/MM/yyyy"))
                          .arg(joursRestants);

        if (joursRestants >= 0 && joursRestants <= 3) {
            notifications.append(msg);
        }

        afficherNotifications();


        // Espacer les notifications pour éviter le chevauchement
        QTimer::singleShot(delay, this, [=]() {
            showSimpleNotification(titre,message,icon,color,6500);
        });

        delay += 600; // attendre 0.6s avant la prochaine notification
    }
}

void SmartElectronic::updateBadge()
{
    QListWidget *list = panneauNotif->findChild<QListWidget*>("listNotif");

    int n = list->count();

    if (n == 0) {
        ui->lbl_badge->setVisible(false);
        return;
    }

    ui->lbl_badge->setText(QString::number(n));
    ui->lbl_badge->setVisible(true);
}
void SmartElectronic::ajouterNotification(const QString &txt)
{
    QListWidget *list = panneauNotif->findChild<QListWidget*>("listNotif");
    list->addItem(txt);

    updateBadge();
}

void SmartElectronic::afficherNotifications()
{
    // ui->listNotifications est un QListWidget supposé existant dans l'UI
    ui->widget_notifications->clear();

    if (notifications.isEmpty()) {
        ui->lbl_badge->hide();
        return;
    }

    // remplir la QListWidget
    for (const QString &n : notifications) {
        ui->widget_notifications->addItem(n);
    }

    // mettre à jour badge (visible)
    ui->lbl_badge->setText(QString::number(notifications.size()));
    ui->lbl_badge->show();
}

void SmartElectronic::on_btn_notif_clicked()
{
    bool visible = ui->widget_notifications->isVisible();
    ui->widget_notifications->setVisible(!visible);
    if (!visible) {
        ui->lbl_badge->hide();
    }
}

void SmartElectronic::on_btnClient_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->GestionClient);
}

void SmartElectronic::on_btnEquipement_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->PageEquipement);
}


//gestion client
bool SmartElectronic::verifTelephone(QString* msg) const
{
    QString tel = ui->lineEdit_tel->text().trimmed();
    if (tel.isEmpty()) { if (msg) *msg = "Téléphone obligatoire."; return false; }
    bool ok = false; tel.toLongLong(&ok);
    if (!ok) { if (msg) *msg = "Téléphone doit être numérique (colonne NUMBER)."; return false; }
    return true;
}

void SmartElectronic::remplirClientTable()
{
    QSqlQueryModel *model = Client::afficher();   // suppose retourner un QSqlQueryModel*
    if (!model) return;

    const int rows = model->rowCount();
    const int cols = model->columnCount();

    ui->ClientTableWidget->clear();
    ui->ClientTableWidget->setRowCount(rows);
    ui->ClientTableWidget->setColumnCount(cols);

    // En-têtes
    QStringList headers;
    for (int c = 0; c < cols; ++c)
        headers << model->headerData(c, Qt::Horizontal).toString();
    ui->ClientTableWidget->setHorizontalHeaderLabels(headers);

    // Données
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            ui->ClientTableWidget->setItem(
                r, c, new QTableWidgetItem(model->data(model->index(r, c)).toString()));

    delete model; // libère le modèle récupéré
}

void SmartElectronic::on_pushButton_1_clicked()   // AJOUT
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
        remplirClientTable();   // pas de clear (selon ta demande)
    } else {
        QMessageBox::critical(this, "Erreur", "Ajout non effectué.");
    }
}

void SmartElectronic::on_pushButton_modifier_clicked()   // MODIFIER
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
        remplirClientTable();
    } else {
        QMessageBox::critical(this, "Modifier", "Mise à jour non effectuée.");
    }
}

void SmartElectronic::on_pushButton_supprimer_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    if (id <= 0) {
        QMessageBox::warning(this, "Supprimer", "ID_CLIENT invalide.");
        return;
    }

    if (Client::supprimer(id)) {
        QMessageBox::information(this, "Supprimer", "Suppression effectuée.");
        remplirClientTable();
        // Clear uniquement à la suppression (comme demandé)
        ui->lineEdit_id->clear();
        ui->lineEdit_nom->clear();
        ui->lineEdit_prenom->clear();
        ui->lineEdit_tel->clear();
        ui->lineEdit_email->clear();
        ui->ClientTableWidget->clearSelection();
    } else {
        QMessageBox::critical(this, "Supprimer", "Suppression non effectuée.");
    }
}

// =========================
// Helpers / Validations
// =========================

QString SmartElectronic::normalizePhone(const QString& raw)
{
    QString s = raw.trimmed();
    QString out; out.reserve(s.size());
    for (QChar ch : s) {
        if (ch.isDigit() || ch == '+') out.append(ch);
    }
    return out;
}

// Tunisie : +216XXXXXXXX ou 8 chiffres
bool SmartElectronic::verifTelephoneTN(QString* msg) const
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

bool SmartElectronic::verifEmail(QString* msg) const
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
void SmartElectronic::on_pushButton_2_clicked()
{
    // Si le champ est déjà vide → on recharge juste la table
    if (ui->lineEdit->text().trimmed().isEmpty()) {
        remplirClientTable();
        return;
    }

    // Sinon on efface le texte : ça déclenchera on_lineEdit_textChanged("")
    ui->lineEdit->clear();   // <- déclenche on_lineEdit_textChanged
}

void SmartElectronic::on_lineEdit_textChanged(const QString &text)
{
    QString searchText = text.trimmed();

    if (searchText.isEmpty()) {
        remplirClientTable();
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

    ui->ClientTableWidget->setRowCount(model->rowCount());
    ui->ClientTableWidget->setColumnCount(model->columnCount());

    // en-têtes
    for (int col = 0; col < model->columnCount(); ++col) {
        ui->ClientTableWidget->setHorizontalHeaderItem(
            col,
            new QTableWidgetItem(model->headerData(col, Qt::Horizontal).toString())
            );
    }

    // données
    for (int row = 0; row < model->rowCount(); ++row)
        for (int col = 0; col < model->columnCount(); ++col)
            ui->ClientTableWidget->setItem(
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




void SmartElectronic::on_pushButton_pdf_clicked()
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





void SmartElectronic::on_pushButton_stat_clicked()
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
void SmartElectronic::on_pushButton_trier_clicked()
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
    ui->ClientTableWidget->setRowCount(model->rowCount());
    ui->ClientTableWidget->setColumnCount(model->columnCount());

    for (int col = 0; col < model->columnCount(); col++) {
        ui->ClientTableWidget->setHorizontalHeaderItem(
            col,
            new QTableWidgetItem(model->headerData(col, Qt::Horizontal).toString())
            );
    }

    for (int row = 0; row < model->rowCount(); row++)
        for (int col = 0; col < model->columnCount(); col++)
            ui->ClientTableWidget->setItem(
                row, col,
                new QTableWidgetItem(model->data(model->index(row, col)).toString())
                );

    delete model;
}

void SmartElectronic::on_pushButton_qr_clicked()
{
    qrcodechai dialog(this);                 // Créer le dialog QR
    dialog.setWindowTitle("QR Code Client"); // Titre de la fenêtre
    dialog.exec();                           // Affichage modal
}
void SmartElectronic::on_pushButton_speech_clicked()
{
    if (!speech) {
        QMessageBox::warning(this, "Speech", "Le moteur de synthèse vocale n'est pas initialisé.");
        return;
    }

    int row = ui->ClientTableWidget->currentRow();
    if (row < 0) {
        speech->say("Veuillez sélectionner un client dans la liste.");
        return;
    }

    QString id        = ui->ClientTableWidget->item(row, 0) ? ui->ClientTableWidget->item(row, 0)->text() : "";
    QString nom       = ui->ClientTableWidget->item(row, 1) ? ui->ClientTableWidget->item(row, 1)->text() : "";
    QString prenom    = ui->ClientTableWidget->item(row, 2) ? ui->ClientTableWidget->item(row, 2)->text() : "";
    QString telephone = ui->ClientTableWidget->item(row, 3) ? ui->ClientTableWidget->item(row, 3)->text() : "";
    QString email     = ui->ClientTableWidget->item(row, 4) ? ui->ClientTableWidget->item(row, 4)->text() : "";

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

