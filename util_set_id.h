#ifndef UTIL_SET_ID_H
#define UTIL_SET_ID_H
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <QDebug>
using namespace std;

class util_set_id
{
public:
    util_set_id();
    int portInit(const char *device);
    bool open_serial_port();
    bool close_serial_port();
    bool set_boud_rate();
    bool send_angle_alone(unsigned char  id,int angle);
    bool send_ID_alone(unsigned char  id);
    int baud_rate;
private:
    int fd;
    unsigned char SendAngle[13];
};

#endif // UTIL_SET_ID_H
