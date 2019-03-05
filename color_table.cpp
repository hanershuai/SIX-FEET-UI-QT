#include "color_table.h"
#include "ui_color_table.h"

Color_Table::Color_Table(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Color_Table)
{
    ui->setupUi(this);
    color_table_init();
}

Color_Table::~Color_Table()
{
    delete ui;
    color_table_clean();
}

void Color_Table::on_Open_clicked()
{
        ui->tip->setText("open Camera Successful !");
    if(!open_camera())
    {
        ui->tip->setText("Fail To Open Camera !!!");
        return;
    }
    cvSetMouseCallback("Video_Show",Choose_Color);
    //this->start();
}

void Color_Table::on_Close_clicked()
{
   close_camera();
    ui->tip->setText("Close Successfully");
}

/*void Color_Table::on_Stop_clicked()
{
    new_file_color_table->stop();
    //cvSetMouseCallback("Video_Show",file_color_table::Choose_Color);
}*/

void Color_Table::on_Reset_clicked()
{
    reset();
    ui->tip->setText("Reset Successfully");
}

void Color_Table::on_Save_Green_clicked()
{
    save_green();
    ui->White_Number->setValue(white);
    ui->Blue_Number->setValue(blue);
    ui->Green_Number->setValue(green);
    white=0;
    blue=0;
    green=0;
}

void Color_Table::on_Save_White_clicked()
{
    save_white();
    ui->White_Number->setValue(white);
    ui->Blue_Number->setValue(blue);
    ui->Green_Number->setValue(green);
    white=0;
    blue=0;
    green=0;
}

void Color_Table::on_Save_Blue_clicked()
{
    save_blue();
    ui->White_Number->setValue(white);
    ui->Blue_Number->setValue(blue);
    ui->Green_Number->setValue(green);
    white=0;
    blue=0;
    green=0;
}

void Color_Table::on_Test_RGB_clicked()
{
    test_rgb();
    ui->tip->setText("Start To Test RGB");
}

void Color_Table::on_Test_HSV_clicked()
{
    test_hsv();
    ui->tip->setText("Start To Test HSV");
}

void Color_Table::on_Video_Test_RGB_clicked()
{
    video_test_rgb();
    ui->tip->setText("Start To Test RGB");
}

void Color_Table::on_Video_Test_HSV_clicked()
{
    video_test_hsv();
    ui->tip->setText("Start To Test HSV");
}

void Color_Table::on_Average_HSV_clicked()
{
    Average_HSV();
    ui->H_Number->setValue(H);
    ui->S_Number->setValue(S);
    ui->V_Number->setValue(V);
    H=0;
    S=0;
    V=0;
}
void Color_Table::on_Image_Load_clicked()
{
    if(!Image_In())
    ui->tip->setText("Fail To Load Image!!!");
    else
    ui->tip->setText("Load Image Successfully!");
}

void Color_Table::on_Image_Save_clicked()
{
    if(!Save_Image())
        ui->tip->setText("Fail To Load Image!!!");
    else
        ui->tip->setText("Save Image Successfully!");
}
/*void Color_Table::run()
{
    ui->tip->setText("open Camera Successful !");
if(!open_camera())
{
    ui->tip->setText("Fail To Open Camera !!!");
    return;
}
//cvSetMouseCallback("Video_Show",Choose_Color);
}*/

void Color_Table::on_Exit_clicked()
{
    this->close();
}
