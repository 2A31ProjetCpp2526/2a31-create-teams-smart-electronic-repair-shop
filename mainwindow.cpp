#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipement.h"


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

MainWindow:: MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    afficherStatEtatPie();
    chargerNotifications();



    // Définir le nombre de colonnes
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setIconSize(QSize(80, 80));
    ui->widget_notifications->setVisible(false);


    timerNotif = new QTimer(this);
    connect(timerNotif, &QTimer::timeout, this, &MainWindow::chargerNotifications);
    timerNotif->start(30000);  // toutes les 30 secondes


    // Donner un nom aux colonnes
    ui->tableWidget->setHorizontalHeaderLabels(
        QStringList() << "ID" << "Type" << "Marque/Modèle"
                      << "Date Dépôt" << "État" << "Description panne"<<"image"
        );

    remplirTable();
    connect(ui->tableWidget, &QTableWidget::cellClicked,
            this, &MainWindow::on_tableWidget_cellClicked);


}
MainWindow:: ~MainWindow()
{
    delete ui;
}



void MainWindow::remplirTable()
{
    QSqlQuery query = Etmp.afficher();

    // Effacer les anciennes lignes
    ui->tableWidget->setRowCount(0);

    int row = 0;
    while (query.next()) {

        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("ID_EQUIPEMENT").toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("TYPE").toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("MARQUE_MODELE").toString()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("DATE_DEPOT").toString()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("ETAT").toString()));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("DESCRIPTION_PANNE").toString()));
        QString imgPath = query.value("IMAGE_PATH").toString();

        QTableWidgetItem *imgItem = new QTableWidgetItem();

        // Vérifier si l’image existe
        if (QFile::exists(imgPath))
        {
            QPixmap pix(imgPath);
            imgItem->setIcon(QIcon(pix.scaled(100, 100, Qt::KeepAspectRatio)));
            ui->tableWidget->setRowHeight(row, 80);
        }
        else
        {
            imgItem->setText("Aucune image");
        }

        ui->tableWidget->setItem(row, 6, imgItem);


        row++;
    }
}
void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    // Récupération des valeurs du tableau
    QString id = ui->tableWidget->item(row, 0)->text();
    QString type = ui->tableWidget->item(row, 1)->text();
    QString marque = ui->tableWidget->item(row, 2)->text();
    QString date = ui->tableWidget->item(row, 3)->text();
    QString etat = ui->tableWidget->item(row, 4)->text();
    QString description = ui->tableWidget->item(row, 5)->text();
    QString img = ui->tableWidget->item(row, 6)->text();
    // Affectation dans les champs du formulaire
    ui->le_id->setText(id);
    ui->cb_type->setCurrentText(type);
    ui->le_marque->setText(marque);
    ui->date_depot->setDate(QDate::fromString(date, "yyyy-MM-dd"));
    ui->cb_etat->setCurrentText(etat);
    ui->te_desc->setPlainText(description);
    ui->le_image->setText(img);

    if (!img.isEmpty())
        ui->label_image->setPixmap(QPixmap(img).scaled(180,180,Qt::KeepAspectRatio));
}

void MainWindow::on_btn_ajouter_clicked()
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
        remplirTable();
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



void MainWindow::on_btn_modifier_clicked()
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
        remplirTable();
        QMessageBox::information(this, "Succès", "Équipement modifié !");
        etat = etat.trimmed().toLower();
        etat[0] = etat[0].toUpper();
        chargerNotifications();


    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Modification échouée.");
    }
}

void MainWindow::on_btn_supprimer_clicked()
{
    int id = ui->le_id->text().toInt();

    if(Etmp.supprimer(id))
    {
        remplirTable();
        QMessageBox::information(this, "Succès", "Équipement supprimé !");
        afficherStatEtatPie();

    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Suppression échouée.");
    }
}
void MainWindow::on_btn_pdf_clicked()
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
void MainWindow::on_btn_recherche_clicked()
{
    QString cle = ui->le_recherche->text();


    if (cle.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez saisir un mot-clé !");
        remplirTable();
        return;
    }

    QSqlQuery query;

    query.prepare(
        "SELECT ID_EQUIPEMENT, TYPE, MARQUE_MODELE, DATE_DEPOT, ETAT, DESCRIPTION_PANNE "
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

    ui->tableWidget->setRowCount(0);

    int row = 0;

    while (query.next()) {
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));

        row++;
    }

    if (row == 0)
        QMessageBox::information(this, "Recherche", "Aucun équipement trouvé !");
}
void MainWindow::on_btn_tri_clicked()
{
    QString critere = ui->cb_tri->currentText();

    QString queryText;

    // 🟦 Tri par TYPE
    if (critere == "TYPE") {
        queryText =
            "SELECT ID_EQUIPEMENT, TYPE, MARQUE_MODELE, DATE_DEPOT, ETAT, DESCRIPTION_PANNE "
            "FROM EQUIPEMENT "
            "ORDER BY TYPE ASC";
    }

    // 🟨 Tri par ÉTAT
    else if (critere == "ETAT") {
        queryText =
            "SELECT ID_EQUIPEMENT, TYPE, MARQUE_MODELE, DATE_DEPOT, ETAT, DESCRIPTION_PANNE "
            "FROM EQUIPEMENT "
            "ORDER BY ETAT ASC";
    }

    QSqlQuery query;

    if (!query.exec(queryText)) {
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
        return;
    }

    // Nettoyer tableau
    ui->tableWidget->setRowCount(0);
    int row = 0;

    while (query.next()) {
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));

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

// Fonction principale pour afficher le graphique en secteurs par état
void MainWindow::afficherStatEtatPie()
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
}
void MainWindow::on_btn_image_clicked()
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
void MainWindow::chargerNotifications()
{
    notifications.clear();

    // Requête : récupérer ID, MARQUE_MODELE et DATE_LIMITE
    QSqlQuery q("SELECT ID_EQUIPEMENT, MARQUE_MODELE, DATE_LIMITE FROM EQUIPEMENT");

    while (q.next()) {
        // Récupérer la date de façon sûre
        QVariant dateVar = q.value("DATE_LIMITE");
        QDate dateLimite = dateVar.toDate();

        if (!dateLimite.isValid())
            continue; // ignorer les lignes sans date valide

        int joursRestants = QDate::currentDate().daysTo(dateLimite);

        // On alerte si date limite dans 0..3 jours (inclus)
        if (joursRestants >= 0 && joursRestants <= 3) {
            QString notif = QString("L'équipement \"%1\" (ID %2) atteint sa limite dans %3 jour(s).")
                                .arg(q.value("MARQUE_MODELE").toString())
                                .arg(q.value("ID_EQUIPEMENT").toString())
                                .arg(joursRestants);
            notifications.append(notif);
        }
    }

    // mettre à jour l'affichage UI
    afficherNotifications();
}

// -----------------------------------------------------------------
// Mettre à jour l'affichage (QListWidget + badge)
void MainWindow::afficherNotifications()
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

void MainWindow::on_btn_notif_clicked()
{
    bool visible = ui->widget_notifications->isVisible();
    ui->widget_notifications->setVisible(!visible);
    if (!visible) {
        ui->lbl_badge->hide();
    }
}






