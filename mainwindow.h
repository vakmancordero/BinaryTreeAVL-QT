#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <BinaryTreeAVL.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    BinaryTreeAVL binaryTreeAVL;

private slots:
    void on_pushButton_clicked();

    void on_actionAdd_new_element_triggered();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_actionDelete_an_item_triggered();

    void on_actionClear_tree_triggered();

    void on_actionExport_tree_triggered();

    void on_addAllButton_clicked();

private:
    Ui::MainWindow *ui;
    void addItem();
    void deleteItem();

};

#endif // MAINWINDOW_H
