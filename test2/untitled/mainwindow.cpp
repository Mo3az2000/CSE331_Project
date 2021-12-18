#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "filetoString.hpp"
#include "formatting.hpp"
#include "xmlToJason.hpp"
#include "Compression.hpp"

QString fileName = "";
QString ourInput = "";
QString filePath = "";
QString xmlName = "";
string myfilePath = "";
string myxmlName = "";
unsigned int myFontSize = 12;
Node* tree;
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
                filePath,
                "All Files (*.*);; XML Files(*.xml)"
                );

    ourInput = QString::fromStdString(fileToSring(fileName.toStdString()));
    ui->textEdit->setText(ourInput);
    myfilePath = fileName.toStdString();
    myxmlName = fileName.toStdString();
    int x = 0;
    for(int i = myfilePath.size(); myfilePath[i-1] != '/'; i--){
        myfilePath.erase(i-1,1);
        x = i-1;
    }
    myxmlName.erase(0,x);
    for(int i = myxmlName.size()-1; myxmlName[i] != '.'; i--){
        myxmlName.erase(i,1);
        x = i-1;
    }

    myxmlName.erase(x,1);
    filePath = QString::fromStdString(myfilePath);
    xmlName = QString::fromStdString(myxmlName);
    ui->labelFileName->setText(fileName);
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
        xml_to_json(fileName.toStdString(),myfilePath);
        ui->textEdit_2->setText(QString::fromStdString(fileToSring(myfilePath+"Json.json")));

        //qDebug()<<QDir::currentPath();
    }

}


void MainWindow::on_compressButton_clicked()
{
    string file_string = eraseSpacing(fileName.toStdString());
    tree = PrintCompressedTree(file_string,myfilePath+myxmlName);
    string myMessage = "File:\t" + myxmlName + ".xml\nis compressed to\nFile:\t" +myxmlName+ "_encodedFile.huff\n";
    QMessageBox::about(this,"Compression Done!", QString::fromStdString(myMessage));
}


void MainWindow::on_decompressButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(
                this,
                tr("Choose Compressed File"),
                filePath,
                "Compressed Files(*.huff)"
                );
    string st = read_huff_file(fileName.toStdString());
    string output = decode_file(tree, st);
    ui->textEdit->setText(QString::fromStdString(output));

}

