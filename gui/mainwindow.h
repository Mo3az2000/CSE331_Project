#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_openFileButton_clicked();

    void on_prettifyButton_clicked();

    void on_decButton_clicked();

    void on_incButton_clicked();

    void on_jsonButton_clicked();

    void on_compressButton_clicked();

    void on_decompressButton_clicked();

    void on_fixButton_clicked();


    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
