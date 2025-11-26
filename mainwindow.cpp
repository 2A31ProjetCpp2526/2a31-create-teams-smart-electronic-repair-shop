#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>



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
