#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <id_set.h>
#include <gyro.h>
#include <color_table.h>
#include <key_frame.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ID_SET *new_id_set;
    GYRO *new_gyro;
    Color_Table *new_color_table;
    key_frame *new_key_frame;
    ~MainWindow();

private slots:
    void on_ID_SET_clicked();

    void on_pushButton_clicked();

    void on_COLOR_TABLE_clicked();

    void on_KEY_FRAME_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
