#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

QString fileCurrentPath;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveFile(QString &path) //save file path
{
    QFile file(path);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out<< ui -> textEdit -> toPlainText();
        file.close();
    }
}
int MainWindow::ask_saveOrNot() //if file is not saved this will ask to file save or not
{
    int S = QMessageBox::question(
        this,
        "Confirm",
        "Do You Want To Save?",
        QMessageBox::Yes | QMessageBox::No
        );
    return S;
}
void MainWindow::on_NEW_clicked() //new file and if the screen already hade text then it will clear the screen
{
    int S;

    if(fileCurrentPath.isEmpty())
    {
        if(!ui->textEdit->toPlainText().isEmpty())
        {
            S = ask_saveOrNot();
            if(S==QMessageBox::Yes)
            {

                fileCurrentPath = QFileDialog::getSaveFileName(
                    this,
                    "Save file",
                    "",
                    "Text Files (*.txt);;All Files (*.*)"
                    );
                if(fileCurrentPath.isEmpty())
                {
                    return ;
                }
                ui->FILENAME->setText(fileCurrentPath);
                saveFile(fileCurrentPath);
            }
            else
            {

                ui->textEdit->setText("");
                ui->FILENAME->setText("Notepad");
                fileCurrentPath="";
                return ;
            }
        }
    }
    else{
        ui->textEdit->setText("");
        ui->FILENAME->setText("Notepad");
        fileCurrentPath="";
    }
}

void MainWindow::on_SAVE_clicked() //this funtion will save the file
{



    if(fileCurrentPath.isEmpty()) // if the screen is empty then it will save the new file
    {

        fileCurrentPath = QFileDialog::getSaveFileName(
            this,
            "Save file",
            "",
            "Text Files (*.txt);;All Files (*.*)"
            );
        if(fileCurrentPath.isEmpty())
        {
            return ;
        }

        saveFile(fileCurrentPath);

    }
    else
    {
        /*if the screen is not empty like it is already open a file then
         it will save the existing oepn file not a new file */

        saveFile(fileCurrentPath);

    }
    ui->FILENAME->setText(fileCurrentPath);

}
void MainWindow::on_SAVEAS_clicked() //for saving existing file as new file
{
      //if text is already then it will save existing file as new file

        fileCurrentPath = QFileDialog::getSaveFileName( //get the path
            this,
            "Save as",
            "",
            "Text Files (*.txt);;All Files (*.*)"
            );
        if(fileCurrentPath.isEmpty())
        {
            return ;
        }
        saveFile(fileCurrentPath);

        ui->FILENAME->setText(fileCurrentPath);

}
void MainWindow::on_OPEN_clicked() //open a existing files
{
    int S;
    if(fileCurrentPath.isEmpty())
    {
        if(!ui->textEdit->toPlainText().isEmpty())
        {
            S = ask_saveOrNot();

            if(S==QMessageBox::Yes)
            {
                fileCurrentPath = QFileDialog::getSaveFileName(
                    this,
                    "Save file",
                    "",
                    "Text Files (*.txt);;All Files (*.*)"
                    );
                if(fileCurrentPath.isEmpty())
                {
                    return ;
                }

                saveFile(fileCurrentPath);

            }
            else
            {
                ui->textEdit->setText("");
                return ;
            }
        }
    }
   fileCurrentPath = QFileDialog::getOpenFileName(//get the path
        this,
        "Save file",
        "",
        "Text Files (*.txt);;All Files (*.*)"
        );
    if(fileCurrentPath.isEmpty())
    {
        return ;
    }
    QFile file(fileCurrentPath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        ui -> textEdit->setPlainText(in.readAll());
        file.close();
    }
    ui->FILENAME->setText(fileCurrentPath);

}
