#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "C:\\", tr("Text Files (*.txt *.docx)"));

    if (!fileName.isEmpty() && !fileName.isNull()) {

        QMessageBox::about(this, "Selected file", fileName);

        ui->pathLine->setText(fileName);

    }

}

void MainWindow::addItem() {

    binaryTreeAVL.ll = 0; binaryTreeAVL.lr = 0;
    binaryTreeAVL.rl = 0; binaryTreeAVL.rr = 0;

    int number = QInputDialog::getInt(this, "Input Integer", "Ingrese un entero a agregar");
    binaryTreeAVL.add(number);

    QDateTime currentDateTime = QDateTime::currentDateTime();

    QString filename = QFileDialog::getSaveFileName(this, "DialogTitle", currentDateTime.toString("yyyy-MM-dd_hh.mm.ss").append(".csv"), "CSV files (.csv);;Zip files (.zip, *.7z)", 0, 0);


    if (!filename.isEmpty() && !filename.isNull()) {

        QFile data(filename);

        if(data.open(QFile::WriteOnly |QFile::Truncate)) {
            QTextStream output(&data);

            output << "Sesion:;" << currentDateTime.toString("yyyy.MM.dd_hh:mm:ss") << endl;
            output << "Insercion individual:;" << QString::number(number) << endl;
            output << "II:;" << binaryTreeAVL.ll << endl;
            output << "DD:;" << binaryTreeAVL.rr << endl;
            output << "ID:;" << binaryTreeAVL.lr << endl;
            output << "DI:;" << binaryTreeAVL.rl << endl;
        }

    }

}

void MainWindow::deleteItem() {

    int number = QInputDialog::getInt(this, "Delete Integer", "Ingrese un entero a eliminar");

    Node *localFind = binaryTreeAVL.find(number);

    if (localFind != NULL) {

        if (localFind->getValue() == number) {

            binaryTreeAVL.ll = 0; binaryTreeAVL.lr = 0;
            binaryTreeAVL.rl = 0; binaryTreeAVL.rr = 0;

            binaryTreeAVL.remove(number);

            QDateTime currentDateTime = QDateTime::currentDateTime();

            QString filename = QFileDialog::getSaveFileName(this, "DialogTitle", currentDateTime.toString("yyyy-MM-dd_hh.mm.ss").append(".csv"), "CSV files (.csv);;Zip files (.zip, *.7z)", 0, 0);

            if (!filename.isEmpty() && !filename.isNull()) {

                QFile data(filename);

                if(data.open(QFile::WriteOnly |QFile::Truncate)) {
                    QTextStream output(&data);

                    output << "Sesion:;" << currentDateTime.toString("yyyy.MM.dd_hh:mm:ss") << endl;
                    output << "Eliminacion individual:;" << QString::number(number) << endl;
                    output << "II:;" << binaryTreeAVL.ll << endl;
                    output << "DD:;" << binaryTreeAVL.rr << endl;
                    output << "ID:;" << binaryTreeAVL.lr << endl;
                    output << "DI:;" << binaryTreeAVL.rl << endl;
                }

            }

        }

    } else {

        QDateTime currentDateTime = QDateTime::currentDateTime();

        QString filename = QFileDialog::getSaveFileName(this, "DialogTitle", currentDateTime.toString("yyyy-MM-dd_hh.mm.ss").append(".csv"), "CSV files (.csv);;Zip files (.zip, *.7z)", 0, 0);

        if (!filename.isEmpty() && !filename.isNull()) {

            QFile data(filename);

            if(data.open(QFile::WriteOnly |QFile::Truncate)) {
                QTextStream output(&data);

                output << "Sesion:;" << currentDateTime.toString("yyyy.MM.dd_hh:mm:ss") << endl;
                output << "Eliminacion individual:;" << QString::number(number) << endl;
                output << ";No existe" << endl;

            }

        }

    }

}

void MainWindow::on_actionAdd_new_element_triggered() {
    addItem();
}

void MainWindow::on_addButton_clicked() {
    addItem();
}

void MainWindow::on_deleteButton_clicked() {
    deleteItem();
}

void MainWindow::on_actionDelete_an_item_triggered() {
    deleteItem();
}

void MainWindow::on_actionClear_tree_triggered() {
    binaryTreeAVL.clear();
}


void MainWindow::on_actionExport_tree_triggered() {

}

void MainWindow::on_addAllButton_clicked() {

    QString text = ui->pathLine->text();

    if (!text.isEmpty()) {

        QString numbers;

        binaryTreeAVL.clear();

        QFile inputFile(ui->pathLine->text());

        QString type = "";

        int counter = 0;

        if (inputFile.open(QIODevice::ReadOnly)) {

           QTextStream in(&inputFile);

           while (!in.atEnd()) {

               if (counter == 0) {

                    if (QString::compare(in.readLine().trimmed(), "I", Qt::CaseInsensitive) == 0) {

                        type = "Entero";

                    } else {

                        if (QString::compare(in.readLine().trimmed(), "F", Qt::CaseInsensitive) == 0) {

                            type = "Flotante";

                        }

                    }

               } else {

                   if (counter == 1) {

                       in.readLine();

                   } else {

                       if (counter > 1) {

                           if (QString::compare(type, "Entero", Qt::CaseInsensitive) == 0) {

                               int number = in.readLine().trimmed().toInt();

                               binaryTreeAVL.add(number);

                               QString localAppend = QString::number(number).append(";");

                               numbers.append(localAppend);

                           } else {

                               int number = (int) in.readLine().trimmed().toFloat();

                               binaryTreeAVL.add(number);

                               QString localAppend = QString::number(number).append(";");

                               numbers.append(localAppend);


                           }

                       }

                   }

               }

               counter++;

           }

           inputFile.close();

        } else {

            QMessageBox::critical(this, "Error", "Archivo incorrecto.");

        }

        QDateTime currentDateTime = QDateTime::currentDateTime();

        QString filename = QFileDialog::getSaveFileName(this, "DialogTitle", currentDateTime.toString("yyyy-MM-dd_hh.mm.ss").append(".csv"), "CSV files (.csv);;Zip files (.zip, *.7z)", 0, 0);

        QFile data(filename);

        if(data.open(QFile::WriteOnly |QFile::Truncate)) {
            QTextStream output(&data);

            output << "Sesion:;" << currentDateTime.toString("yyyy.MM.dd_hh:mm:ss") << endl;
            output << ";" << endl;
            output << "Dataset:;" << inputFile.fileName() << endl;
            output << "Tipo:;" << type << endl;
            output << "Total de elementos:;" << counter - 2 << endl;
            output << "Elementos:;" << numbers << endl;
            output << "Resultados:;" << endl;
            output << "II:;" << binaryTreeAVL.ll << endl;
            output << "DD:;" << binaryTreeAVL.rr << endl;
            output << "ID:;" << binaryTreeAVL.lr << endl;
            output << "DI:;" << binaryTreeAVL.rl << endl;
        }

    } else {

        QMessageBox::critical(this, "Error", "Por favor, introduzca la ruta de un archivo.");

    }

}
