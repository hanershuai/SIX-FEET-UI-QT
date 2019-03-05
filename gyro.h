#ifndef GYRO_H
#define GYRO_H

#include <QDialog>
#include <QDebug>
#include <util_gyro.h>
namespace Ui {
class GYRO;
}

class GYRO : public QDialog
{
    Q_OBJECT
public:
    explicit GYRO(QWidget *parent = 0);
    ~GYRO();

private slots:
    void on_Open_Port_clicked();

    void on_Close_Port_clicked();

    void on_Get_Angle_clicked();

private:
    Ui::GYRO *ui;
    util_gyro *new_util_gyro;
    bool open;
};

#endif // GYRO_H
