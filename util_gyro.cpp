#include "util_gyro.h"

util_gyro::util_gyro()//: QThread(parent)
{
    this->fd=0;
    this->Open=0;
    for(int i=0;i<3;i++)
    {
        angle[i]=0;
    }
}
int util_gyro::port_init(const char *dev)
{
    fd=open(dev,O_RDWR | O_NOCTTY |O_NONBLOCK);
    if (fd== -1)
    {
        cerr << "Can't Open Serial Port  " << dev << endl;
    }//打开串口
    struct termios options;
    if (tcgetattr(fd, &options) != 0)
        perror("SetupSerial 1");
    options.c_cflag = B9600| CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    options.c_cc[VTIME] = 0;
    options.c_cc[VMIN] = 0;
    if (tcsetattr(fd, TCSANOW, &options) != 0)
        perror("SetupSerial 3");
    return fd;
}
bool util_gyro::open_port()
{
    fd= port_init("/dev/ttyUSB0");
      if(fd==-1)
      {
          cout<<"can't open serial ttyUSB0"<<endl;
          fd= port_init("/dev/ttyUSB1");
          if(fd==-1)
          {
               cout<<"can't open seria lttyUSB1"<<endl;
               fd= port_init("/dev/ttyUSB2");
               if(fd==-1)
               {
                   cout<<"can't open seria lttyUSB2"<<endl;
                   fd=port_init("/dev/ttyUSB3");
                   if(fd==-1)
                   {
                       cout<<"can't open seria lttyUSB3"<<endl;
                       fd=port_init("/dev/ttyUSB4");
                       if(fd==-1)
                            {cout<<"can't open seria lttyUSB4"<<endl;
                            fd=port_init("/dev/ttyUSB5");
                            if(fd==-1)
                                {
                                cout<<"can't open seria lttyUSB5"<<endl;
                                return false;
                                }
                            else
                            {
                                cout<<"open serial ttyUSB5"<<endl;
                                return true;
                            }
                            }
                       else
                       {
                           cout<<"open serial ttyUSB4"<<endl;
                           return true;
                       }
                   }
                   else
                   {cout<<"open serial ttyUSB3"<<endl;
                       return true;
                   }
               }
               else
               {
                   cout<<" open serial ttyUSB2"<<endl;
                   return true;
               }

          }
          else
          {
              cout<<"open serial ttyUSB1"<<endl;
              return true;
          }

      }
      else
      {
           cout<<"open serial ttyUSB0"<<endl;
           return true;
      }

}
bool util_gyro::close_port()
{
    if(close(fd)==-1)
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool util_gyro::read_serial(void *buf, int length)
{
    void *buf_tmp = buf;
    int bytes_remain = length;
    int bytes_send = 0;
    int count = 0;
    fcntl(fd,F_SETFL,FNDELAY);
    do
    {
        bytes_send = read(fd, buf_tmp, bytes_remain);
        if(bytes_send > 0){
            count = 0;
            buf_tmp += bytes_send;
            bytes_remain -=bytes_send;
        }
        else
        {
            count++;
            if(count > 20000){
                return false;
            }
        }
    }while(bytes_remain > 0);
    return true;
}
bool util_gyro::get_angle()
{
        //double angleX[10],angleY[10],angleZ[10];
        unsigned char data[11];
        unsigned char find;
        int count;
        int num;
        for(int i=0;i<10;i++)
            {
                num=0;
                count=0;
                while (1)
                {
                    num++;
                    if(num>100) return false;
                    read_serial(&find, 1);
                    data[count] = find;
                    if (data[0] != 0x55 && count == 0)
                    {
                    continue;
                    }
                    count++;
                    if (count == 2 && data[1] != 0x53 )
                    {
                    count = 0;
                    continue;
                    }
                    if (count == 11)
                    {
                     count = 0;
                    break;
                    }
                }
                //angleX[i]=(double)(shuju[2]|shuju[3]<<8)/32768*180.0;
                //angleY[i]=(double)(shuju[4]|shuju[5]<<8)/32768*180.0;
                //angleZ[i]=(double)(shuju[6]|shuju[7]<<8)/32768*180.0;
                angle[0]+=(double)(data[2]|data[3]<<8)/32768*180.0;
                angle[1]+=(double)(data[4]|data[5]<<8)/32768*180.0;
                angle[2]+=(double)(data[6]|data[7]<<8)/32768*180.0;
            }
        angle[0]=angle[0]/10;
        angle[1]=angle[1]/10;
        angle[2]=angle[2]/10;
}
void util_gyro::run()
{
    while(open)
    get_angle();
}
