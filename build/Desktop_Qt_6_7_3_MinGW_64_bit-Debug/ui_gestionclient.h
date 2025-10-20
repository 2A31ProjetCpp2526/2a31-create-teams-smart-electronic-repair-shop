/********************************************************************************
** Form generated from reading UI file 'gestionclient.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GESTIONCLIENT_H
#define UI_GESTIONCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GestionClient
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QGroupBox *groupBox_4;
    QPushButton *pushButton_9;
    QGroupBox *groupBox_5;
    QPushButton *pushButton_10;
    QPushButton *pushButton_4;
    QGroupBox *groupBox_2;
    QLabel *label_2;
    QLineEdit *lineEdit_id;
    QLabel *label_3;
    QLineEdit *lineEdit_nom;
    QLabel *label_4;
    QLineEdit *lineEdit_prenom;
    QLabel *label_5;
    QLineEdit *lineEdit_tel;
    QLabel *label_6;
    QLineEdit *lineEdit_email;
    QPushButton *pushButton_1;
    QTableWidget *tableWidget;
    QWidget *widget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLabel *label_8;
    QPushButton *pushButton_3;
    QLabel *label_7;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *pushButton_5;
    QPushButton *pushButton_modifier;
    QPushButton *pushButton_supprimer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GestionClient)
    {
        if (GestionClient->objectName().isEmpty())
            GestionClient->setObjectName("GestionClient");
        GestionClient->resize(1194, 643);
        centralwidget = new QWidget(GestionClient);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 1191, 601));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(370, 30, 201, 121));
        groupBox_4->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 2px solid #8A2BE2;\n"
"    border-radius: 15px;\n"
"    padding: 10px;\n"
"    background-color: #F3E8FD;\n"
"    margin-top: 10px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    color: #8A2BE2;\n"
"    font-weight: bold;\n"
"}"));
        pushButton_9 = new QPushButton(groupBox_4);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(30, 40, 131, 51));
        pushButton_9->setStyleSheet(QString::fromUtf8("background-color: #9370DB;  /* Violet plus clair */\n"
"    color: white;\n"
"    border-radius: 15px;\n"
"    padding: 8px;\n"
"    border: 2px solid #9370DB;"));
        groupBox_5 = new QGroupBox(groupBox);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(650, 30, 201, 121));
        groupBox_5->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 2px solid #8A2BE2;\n"
"    border-radius: 15px;\n"
"    padding: 10px;\n"
"    background-color: #F3E8FD;\n"
"    margin-top: 10px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    color: #8A2BE2;\n"
"    font-weight: bold;\n"
"}"));
        pushButton_10 = new QPushButton(groupBox_5);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(30, 40, 141, 51));
        pushButton_10->setStyleSheet(QString::fromUtf8("background-color: #9370DB;  /* Violet plus clair */\n"
"    color: white;\n"
"    border-radius: 15px;\n"
"    padding: 8px;\n"
"    border: 2px solid #9370DB;"));
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(370, 510, 151, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #9305F2;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 6px 12px;\n"
"    font-size: 18px;\n"
"}"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(20, 40, 241, 491));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        groupBox_2->setFont(font);
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: #FFFFFF;\n"
"    border: 10px solid #9305F2;   /* Violet clair */\n"
"    border-radius: 15px;         /* Coins arrondis */\n"
"    margin-top: 30px;            /* D\303\251calage du titre */\n"
"    padding: 12px;\n"
"    color: #48038C;              /* Couleur du texte interne */\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"/* Titre du QGroupBox */\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;   /* Centr\303\251 en haut */\n"
"    padding: 15px 35px;\n"
"    background-color: white;\n"
"    color: #48038C;\n"
"    border-radius: 10px;\n"
"    font-weight: bold;\n"
"}"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 80, 91, 31));
        label_2->setStyleSheet(QString::fromUtf8("QLabel {background-color: transparent; color: #260259; /* Texte sombre lisible */ font-size: 18px; font-weight: bold; }"));
        lineEdit_id = new QLineEdit(groupBox_2);
        lineEdit_id->setObjectName("lineEdit_id");
        lineEdit_id->setGeometry(QRect(40, 110, 161, 26));
        lineEdit_id->setStyleSheet(QString::fromUtf8("QLineEdit { background: #FFFFFF; border: 2px solid #6BA5F2; border-radius: 10px; padding: 6px 10px; color: #260259; } QLineEdit:focus  { border: 2px solid #9305F2; background: #F3E9FF; }"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(50, 140, 81, 31));
        label_3->setStyleSheet(QString::fromUtf8("QLabel {background-color: transparent; color: #260259; /* Texte sombre lisible */ font-size: 18px; font-weight: bold; }"));
        lineEdit_nom = new QLineEdit(groupBox_2);
        lineEdit_nom->setObjectName("lineEdit_nom");
        lineEdit_nom->setGeometry(QRect(40, 170, 161, 26));
        lineEdit_nom->setStyleSheet(QString::fromUtf8("QLineEdit { background: #FFFFFF; border: 2px solid #6BA5F2; border-radius: 10px; padding: 6px 10px; color: #260259; } QLineEdit:focus  { border: 2px solid #9305F2; background: #F3E9FF; }"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 210, 91, 31));
        label_4->setStyleSheet(QString::fromUtf8("QLabel {background-color: transparent; color: #260259; /* Texte sombre lisible */ font-size: 18px; font-weight: bold; }"));
        lineEdit_prenom = new QLineEdit(groupBox_2);
        lineEdit_prenom->setObjectName("lineEdit_prenom");
        lineEdit_prenom->setGeometry(QRect(40, 240, 161, 26));
        lineEdit_prenom->setStyleSheet(QString::fromUtf8("QLineEdit { background: #FFFFFF; border: 2px solid #6BA5F2; border-radius: 10px; padding: 6px 10px; color: #260259; } QLineEdit:focus  { border: 2px solid #9305F2; background: #F3E9FF; }"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(50, 270, 111, 31));
        label_5->setStyleSheet(QString::fromUtf8("QLabel {background-color: transparent; color: #260259; /* Texte sombre lisible */ font-size: 18px; font-weight: bold; }"));
        lineEdit_tel = new QLineEdit(groupBox_2);
        lineEdit_tel->setObjectName("lineEdit_tel");
        lineEdit_tel->setGeometry(QRect(40, 310, 161, 26));
        lineEdit_tel->setStyleSheet(QString::fromUtf8("QLineEdit { background: #FFFFFF; border: 2px solid #6BA5F2; border-radius: 10px; padding: 6px 10px; color: #260259; } QLineEdit:focus  { border: 2px solid #9305F2; background: #F3E9FF; }"));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(50, 350, 71, 21));
        label_6->setStyleSheet(QString::fromUtf8("QLabel {background-color: transparent; color: #260259; /* Texte sombre lisible */ font-size: 18px; font-weight: bold; }"));
        lineEdit_email = new QLineEdit(groupBox_2);
        lineEdit_email->setObjectName("lineEdit_email");
        lineEdit_email->setGeometry(QRect(42, 380, 161, 26));
        lineEdit_email->setStyleSheet(QString::fromUtf8("QLineEdit { background: #FFFFFF; border: 2px solid #6BA5F2; border-radius: 10px; padding: 6px 10px; color: #260259; } QLineEdit:focus  { border: 2px solid #9305F2; background: #F3E9FF; }"));
        pushButton_1 = new QPushButton(groupBox_2);
        pushButton_1->setObjectName("pushButton_1");
        pushButton_1->setGeometry(QRect(50, 420, 141, 41));
        QFont font1;
        pushButton_1->setFont(font1);
        pushButton_1->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background-color: #9305F2;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 6px 12px;\n"
"    font-size: 18px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #7a04c2; /* un peu plus sombre au survol */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #5c0391; /* encore plus sombre quand press\303\251 */\n"
"}"));
        tableWidget = new QTableWidget(groupBox);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget->rowCount() < 5)
            tableWidget->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setItem(0, 5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setItem(1, 5, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(2, 5, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(3, 5, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(4, 5, __qtablewidgetitem10);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(270, 250, 791, 241));
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: #F5F0FF;   /* Violet tr\303\250s tr\303\250s clair */\n"
"    border: 2px solid #1034A6;\n"
"    border-radius: 12px;\n"
"    gridline-color: white;       /* Lignes blanches */\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #1034A6;   /* Bleu fonc\303\251 */\n"
"    color: white;                /* Texte blanc */\n"
"    border: none;\n"
"    padding: 6px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QHeaderView::section:first {\n"
"    border-top-left-radius: 8px;\n"
"}\n"
"\n"
"QHeaderView::section:last {\n"
"    border-top-right-radius: 8px;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    border: 1px solid white;     /* Bordures blanches entre cellules */\n"
"}"));
        widget = new QWidget(groupBox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(650, 180, 401, 51));
        widget->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color:#9305F2;   /* fond violet */\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    background-color: white;     /* champ blanc */\n"
"    color: #333;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding-left: 25px;          /* espace pour l\342\200\231ic\303\264ne de recherche */\n"
"    padding-right: 25px;         /* espace pour l\342\200\231ic\303\264ne d\342\200\231action */\n"
"    height: 28px;\n"
"    font-size: 15px;\n"
"}"));
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(30, 10, 361, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setStyleSheet(QString::fromUtf8("font-size: 16px"));

        horizontalLayout->addWidget(pushButton_2);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setStyleSheet(QString::fromUtf8("\n"
"button->setStyleSheet(\n"
"    \"QPushButton {\"\n"
"    \"  color: #6BA5F2;\"       // couleur du texte\n"
"    \"  background-color: white;\"\n"
"    \"  border: 1px solid #6BA5F2;\"\n"
"    \"}\"\n"
");\n"
""));

        horizontalLayout->addWidget(lineEdit);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(280, 180, 351, 51));
        label_8->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: transparent;\n"
"    color: #48038C;\n"
"    font-size: 30px;   /* plus grand pour un titre */\n"
"    font-weight: bold; /* en gras */\n"
"}"));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(530, 180, 101, 51));
        pushButton_3->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background-color: #9305F2;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 6px 12px;\n"
"    font-size: 18px;\n"
"}"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(1000, 30, 161, 121));
        label_7->setPixmap(QPixmap(QString::fromUtf8("../../OneDrive/Documents/logo qt.jpg")));
        label_7->setScaledContents(true);
        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(590, 510, 281, 40));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: transparent;\n"
"    color: #48038C;\n"
"    font-size: 18px;   /* plus grand pour un titre */\n"
"    font-weight: bold; /* en gras */\n"
"}"));

        horizontalLayout_2->addWidget(label);

        comboBox = new QComboBox(layoutWidget1);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox { background: #FFFFFF; border: 2px solid #6BA5F2; border-radius: 10px; padding: 6px 10px; color: #260259; } QComboBox:focus { border: 2px solid #9305F2; background: #F3E9FF; }"));

        horizontalLayout_2->addWidget(comboBox);

        pushButton_5 = new QPushButton(layoutWidget1);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background-color: #9305F2;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 6px 12px;\n"
"    font-size: 18px;\n"
"}"));

        horizontalLayout_2->addWidget(pushButton_5);

        pushButton_modifier = new QPushButton(groupBox);
        pushButton_modifier->setObjectName("pushButton_modifier");
        pushButton_modifier->setGeometry(QRect(1090, 390, 71, 71));
        pushButton_supprimer = new QPushButton(groupBox);
        pushButton_supprimer->setObjectName("pushButton_supprimer");
        pushButton_supprimer->setGeometry(QRect(1090, 310, 71, 71));
        GestionClient->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GestionClient);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1194, 26));
        GestionClient->setMenuBar(menubar);
        statusbar = new QStatusBar(GestionClient);
        statusbar->setObjectName("statusbar");
        GestionClient->setStatusBar(statusbar);

        retranslateUi(GestionClient);

        QMetaObject::connectSlotsByName(GestionClient);
    } // setupUi

    void retranslateUi(QMainWindow *GestionClient)
    {
        GestionClient->setWindowTitle(QCoreApplication::translate("GestionClient", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GestionClient", "GroupBox", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("GestionClient", "Historique", nullptr));
        pushButton_9->setText(QCoreApplication::translate("GestionClient", "Historique \360\237\223\205", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("GestionClient", "QR code", nullptr));
        pushButton_10->setText(QCoreApplication::translate("GestionClient", "QR code \360\237\226\274\357\270\217", nullptr));
        pushButton_4->setText(QCoreApplication::translate("GestionClient", "Statistique\360\237\223\212", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("GestionClient", "Ajouter", nullptr));
        label_2->setText(QCoreApplication::translate("GestionClient", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:700;\">ID</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("GestionClient", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">Nom</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("GestionClient", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">Prenom</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("GestionClient", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">T\303\251l\303\251phone</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("GestionClient", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">Email</span></p></body></html>", nullptr));
        pushButton_1->setText(QCoreApplication::translate("GestionClient", "Valider\342\230\221\357\270\217 ", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("GestionClient", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("GestionClient", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("GestionClient", "Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("GestionClient", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("GestionClient", "Email", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        pushButton_2->setText(QCoreApplication::translate("GestionClient", "\360\237\224\215", nullptr));
        lineEdit->setText(QCoreApplication::translate("GestionClient", "Rechercher", nullptr));
        label_8->setText(QCoreApplication::translate("GestionClient", "<html><head/><body><p>Liste des Clients:</p></body></html>", nullptr));
        pushButton_3->setText(QCoreApplication::translate("GestionClient", "\360\237\223\221PDF", nullptr));
        label_7->setText(QString());
        label->setText(QCoreApplication::translate("GestionClient", "Trier par ", nullptr));
        comboBox->setItemText(0, QString());
        comboBox->setItemText(1, QCoreApplication::translate("GestionClient", "Nom", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("GestionClient", "Prenom", nullptr));

        pushButton_5->setText(QCoreApplication::translate("GestionClient", "Trier", nullptr));
        pushButton_modifier->setText(QCoreApplication::translate("GestionClient", "\342\234\217\357\270\217", nullptr));
        pushButton_supprimer->setText(QCoreApplication::translate("GestionClient", "\360\237\227\221\357\270\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GestionClient: public Ui_GestionClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GESTIONCLIENT_H
