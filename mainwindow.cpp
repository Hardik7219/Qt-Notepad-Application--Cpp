#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

// #include<iostream>
// #include<fstream>
QString areaText;
QString fileOpen;
QString filePath;
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


void MainWindow::on_NEW_clicked() //new file and if the screen already hade text then it will clear the screen
{
    areaText = ui->textEdit->toPlainText();
    int S;
    if(fileCurrentPath.isEmpty())
    {
        if(!areaText.isEmpty())
        {
            S = QMessageBox::question(
                this,
                "Confirm",
                "Do You Want To Save?",
                QMessageBox::Yes | QMessageBox::No
            );
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

                QFile file(fileCurrentPath);

                    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QTextStream out(&file);
                        out<< ui -> textEdit -> toPlainText();
                    file.close();
                }
            }
            else
            {
                ui->textEdit->setText("");
                return ;
            }
        }
    }
    else{
        ui->textEdit->setText("");
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

        QFile file(fileCurrentPath);

        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out<< ui -> textEdit -> toPlainText();
            file.close();
        }
    }
    else
    {
        /*if the screen is not empty like it is already open a file then
         it will save the existing oepn file not a new file */

        QFile file(fileCurrentPath);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out<< ui -> textEdit -> toPlainText();
            file.close();

        }
    }
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
        QFile file(fileCurrentPath);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out<< ui -> textEdit -> toPlainText();
            file.close();
        }
}
void MainWindow::on_OPEN_clicked() //open a existing files
{
    areaText = ui->textEdit->toPlainText();
    int S;
    if(fileCurrentPath.isEmpty())
    {
        if(!areaText.isEmpty())
        {
            S = QMessageBox::question(
                this,
                "Confirm",
                "Do You Want To Save?",
                QMessageBox::Yes | QMessageBox::No
                );
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

                QFile file(fileCurrentPath);

                if(file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QTextStream out(&file);
                    out<< ui -> textEdit -> toPlainText();
                    file.close();
                }
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
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream in(&file);
        ui -> textEdit->setPlainText(in.readAll());
        // areaText = ui->textEdit->toPlainText();
        file.close();
    }
}
