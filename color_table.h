#ifndef COLOR_TABLE_H
#define COLOR_TABLE_H
#include <QDialog>
#include <file_color_table.h>
#include <QThread>
namespace Ui {
class Color_Table;
}

class Color_Table : public QDialog//,public QThread
{
    Q_OBJECT

public:
    explicit Color_Table(QWidget *parent = 0);
    ~Color_Table();

private slots:
    void on_Open_clicked();

    void on_Close_clicked();

//    void on_Stop_clicked();

    void on_Reset_clicked();

    void on_Save_Green_clicked();

    void on_Save_White_clicked();

    void on_Save_Blue_clicked();

    void on_Test_RGB_clicked();

    void on_Test_HSV_clicked();

    void on_Video_Test_RGB_clicked();

    void on_Video_Test_HSV_clicked();

    void on_Average_HSV_clicked();

    void on_Image_Load_clicked();

    void on_Image_Save_clicked();

    void on_Exit_clicked();

private:
    Ui::Color_Table *ui;
//protected:
//    void run();
};

#endif // COLOR_TABLE_H
