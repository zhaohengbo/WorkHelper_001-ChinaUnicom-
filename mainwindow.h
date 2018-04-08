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

    void on_pushButton_next_clicked();

    void on_pushButton_create_clicked();

    void on_actionExit_triggered();

    void on_actionNew_File_triggered();

    void on_actionAbout_triggered();

    void on_actionAboutQt_triggered();

    void on_actionStyle_White_triggered();

    void on_actionStyle_Black_triggered();

    void on_switchControl_plotall_toggled(bool checked);

    void on_switchControl_plot01_toggled(bool checked);
    void on_switchControl_plot02_toggled(bool checked);
    void on_switchControl_plot03_toggled(bool checked);
    void on_switchControl_plot04_toggled(bool checked);
    void on_switchControl_plot05_toggled(bool checked);
    void on_switchControl_plot06_toggled(bool checked);
    void on_switchControl_plot07_toggled(bool checked);
    void on_switchControl_plot08_toggled(bool checked);
    void on_switchControl_plot09_toggled(bool checked);
    void on_switchControl_plot10_toggled(bool checked);
    void on_switchControl_plot11_toggled(bool checked);
    void on_switchControl_plot12_toggled(bool checked);

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
