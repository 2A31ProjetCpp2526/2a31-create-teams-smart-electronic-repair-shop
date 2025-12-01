#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "equipement.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_ajouter_clicked();
    void on_btn_modifier_clicked();
    void on_btn_supprimer_clicked();
    void on_btn_actualiser_clicked();
    //void on_tableWidget_cellChanged(int row, int column);


private:
    Ui::MainWindow *ui;
    Equipement eqTmp;

    void refreshTable();
    void clearForm();
};

#endif // MAINWINDOW_H
