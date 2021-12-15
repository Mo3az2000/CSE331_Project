#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "filetoString.hpp"
#include "formatting.hpp"



QString fileName = "";
QString ourInput = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit_2->setTabStopDistance(40);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_openFileButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(
                this,
                tr("Choose File"),
                "C://",
                "All Files (*.*);; XML Files(*.xml)"
                );
    ui->labelFileName->setText(fileName);
    ourInput = QString::fromStdString(fileToSring(fileName.toStdString()));
    ui->textEdit->setText(ourInput);
}


void MainWindow::on_prettifyButton_clicked()
{
    QString myOutput = QString::fromStdString(formatting(ourInput.toStdString()));
    ui->textEdit_2->setText(myOutput);
}

