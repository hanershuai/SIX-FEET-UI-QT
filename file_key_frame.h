#ifndef FILE_KEY_FRAME_H
#define FILE_KEY_FRAME_H
#include<time.h>
#include<stdio.h>
#include<QList>
#include<QDebug>

class file_key_frame
{
public:
    file_key_frame();
    bool save_file(const char *filename,QList<int *> list);
    bool save_file_Txt(const char *filename,int length,int angle[24][22],int speed[10]);
    bool save_Txt_Insert(const char *filename,int length, int angle[24][22],int speed[10]);
    bool save_binary_Insert(const char *filename,int length,int angle[24][22]);
    char read_file(const char *filename,QList<int *> list,int angle[24][22]);
};

#endif // FILE_KEY_FRAME_H
