#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include<QFileDialog>
#include<QFile>
#include<QTextStream>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void on_NEW_clicked(); //new file
    void on_SAVE_clicked(); //save the file
    void on_OPEN_clicked(); //open a existing file
    void on_SAVEAS_clicked(); //save the existing file as new file
    void saveFile(QString &path); //save file logic
    int ask_saveOrNot();//if file is not saved this will ask to file save or not
};
#endif // MAINWINDOW_H
