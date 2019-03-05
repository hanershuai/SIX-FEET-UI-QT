#ifndef KEY_FRAME_H
#define KEY_FRAME_H

#include <QDialog>
#include <QFileDialog>
#include <QStringListModel>
#include <file_key_frame.h>
#include <util_key_frame.h>
namespace Ui {
class key_frame;
}

class key_frame : public QDialog
{
    Q_OBJECT

public:
    explicit key_frame(QWidget *parent = 0);
    ~key_frame();

private slots:
    void on_Load_clicked();

    void on_Open_clicked();

    void on_Close_clicked();

    void on_Small_21_clicked();

    void on_Small_20_clicked();

    void on_Small_15_clicked();

    void on_Small_16_clicked();

    void on_Small_18_clicked();

    void on_Small_19_clicked();

    void on_Exit_clicked();

    void on_Add_clicked();

    void on_Insert_clicked();

    void on_Save_clicked();

    void on_Remove_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_spinBox_ID21_valueChanged(int arg1);

    void on_spinBox_ID20_valueChanged(int arg1);

    void on_spinBox_ID14_valueChanged(int arg1);

    void on_spinBox_ID15_valueChanged(int arg1);

    void on_spinBox_ID16_valueChanged(int arg1);

    void on_spinBox_ID17_valueChanged(int arg1);

    void on_spinBox_ID18_valueChanged(int arg1);

    void on_spinBox_ID19_valueChanged(int arg1);

    void on_spinBox_ID02_valueChanged(int arg1);

    void on_spinBox_ID03_valueChanged(int arg1);

    void on_spinBox_ID04_valueChanged(int arg1);

    void on_spinBox_ID05_valueChanged(int arg1);

    void on_spinBox_ID08_valueChanged(int arg1);

    void on_spinBox_ID10_valueChanged(int arg1);

    void on_spinBox_ID11_valueChanged(int arg1);

    void on_spinBox_ID09_valueChanged(int arg1);

    void on_Save_Binary_clicked();

    void on_Spped1_valueChanged(int arg1);

    void on_Speed2_valueChanged(int arg1);

    void on_Speed3_valueChanged(int arg1);

    void on_Speed4_valueChanged(int arg1);

    void on_Speed5_valueChanged(int arg1);

    void on_Speed6_valueChanged(int arg1);

    void on_Speed7_valueChanged(int arg1);

    void on_Speed8_valueChanged(int arg1);

    void on_Speed9_valueChanged(int arg1);

    void on_Speed10_valueChanged(int arg1);

    void on_Save_Txt_clicked();

    void on_Txt_Insert_clicked();

    void on_Binary_Insert_clicked();

    void on_spinBox_ID06_valueChanged(int arg1);

    void on_spinBox_ID07_valueChanged(int arg1);

    void on_spinBox_ID12_valueChanged(int arg1);

    void on_spinBox_ID13_valueChanged(int arg1);

    void on_Play_Insert_clicked();

private:
    Ui::key_frame *ui;
    util_key_frame *new_util_key_frame;
    file_key_frame *new_file_key_frame;
    bool open;
    int ServoAngle[24][22];
    int ViewRows;
    int ListNum;
    int Speed[10];
    QList<int *> my;
    QStringList user;
    QStringList user_show;
    QString str ;
    QStringListModel *model ;
};

#endif // KEY_FRAME_H
