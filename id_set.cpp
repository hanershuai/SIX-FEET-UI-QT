#include "id_set.h"
#include "ui_id_set.h"

ID_SET::ID_SET(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ID_SET)
{
    ui->setupUi(this);
    new_util_set_id=new util_set_id;
    this->open=false;
}

ID_SET::~ID_SET()
{
    delete ui;
}

void ID_SET::on_open_port_clicked()
{
    if(new_util_set_id->open_serial_port())
    {
        open = true;
        ui->tip->setText("Open port Successfully!");
    }
    else
    {
        //open = false;
        ui->tip->setText("Can't open port!!!");
    }
}

void ID_SET::on_close_port_clicked()
{
    if(new_util_set_id->close_serial_port())
    {
        open=false;
        ui->tip->setText("Close port Successfully!");
    }
    else
    {
        //open=true;
        ui->tip->setText("Fail To Close port!!!");
    }
}

void ID_SET::on_set_id_clicked()
{
    if(open)
    {
    if(new_util_set_id->send_ID_alone(ui->ID->value()))
     {
        ui->tip->setText("Set ID Successfully!");
     }
    else
      {
        ui->tip->setText("Fail To Set ID!!!");
      }
    }
    else
        ui->tip->setText("Must Open Port Firstly!");
}

void ID_SET::on_pushButton_clicked()
{
    if(new_util_set_id->send_angle_alone(ui->ID->value(),ui->angle->value()))
    {
        ui->tip->setText("Send Angle Successfully!");
    }
    else
    {
        ui->tip->setText(("Fail To Send Angle"));
    }
}

void ID_SET::on_Boud_Rate_valueChanged(int arg1)
{
    if(open)
        new_util_set_id->baud_rate=arg1;
    else
        ui->Boud_Rate->setValue(new_util_set_id->baud_rate);
}

void ID_SET::on_Set_Boud_Rate_clicked()
{
    if(open=true)
    if(new_util_set_id->set_boud_rate())
        ui->tip->setText("Set Baud Rate Successfully");
    else ui->tip->setText("Fail To Set Baud Rate");
}

void ID_SET::on_ID_valueChanged(int arg1)
{
    if(!open)
        ui->ID->setValue(1);
}

void ID_SET::on_angle_valueChanged(int arg1)
{
    if(!open)
        ui->angle->setValue(0);
}

void ID_SET::on_Exit_clicked()
{
    this->close();
}
