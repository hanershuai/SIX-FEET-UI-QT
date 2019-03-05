#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ID_SET_clicked()
{
    new_id_set=new ID_SET;
    new_id_set->show();
}

void MainWindow::on_pushButton_clicked()
{
    new_gyro=new GYRO;
    new_gyro->show();
}

void MainWindow::on_COLOR_TABLE_clicked()
{
    new_color_table=new Color_Table;
    new_color_table->show();
}

void MainWindow::on_KEY_FRAME_clicked()
{
    new_key_frame=new key_frame;
    new_key_frame->show();
}
