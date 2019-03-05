#ifndef UTIL_GYRO_H
#define UTIL_GYRO_H
#include<fcntl.h>
#include<iostream>
#include <unistd.h>
#include<termios.h>
#include <QThread>
using namespace std;
class util_gyro:public QThread
{
public:
    util_gyro();
    bool read_serial(void *buf, int length);
    int port_init(const char* dev);
    bool open_port();
    bool close_port();
    bool get_angle();
    double angle[3];
    bool Open;
private:
    int fd;
protected:
    void run();
};

#endif // UTIL_GYRO_H
