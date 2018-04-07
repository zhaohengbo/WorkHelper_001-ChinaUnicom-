#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "datamanage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lineEdit_maininput_returnPressed();

    void on_verticalSlider_page_valueChanged(int value);

    void on_verticalSlider_plain_valueChanged(int value);

    void on_checkBox_type_stateChanged(int arg1);

    void on_checkBox_plot01_clicked();

    void on_checkBox_plot02_clicked();

    void on_checkBox_plot03_clicked();

    void on_checkBox_plot04_clicked();

    void on_checkBox_plot05_clicked();

    void on_checkBox_plot06_clicked();

    void on_checkBox_plot07_clicked();

    void on_checkBox_plot08_clicked();

    void on_checkBox_plot09_clicked();

    void on_checkBox_plot10_clicked();

    void on_checkBox_plot11_clicked();

    void on_checkBox_plot12_clicked();

    void on_pushButton_next_clicked();

    void on_checkBox_plotall_clicked();

    void on_pushButton_create_clicked();

    void on_actionExit_triggered();

    void on_actionNew_File_triggered();

    void on_actionAbout_triggered();

    void on_actionAboutQt_triggered();

    void on_actionStyle_White_triggered();

    void on_actionStyle_Black_triggered();

private:
    Ui::MainWindow *ui;

    DataManage datamanager;

    int current_plain=0;
    int current_page=0;

    void output();

    void setcheckbox();
    void getcheckbox();
    void resetcheckbox(bool logic);

    QString output_file = "";
    QString log_path = "";

    QLabel *msgLabel;

    void showStatusMessage(const QString &message);
};

#endif // MAINWINDOW_H
