#include "datamanage.h"

DataManage::DataManage(QObject *parent) : QObject(parent)
{
    clear();
}


void DataManage::clear()
{
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<30;j++)
        {
            for(int k=0;k<12;k++)
            {
                box_data.page[i].plate[j].inuse[k] = false;
            }
        }
    }

    box_data.name = "";
    box_data.type = Box_Type_Single;
}


void DataManage::setname(QString name)
{
    box_data.name = name;
}


void DataManage::settype(Box_Type type)
{
    box_data.type = type;
}

void DataManage::setdata(int page_number,int plate_number,int slotnumber,bool state)
{
    box_data.page[page_number].plate[plate_number].inuse[slotnumber] = state;
}

bool DataManage::getdata(int page_number,int plate_number,int slotnumber)
{
    return box_data.page[page_number].plate[plate_number].inuse[slotnumber];
}

QString DataManage::getresult()
{
    QString result = "";
    if(box_data.type == Box_Type_Double)
    {
        for(int i=0;i<2;i++)
        {
            for(int j=0;j<30;j++)
            {
                for(int k=0;k<12;k++)
                {
                    result += "光交接箱";
                    result +=  "\t";
                    result += box_data.name;
                    result += "\t";
                    result += QString("'%1").arg((i+1), 2, 10, QChar('0'));
                    result += "\t";
                    result += QString("'%1").arg((j+1), 2, 10, QChar('0'));
                    result += "\t";
                    result +=  QString("%1").arg((k+1));
                    result += "\t";
                    if(box_data.page[i].plate[j].inuse[k])
                        result += "在用";
                    else
                        result += "空闲";
                    result += "\r\n";
                }
            }
        }
    }
    else
    {
        for(int j=0;j<30;j++)
        {
            for(int k=0;k<12;k++)
            {
                result += "光交接箱";
                result +=  "\t";
                result += box_data.name;
                result += "\t";
                result += QString("'%1").arg((0+1), 2, 10, QChar('0'));
                result += "\t";
                result += QString("'%1").arg((j+1), 2, 10, QChar('0'));
                result += "\t";
                result +=  QString("%1").arg((k+1));
                result += "\t";
                if(box_data.page[0].plate[j].inuse[k])
                    result += "在用";
                else
                    result += "空闲";
                result += "\r\n";
            }
        }
    }
    return result;
}
