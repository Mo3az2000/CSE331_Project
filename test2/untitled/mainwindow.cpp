#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "filetoString.hpp"
#include "formatting.hpp"
#include "xmlToJason.hpp"


QString fileName = "";
QString ourInput = "";
unsigned int myFontSize = 12;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setTabStopDistance(4*myFontSize);
    ui->textEdit_2->setTabStopDistance(4*myFontSize);
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
    QString myOutput = QString::fromStdString(formatting(ui->textEdit->toPlainText().toStdString()));
    ui->textEdit_2->setText(myOutput);
}


void MainWindow::on_decButton_clicked()
{
    if(myFontSize > 6){
        myFontSize -= 2;
        ui->textEdit->setFontPointSize(myFontSize);
        ui->textEdit->setTabStopDistance(4*myFontSize);
        ui->textEdit->setText(ui->textEdit->toPlainText());

        ui->textEdit_2->setFontPointSize(myFontSize);
        ui->textEdit_2->setTabStopDistance(4*myFontSize);
        ui->textEdit_2->setText(ui->textEdit_2->toPlainText());
    }
}


void MainWindow::on_incButton_clicked()
{
    if(myFontSize < 72){
        myFontSize += 2;
        ui->textEdit->setFontPointSize(myFontSize);
        ui->textEdit->setTabStopDistance(4*myFontSize);
        ui->textEdit->setText(ui->textEdit->toPlainText());

        ui->textEdit_2->setFontPointSize(myFontSize);
        ui->textEdit_2->setTabStopDistance(4*myFontSize);
        ui->textEdit_2->setText(ui->textEdit_2->toPlainText());
    }
}


void MainWindow::on_jsonButton_clicked()
{
    if(fileName.toStdString().size() > 0){
        xml_to_json(fileName.toStdString());
        ui->textEdit_2->setText(QString::fromStdString(fileToSring("Json.json")));

        qDebug()<<QDir::currentPath();
    }

}

