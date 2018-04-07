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
            ui->checkBox_plotall->setChecked(false);
            setcheckbox();
        }
        else
        {
            ui->checkBox_plotall->setChecked(false);
            setcheckbox();
        }
        ui->verticalSlider_page->setValue(current_page + 1);
        ui->verticalSlider_plain->setValue(current_plain + 1);

        ui->lcdNumber_page->display(current_page + 1);
        ui->lcdNumber_plain->display(current_plain + 1);
    }
    else
    {
        int input_number;
        input_number = input.toInt();

        if((input_number > 30) || (input_number < 1))
        {
            QMessageBox::warning(this,"error input","value not in range",QMessageBox::Ok,QMessageBox::NoButton);
        }
        else
        {
            if(ui->checkBox_inputtype->isChecked())
                datamanager.setdata(current_page,current_plain,(input_number-1),true);
            else
                datamanager.setdata(current_page,current_plain,(input_number-1),false);

            setcheckbox();
        }

    }

}


void MainWindow::output()
{
    if(ui->lineEdit_name->text() == "")
    {
        QMessageBox::warning(this,"error noname","you have not type name",QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }

    datamanager.setname(ui->lineEdit_name->text());
    if(ui->checkBox_type->isChecked())
        datamanager.settype(Box_Type_Double);
    else
        datamanager.settype(Box_Type_Single);
    QString content = datamanager.getresult();

    datamanager.clear();

    //qDebug() << content;
    QFile file( "d:\\output\\output.txt" );
    if ( file.open( QIODevice::Append ) ) {//只读模式
        QTextStream stream( &file );
        stream << content;
        file.close();
    }
    QFile logfile( "d:\\output\\log\\" + ui->lineEdit_name->text() + ".txt" );
    if ( logfile.open( QIODevice::Append ) ) {//只读模式
        QTextStream stream( &logfile );
        stream << content;
        file.close();
    }

    ui->lineEdit_name->setText("");
    ui->checkBox_type->setChecked(false);

    QMessageBox::information(this,"data enter!","you have enter one piece of data");
}

void MainWindow::resetcheckbox(bool logic)
{
    ui->checkBox_plot01->setChecked(logic);
    ui->checkBox_plot02->setChecked(logic);
    ui->checkBox_plot03->setChecked(logic);
    ui->checkBox_plot04->setChecked(logic);
    ui->checkBox_plot05->setChecked(logic);
    ui->checkBox_plot06->setChecked(logic);
    ui->checkBox_plot07->setChecked(logic);
    ui->checkBox_plot08->setChecked(logic);
    ui->checkBox_plot09->setChecked(logic);
    ui->checkBox_plot10->setChecked(logic);
    ui->checkBox_plot11->setChecked(logic);
    ui->checkBox_plot12->setChecked(logic);
}

void MainWindow::getcheckbox()
{
    datamanager.setdata(current_page,current_plain,0,ui->checkBox_plot01->isChecked());
    datamanager.setdata(current_page,current_plain,1,ui->checkBox_plot02->isChecked());
    datamanager.setdata(current_page,current_plain,2,ui->checkBox_plot03->isChecked());
    datamanager.setdata(current_page,current_plain,3,ui->checkBox_plot04->isChecked());
    datamanager.setdata(current_page,current_plain,4,ui->checkBox_plot05->isChecked());
    datamanager.setdata(current_page,current_plain,5,ui->checkBox_plot06->isChecked());
    datamanager.setdata(current_page,current_plain,6,ui->checkBox_plot07->isChecked());
    datamanager.setdata(current_page,current_plain,7,ui->checkBox_plot08->isChecked());
    datamanager.setdata(current_page,current_plain,8,ui->checkBox_plot09->isChecked());
    datamanager.setdata(current_page,current_plain,9,ui->checkBox_plot10->isChecked());
    datamanager.setdata(current_page,current_plain,10,ui->checkBox_plot11->isChecked());
    datamanager.setdata(current_page,current_plain,11,ui->checkBox_plot12->isChecked());
}

void MainWindow::setcheckbox()
{
    ui->checkBox_plot01->setChecked(datamanager.getdata(current_page,current_plain,0));
    ui->checkBox_plot02->setChecked(datamanager.getdata(current_page,current_plain,1));
    ui->checkBox_plot03->setChecked(datamanager.getdata(current_page,current_plain,2));
    ui->checkBox_plot04->setChecked(datamanager.getdata(current_page,current_plain,3));
    ui->checkBox_plot05->setChecked(datamanager.getdata(current_page,current_plain,4));
    ui->checkBox_plot06->setChecked(datamanager.getdata(current_page,current_plain,5));
    ui->checkBox_plot07->setChecked(datamanager.getdata(current_page,current_plain,6));
    ui->checkBox_plot08->setChecked(datamanager.getdata(current_page,current_plain,7));
    ui->checkBox_plot09->setChecked(datamanager.getdata(current_page,current_plain,8));
    ui->checkBox_plot10->setChecked(datamanager.getdata(current_page,current_plain,9));
    ui->checkBox_plot11->setChecked(datamanager.getdata(current_page,current_plain,10));
    ui->checkBox_plot12->setChecked(datamanager.getdata(current_page,current_plain,11));
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

void MainWindow::on_checkBox_plot01_clicked()
{
    getcheckbox();
}

void MainWindow::on_checkBox_plot02_clicked()
{
    getcheckbox();
}

void MainWindow::on_checkBox_plot03_clicked()
{
    getcheckbox();
}

void MainWindow::on_checkBox_plot04_clicked()
{
    getcheckbox();
}

void MainWindow::on_checkBox_plot05_clicked()
{
    getcheckbox();
}

void MainWindow::on_checkBox_plot06_clicked()
{
    getcheckbox();
}

void MainWindow::on_checkBox_plot07_clicked()
{
    getcheckbox();
}

void MainWindow::on_checkBox_plot08_clicked()
{
    getcheckbox();
}

void MainWindow::on_checkBox_plot09_clicked()
{
    getcheckbox();
}

void MainWindow::on_checkBox_plot10_clicked()
{
    getcheckbox();
}

void MainWindow::on_checkBox_plot11_clicked()
{
    getcheckbox();
}

void MainWindow::on_checkBox_plot12_clicked()
{
    getcheckbox();
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
}

void MainWindow::on_checkBox_plotall_clicked()
{
    if(ui->checkBox_plotall->isChecked())
    {
        resetcheckbox(true);
    }
    else
    {
        resetcheckbox(false);
    }
    getcheckbox();
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
}

void MainWindow::on_verticalSlider_page_valueChanged(int value)
{
    current_page = value - 1;
    ui->lcdNumber_page->display(current_page + 1);
    setcheckbox();
}

void MainWindow::on_verticalSlider_plain_valueChanged(int value)
{
    current_plain = value - 1;
    ui->lcdNumber_plain->display(current_plain + 1);
    setcheckbox();
}
