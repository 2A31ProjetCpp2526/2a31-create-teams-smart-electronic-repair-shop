#ifndef GESTIONCLIENT_H
#define GESTIONCLIENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GestionClient; }   // Class name du .ui
QT_END_NAMESPACE

class gestionclient : public QMainWindow
{
    Q_OBJECT
public:
    explicit gestionclient(QWidget *parent = nullptr);
    ~gestionclient();

private slots:
    void on_pushButton_1_clicked();         // Ajouter (objectName = pushButton_1)
    void on_pushButton_modifier_clicked();  // Modifier (objectName = pushButton_modifier)
    void on_pushButton_supprimer_clicked(); // Supprimer (objectName = pushButton_supprimer)

private:
    void remplirTable();
    bool verifTelephone(QString* msg=nullptr) const;

    Ui::GestionClient *ui;
};

#endif // GESTIONCLIENT_H
