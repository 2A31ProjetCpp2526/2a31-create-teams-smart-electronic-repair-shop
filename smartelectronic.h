#ifndef SmartElectronic_H
#define SmartElectronic_H

#include "equipement.h"
#include <QMainWindow>
#include <QTimer>
#include <QSet>
#include <QListWidget>
#include <QMenu>
#include <QAction>
#include <QMenu>
#include <QAction>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGraphicsScene>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextToSpeech>
#include <QVoice>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class SmartElectronic; }
QT_END_NAMESPACE

class  SmartElectronic : public QMainWindow
{
    Q_OBJECT
public:
    explicit  SmartElectronic(QWidget *parent = nullptr);
    ~SmartElectronic();

private slots:
    //equipement
    void on_btnClient_clicked();
    void on_btnEquipement_clicked();
    void on_btn_ajouter_clicked();// Ajouter
    void on_btn_modifier_clicked();// Modifier
    void on_btn_supprimer_clicked();  // Supprimer
    void on_EquipementTableWidget_cellClicked(int row, int column);
    void on_btn_pdf_clicked();
    void on_btn_recherche_clicked();
    void on_btn_tri_clicked();
    void afficherStatEtatPie();
    void on_btn_image_clicked();
    void chargerNotifications();
    void showSimpleNotification(const QString &title,
                         const QString &message,
                         const QString &icon,
                         QColor color,
                              int duration);
   void updateBadge();
   void ajouterNotification(const QString &txt);
   void afficherNotifications();
   void on_btn_notif_clicked();

   //client
   void on_pushButton_1_clicked();         // Ajouter
   void on_pushButton_modifier_clicked();  // Modifier
   void on_pushButton_supprimer_clicked(); // Supprimer
   void on_pushButton_2_clicked();
   void on_pushButton_pdf_clicked();
   void on_pushButton_stat_clicked();
   void on_pushButton_trier_clicked();
   void on_pushButton_qr_clicked();
   void on_pushButton_speech_clicked();   // 🔊 AJOUT ICI
   void on_lineEdit_textChanged(const QString &text);

private:
    //equipement
    void remplirEquipementTable();

    QTimer *timerNotif;
    QSet<QString> notificationsVues;
    QListWidget *historiqueNotif;
    QWidget *panneauNotif = nullptr;
    bool notifPanelVisible = false;

    // Liste des notifications
    QStringList notifications;
    bool notificationShown = false;

    //client
    void remplirClientTable();

    // Validations
    bool verifTelephone(QString* msg=nullptr) const;
    static QString normalizePhone(const QString& raw);
    bool verifTelephoneTN(QString* msg=nullptr) const;
    bool verifEmail(QString* msg=nullptr) const;


    Ui::SmartElectronic *ui;
    Equipement Etmp;
    QTextToSpeech *speech;
    QComboBox *voiceCombo;
};
#endif
