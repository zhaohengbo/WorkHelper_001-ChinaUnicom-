#ifndef DATAMANAGE_H
#define DATAMANAGE_H

#include <QObject>

enum Box_Type{
    Box_Type_Single,
    Box_Type_Double
};

typedef struct{
    bool inuse[12];
}Plate_Data;

typedef struct{
    Plate_Data plate[30];
}Page_Data;

typedef struct{
    Box_Type type = Box_Type_Single;
    QString name = "";
    Page_Data page[2];
}Box_Data;

class DataManage : public QObject
{
    Q_OBJECT
public:
    explicit DataManage(QObject *parent = nullptr);

    void clear();

    void setname(QString name);

    void settype(Box_Type type);

    void setdata(int page_number,int plate_number,int slotnumber,bool state);

    QString getresult();

    bool getdata(int page_number,int plate_number,int slotnumber);

signals:

public slots:

private:
    Box_Data box_data;
};

#endif // DATAMANAGE_H
