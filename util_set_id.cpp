#include "util_set_id.h"

util_set_id::util_set_id()
{
    this->fd=0;
    baud_rate=9600;
}
int util_set_id::portInit(const char *device)
{
    int fd_ = open(device, O_RDWR | O_NOCTTY | O_NDELAY);    //| O_NOCTTY | O_NDELAY
    if (fd_ == -1)
    {
        cerr << "Can't Open Serial Port  " << device << endl;
    }//打开串口
    struct termios options;
    if (tcgetattr(fd_, &options) != 0)
        perror("SetupSerial 1");
    options.c_cflag = B115200| CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    options.c_cc[VTIME] = 0;
    options.c_cc[VMIN] = 0;
    if (tcsetattr(fd_, TCSANOW, &options) != 0)
        perror("SetupSerial 3");
    return fd_;
}

bool util_set_id::open_serial_port()
{
    fd= portInit("/dev/ttyUSB0");
      if(fd==-1)
      {
          cout<<"can't open serial ttyUSB0"<<endl;
          fd= portInit("/dev/ttyUSB1");
          if(fd==-1)
          {
               cout<<"can't open seria lttyUSB1"<<endl;
               fd= portInit("/dev/ttyUSB2");
               if(fd==-1)
               {
                   cout<<"can't open seria lttyUSB2"<<endl;
                   fd=portInit("/dev/ttyUSB3");
                   if(fd==-1)
                   {
                       cout<<"can't open seria lttyUSB3"<<endl;
                       fd=portInit("/dev/ttyUSB4");
                       if(fd==-1)
                            {cout<<"can't open seria lttyUSB4"<<endl;
                            fd=portInit("/dev/ttyUSB5");
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

bool util_set_id::close_serial_port()
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

bool util_set_id::send_angle_alone(unsigned char  id,int angle)
{
    unsigned char crc = 0;
    SendAngle[0] =  0xff;
    SendAngle[1] =  0xff;
    SendAngle[2] =  0xfe;
    SendAngle[3] =  0x09;//Length(L+1)*N+4
    SendAngle[4] =  0x83;//  SYNC WRITE
    SendAngle[5] =  0x1e;//Goal Position(L) Adress
    SendAngle[6] =  0x04;//The length of the data to be written

    SendAngle[7] =  id & 0xff;
    SendAngle[8] =  angle & 0xff;
    SendAngle[9] =  (angle >> 8) & 0xff;
    SendAngle[10] =  0xff;
    SendAngle[11] =  0x01;

    for(int i=2;i <= 11;i++)
    {
        crc += SendAngle[i];
    }
    SendAngle[12] = (unsigned char)(~crc);

    if(write(fd,SendAngle,13*sizeof(unsigned char)) == 13)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool util_set_id::send_ID_alone(unsigned char  id)
{
    unsigned char crc = 0;
    SendAngle[0] =  0xff;
    SendAngle[1] =  0xff;
    SendAngle[2] =  0xfe;
    SendAngle[3] =  0x04;//Length(L+1)*N+4
    SendAngle[4] =  0x03;//  WRITE_DATA
    SendAngle[5] =  0x03;//Goal Position(L) Adress
    SendAngle[6] =  id & 0xff;//The length of the data to be written

    for(int i=2;i <= 6;i++)
    {
        crc += SendAngle[i];
    }
    SendAngle[7] = (unsigned char)(~crc);

    if(write(fd,SendAngle,8*sizeof(unsigned char)) == 8)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool util_set_id::set_boud_rate()
{
    unsigned char crc = 0;
    SendAngle[0] =  0xff;
    SendAngle[1] =  0xff;
    SendAngle[2] =  0xfe;
    SendAngle[3] =  0x04;//Length(L+1)*N+4
    SendAngle[4] =  0x03;//  WRITE_DATA
    SendAngle[5] =  0x04;//Goal Position(L) Adress
    if(baud_rate==9600)
    SendAngle[6] =0xcf;//The length of the data to be written
    else if(baud_rate==19200)
    SendAngle[6]=0x67;
    else if(baud_rate==57600)
    SendAngle[6]=0x22;
    else if(baud_rate==115200)
    SendAngle[6]=0x10;
    else return false;
    for(int i=2;i <= 6;i++)
    {
        crc += SendAngle[i];
    }
    SendAngle[7] = (unsigned char)(~crc);

    if(write(fd,SendAngle,8*sizeof(unsigned char)) == 8)
    {
        return true;
    }
    else
    {
        return false;
    }
}
