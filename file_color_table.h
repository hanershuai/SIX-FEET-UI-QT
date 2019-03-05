#ifndef FILE_COLOR_TABLE_H
#define FILE_COLOR_TABLE_H
#include<QDebug>
#include<iostream>
#include<cmath>
#include"stdlib.h"
#include"stdio.h"
#include <opencv2/opencv.hpp>
using namespace std;
void color_table_init();
void color_table_clean();
void Choose_Color(int event, int x, int y, int flag, void *param);
void Draw_Rect(CvPoint PT1,CvPoint PT2);
bool open_camera();
void close_camera();
//    void stop();
void reset();
void save_green();
void save_white();
void save_blue();
bool save_rgb_file(int flag);
bool save_hsv_file(int flag);
bool read_rgb_file();
bool read_hsv_file();
bool Save_Image();
bool Image_In();
void test_rgb();
void test_hsv();
void video_test_rgb();
void video_test_hsv();
void Average_HSV();
extern int video_stop,stop_num,open_num,white,green,blue;
extern long int H,S,V;
extern CvPoint pt1,pt2;
extern int drawing_box,on_choosing;
extern IplImage *src,*dst,*frame_temp,*Image_Out,*Image_Out_320,*Image_Out_HSV,*Image_Out_HSV_320,*Image_test,*Image_test_gray,*frame,*frame_test,*frame_test_gray;
extern int BGR[64][64][64],ym[64][64][64],ym_hsv[64][64][64],Zero[64][64][64],BGR1[64][64][64],HSV[64][64][64],HSV1[64][64][64],txt_1[64][64][64],txt_2[64][64][64];
extern CvCapture *capture;
extern const char *rgb_file,*hsv_file;
extern CvMat *Mat_Out;
#endif // FILE_COLOR_TABLE_H
