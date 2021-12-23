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
    QPushButton *fixButton;
    QPushButton *compressButton;
    QPushButton *decompressButton;
    QPushButton *jsonButton;
    QPushButton *saveButton;
    QPushButton *decButton;
    QPushButton *incButton;
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
        MainWindow->resize(1094, 627);
        QFont font;
        font.setPointSize(14);
        font.setBold(false);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-radius: 25px;\n"
"padding: 0 8px;\n"
"background:#333333;\n"
"font: 700 12pt \"Consolas\";\n"
"height: 50px;\n"
"color: white;\n"
"}\n"
"QPushButton:hover {\n"
"border:2px solid;	\n"
"border-color: rgb(86, 156, 214);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"         \n"
"	background-color: rgb(55, 55, 61);\n"
"}\n"
"QMainWindow{\n"
"background:#252526\n"
"}\n"
"QLabel{\n"
"color:#6a9955;\n"
"}\n"
"QTextEdit{\n"
"background:#1e1e1e;\n"
"color:#d4d4d4;\n"
"}\n"
"QMessageBox{\n"
"font: 700 15pt \"Courier\";\n"
"background:#252526;\n"
"color:#6a9955;\n"
"width:1200px;\n"
"}\n"
"\n"
""));
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

        fixButton = new QPushButton(centralwidget);
        fixButton->setObjectName(QString::fromUtf8("fixButton"));

        horizontalLayout->addWidget(fixButton);

        compressButton = new QPushButton(centralwidget);
        compressButton->setObjectName(QString::fromUtf8("compressButton"));

        horizontalLayout->addWidget(compressButton);

        decompressButton = new QPushButton(centralwidget);
        decompressButton->setObjectName(QString::fromUtf8("decompressButton"));

        horizontalLayout->addWidget(decompressButton);

        jsonButton = new QPushButton(centralwidget);
        jsonButton->setObjectName(QString::fromUtf8("jsonButton"));

        horizontalLayout->addWidget(jsonButton);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        horizontalLayout->addWidget(saveButton);

        decButton = new QPushButton(centralwidget);
        decButton->setObjectName(QString::fromUtf8("decButton"));
        decButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	font: 700 8pt \"Courier New\";\n"
"}"));

        horizontalLayout->addWidget(decButton);

        incButton = new QPushButton(centralwidget);
        incButton->setObjectName(QString::fromUtf8("incButton"));
        incButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	font: 700 16pt \"Courier New\";\n"
"}"));

        horizontalLayout->addWidget(incButton);


        verticalLayout->addLayout(horizontalLayout);

        labelFileName = new QLabel(centralwidget);
        labelFileName->setObjectName(QString::fromUtf8("labelFileName"));
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(true);
        labelFileName->setFont(font1);
        labelFileName->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(labelFileName);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QFont font2;
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
        menubar->setGeometry(QRect(0, 0, 1094, 26));
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
        fixButton->setText(QCoreApplication::translate("MainWindow", "Fix Errors", nullptr));
        compressButton->setText(QCoreApplication::translate("MainWindow", "Compress", nullptr));
        decompressButton->setText(QCoreApplication::translate("MainWindow", "Decompress", nullptr));
        jsonButton->setText(QCoreApplication::translate("MainWindow", "\342\206\222 JSON", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save Output", nullptr));
        decButton->setText(QCoreApplication::translate("MainWindow", "Aa", nullptr));
        incButton->setText(QCoreApplication::translate("MainWindow", "Aa", nullptr));
        labelFileName->setText(QCoreApplication::translate("MainWindow", "No File Opened", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
