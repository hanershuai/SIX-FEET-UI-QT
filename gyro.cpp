#include "gyro.h"
#include "ui_gyro.h"

GYRO::GYRO(QWidget *parent) :
    QDialog(parent),//QThread(parent),
    ui(new Ui::GYRO)
{
    ui->setupUi(this);
    new_util_gyro=new util_gyro;
    this->open=false;
}

GYRO::~GYRO()
{
    delete ui;
}

void GYRO::on_Open_Port_clicked()
{
    if(new_util_gyro->open_port())
    {
        open = true;
        new_util_gyro->Open=true;
        new_util_gyro->start();
        ui->tip->setText("Open port Successfully!");
    }
    else
    {
        //open = false;
        ui->tip->setText("Can't open port!!!");
    }
}

void GYRO::on_Close_Port_clicked()
{
    if(new_util_gyro->close_port())
    {
        open=false;
        new_util_gyro->Open=false;
        ui->tip->setText("Close port Successfully!");
    }
    else
    {
        //open=true;
        ui->tip->setText("Fail To Close port!!!");
    }
}

void GYRO::on_Get_Angle_clicked()
{
    if(open)
    {
        //char c;
        ui->tip->setText("Get Angle Successfully!");
        //new_util_gyro->get_angle();
        ui->X_Number->setValue(new_util_gyro->angle[0]);
        ui->Y_Number->setValue(new_util_gyro->angle[1]);
        ui->Z_Number->setValue(new_util_gyro->angle[2]);
        //qDebug()<<"111"<<endl;
        //sleep(1);
    }
    if(!open)
    {
        ui->tip->setText("Can't Get Angle");
    }
    return;
}

