#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "equipement.h"
#include <QMainWindow>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class  MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit  MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_ajouter_clicked();// Ajouter
    void on_btn_modifier_clicked();// Modifier
    void on_btn_supprimer_clicked();  // Supprimer
    void on_tableWidget_cellClicked(int row, int column);
    void on_btn_pdf_clicked();
  void on_btn_recherche_clicked();
    void on_btn_tri_clicked();
  void afficherStatEtatPie();
  void on_btn_image_clicked();
  void chargerNotifications();
  void afficherNotifications();
  void on_btn_notif_clicked();



    // Aller à MainWindow

private:
    void remplirTable();

    QTimer *timerNotif;

    // Liste des notifications
    QStringList notifications;




    Ui::MainWindow *ui;
    Equipement Etmp;
};
#endif
