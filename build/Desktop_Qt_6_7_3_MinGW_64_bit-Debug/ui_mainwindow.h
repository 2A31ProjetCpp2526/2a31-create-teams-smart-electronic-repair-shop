/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *le_marque;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_7;
    QTextEdit *te_desc;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *le_id;
    QPushButton *btnGenerer_;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QComboBox *cb_type;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QDateEdit *date_depot;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btn_ajouter;
    QPushButton *pushButton_3;
    QLabel *label_8;
    QTableWidget *tableWidget;
    QPushButton *pushButton_5;
    QLabel *label_10;
    QLabel *label_12;
    QWidget *widget_2;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_4;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QComboBox *comboBox_2;
    QPushButton *pushButton_6;
    QPushButton *btn_modifier;
    QPushButton *btn_supprimer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1199, 650);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("QWidget { background-color: #E6E6FA ;  }"));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 0, 341, 611));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8("\n"
"QGroupBox {\n"
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
"    padding: 10px 30px;\n"
"    background-color: white;\n"
"    color: #48038C;\n"
"    border-radius: 10px;\n"
"    font-weight: bold;\n"
"}\n"
"```\n"
"\n"
"```\n"
""));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 50, 161, 20));
        label->setStyleSheet(QString::fromUtf8("QLabel {background-color: transparent; color: #260259; /* Texte sombre lisible */ font-size: 18px; font-weight: bold; }"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 110, 161, 20));
        label_2->setStyleSheet(QString::fromUtf8("QLabel {background-color: transparent; color: #260259; /* Texte sombre lisible */ font-size: 18px; font-weight: bold; }"));
        le_marque = new QLineEdit(groupBox);
        le_marque->setObjectName("le_marque");
        le_marque->setGeometry(QRect(10, 140, 151, 21));
        le_marque->setStyleSheet(QString::fromUtf8("QLineEdit { background: #FFFFFF; border: 2px solid #6BA5F2; border-radius: 10px; padding: 6px 10px; color: #260259; } QLineEdit:focus { border: 2px solid #9305F2; background: #F3E9FF; }"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 170, 191, 20));
        label_3->setStyleSheet(QString::fromUtf8("QLabel {background-color: transparent; color: #260259; /* Texte sombre lisible */ font-size: 18px; font-weight: bold; }"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(12, 419, 171, 101));
        label_6->setStyleSheet(QString::fromUtf8("QLabel {background-color: transparent; color: #260259; /* Texte sombre lisible */ font-size: 18px; font-weight: bold; }"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(170, 450, 141, 31));
        label_7->setStyleSheet(QString::fromUtf8("QLabel {background-color: transparent; color: #260259; /* Texte sombre lisible */ font-size: 18px; font-weight: bold; }"));
        te_desc = new QTextEdit(groupBox);
        te_desc->setObjectName("te_desc");
        te_desc->setGeometry(QRect(20, 190, 301, 121));
        te_desc->setStyleSheet(QString::fromUtf8(" QTextEdit { background: #FFFFFF; border: 2px solid #6BA5F2; border-radius: 10px; padding: 6px 10px; color: #260259; } QTextEdit:focus { border: 2px solid #9305F2; background: #F3E9FF; }"));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 70, 241, 40));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        le_id = new QLineEdit(layoutWidget);
        le_id->setObjectName("le_id");
        le_id->setStyleSheet(QString::fromUtf8("QLineEdit { background: #FFFFFF; border: 2px solid #6BA5F2; border-radius: 10px; padding: 6px 10px; color: #260259; } QLineEdit:focus  { border: 2px solid #9305F2; background: #F3E9FF; }"));

        horizontalLayout_2->addWidget(le_id);

        btnGenerer_ = new QPushButton(layoutWidget);
        btnGenerer_->setObjectName("btnGenerer_");
        btnGenerer_->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"}\n"
""));

        horizontalLayout_2->addWidget(btnGenerer_);

        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(20, 320, 185, 40));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("QLabel {background-color: transparent; color: #260259; /* Texte sombre lisible */ font-size: 18px; font-weight: bold; }"));

        horizontalLayout_3->addWidget(label_4);

        cb_type = new QComboBox(layoutWidget1);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::Computer));
        cb_type->addItem(icon, QString());
        cb_type->addItem(QString());
        cb_type->addItem(QString());
        cb_type->setObjectName("cb_type");
        cb_type->setStyleSheet(QString::fromUtf8(" QComboBox { background: #FFFFFF; border: 2px solid #6BA5F2; border-radius: 10px; padding: 6px 10px; color: #260259; } QComboBox:focus { border: 2px solid #9305F2; background: #F3E9FF; }"));

        horizontalLayout_3->addWidget(cb_type);

        layoutWidget2 = new QWidget(groupBox);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(10, 370, 266, 40));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("QLabel {background-color: transparent; color: #260259; /* Texte sombre lisible */ font-size: 18px; font-weight: bold; }"));

        horizontalLayout_4->addWidget(label_5);

        date_depot = new QDateEdit(layoutWidget2);
        date_depot->setObjectName("date_depot");
        date_depot->setStyleSheet(QString::fromUtf8(" QDateEdit { background: #FFFFFF; border: 2px solid #6BA5F2; border-radius: 10px; padding: 6px 10px; color: #260259; }  QDateEdit:focus { border: 2px solid #9305F2; background: #F3E9FF; }"));

        horizontalLayout_4->addWidget(date_depot);

        layoutWidget3 = new QWidget(groupBox);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(40, 540, 261, 38));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        btn_ajouter = new QPushButton(layoutWidget3);
        btn_ajouter->setObjectName("btn_ajouter");
        QFont font1;
        btn_ajouter->setFont(font1);
        btn_ajouter->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"}\n"
""));

        horizontalLayout_5->addWidget(btn_ajouter);

        pushButton_3 = new QPushButton(layoutWidget3);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    color: #6BA5F2;\n"
"    border: 0px solid #6BA5F2;\n"
"    border-radius: 0px;\n"
"    padding: 0px 0px;\n"
"    font-size: 18px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #f0f8ff; /* l\303\251ger bleu clair au survol */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #dceeff; /* bleu encore plus marqu\303\251 quand press\303\251 */\n"
"}\n"
""));

        horizontalLayout_5->addWidget(pushButton_3);

        label_8 = new QLabel(widget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(380, 60, 301, 41));
        label_8->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: transparent;\n"
"    color: #48038C;\n"
"    font-size: 30px;   /* plus grand pour un titre */\n"
"    font-weight: bold; /* en gras */\n"
"}\n"
""));
        tableWidget = new QTableWidget(widget);
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
        if (tableWidget->rowCount() < 6)
            tableWidget->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem11);
        QBrush brush(QColor(255, 170, 255, 255));
        brush.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setForeground(brush);
        tableWidget->setItem(0, 0, __qtablewidgetitem12);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../DELL/Desktop/pngtree-delete-button-functionality-icon-image_1127707.jpg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        QBrush brush1(QColor(8, 0, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setForeground(brush1);
        __qtablewidgetitem13->setIcon(icon1);
        tableWidget->setItem(0, 5, __qtablewidgetitem13);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(360, 101, 791, 261));
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
"}\n"
""));
        pushButton_5 = new QPushButton(widget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(690, 60, 51, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    color: #6BA5F2;\n"
"    border: 0px solid #6BA5F2;\n"
"    border-radius: 0px;\n"
"    padding: 0px 0px;\n"
"    font-size: 18px;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../downloads/pdf-93-removebg-preview.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_5->setIcon(icon2);
        pushButton_5->setIconSize(QSize(40, 40));
        label_10 = new QLabel(widget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(442, 449, 691, 151));
        label_12 = new QLabel(widget);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(790, 10, 371, 41));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(800, 60, 301, 40));
        widget_2->setStyleSheet(QString::fromUtf8("QWidget {\n"
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
"}\n"
"\n"
""));
        layoutWidget4 = new QWidget(widget_2);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(0, 0, 291, 37));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        pushButton_4 = new QPushButton(layoutWidget4);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setStyleSheet(QString::fromUtf8("button->setStyleSheet(\n"
"    \"QPushButton {\"\n"
"    \"  color: #6BA5F2;\"       // couleur du texte\n"
"    \"  background-color: white;\"\n"
"    \"  border: 1px solid #6BA5F2;\"\n"
"    \"}\"\n"
");\n"
""));
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::EditFind));
        pushButton_4->setIcon(icon3);

        horizontalLayout_6->addWidget(pushButton_4);

        lineEdit_3 = new QLineEdit(layoutWidget4);
        lineEdit_3->setObjectName("lineEdit_3");

        horizontalLayout_6->addWidget(lineEdit_3);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(1092, 8, 71, 41));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    color: #6BA5F2;\n"
"    border: 0px solid #6BA5F2;\n"
"    border-radius: 0px;\n"
"    padding: 0px 0px;\n"
"    font-size: 18px;\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../downloads/png-transparent-bell-notification-communication-information-icon-thumbnail-removebg-preview.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon4);
        pushButton->setIconSize(QSize(40, 40));
        layoutWidget5 = new QWidget(widget);
        layoutWidget5->setObjectName("layoutWidget5");
        layoutWidget5->setGeometry(QRect(390, 380, 301, 40));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget5);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("QLabel { color: #260259; /* Texte sombre lisible */ font-size: 18px; font-weight: bold; }"));

        horizontalLayout_7->addWidget(label_9);

        comboBox_2 = new QComboBox(layoutWidget5);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setStyleSheet(QString::fromUtf8(" QComboBox { background: #FFFFFF; border: 2px solid #6BA5F2; border-radius: 10px; padding: 6px 10px; color: #260259; } QComboBox:focus { border: 2px solid #9305F2; background: #F3E9FF; }"));

        horizontalLayout_7->addWidget(comboBox_2);

        pushButton_6 = new QPushButton(layoutWidget5);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"}\n"
""));

        horizontalLayout_7->addWidget(pushButton_6);

        btn_modifier = new QPushButton(widget);
        btn_modifier->setObjectName("btn_modifier");
        btn_modifier->setGeometry(QRect(702, 378, 121, 41));
        btn_modifier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"}\n"
""));
        btn_modifier->setIconSize(QSize(30, 30));
        btn_supprimer = new QPushButton(widget);
        btn_supprimer->setObjectName("btn_supprimer");
        btn_supprimer->setGeometry(QRect(840, 380, 151, 41));
        btn_supprimer->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"}\n"
""));

        horizontalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Smart Electronic Repair Shop", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Formulaire", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "ID_Equipement *", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Marque/Mod\303\251le *", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Descrition de panne *", nullptr));
        label_6->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "Ajouter Image *", nullptr));
        btnGenerer_->setText(QCoreApplication::translate("MainWindow", "G\303\251n\303\251rer", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Type *", nullptr));
        cb_type->setItemText(0, QCoreApplication::translate("MainWindow", "PC", nullptr));
        cb_type->setItemText(1, QCoreApplication::translate("MainWindow", "Tablette ", nullptr));
        cb_type->setItemText(2, QCoreApplication::translate("MainWindow", "Smartphone", nullptr));

        label_5->setText(QCoreApplication::translate("MainWindow", "Date de depot *", nullptr));
        btn_ajouter->setText(QCoreApplication::translate("MainWindow", "Enregistrer", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Annuler ", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Liste des \303\251quipement", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID ", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Marque/Mod\303\251le", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "DateDepot", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Etat", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        pushButton_5->setText(QString());
        label_10->setText(QCoreApplication::translate("MainWindow", "statistique", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "l'equipement devrait etre prete dans deux jour ", nullptr));
        pushButton_4->setText(QString());
        pushButton->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "Trier par ", nullptr));
        comboBox_2->setItemText(0, QString());
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Type", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "Etat", nullptr));

        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Trier", nullptr));
        btn_modifier->setText(QCoreApplication::translate("MainWindow", "Modifier \342\234\217\357\270\217", nullptr));
        btn_supprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer \360\237\227\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
