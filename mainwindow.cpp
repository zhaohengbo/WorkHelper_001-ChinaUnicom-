#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    datamanager.clear();
    current_plain=0;
    current_page=0;
    ui->verticalSlider_page->setValue(current_page + 1);
    ui->verticalSlider_plain->setValue(current_plain + 1);

    ui->verticalSlider_page->setMaximum(1);

    ui->lcdNumber_page->display(current_page + 1);
    ui->lcdNumber_plain->display(current_plain + 1);
    setcheckbox();

    msgLabel = new QLabel();
    statusBar()->addWidget(msgLabel);

    ui->actionStyle_Black->setChecked(false);
    ui->actionStyle_White->setChecked(true);

    showStatusMessage("提示:请先建立新文件");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_maininput_returnPressed()
{
    QString input;
    input = ui->lineEdit_maininput->text();
    ui->lineEdit_maininput->setText("");

    if(input == "")
    {
        current_plain++;
        if(current_plain >= 30)
        {
            current_plain = 0;
            if(ui->checkBox_type->isChecked())
            {
                current_page++;
                if(current_page >= 2)
                {
                    current_page = 0;

                    output();
                }
            }
            else
            {
                current_page = 0;

                output();
            }
            ui->switchControl_plotall->setToggle(false);
            setcheckbox();
        }
        else
        {
            ui->switchControl_plotall->setToggle(false);
            setcheckbox();
        }
        ui->verticalSlider_page->setValue(current_page + 1);
        ui->verticalSlider_plain->setValue(current_plain + 1);

        ui->lcdNumber_page->display(current_page + 1);
        ui->lcdNumber_plain->display(current_plain + 1);

        ui->switchControl_plotall->setToggle(false);
    }
    else
    {
        int input_number;
        input_number = input.toInt();

        if((input_number > 30) || (input_number < 1))
        {
            QMessageBox::warning(this,"输入错误","数值不在范围(1-30)",QMessageBox::Ok,QMessageBox::NoButton);
        }
        else
        {
            datamanager.setdata(current_page,current_plain,(input_number-1),!datamanager.getdata(current_page,current_plain,(input_number-1)));

            setcheckbox();
        }

    }

}


void MainWindow::output()
{
    if(ui->lineEdit_name->text().isEmpty())
    {
        QMessageBox::warning(this,"名称错误","没有输入光交接箱名称",QMessageBox::Ok,QMessageBox::NoButton);
        showStatusMessage("名称错误:没有输入光交接箱名称");
        return;
    }

    if(output_file.isEmpty())
    {
        QMessageBox::warning(this,"无法输出主文件","还没新建输出文件",QMessageBox::Ok,QMessageBox::NoButton);
        showStatusMessage("无法输出主文件:还没新建输出文件");
        return;
    }

    if(output_file.isEmpty())
    {
        QMessageBox::warning(this,"无法输出日志文件","输出日志目录不存在(但会继续输出主文件)",QMessageBox::Ok,QMessageBox::NoButton);
        showStatusMessage("无法输出日志文件:输出日志目录不存在(但会继续输出主文件)");
    }

    datamanager.setname(ui->lineEdit_name->text());
    if(ui->checkBox_type->isChecked())
        datamanager.settype(Box_Type_Double);
    else
        datamanager.settype(Box_Type_Single);
    QString content = datamanager.getresult();

    //qDebug() << content;
    QFile file(output_file);
    if ( file.open( QIODevice::Append ) ) {//只读模式
        QTextStream stream( &file );
        stream << content;
        file.close();
    }
    else
    {
        QMessageBox::warning(this,"输出失败","输出文件失败！",QMessageBox::Ok,QMessageBox::NoButton);
        showStatusMessage("输出失败:输出文件失败！");
        return;
    }
    QFile logfile(log_path + ui->lineEdit_name->text() + ".log");
    if ( logfile.open( QIODevice::WriteOnly ) ) {
        QTextStream stream( &logfile );
        stream << content;
        file.close();
    }
    else
    {
        QMessageBox::warning(this,"输出失败","输出日志文件失败(但已输出到主输出文件)！",QMessageBox::Ok,QMessageBox::NoButton);
        showStatusMessage("输出失败:输出日志文件失败(但已输出到主输出文件)！");
    }

    datamanager.clear();

    showStatusMessage("数据录入成功:您已成功录入一份光交接箱数据:" + ui->lineEdit_name->text() + "，主输出文件:" + output_file);

    ui->lineEdit_name->setText("");
    ui->checkBox_type->setChecked(false);

    QMessageBox::information(this,"数据录入成功","您已成功录入一份光交接箱数据");
}

void MainWindow::resetcheckbox(bool logic)
{
    ui->switchControl_plot01->setToggle(logic);
    ui->switchControl_plot01->setToggle(logic);
    ui->switchControl_plot02->setToggle(logic);
    ui->switchControl_plot03->setToggle(logic);
    ui->switchControl_plot04->setToggle(logic);
    ui->switchControl_plot05->setToggle(logic);
    ui->switchControl_plot06->setToggle(logic);
    ui->switchControl_plot07->setToggle(logic);
    ui->switchControl_plot08->setToggle(logic);
    ui->switchControl_plot09->setToggle(logic);
    ui->switchControl_plot10->setToggle(logic);
    ui->switchControl_plot11->setToggle(logic);
    ui->switchControl_plot12->setToggle(logic);
}

void MainWindow::getcheckbox()
{
    datamanager.setdata(current_page,current_plain,0,ui->switchControl_plot01->isToggled());
    datamanager.setdata(current_page,current_plain,1,ui->switchControl_plot02->isToggled());
    datamanager.setdata(current_page,current_plain,2,ui->switchControl_plot03->isToggled());
    datamanager.setdata(current_page,current_plain,3,ui->switchControl_plot04->isToggled());
    datamanager.setdata(current_page,current_plain,4,ui->switchControl_plot05->isToggled());
    datamanager.setdata(current_page,current_plain,5,ui->switchControl_plot06->isToggled());
    datamanager.setdata(current_page,current_plain,6,ui->switchControl_plot07->isToggled());
    datamanager.setdata(current_page,current_plain,7,ui->switchControl_plot08->isToggled());
    datamanager.setdata(current_page,current_plain,8,ui->switchControl_plot09->isToggled());
    datamanager.setdata(current_page,current_plain,9,ui->switchControl_plot10->isToggled());
    datamanager.setdata(current_page,current_plain,10,ui->switchControl_plot11->isToggled());
    datamanager.setdata(current_page,current_plain,11,ui->switchControl_plot12->isToggled());
}

void MainWindow::setcheckbox()
{
    ui->switchControl_plot01->setToggle(datamanager.getdata(current_page,current_plain,0));
    ui->switchControl_plot02->setToggle(datamanager.getdata(current_page,current_plain,1));
    ui->switchControl_plot03->setToggle(datamanager.getdata(current_page,current_plain,2));
    ui->switchControl_plot04->setToggle(datamanager.getdata(current_page,current_plain,3));
    ui->switchControl_plot05->setToggle(datamanager.getdata(current_page,current_plain,4));
    ui->switchControl_plot06->setToggle(datamanager.getdata(current_page,current_plain,5));
    ui->switchControl_plot07->setToggle(datamanager.getdata(current_page,current_plain,6));
    ui->switchControl_plot08->setToggle(datamanager.getdata(current_page,current_plain,7));
    ui->switchControl_plot09->setToggle(datamanager.getdata(current_page,current_plain,8));
    ui->switchControl_plot10->setToggle(datamanager.getdata(current_page,current_plain,9));
    ui->switchControl_plot11->setToggle(datamanager.getdata(current_page,current_plain,10));
    ui->switchControl_plot12->setToggle(datamanager.getdata(current_page,current_plain,11));
}

void MainWindow::on_checkBox_type_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    if(ui->checkBox_type->isChecked())
    {
        ui->verticalSlider_page->setMaximum(2);
        datamanager.settype(Box_Type_Double);
    }
    else
    {
        if(current_page > 0)
        {
            current_page = 0;
            ui->verticalSlider_page->setValue(current_page + 1);
            ui->verticalSlider_plain->setValue(current_plain + 1);

            ui->verticalSlider_page->setMaximum(1);

            ui->lcdNumber_page->display(current_page + 1);
            ui->lcdNumber_plain->display(current_plain + 1);
            setcheckbox();
        }
        datamanager.settype(Box_Type_Single);
    }
}

void MainWindow::on_pushButton_next_clicked()
{
    current_plain++;
    if(current_plain >= 30)
    {
        current_plain = 0;
        if(ui->checkBox_type->isChecked())
        {
            current_page++;
            if(current_page >= 2)
            {
                current_page = 0;
                output();
            }
        }
        else
        {
            current_page = 0;
            output();
        }
        setcheckbox();
    }
    else
    {
        setcheckbox();
    }
    ui->verticalSlider_page->setValue(current_page + 1);
    ui->verticalSlider_plain->setValue(current_plain + 1);

    ui->lcdNumber_page->display(current_page + 1);
    ui->lcdNumber_plain->display(current_plain + 1);

    ui->switchControl_plotall->setToggle(false);
}

void MainWindow::on_pushButton_create_clicked()
{
    output();

    current_plain=0;
    current_page=0;

    ui->verticalSlider_page->setValue(current_page + 1);
    ui->verticalSlider_plain->setValue(current_plain + 1);

    ui->lcdNumber_page->display(current_page + 1);
    ui->lcdNumber_plain->display(current_plain + 1);

    setcheckbox();

    ui->switchControl_plotall->setToggle(false);
}

void MainWindow::on_verticalSlider_page_valueChanged(int value)
{
    current_page = value - 1;
    ui->lcdNumber_page->display(current_page + 1);
    setcheckbox();
    ui->switchControl_plotall->setToggle(false);
}

void MainWindow::on_verticalSlider_plain_valueChanged(int value)
{
    current_plain = value - 1;
    ui->lcdNumber_plain->display(current_plain + 1);
    setcheckbox();
    ui->switchControl_plotall->setToggle(false);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNew_File_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("输出文件为"), "", "Config Files (*.txt)");

    if(fileName.isEmpty())
    {
        QMessageBox::warning(this,"新建失败","没有指定文件名",QMessageBox::Ok,QMessageBox::NoButton);
        showStatusMessage("新建失败:没有指定文件名");
        return;
    }

    output_file = fileName;

    showStatusMessage("主输出文件:" + output_file);

    QFileInfo fi;

    fi = QFileInfo(fileName);

    QString filePath = fi.absolutePath(); //获取文件路径(不包含文件名)

    if(filePath.isEmpty())
    {
        QMessageBox::warning(this,"新建失败","文件路径获取失败",QMessageBox::Ok,QMessageBox::NoButton);
        showStatusMessage("新建失败:文件路径获取失败");
        return;
    }
    else
    {
        QDir logDir;
        filePath += "/log/";

        if(!logDir.exists(filePath))
        {
            if(!logDir.mkpath(filePath))
            {
                QMessageBox::warning(this,"新建失败","无法创建日志目录",QMessageBox::Ok,QMessageBox::NoButton);
                showStatusMessage("新建失败:无法创建日志目录");
                return;
            }
        }
    }

    log_path = filePath;


}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"关于","王晓彤制作，Copyright©2018");
}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::showStatusMessage(const QString &message)
{
    msgLabel->setText(message);
}

void MainWindow::on_actionStyle_White_triggered()
{
    ui->actionStyle_Black->setChecked(false);
    ui->actionStyle_White->setChecked(true);
    QFile file(":/qss/flatwhite.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void MainWindow::on_actionStyle_Black_triggered()
{
    ui->actionStyle_White->setChecked(false);
    ui->actionStyle_Black->setChecked(true);
    QFile file(":/qss/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void MainWindow::on_switchControl_plotall_toggled(bool checked)
{
    if(checked)
    {
        resetcheckbox(true);
    }
    else
    {
        resetcheckbox(false);
    }
    getcheckbox();
}



void MainWindow::on_switchControl_plot01_toggled(bool checked)
{
    datamanager.setdata(current_page,current_plain,0,checked);
}
void MainWindow::on_switchControl_plot02_toggled(bool checked)
{
    datamanager.setdata(current_page,current_plain,1,checked);
}
void MainWindow::on_switchControl_plot03_toggled(bool checked)
{
    datamanager.setdata(current_page,current_plain,2,checked);
}
void MainWindow::on_switchControl_plot04_toggled(bool checked)
{
    datamanager.setdata(current_page,current_plain,3,checked);
}
void MainWindow::on_switchControl_plot05_toggled(bool checked)
{
    datamanager.setdata(current_page,current_plain,4,checked);
}
void MainWindow::on_switchControl_plot06_toggled(bool checked)
{
    datamanager.setdata(current_page,current_plain,5,checked);
}
void MainWindow::on_switchControl_plot07_toggled(bool checked)
{
    datamanager.setdata(current_page,current_plain,6,checked);
}
void MainWindow::on_switchControl_plot08_toggled(bool checked)
{
    datamanager.setdata(current_page,current_plain,7,checked);
}
void MainWindow::on_switchControl_plot09_toggled(bool checked)
{
    datamanager.setdata(current_page,current_plain,8,checked);
}
void MainWindow::on_switchControl_plot10_toggled(bool checked)
{
    datamanager.setdata(current_page,current_plain,9,checked);
}
void MainWindow::on_switchControl_plot11_toggled(bool checked)
{
    datamanager.setdata(current_page,current_plain,10,checked);
}
void MainWindow::on_switchControl_plot12_toggled(bool checked)
{
    datamanager.setdata(current_page,current_plain,11,checked);
}
