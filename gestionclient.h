#ifndef GESTIONCLIENT_H
#define GESTIONCLIENT_H
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGraphicsScene>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextToSpeech>
#include <QVoice>
#include <QMainWindow>
#include <QComboBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "equipement.h"

//
// ==== Classe gestionclient ====
//
QT_BEGIN_NAMESPACE
namespace Ui { class GestionClient; }
QT_END_NAMESPACE

class gestionclient : public QMainWindow
{
    Q_OBJECT
public:
    explicit gestionclient(QWidget *parent = nullptr);
    ~gestionclient();

private slots:
    void on_pushButton_1_clicked();         // Ajouter
    void on_pushButton_modifier_clicked();  // Modifier
    void on_pushButton_supprimer_clicked(); // Supprimer
    void on_tableWidget_cellClicked(int row, int column);
    void goTomainwindow();
    void on_pushButton_2_clicked();
    void on_pushButton_pdf_clicked();
    void on_pushButton_stat_clicked();
    void on_pushButton_trier_clicked();
    void on_pushButton_qr_clicked();
     void on_pushButton_speech_clicked();   // 🔊 AJOUT ICI
     void on_lineEdit_textChanged(const QString &text);

   // Aller à MainWindow

private:
    void remplirTable();

    // Validations
    bool verifTelephone(QString* msg=nullptr) const;
    static QString normalizePhone(const QString& raw);
    bool verifTelephoneTN(QString* msg=nullptr) const;
    bool verifEmail(QString* msg=nullptr) const;

    Ui::GestionClient *ui;
    QTextToSpeech *speech;
    QComboBox *voiceCombo;
    QSerialPort *arduino;
    QString arduinoPortName = "";
};


//
// ==== Classe MainWindow ====
//
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

#endif // GESTIONCLIENT_H
