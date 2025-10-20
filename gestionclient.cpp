#include "gestionclient.h"
#include "ui_gestionclient.h"
#include "client.h"
#include <QMessageBox>
#include <QTableWidgetItem>

gestionclient::gestionclient(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::GestionClient)
{
    ui->setupUi(this);
    remplirTable();   // affiche au démarrage
}

gestionclient::~gestionclient()
{
    delete ui;
}

// ---- Vérif téléphone (colonne NUMBER NOT NULL en base)
bool gestionclient::verifTelephone(QString* msg) const
{
    QString tel = ui->lineEdit_tel->text().trimmed();
    if (tel.isEmpty()) { if (msg) *msg = "Téléphone obligatoire."; return false; }
    bool ok=false; tel.toLongLong(&ok);
    if (!ok) { if (msg) *msg = "Téléphone doit être numérique (colonne NUMBER)."; return false; }
    return true;
}

// ---- Remplir le QTableWidget depuis Client::afficher()
void gestionclient::remplirTable()
{
    auto *model = Client::afficher();   // QSqlQueryModel*
    const int rows = model->rowCount();
    const int cols = model->columnCount();

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(rows);
    ui->tableWidget->setColumnCount(cols);

    QStringList headers;
    for (int c = 0; c < cols; ++c)
        headers << model->headerData(c, Qt::Horizontal).toString();
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            ui->tableWidget->setItem(
                r, c, new QTableWidgetItem(model->data(model->index(r, c)).toString()));
}

// ================== AJOUTER ==================
void gestionclient::on_pushButton_1_clicked()
{
    QString msg;
    if (!verifTelephone(&msg)) { QMessageBox::warning(this, "Saisie", msg); return; }

    Client c;
    c.id_client = ui->lineEdit_id->text().toInt();
    c.nom       = ui->lineEdit_nom->text();
    c.prenom    = ui->lineEdit_prenom->text();
    c.telephone = ui->lineEdit_tel->text();
    c.email     = ui->lineEdit_email->text();

    if (c.ajouter()) {
        QMessageBox::information(this, "Succès", "Ajout effectué.");
        remplirTable();
    } else {
        QMessageBox::critical(this, "Erreur", "Ajout non effectué.");
    }
}   // <--- FIN de on_pushButton_1_clicked()

// ================== MODIFIER ==================
void gestionclient::on_pushButton_modifier_clicked()
{
    QString msg;
    if (!verifTelephone(&msg)) { QMessageBox::warning(this, "Saisie", msg); return; }

    int id = ui->lineEdit_id->text().toInt();
    if (id <= 0) { QMessageBox::warning(this, "Modifier", "ID_CLIENT invalide."); return; }

    Client c;
    c.id_client = id;
    c.nom       = ui->lineEdit_nom->text();
    c.prenom    = ui->lineEdit_prenom->text();
    c.telephone = ui->lineEdit_tel->text();
    c.email     = ui->lineEdit_email->text();

    if (c.modifier()) {
        QMessageBox::information(this, "Modifier", "Mise à jour effectuée.");
        remplirTable();
    } else {
        QMessageBox::critical(this, "Modifier", "Mise à jour non effectuée.");
    }
}   // <--- FIN de on_pushButton_modifier_clicked()

// ================== SUPPRIMER ==================
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
    } else {
        QMessageBox::critical(this, "Supprimer", "Suppression non effectuée.");
    }
}   // <--- FIN de on_pushButton_supprimer_clicked()
