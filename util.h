#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <QDebug>
using namespace std;
class Util
{
public:
    Util();
    int portInit(const char *device);
    bool open_serial_port();
    bool close_serial_port();
    bool send_angle_alone(unsigned char  id,int angle[22]);
    bool send_angle_mirror(unsigned char id_l,unsigned char id_r,int angle[22]);
    bool send_angle_union(int angle[22]);
    bool send_ID_alone(unsigned char  id);
private:
    int fd;
    unsigned char SendAngle[113];
};

#endif // UTIL_H
