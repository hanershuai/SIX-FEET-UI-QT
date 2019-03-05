#ifndef ID_SET_H
#define ID_SET_H

#include <QDialog>
#include <util_set_id.h>
namespace Ui {
class ID_SET;
}

class ID_SET : public QDialog
{
    Q_OBJECT

public:
    explicit ID_SET(QWidget *parent = 0);
    ~ID_SET();

private slots:
    void on_open_port_clicked();

    void on_close_port_clicked();

    void on_set_id_clicked();

    void on_pushButton_clicked();

    void on_Boud_Rate_valueChanged(int arg1);

    void on_Set_Boud_Rate_clicked();

    void on_ID_valueChanged(int arg1);

    void on_angle_valueChanged(int arg1);

    void on_Exit_clicked();

private:
    Ui::ID_SET *ui;
    bool open;
    util_set_id *new_util_set_id;
};

#endif // ID_SET_H
