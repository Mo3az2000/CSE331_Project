/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *openFileButton;
    QPushButton *prettifyButton;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QLabel *labelFileName;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(829, 627);
        QFont font;
        font.setFamilies({QString::fromUtf8("Courier New")});
        font.setPointSize(14);
        font.setBold(true);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        openFileButton = new QPushButton(centralwidget);
        openFileButton->setObjectName(QString::fromUtf8("openFileButton"));

        horizontalLayout->addWidget(openFileButton);

        prettifyButton = new QPushButton(centralwidget);
        prettifyButton->setObjectName(QString::fromUtf8("prettifyButton"));

        horizontalLayout->addWidget(prettifyButton);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        horizontalLayout->addWidget(pushButton_5);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout);

        labelFileName = new QLabel(centralwidget);
        labelFileName->setObjectName(QString::fromUtf8("labelFileName"));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Courier New")});
        font1.setPointSize(8);
        font1.setBold(true);
        labelFileName->setFont(font1);

        verticalLayout->addWidget(labelFileName);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Courier New")});
        font2.setPointSize(12);
        font2.setBold(true);
        textEdit->setFont(font2);

        horizontalLayout_2->addWidget(textEdit);

        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setFont(font2);
        textEdit_2->setLineWrapMode(QTextEdit::NoWrap);
        textEdit_2->setTabStopDistance(80.000000000000000);

        horizontalLayout_2->addWidget(textEdit_2);


        verticalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 829, 33));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Text Editor", nullptr));
        openFileButton->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
        prettifyButton->setText(QCoreApplication::translate("MainWindow", "Prettify", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Button 3", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        labelFileName->setText(QCoreApplication::translate("MainWindow", "No File Opened", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
