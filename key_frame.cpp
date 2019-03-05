#include "key_frame.h"
#include "ui_key_frame.h"

key_frame::key_frame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::key_frame)
{
    this->new_util_key_frame = new util_key_frame();
    this->new_file_key_frame = new file_key_frame();
    this->open = false;
    this->str = "first second third fourth fifth sixth seventh eighth ninth tenth";
    this->user = str.split(" ");
    this->user_show = QStringList(user[0]);
    this->ListNum = 0;
    this->ViewRows = 0;
    for(int i=0;i<10;i++)
    {
        this->Speed[i]=50;
    }
    this->model = new QStringListModel(user_show);
    this->model->setStringList(user_show);
//    ui->listView->setModel(model);        //useList是个QListView
    for(unsigned int i = 0;i<sizeof(ServoAngle)/sizeof(ServoAngle[0]);i++)
    for(unsigned int j = 0;j<sizeof(ServoAngle[i])/sizeof(int);j++)
    {
        ServoAngle[i][j] =512;
    }
     this->my.append(ServoAngle[0]);
     //this->resize(1150,695);
     ui->setupUi(this);
     ui->listView->setModel(model);
}

key_frame::~key_frame()
{
    delete ui;
}

void key_frame::on_Load_clicked()
{
    QFileDialog* fd = new QFileDialog(this);//创建对话框
    QString fileName = fd->getOpenFileName(
                   this, "open text file",
                   ".",
                   "Text files (*.txt );;All files (*.*)");
    if(!fileName.isEmpty())
    {
        qDebug()<<fileName.toStdString().c_str();
        char length = new_file_key_frame->read_file(fileName.toStdString().c_str(),my,ServoAngle);

        my.clear();
        for(int i=0;i<int (length);i++)
        {
            my.append(ServoAngle[i]);
        }
//        for(int i=0;i<3;i++)
//        for(int j=0;j<22;j++)
//        {
//            qDebug()<<"angle = "<<i<<j<<"="<<ServoAngle[i][j];
//        }

        model->removeRows(0,user_show.length());
        user_show.clear();
        for(int i=0;i<my.length();i++)
        {
            user_show.append(user[i]);
        }
         model->setStringList(user_show);
         qDebug()<<"new";
         qDebug()<<my.length();
         for(int i=0;i<my.length();i++)
         for(int j=0;j<22;j++)
         {
             qDebug()<<"my"<<i<<j<<"="<<*(my.at(i)+j);
         }

         ListNum = my.length()-1;
    }
}

void key_frame::on_Open_clicked()
{
    if(new_util_key_frame->open_serial_port())
    {
        open = true;
    }
    else
    {
        open = false;
    }
}

void key_frame::on_Close_clicked()
{
    new_util_key_frame->close_serial_port();
    open = false;
}

void key_frame::on_Small_21_clicked()
{
    int x=ui->spinBox_ID21->value();
    if(ui->Small_21->isChecked())
    {
        ui->horizontalSlider_ID21->setRange(0,1023);
        ui->spinBox_ID21->setRange(0,1023);
        if(x>1023)
            ui->horizontalSlider_ID21->setValue(512);
        else
            ui->horizontalSlider_ID21->setValue(x);
    }
    else
    {
        ui->horizontalSlider_ID21->setRange(0,4095);
        ui->spinBox_ID21->setRange(0,4095);
        ui->horizontalSlider_ID21->setValue(x);
        ui->spinBox_ID21->setValue(x);
    }
}

void key_frame::on_Small_20_clicked()
{
    int x=ui->spinBox_ID20->value();
    if(ui->Small_20->isChecked())
    {
        ui->horizontalSlider_ID20->setRange(0,1023);
        ui->spinBox_ID20->setRange(0,1023);
        if(x>1023)
             ui->horizontalSlider_ID20->setValue(512);
        else
            ui->horizontalSlider_ID20->setValue(x);
    }
    else
    {
        ui->horizontalSlider_ID20->setRange(0,4095);
        ui->spinBox_ID20->setRange(0,4095);
        ui->horizontalSlider_ID20->setValue(x);
    }
}

void key_frame::on_Small_15_clicked()
{
    int x=ui->spinBox_ID15->value();
    if(ui->Small_15->isChecked())
    {
        ui->horizontalSlider_ID15->setRange(0,1023);
        ui->spinBox_ID15->setRange(0,1023);
        if(x>1023)
            ui->horizontalSlider_ID15->setValue(512);
        else
            ui->horizontalSlider_ID15->setValue(x);
    }
    else
    {
        ui->horizontalSlider_ID15->setRange(0,4095);
        ui->spinBox_ID15->setRange(0,4095);
        ui->horizontalSlider_ID15->setValue(x);
    }
}

void key_frame::on_Small_16_clicked()
{
    int x=ui->spinBox_ID16->value();
    if(ui->Small_16->isChecked())
    {
        ui->spinBox_ID16->setRange(0,1023);
        ui->horizontalSlider_ID16->setRange(0,1023);
        if(x>1023)
            ui->horizontalSlider_ID16->setValue(512);
        else
            ui->horizontalSlider_ID16->setValue(x);
    }
    else
    {
        ui->horizontalSlider_ID16->setRange(0,4095);
        ui->spinBox_ID16->setRange(0,4095);
        ui->horizontalSlider_ID16->setValue(x);
    }
}

void key_frame::on_Small_18_clicked()
{
    int x=ui->spinBox_ID18->value();
    if(ui->Small_18->isChecked())
    {
        ui->horizontalSlider_ID18->setRange(0,1023);
        ui->spinBox_ID18->setRange(0,1023);
        if(x>1023)
            ui->horizontalSlider_ID18->setValue(512);
        else
            ui->horizontalSlider_ID18->setValue(x);
    }
    else
    {
        ui->horizontalSlider_ID18->setRange(0,4095);
        ui->spinBox_ID18->setRange(0,4095);
        ui->horizontalSlider_ID18->setValue(x);
    }
}

void key_frame::on_Small_19_clicked()
{
    int x=ui->spinBox_ID19->value();
    if(ui->Small_19->isChecked())
    {
        ui->horizontalSlider_ID19->setRange(0,1023);
        ui->spinBox_ID19->setRange(0,1023);
        if(x>1023)
        ui->horizontalSlider_ID19->setValue(512);
        else
        ui->horizontalSlider_ID19->setValue(x);
    }
    else
    {
        ui->horizontalSlider_ID19->setRange(0,4095);
        ui->spinBox_ID19->setRange(0,4095);
        ui->horizontalSlider_ID19->setValue(x);
    }
}

void key_frame::on_Exit_clicked()
{
    this->close();
}

void key_frame::on_Add_clicked()
{
    if(user_show.length() <= 24)
    {
        ListNum++;
        if(ListNum < 10)
        {
            user_show.append(user[ListNum]);
        }
        else
        {
            user_show.append("add");
        }
        my.append(ServoAngle[user_show.length()-1]);
        model->setStringList(user_show);
    }

}

void key_frame::on_Insert_clicked()
{
    if((user_show.length() <= 24))
    {
    user_show.insert(ViewRows,"insert");
    model->setStringList(user_show);
        for(int i= user_show.length()-1;i>ViewRows;i--)
        {
            for(unsigned int j = 0;j<sizeof(ServoAngle[i])/sizeof(int);j++)
            {
                ServoAngle[i][j] = ServoAngle[i-1][j];
            }
            my.replace(i-1,ServoAngle[i]);
        }
    my.insert(ViewRows,ServoAngle[ViewRows]);
    }
}

void key_frame::on_Save_clicked()
{
    user_show.replace(ViewRows,QString(user_show[ViewRows]).toUpper());
    my.replace(ViewRows,ServoAngle[ViewRows]);
    model->setStringList(user_show);
}

void key_frame::on_Remove_clicked()
{
    user_show.removeAt(ViewRows);
    model->removeRows(ViewRows,1);
    my.removeAt(ViewRows);

    for(int i= ViewRows ;i < user_show.length()-1;i++)
    {
        for(unsigned int j = 0;j<sizeof(ServoAngle[i])/sizeof(int);j++)
        {
            ServoAngle[i][j] = ServoAngle[i+1][j];
        }
        my.replace(i,ServoAngle[i]);
    }
}

void key_frame::on_listView_clicked(const QModelIndex &index)
{
    ViewRows = index.row();
    qDebug()<<"rows ="<<ViewRows;
    qDebug()<<"length ="<<my.length();
    //    qDebug()<<index.data();
    //    qDebug()<<index;
    ui->horizontalSlider_ID02->setValue(*(my.at(ViewRows)+2));
    ui->horizontalSlider_ID03->setValue(*(my.at(ViewRows)+3));
    ui->horizontalSlider_ID04->setValue(*(my.at(ViewRows)+4));
    ui->horizontalSlider_ID05->setValue(*(my.at(ViewRows)+5));
    ui->horizontalSlider_ID06->setValue(*(my.at(ViewRows)+6));
    ui->horizontalSlider_ID07->setValue(*(my.at(ViewRows)+7));
    ui->horizontalSlider_ID08->setValue(*(my.at(ViewRows)+8));
    ui->horizontalSlider_ID09->setValue(*(my.at(ViewRows)+9));
    ui->horizontalSlider_ID10->setValue(*(my.at(ViewRows)+10));
    ui->horizontalSlider_ID11->setValue(*(my.at(ViewRows)+11));
    ui->horizontalSlider_ID12->setValue(*(my.at(ViewRows)+12));
    ui->horizontalSlider_ID13->setValue(*(my.at(ViewRows)+13));
    ui->horizontalSlider_ID14->setValue(*(my.at(ViewRows)+14));
    ui->horizontalSlider_ID15->setValue(*(my.at(ViewRows)+15));
    ui->horizontalSlider_ID16->setValue(*(my.at(ViewRows)+16));
    ui->horizontalSlider_ID17->setValue(*(my.at(ViewRows)+17));
    ui->horizontalSlider_ID18->setValue(*(my.at(ViewRows)+18));
    ui->horizontalSlider_ID19->setValue(*(my.at(ViewRows)+19));
    ui->horizontalSlider_ID20->setValue(*(my.at(ViewRows)+20));
    ui->horizontalSlider_ID21->setValue(*(my.at(ViewRows)+21));
    new_util_key_frame->send_angle_union(my.at(ViewRows),Speed);

}

void key_frame::on_listView_doubleClicked(const QModelIndex &index)
{
    /*for(int j=0;j<22;j++)
    {
        qDebug()<<"my send ="<<"="<<*(my.at(index.row())+j);
    }*/
    for(int i=index.row();i<my.length();i++)
    {
        new_util_key_frame->send_angle_union(my.at(i),Speed);
        sleep(1);
    }
}

void key_frame::on_spinBox_ID21_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][21] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(21,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID21->setValue(ServoAngle[ViewRows][21]);
    }
}

void key_frame::on_spinBox_ID20_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][20] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(20,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID20->setValue(ServoAngle[ViewRows][20]);
    }
}

void key_frame::on_spinBox_ID14_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][14] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(14,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID14->setValue(ServoAngle[ViewRows][14]);
    }
}

void key_frame::on_spinBox_ID15_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][15] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(15,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID15->setValue(ServoAngle[ViewRows][15]);
    }
}

void key_frame::on_spinBox_ID16_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][16] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(16,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID16->setValue(ServoAngle[ViewRows][16]);
    }
}

void key_frame::on_spinBox_ID17_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][17] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(17,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID17->setValue(ServoAngle[ViewRows][17]);
    }
}

void key_frame::on_spinBox_ID18_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][18] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(18,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID18->setValue(ServoAngle[ViewRows][18]);
    }
}

void key_frame::on_spinBox_ID19_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][19] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(19,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID19->setValue(ServoAngle[ViewRows][19]);
    }
}

void key_frame::on_spinBox_ID02_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][2] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(2,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID02->setValue(ServoAngle[ViewRows][2]);
    }
}

void key_frame::on_spinBox_ID03_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][3] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(3,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID03->setValue(ServoAngle[ViewRows][3]);
    }
}

void key_frame::on_spinBox_ID04_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][4] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(4,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID04->setValue(ServoAngle[ViewRows][4]);
    }
}

void key_frame::on_spinBox_ID05_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][5] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(5,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID05->setValue(ServoAngle[ViewRows][5]);
    }
}

void key_frame::on_spinBox_ID08_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][8] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(8,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID08->setValue(ServoAngle[ViewRows][8]);
    }
}

void key_frame::on_spinBox_ID10_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][10] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(10,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID10->setValue(ServoAngle[ViewRows][10]);
    }
}

void key_frame::on_spinBox_ID11_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][11] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(11,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID11->setValue(ServoAngle[ViewRows][11]);
    }
}

void key_frame::on_spinBox_ID09_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][9] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(9,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID09->setValue(ServoAngle[ViewRows][9]);
    }
}

void key_frame::on_Save_Binary_clicked()
{
    QString model = ".txt";
    QString fileName = QFileDialog::getSaveFileName(
                   this, "save text file",
                   ".",
                   "Text files (*.txt );;All files (*.*)");

    if((!fileName.isEmpty())&&(fileName.indexOf(model,1)))
    {
        qDebug()<<fileName.toStdString().c_str();
        new_file_key_frame->save_file(fileName.toStdString().c_str(),my);
//        ImageProcessing->SaveImage(fileName.toStdString().c_str(), CheckState , iLowH , iHighH , iLowS , iHighS , iLowV , iHighV);
    }

}

void key_frame::on_Spped1_valueChanged(int arg1)
{
    Speed[0]=arg1;
}

void key_frame::on_Speed2_valueChanged(int arg1)
{
    Speed[1]=arg1;
}

void key_frame::on_Speed3_valueChanged(int arg1)
{
    Speed[2]=arg1;
}

void key_frame::on_Speed4_valueChanged(int arg1)
{
    Speed[3]=arg1;
}

void key_frame::on_Speed5_valueChanged(int arg1)
{
    Speed[4]=arg1;
}

void key_frame::on_Speed6_valueChanged(int arg1)
{
    Speed[5]=arg1;
}

void key_frame::on_Speed7_valueChanged(int arg1)
{
    Speed[6]=arg1;
}

void key_frame::on_Speed8_valueChanged(int arg1)
{
    Speed[7]=arg1;
}

void key_frame::on_Speed9_valueChanged(int arg1)
{
    Speed[8]=arg1;
}

void key_frame::on_Speed10_valueChanged(int arg1)
{
    Speed[9]=arg1;
}

void key_frame::on_Save_Txt_clicked()
{
    QString model = ".txt";
    QString fileName = QFileDialog::getSaveFileName(
                   this, "save text file",
                   ".",
                   "Text files (*.txt );;All files (*.*)");

    if((!fileName.isEmpty())&&(fileName.indexOf(model,1)))
    {
        qDebug()<<fileName.toStdString().c_str();
        new_file_key_frame->save_file_Txt(fileName.toStdString().c_str(),my.length(), ServoAngle,Speed);
//        ImageProcessing->SaveImage(fileName.toStdString().c_str(), CheckState , iLowH , iHighH , iLowS , iHighS , iLowV , iHighV);
    }

}

void key_frame::on_Txt_Insert_clicked()
{
    QString model = ".txt";
    QString fileName = QFileDialog::getSaveFileName(
                   this, "save text file",
                   ".",
                   "Text files (*.txt );;All files (*.*)");

    if((!fileName.isEmpty())&&(fileName.indexOf(model,1)))
    {
        qDebug()<<fileName.toStdString().c_str();
        new_file_key_frame->save_Txt_Insert(fileName.toStdString().c_str(),my.length(), ServoAngle,Speed);
//        ImageProcessing->SaveImage(fileName.toStdString().c_str(), CheckState , iLowH , iHighH , iLowS , iHighS , iLowV , iHighV);
    }

}

void key_frame::on_Binary_Insert_clicked()
{
    QString model = ".txt";
    QString fileName = QFileDialog::getSaveFileName(
                   this, "save text file",
                   ".",
                   "Text files (*.txt );;All files (*.*)");

    if((!fileName.isEmpty())&&(fileName.indexOf(model,1)))
    {
        qDebug()<<fileName.toStdString().c_str();
        new_file_key_frame->save_binary_Insert(fileName.toStdString().c_str(),my.length(),ServoAngle);
//        ImageProcessing->SaveImage(fileName.toStdString().c_str(), CheckState , iLowH , iHighH , iLowS , iHighS , iLowV , iHighV);
    }

}

void key_frame::on_spinBox_ID06_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][6] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(6,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID06->setValue(ServoAngle[ViewRows][3]);
    }
}

void key_frame::on_spinBox_ID07_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][7] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(7,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID03->setValue(ServoAngle[ViewRows][7]);
    }
}

void key_frame::on_spinBox_ID12_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][12] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(12,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID03->setValue(ServoAngle[ViewRows][12]);
    }
}

void key_frame::on_spinBox_ID13_valueChanged(int arg1)
{
    if(open)
    {       ServoAngle[ViewRows][13] = arg1;
            if(ui->Union->isChecked())
            {
                new_util_key_frame->send_angle_union(ServoAngle[ViewRows],Speed);
            }
            else
            {
                new_util_key_frame->send_angle_alone(13,ServoAngle[ViewRows]);
            }
    }
    else
    {
        ui->spinBox_ID03->setValue(ServoAngle[ViewRows][13]);
    }
}
void key_frame::on_Play_Insert_clicked()
{
    QList <int *>list;
    int angle_temp[110][22];
    for(int i=0;i<(my.length()-1);i++)
    {
        for(int j=0;j<10;j++)
        {
           /* if(i==2)
            {
                for(int n=0;n<2;n++)
                    angle_temp[i*10+j][n]=2048;
                for(int k=2;k<22;k++)
                    angle_temp[i*10+j][k]=ServoAngle[i][k];
            }
            else*/
            {
            for(int n=0;n<2;n++)
                angle_temp[i*10+j][n]=2048;
            for(int k=2;k<22;k++)
                angle_temp[i*10+j][k]=ServoAngle[i][k]+(ServoAngle[i+1][k]-ServoAngle[i][k])*j/9;
            }
        }
    }
    for(int l=0;l<22;l++)
    {
        angle_temp[(my.length()-1)*10][l]=ServoAngle[my.length()-1][l];
        //qDebug()<<angle_temp[(length-1)*10][l]<<endl;
    }
    for(int p=0;p<=(my.length()-1)*10;p++)
    {
        list.append(angle_temp[p]);
    }
    for(int i=0;i<list.length();i++)
    {
        new_util_key_frame->send_angle_union(list.at(i),Speed);
        usleep(100000);
    }
}
