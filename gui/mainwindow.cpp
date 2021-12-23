#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "filetoString.hpp"
#include "formatting.hpp"
#include "xmlToJason.hpp"
#include "Compression.hpp"
#include "Correct_Error.hpp"



QString ourInput = "";
QString fileName = "";
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
                "XML Files(*.xml);;All Files (*.*)"
                );
    if(fileName.size()){
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
    if(fileName.size()){
        string file_string = eraseSpacing(fileName.toStdString());
        tree = PrintCompressedTree(file_string,myfilePath+myxmlName);

        ifstream in_file(fileName.toStdString(), ios::binary);
        in_file.seekg(0, ios::end);
        long long infile_size = in_file.tellg();

        ifstream out_file(myfilePath+myxmlName+ "_encodedFile.huff", ios::binary);
        out_file.seekg(0, ios::end);
        long long outfile_size = out_file.tellg();

        string myMessage =
                "File:\t" + myxmlName + ".xml\nsize:\t"+to_string(infile_size)+ " Bytes"+
                "\n\nis compressed to\n\nFile:\t" +myxmlName +
                "_encodedFile.huff\nsize:\t"+to_string(outfile_size)+" Bytes\n";


        //QMessageBox::about(this,"Compression Done!", QString::fromStdString(myMessage));
        QMessageBox myMsg;

        myMsg.setText(QString::fromStdString(myMessage));
        myMsg.setWindowTitle("Compression Done!");
        myMsg.setIconPixmap(QPixmap(":/res/img/perf.png").scaled(150,150));
        //myMsg.setStyleSheet("font: 700 15pt \"Courier\"");
        myMsg.setStyleSheet("font: 700 12pt \"Courier\";;background:#252526;;color:#6a9955;;");


        myMsg.exec();
    }

}


void MainWindow::on_decompressButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(
                this,
                tr("Choose Compressed File"),
                filePath,
                "Compressed Files(*.huff)"
                );
    if(fileName.size()){
        string st = read_huff_file(fileName.toStdString());
        string output = decode_file(tree, st);
        ui->textEdit->setText(QString::fromStdString(output));
    }
}


void MainWindow::on_fixButton_clicked()
{
    string outputPath = myfilePath+myxmlName+"_Fixed.xml";
    vector <string> myVector = correctError(fileName.toStdString(),outputPath);
    QString msgOutput = "Found " + QString::number(myVector.size()) + " Errors:\n";
    for(int i = 0; i < (int)myVector.size(); i++){
        msgOutput = msgOutput + QString::fromStdString(myVector[i]) + "\n";
    }
    if(myVector.size()){
        //QMessageBox msgFix;
        QMessageBox msgBox;
        msgBox.setText(msgOutput);
        msgBox.setWindowTitle("Found Errors!");
        msgBox.addButton(tr("Fix them!"), QMessageBox::YesRole);
        msgBox.setStyleSheet("font: 700 12pt \"Courier\";;background:#252526;;color:#6a9955;;");

        msgBox.exec();
        //QMessageBox::warning(this,"Found Errors!", msgOutput);

        ourInput = QString::fromStdString(fileToSring(outputPath));
        ui->textEdit->setText(ourInput);
        fileName = QString::fromStdString(outputPath);
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

        QMessageBox myMsg;
        myMsg.setText("Errors Fixed!\nFile Saved as:\n" + fileName);
        myMsg.setWindowTitle("Errors Fixed!");
        myMsg.setIconPixmap(QPixmap(":/res/img/perf.png").scaled(150,150));
        myMsg.setStyleSheet("font: 700 14pt \"Courier\";;background:#252526;;color:#6a9955;;");
        myMsg.exec();
    }
    else{
        QMessageBox myMsg;

        myMsg.setText("No Errors is Found in this File");
        myMsg.setWindowTitle("No Errors!");
        myMsg.setIconPixmap(QPixmap(":/res/img/perf.png").scaled(150,150));
        myMsg.setStyleSheet("font: 700 12pt \"Courier\";;background:#252526;;color:#6a9955;;");
        myMsg.exec();
    }
}


void MainWindow::on_saveButton_clicked()
{
    QString f = QFileDialog::getSaveFileName(this, tr("Save File"),
                                             filePath,
                                             tr("XML file(*.xml);;JSON file(*.json);;TEXT file(*.txt)"));
    if(f.size()){
        fstream saveOutput;
        saveOutput.open(f.toStdString(),ios::out);
        if(saveOutput.is_open()){
            saveOutput<< ui->textEdit_2->toPlainText().toStdString();
            saveOutput.close();
        }
        QMessageBox myMsg;

        myMsg.setText("File saved As:\n"+f);
        myMsg.setWindowTitle("File Saved!");
        myMsg.setIconPixmap(QPixmap(":/res/img/perf.png").scaled(150,150));
        //myMsg.setStyleSheet("font: 700 15pt \"Courier\"");
        myMsg.setStyleSheet("font: 700 12pt \"Courier\";;background:#252526;;color:#6a9955;;");


        myMsg.exec();
    }
}

