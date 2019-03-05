#include "file_color_table.h"
int video_stop,stop_num,open_num,white,green,blue;
long int H,S,V;
CvPoint pt1,pt2;
int drawing_box,on_choosing;
IplImage *src,*dst,*frame_temp,*Image_Out,*Image_Out_320,*Image_Out_HSV,*Image_Out_HSV_320,*Image_test,*Image_test_gray,*frame,*frame_test,*frame_test_gray;
int BGR[64][64][64],ym[64][64][64],ym_hsv[64][64][64],Zero[64][64][64],BGR1[64][64][64],HSV[64][64][64],HSV1[64][64][64],txt_1[64][64][64],txt_2[64][64][64];
CvCapture *capture;
const char *rgb_file="ColourTable_RGB.txt",*hsv_file="ColourTable_HSV.txt";
CvMat *Mat_Out;
void color_table_init()
{
    drawing_box=0;
    on_choosing=0;
    video_stop=0;
    capture=cvCreateCameraCapture(1);
    H=0;S=0;V=0;
    white=0;blue=0;green=0;
    int i=0,j=0,k=0;
    for(i=0;i<64;i++)
        for(j=0;j<64;j++)
            for(k=0;k<64;k++)
            {
                Zero[i][j][k]=0;
            }
}
void color_table_clean()
{
    cvReleaseCapture(&capture);
    cvReleaseImage(&frame);
    cvDestroyAllWindows();
}
bool open_camera()
{
    video_stop=0;
    char c=0;
    while(!video_stop)
    {
    if((frame=cvQueryFrame(capture))==NULL)
        return false;
       cvShowImage("Video_Show",frame);
       c=cvWaitKey(33);
       if(c==32)
           break;
    }
    on_choosing=1;
    video_stop=1;
    src=cvCreateImage(cvSize(640,480),frame->depth,frame->nChannels);
    dst=cvCreateImage(cvSize(640,480),frame->depth,frame->nChannels);
    cvResize(frame,src);
    cvResize(frame,dst);
    cvShowImage("Video_Show",src);
    return true;
}
void close_camera()
{
    video_stop=1;
    on_choosing=0;
    cvDestroyAllWindows();
}
void reset()
{
    cvZero(Mat_Out);
    int i=0,j=0,k=0,r=0;
     for(i=0;i<64;i++)
          for(j=0;j<64;j++)
                for(k=0;k<64;k++)
                {
                    BGR[i][j][k]=0;
                    HSV[i][j][k]=0;
                    BGR1[i][j][k]=0;
                    HSV1[i][j][k]=0;
                }

}
void save_white()
{
    Image_Out_320=cvCreateImage(cvSize(src->width/4,src->height/4),src->depth,src->nChannels);
    Image_Out_HSV_320=cvCreateImage(cvSize(src->width/4,src->height/4),src->depth,src->nChannels);
    cvResize(Image_Out,Image_Out_320);
    cvResize(Image_Out_HSV,Image_Out_HSV_320);
    int p=0,R,G,B,H,S,V,i,j,width=Image_Out->width,height=Image_Out->height,width_320=Image_Out_320->width,height_320=Image_Out_320->height;
    qDebug()<<"saving.......";
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
           B=CV_IMAGE_ELEM(Image_Out,unsigned char,i,j*3+0);
           G=CV_IMAGE_ELEM(Image_Out,unsigned char,i,j*3+1);
           R=CV_IMAGE_ELEM(Image_Out,unsigned char,i,j*3+2);
           B=B/4;
           G=G/4;
           R=R/4;
           BGR[B][G][R]=2;
           if((BGR[B][G][R]==1)||(BGR1[B][G][R]==1))
           {
               BGR[B][G][R]=1;
               {
                   int b1=B-5,b2=B+5,g1=G-5,g2=G+5,r1=R-5,r2=R+5;
                   int i,j,k;
                   if(b1<0)b1=0;if(g1<0)g1=0;if(r1<0)r1=0;
                   for(i=b1;i<b2&&i<64;i++)
                       for(j=g1;j<g2&&j<64;j++)
                           for(k=r1;k<r2&&k<64;k++)
                               BGR[i][j][k]=1;
               }
           }
           if((BGR[B][G][R]==2)||(BGR1[B][G][R]==2))
           {
               BGR[B][G][R]=2;
               {
                   int b1=B-5,b2=B+5,g1=G-5,g2=G+5,r1=R-5,r2=R+5;
                   int i,j,k;
                   if(b1<0)b1=0;if(g1<0)g1=0;if(r1<0)r1=0;
                   for(i=b1;i<b2&&i<64;i++)
                       for(j=g1;j<g2&&j<64;j++)
                           for(k=r1;k<r2&&k<64;k++)
                               BGR[i][j][k]=2;
               }
           }
           p++;
        }
        for(j=0;j<width;j++)
        {
            H=CV_IMAGE_ELEM(Image_Out_HSV,unsigned char,i,j*3+0);
            S=CV_IMAGE_ELEM(Image_Out_HSV,unsigned char,i,j*3+1);
            V=CV_IMAGE_ELEM(Image_Out_HSV,unsigned char,i,j*3+2);
            H=H/4;
            S=S/4;
            V=V/4;
            HSV[H][S][V]=2;
            if(HSV[H][S][V]==2||HSV1[H][S][V]==2)
            {   HSV[H][S][V]=2;
                int i,j,k;
                int h1=H-2,h2=H+2,s1=S-2,s2=S+2,v1=V-2,v2=V+2;
                if(h1<0)h1=0;if(s1<0)s1=0;if(v1=0)v1=0;
                if(h2>45)h2=44;if(s2>64)s2=63;if(v2>64)v2=63;
                for(i=h1;i<h2;i++)
                    for(j=s1;j<s2;j++)
                        for(k=v1;k<v2;k++)
                            HSV[i][j][k]=2;
            }
            if(HSV[H][S][V]==1||HSV1[H][S][V]==1)
            {
                HSV[H][S][V]=1;
                int i,j,k;
                int h1=H-2,h2=H+2,s1=S-2,s2=S+2,v1=V-2,v2=V+2;
                if(h1<0)h1=0;if(s1<0)s1=0;if(v1=0)v1=0;
                if(h2>45)h2=44;if(s2>64)s2=63;if(v2>64)v2=63;
                for(i=h1;i<h2;i++)
                    for(j=s1;j<s2;j++)
                        for(k=v1;k<v2;k++)
                            HSV[i][j][k]=1;
            }
        }
    }
    for(i=0;i<height_320;i++)
    {
        for(j=0;j<width_320;j++)
        {
           B=CV_IMAGE_ELEM(Image_Out_320,unsigned char,i,j*3+0);
           G=CV_IMAGE_ELEM(Image_Out_320,unsigned char,i,j*3+1);
           R=CV_IMAGE_ELEM(Image_Out_320,unsigned char,i,j*3+2);
           B=B/4;
           G=G/4;
           R=R/4;
           BGR[B][G][R]=2;
           if((BGR[B][G][R]==1)||(BGR1[B][G][R]==1))
           {
               BGR[B][G][R]=1;
               {
                   int b1=B-5,b2=B+5,g1=G-5,g2=G+5,r1=R-5,r2=R+5;
                   int i,j,k;
                   if(b1<0)b1=0;if(g1<0)g1=0;if(r1<0)r1=0;
                   for(i=b1;i<b2&&i<64;i++)
                       for(j=g1;j<g2&&j<64;j++)
                           for(k=r1;k<r2&&k<64;k++)
                               BGR[i][j][k]=1;
               }
           }
           if((BGR[B][G][R]==2)||(BGR1[B][G][R]==2))
           {
               BGR[B][G][R]=2;
               {
                   int b1=B-5,b2=B+5,g1=G-5,g2=G+5,r1=R-5,r2=R+5;
                   int i,j,k;
                   if(b1<0)b1=0;if(g1<0)g1=0;if(r1<0)r1=0;
                   for(i=b1;i<b2&&i<64;i++)
                       for(j=g1;j<g2&&j<64;j++)
                           for(k=r1;k<r2&&k<64;k++)
                               BGR[i][j][k]=2;
               }
           }
           p++;
        }
        for(j=0;j<width_320;j++)
        {
            H=CV_IMAGE_ELEM(Image_Out_HSV_320,unsigned char,i,j*3+0);
            S=CV_IMAGE_ELEM(Image_Out_HSV_320,unsigned char,i,j*3+1);
            V=CV_IMAGE_ELEM(Image_Out_HSV_320,unsigned char,i,j*3+2);
            H=H/4;
            S=S/4;
            V=V/4;
            HSV[H][S][V]=2;
            if(HSV[H][S][V]==2||HSV1[H][S][V]==2)
            {
                HSV[H][S][V]=2;
                int i,j,k;
                int h1=H-2,h2=H+2,s1=S-2,s2=S+2,v1=V-2,v2=V+2;
                if(h1<0)h1=0;if(s1<0)s1=0;if(v1=0)v1=0;
                if(h2>45)h2=44;if(s2>64)s2=63;if(v2>64)v2=63;
                for(i=h1;i<h2;i++)
                    for(j=s1;j<s2;j++)
                        for(k=v1;k<v2;k++)
                            HSV[i][j][k]=2;
            }
            if(HSV[H][S][V]==1||HSV1[H][S][V]==1)
            {
                HSV[H][S][V]=1;
                int i,j,k;
                int h1=H-2,h2=H+2,s1=S-2,s2=S+2,v1=V-2,v2=V+2;
                if(h1<0)h1=0;if(s1<0)s1=0;if(v1=0)v1=0;
                if(h2>45)h2=44;if(s2>64)s2=63;if(v2>64)v2=63;
                for(i=h1;i<h2;i++)
                    for(j=s1;j<s2;j++)
                        for(k=v1;k<v2;k++)
                            HSV[i][j][k]=1;
            }
        }
    }
    qDebug()<<"PPPPP";
    qDebug()<<p;
    save_rgb_file(1);
    save_hsv_file(1);
    {
        int i=0,j=0,k=0;
        for(i=0;i<64;i++)
            for(j=0;j<64;j++)
                for(k=0;k<64;k++)
                {
                   if(HSV[i][j][k]==2)
                       white++;
                   if(HSV[i][j][k]==3)
                       blue++;
                   if(HSV[i][j][k]==1)
                      green++;

                }
    }
}
void save_green()
{
    Image_Out_320=cvCreateImage(cvSize(src->width/2,src->height/2),src->depth,src->nChannels);
    Image_Out_HSV_320=cvCreateImage(cvSize(src->width/2,src->height/2),src->depth,src->nChannels);
    cvResize(Image_Out,Image_Out_320);
    cvResize(Image_Out_HSV,Image_Out_HSV_320);
    int p=0,R,G,B,H,S,V,i,j,width=Image_Out->width,height=Image_Out->height,width_320=Image_Out_320->width,height_320=Image_Out_320->height;
    qDebug()<<"saving.......";
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
           B=CV_IMAGE_ELEM(Image_Out,unsigned char,i,j*3+0);
           G=CV_IMAGE_ELEM(Image_Out,unsigned char,i,j*3+1);
           R=CV_IMAGE_ELEM(Image_Out,unsigned char,i,j*3+2);
           B=B/4;
           G=G/4;
           R=R/4;
           //qDebug()<<B<<G<<R;
           BGR[B][G][R]=1;
           if((BGR[B][G][R]==1)||(BGR1[B][G][R]==1))
           {
               BGR[B][G][R]=1;
               {
                   int b1=B-2,b2=B+2,g1=G-2,g2=G+2,r1=R-2,r2=R+2;
                   int i,j,k;
                   if(b1<0)b1=0;if(g1<0)g1=0;if(r1<0)r1=0;
                   for(i=b1;i<b2&&i<64;i++)
                       for(j=g1;j<g2&&j<64;j++)
                           for(k=r1;k<r2&&k<64;k++)
                               BGR[i][j][k]=1;
               }
           }
           if((BGR[B][G][R]==2)||(BGR1[B][G][R]==2))
           {
               BGR[B][G][R]=2;
               {
                   int b1=B-2,b2=B+2,g1=G-2,g2=G+2,r1=R-2,r2=R+2;
                   int i,j,k;
                   if(b1<0)b1=0;if(g1<0)g1=0;if(r1<0)r1=0;
                   for(i=b1;i<b2&&i<64;i++)
                       for(j=g1;j<g2&&j<64;j++)
                           for(k=r1;k<r2&&k<64;k++)
                               BGR[i][j][k]=2;
               }
           }
           p++;
        }
        for(j=0;j<width;j++)
        {
            H=CV_IMAGE_ELEM(Image_Out_HSV,unsigned char,i,j*3+0);
            S=CV_IMAGE_ELEM(Image_Out_HSV,unsigned char,i,j*3+1);
            V=CV_IMAGE_ELEM(Image_Out_HSV,unsigned char,i,j*3+2);
            H=H/4;
            S=S/4;
            V=V/4;
            HSV[H][S][V]=1;
            if(HSV[H][S][V]==1||HSV1[H][S][V]==1)
            {
                HSV[H][S][V]=1;
                int i,j,k;
                int h1=H-2,h2=H+2,s1=S-2,s2=S+2,v1=V-2,v2=V+2;
                if(h1<0)h1=0;if(s1<0)s1=0;if(v1=0)v1=0;
                if(h2>45)h2=44;if(s2>64)s2=63;if(v2>64)v2=63;
                for(i=h1;i<h2;i++)
                    for(j=s1;j<s2;j++)
                        for(k=v1;k<v2;k++)
                            HSV[i][j][k]=1;
            }
            if(HSV[H][S][V]==2||HSV1[H][S][V]==2)
            {
                HSV[H][S][V]=2;
                int i,j,k;
                int h1=H-2,h2=H+2,s1=S-2,s2=S+2,v1=V-2,v2=V+2;
                if(h1<0)h1=0;if(s1<0)s1=0;if(v1=0)v1=0;
                if(h2>45)h2=44;if(s2>64)s2=63;if(v2>64)v2=63;
                for(i=h1;i<h2;i++)
                    for(j=s1;j<s2;j++)
                        for(k=v1;k<v2;k++)
                            HSV[i][j][k]=2;
            }
        }
    }
    for(i=0;i<height_320;i++)
    {
        for(j=0;j<width_320;j++)
        {
           B=CV_IMAGE_ELEM(Image_Out_320,unsigned char,i,j*3+0);
           G=CV_IMAGE_ELEM(Image_Out_320,unsigned char,i,j*3+1);
           R=CV_IMAGE_ELEM(Image_Out_320,unsigned char,i,j*3+2);
           B=B/4;
           G=G/4;
           R=R/4;
           BGR[B][G][R]=1;
           if((BGR[B][G][R]==1)||(BGR1[B][G][R]==1))
           {
               BGR[B][G][R]=1;
               {
                   int b1=B-2,b2=B+2,g1=G-2,g2=G+2,r1=R-2,r2=R+2;
                   int i,j,k;
                   if(b1<0)b1=0;if(g1<0)g1=0;if(r1<0)r1=0;
                   for(i=b1;i<b2&&i<64;i++)
                       for(j=g1;j<g2&&j<64;j++)
                           for(k=r1;k<r2&&k<64;k++)
                               BGR[i][j][k]=1;
               }
           }
           if((BGR[B][G][R]==2)||(BGR1[B][G][R]==2))
           {
               BGR[B][G][R]=2;
               {
                   int b1=B-2,b2=B+2,g1=G-2,g2=G+2,r1=R-2,r2=R+2;
                   int i,j,k;
                   if(b1<0)b1=0;if(g1<0)g1=0;if(r1<0)r1=0;
                   for(i=b1;i<b2&&i<64;i++)
                       for(j=g1;j<g2&&j<64;j++)
                           for(k=r1;k<r2&&k<64;k++)
                               BGR[i][j][k]=2;
               }
           }
           p++;
        }
        for(j=0;j<width_320;j++)
        {
            H=CV_IMAGE_ELEM(Image_Out_HSV_320,unsigned char,i,j*3+0);
            S=CV_IMAGE_ELEM(Image_Out_HSV_320,unsigned char,i,j*3+1);
            V=CV_IMAGE_ELEM(Image_Out_HSV_320,unsigned char,i,j*3+2);
            H=H/4;
            S=S/4;
            V=V/4;
            HSV[H][S][V]=1;
            if(HSV[H][S][V]==1||HSV1[H][S][V]==1)
            {
                HSV[H][S][V]=1;
                int i,j,k;
                int h1=H-2,h2=H+2,s1=S-2,s2=S+2,v1=V-2,v2=V+2;
                if(h1<0)h1=0;if(s1<0)s1=0;if(v1=0)v1=0;
                if(h2>45)h2=44;if(s2>64)s2=63;if(v2>64)v2=63;
                for(i=h1;i<h2;i++)
                    for(j=s1;j<s2;j++)
                        for(k=v1;k<v2;k++)
                            HSV[i][j][k]=1;
            }
            if(HSV[H][S][V]==2||HSV1[H][S][V]==2)
            {
                HSV[H][S][V]=2;
                int i,j,k;
                int h1=H-2,h2=H+2,s1=S-2,s2=S+2,v1=V-2,v2=V+2;
                if(h1<0)h1=0;if(s1<0)s1=0;if(v1=0)v1=0;
                if(h2>45)h2=44;if(s2>64)s2=63;if(v2>64)v2=63;
                for(i=h1;i<h2;i++)
                    for(j=s1;j<s2;j++)
                        for(k=v1;k<v2;k++)
                            HSV[i][j][k]=2;
            }
        }
    }
    /*{
        int i=0,j=0,k=0,r=0;
        for(i=0;i<64;i++)
            for(j=0;j<64;j++)
                for(k=0;k<64;k++)
                {
                    if(HSV[i][j][k]==1)
                        r++;
                }
        qDebug()<<r;
    }*/
    qDebug()<<"PPPPP";
    qDebug()<<p;
    save_rgb_file(1);
    save_hsv_file(1);
    {
        int i=0,j=0,k=0;
        for(i=0;i<64;i++)
            for(j=0;j<64;j++)
                for(k=0;k<64;k++)
                {
                   if(HSV[i][j][k]==2)
                       white++;
                   if(HSV[i][j][k]==3)
                       blue++;
                   if(HSV[i][j][k]==1)
                      green++;

                }
    }
}
void save_blue()
{
    Image_Out_320=cvCreateImage(cvSize(src->width/2,src->height/2),src->depth,src->nChannels);
    Image_Out_HSV_320=cvCreateImage(cvSize(src->width/2,src->height/2),src->depth,src->nChannels);
    cvResize(Image_Out,Image_Out_320);
    cvResize(Image_Out_HSV,Image_Out_HSV_320);
    int p=0,R,G,B,H,S,V,i,j,width=Image_Out->width,height=Image_Out->height,width_320=Image_Out_320->width,height_320=Image_Out_320->height;
    qDebug()<<"saving.......";
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
           B=CV_IMAGE_ELEM(Image_Out,unsigned char,i,j*3+0);
           G=CV_IMAGE_ELEM(Image_Out,unsigned char,i,j*3+1);
           R=CV_IMAGE_ELEM(Image_Out,unsigned char,i,j*3+2);
           B=B/4;
           G=G/4;
           R=R/4;
           //qDebug()<<B<<G<<R;
           BGR[B][G][R]=3;
           if((BGR[B][G][R]==1)||(BGR1[B][G][R]==1))
           {
               BGR[B][G][R]=1;
               {
                   int b1=B-2,b2=B+2,g1=G-2,g2=G+2,r1=R-2,r2=R+2;
                   int i,j,k;
                   if(b1<0)b1=0;if(g1<0)g1=0;if(r1<0)r1=0;
                   for(i=b1;i<b2&&i<64;i++)
                       for(j=g1;j<g2&&j<64;j++)
                           for(k=r1;k<r2&&k<64;k++)
                               BGR[i][j][k]=1;
               }
           }
           if((BGR[B][G][R]==2)||(BGR1[B][G][R]==2))
           {
               BGR[B][G][R]=2;
               {
                   int b1=B-2,b2=B+2,g1=G-2,g2=G+2,r1=R-2,r2=R+2;
                   int i,j,k;
                   if(b1<0)b1=0;if(g1<0)g1=0;if(r1<0)r1=0;
                   for(i=b1;i<b2&&i<64;i++)
                       for(j=g1;j<g2&&j<64;j++)
                           for(k=r1;k<r2&&k<64;k++)
                               BGR[i][j][k]=2;
               }
           }
           if((BGR[B][G][R]==3)||(BGR1[B][G][R]==3))
           {
               BGR[B][G][R]=3;
               {
                   int b1=B-2,b2=B+2,g1=G-2,g2=G+2,r1=R-2,r2=R+2;
                   int i,j,k;
                   if(b1<0)b1=0;if(g1<0)g1=0;if(r1<0)r1=0;
                   for(i=b1;i<b2&&i<64;i++)
                       for(j=g1;j<g2&&j<64;j++)
                           for(k=r1;k<r2&&k<64;k++)
                               BGR[i][j][k]=3;
               }
           }
           p++;
        }
        for(j=0;j<width;j++)
        {
            H=CV_IMAGE_ELEM(Image_Out_HSV,unsigned char,i,j*3+0);
            S=CV_IMAGE_ELEM(Image_Out_HSV,unsigned char,i,j*3+1);
            V=CV_IMAGE_ELEM(Image_Out_HSV,unsigned char,i,j*3+2);
            H=H/4;
            S=S/4;
            V=V/4;
            HSV[H][S][V]=3;
            if(HSV[H][S][V]==1||HSV1[H][S][V]==1)
            {
                HSV[H][S][V]=1;
                int i,j,k;
                int h1=H-2,h2=H+2,s1=S-2,s2=S+2,v1=V-2,v2=V+2;
                if(h1<0)h1=0;if(s1<0)s1=0;if(v1=0)v1=0;
                if(h2>45)h2=44;if(s2>64)s2=63;if(v2>64)v2=63;
                for(i=h1;i<h2;i++)
                    for(j=s1;j<s2;j++)
                        for(k=v1;k<v2;k++)
                            HSV[i][j][k]=1;
            }
            if(HSV[H][S][V]==2||HSV1[H][S][V]==2)
            {
                HSV[H][S][V]=2;
                int i,j,k;
                int h1=H-2,h2=H+2,s1=S-2,s2=S+2,v1=V-2,v2=V+2;
                if(h1<0)h1=0;if(s1<0)s1=0;if(v1=0)v1=0;
                if(h2>45)h2=44;if(s2>64)s2=63;if(v2>64)v2=63;
                for(i=h1;i<h2;i++)
                    for(j=s1;j<s2;j++)
                        for(k=v1;k<v2;k++)
                            HSV[i][j][k]=2;
            }
            if(HSV[H][S][V]==3||HSV1[H][S][V]==3)
            {
                HSV[H][S][V]=3;
                int i,j,k;
                int h1=H-2,h2=H+2,s1=S-2,s2=S+2,v1=V-2,v2=V+2;
                if(h1<0)h1=0;if(s1<0)s1=0;if(v1=0)v1=0;
                if(h2>45)h2=44;if(s2>64)s2=63;if(v2>64)v2=63;
                for(i=h1;i<h2;i++)
                    for(j=s1;j<s2;j++)
                        for(k=v1;k<v2;k++)
                            HSV[i][j][k]=3;
            }
        }
    }
    save_rgb_file(1);
    save_hsv_file(1);
    {
        int i=0,j=0,k=0;
        for(i=0;i<64;i++)
            for(j=0;j<64;j++)
                for(k=0;k<64;k++)
                {
                   if(HSV[i][j][k]==2)
                       white++;
                   if(HSV[i][j][k]==3)
                       blue++;
                   if(HSV[i][j][k]==1)
                      green++;

                }
    }
}
void Choose_Color(int event, int x, int y, int flag, void*param)
{
    pt2=cvPoint(x,y);
    switch(event)
    {
    case CV_EVENT_LBUTTONDOWN:
          {
              if(drawing_box==0)
              {
                  drawing_box=1;
                  pt1=cvPoint(x,y);
              }
          }
    case CV_EVENT_MOUSEMOVE:
         {
              if(drawing_box)
                 Draw_Rect(pt1,pt2);
         }
    case CV_EVENT_LBUTTONUP:
         {
              if(drawing_box)
              {
                  Draw_Rect(pt1,pt2);
                  on_choosing=0;
                  drawing_box=0;
              }
         }
    }
}
/*void file_color_table::stop()
{
    on_choosing=1;
    video_stop=1;
    src=cvCreateImage(cvSize(640,480),frame->depth,frame->nChannels);
    dst=cvCreateImage(cvSize(640,480),frame->depth,frame->nChannels);
    cvResize(frame,src);
    cvResize(frame,dst);
    cvShowImage("Video_Show",src);
    //cvSetMouseCallback("Video_Show",Choose_Color);
}*/
void Draw_Rect(CvPoint PT1,CvPoint PT2)
{
      int x=PT1.x,y=PT1.y,width,height;
      CvPoint pt=cvPoint(x,y);
      if(PT1.x>PT2.x)
      {
          PT1.x=PT2.x;
          PT2.x=x;
      }
      if(PT1.y>PT2.y)
      {
          PT1.y=PT2.y;
          PT2.y=y;
      }
      height=abs(PT2.y-PT1.y);
      width=abs(PT2.x-PT1.x);
      cvResetImageROI(src);
      cvCopy(src,dst);
      cvRectangle(dst,PT1,PT2,cvScalar(255,255,255),1);
      cvShowImage("Video_Show",dst);
      CvRect rect=cvRect(PT1.x,PT1.y,width,height);
      cvSetImageROI(src,rect);
      CvSize sz=cvSize(width,height);
      Image_Out=cvCreateImage(sz,src->depth,src->nChannels);
  //    Image_Out_320=cvCreateImage(cvSize(src->width/2,src->height/2),src->depth,src->nChannels);
      Image_Out_HSV=cvCreateImage(sz,src->depth,src->nChannels);
  //    Image_Out_HSV_320=cvCreateImage(cvSize(src->width/2,src->height/2),src->depth,src->nChannels);
      cvCopy(src,Image_Out);
      cvSmooth(Image_Out,Image_Out);
  //    cvResize(Image_Out,Image_Out_320);
      cvCvtColor(Image_Out,Image_Out_HSV,CV_BGR2HSV);
  //    cvResize(Image_Out_HSV,Image_Out_HSV_320);
      cvWaitKey(30);
}
bool save_rgb_file(int flag)
{
    FILE *file;
    if((file=fopen(rgb_file,"w"))==NULL)
    {
        qDebug()<<"open the rgb_file failed";
        return 0;
    }
    if(flag==1)
    {
        if((fwrite(BGR,64*sizeof(int),64*64,file))==-1)
           {
               qDebug()<<"write the file failed";
               return 0;
           }
        else
               qDebug()<<"write the file succeed";
    }
    else if(flag==0)
    {
        if((fwrite(Zero,64*sizeof(int),64*64,file))==-1)
        {
            qDebug()<<"write the rgb_file failed";
            return 0;
        }
        else
            qDebug()<<"write the file succeed";

    }
    fclose(file);
    qDebug()<<"rgb_file saved";
    return 1;
}
bool save_hsv_file(int flag)
{
    FILE *file;
    if((file=fopen(hsv_file,"w"))==NULL)
    {
        qDebug()<<"open the hsv_file failed";
        return 0;
    }
    if(flag==1)
    {
        if((fwrite(HSV,64*sizeof(int),64*64,file))==-1)
        {
            qDebug()<<"write hsv_file failed";
            return 0;
        }
        else
            qDebug()<<"write hsv_file succeed";
    }
    else if(flag==0)
    {
        if((fwrite(Zero,64*sizeof(int),64*64,file))==-1)
        {
            qDebug()<<"write hsv_file failed";
            return 0;
        }
        else
            qDebug()<<"write hsv_file succeed";
    }

    fclose(file);
    qDebug()<<"hsv_file saved";
    return 1;
}
bool read_rgb_file()
{
    FILE *file;
    if((file=fopen(rgb_file,"r"))==NULL)
    {
        qDebug()<<"open the file failed";
        return 0;
    }

    if((fread(ym,64*sizeof(int),64*64,file))==-1)
    {
        qDebug()<<"read the file failed";
        return 0;
    }
    else
        qDebug()<<"read the file successfully";
    fclose(file);
    return 1;
}
bool read_hsv_file()
{
    FILE *file;
    if((file=fopen(hsv_file,"r"))==NULL)
    {
        qDebug()<<"open the file failed";
        return 0;
    }

    if((fread(ym_hsv,64*sizeof(int),64*64,file))==-1)
    {
        qDebug()<<"read the file failed";
        return 0;
    }
    else
        qDebug()<<"read the file successful";
    fclose(file);
    return 1;
}
void test_rgb()
{
    frame_temp=cvCloneImage(frame);
    read_rgb_file();
    Image_test=cvCreateImage(cvSize(frame_temp->width/2,frame_temp->height/2),frame_temp->depth,frame_temp->nChannels);
    cvResize(frame_temp,Image_test);
    cvSmooth(Image_test,Image_test);
    Image_test_gray=cvCreateImage(cvGetSize(Image_test),Image_test->depth,1);
    cvCvtColor(Image_test,Image_test_gray,CV_RGB2GRAY);
    int width,height,step;
    width=Image_test->width;
    height=Image_test->height;
    step=Image_test_gray->widthStep/sizeof(char);
    int R,G,B;
    //char *data=Image_test_gray->imageData;
        //cvNamedWindow("test_green");
       // cvShowImage("test_green",Image_test_gray);
        //cvWaitKey(0);
        //cvShowImage("test_green",Image_test);
        //cvWaitKey(0);
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            B=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+0);
            G=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+1);
            R=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+2);
            B=B/4;
            G=G/4;
            R=R/4;
            if(ym[B][G][R]==1)
            {
                CV_IMAGE_ELEM(Image_test_gray, unsigned char, i, j) = 255;

            }
            else
            {
                CV_IMAGE_ELEM(Image_test_gray, unsigned char, i, j ) = 0;

            }

        }
    }
    cvShowImage("test_rgb_green",Image_test_gray);
    cvWaitKey(0);
    cvDestroyWindow("test_rgb_green");
//white!!!
    cvNamedWindow("test_rgb_white");
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            B=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+0);
            G=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+1);
            R=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+2);
            B=B/4;
            G=G/4;
            R=R/4;
            if(ym[B][G][R]==2)
            {
                CV_IMAGE_ELEM(Image_test_gray, unsigned char, i, j) = 255;

            }
            else
            {
                CV_IMAGE_ELEM(Image_test_gray, unsigned char, i, j ) = 0;

            }

        }
    }
        cvShowImage("test_rgb_white",Image_test_gray);
        cvWaitKey(0);
        cvDestroyWindow("test_rgb_white");
//blue
        cvNamedWindow("test_rgb_blue");
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            B=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+0);
            G=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+1);
            R=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+2);
            B=B/4;
            G=G/4;
            R=R/4;
            if(ym[B][G][R]==3)
            {
                CV_IMAGE_ELEM(Image_test_gray, unsigned char, i, j) = 255;

            }
            else
            {
                CV_IMAGE_ELEM(Image_test_gray, unsigned char, i, j ) = 0;

            }

        }
    }
    cvShowImage("test_rgb_blue",Image_test_gray);
    cvWaitKey(0);
    cvDestroyWindow("test_rgb_blue");
    cvReleaseImage(&frame_temp);
    cvReleaseImage(&Image_test);
    cvReleaseImage(&Image_test_gray);
    return;
}
void test_hsv()
{
    frame_temp=cvCloneImage(frame);
    read_hsv_file();
    Image_test=cvCreateImage(cvSize(frame_temp->width/2,frame_temp->height/2),frame_temp->depth,frame_temp->nChannels);
    cvResize(frame_temp,Image_test);
    cvCvtColor(Image_test,Image_test,CV_BGR2HSV);
    Image_test_gray=cvCreateImage(cvGetSize(Image_test),Image_test->depth,1);
    int width,height,step;
    width=Image_test->width;
    height=Image_test->height;
    step=Image_test_gray->widthStep/sizeof(char);
    int H,S,V;//r;
//    char *data=Image_test_gray->imageData;
        cvShowImage("test_hsv_green",Image_test);
        cvWaitKey(0);
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            H=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+0);
            S=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+1);
            V=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+2);
            H=H/4;
            S=S/4;
            V=V/4;
            if(ym_hsv[H][S][V]==1)
            {
                CV_IMAGE_ELEM(Image_test_gray, unsigned char, i, j) = 255;


            }
            else
            {
                CV_IMAGE_ELEM(Image_test_gray, unsigned char, i, j ) = 0;

            }


        }
    }
    cvShowImage("test_hsv_green",Image_test_gray);
    cvWaitKey(0);
    cvDestroyWindow("test_hsv_green");
//white
    cvNamedWindow("test_hsv_white");
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            H=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+0);
            S=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+1);
            V=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+2);
            H=H/4;
            S=S/4;
            V=V/4;
            if(ym_hsv[H][S][V]==2)
            {
                CV_IMAGE_ELEM(Image_test_gray, unsigned char, i, j) = 255;

            }
            else
            {
                CV_IMAGE_ELEM(Image_test_gray, unsigned char, i, j ) = 0;

            }
        }
    }
    cvShowImage("test_hsv_white",Image_test_gray);
    cvWaitKey(0);
    cvDestroyWindow("test_hsv_white");
//blue
    cvNamedWindow("test_hsv_blue");
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            H=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+0);
            S=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+1);
            V=CV_IMAGE_ELEM(Image_test,unsigned char,i,j*3+2);
            H=H/4;
            S=S/4;
            V=V/4;
            if(ym_hsv[H][S][V]==3)
            {
                CV_IMAGE_ELEM(Image_test_gray, unsigned char, i, j) = 255;

            }
            else
            {
                CV_IMAGE_ELEM(Image_test_gray, unsigned char, i, j ) = 0;

            }
        }
    }
    cvShowImage("test_hsv_blue",Image_test_gray);
    cvWaitKey(0);
    cvDestroyWindow("test_hsv_blue");
    cvReleaseImage(&frame_temp);
    cvReleaseImage(&Image_test);
    cvReleaseImage(&Image_test_gray);
    return;
}
void video_test_rgb()
{
    char c=0;
    cvNamedWindow("Video_Test",1);
    read_rgb_file();
   while(1)
   {
       int width,height;//widthStep;
       frame_test=cvQueryFrame(capture);
       frame_test_gray=cvCreateImage(cvGetSize(frame_test),frame_test->depth,3);
       width=frame_test->width;
       height=frame_test->height;
       int R,G,B;
       for(int i=0;i<height;i++)
       {
           for(int j=0;j<width;j++)
           {
               B=CV_IMAGE_ELEM(frame_test,unsigned char,i,j*3+0);
               G=CV_IMAGE_ELEM(frame_test,unsigned char,i,j*3+1);
               R=CV_IMAGE_ELEM(frame_test,unsigned char,i,j*3+2);
               B=B/4;
               G=G/4;
               R=R/4;
               if(ym[B][G][R]==1)
               {
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+0) = 0;
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+1) = 255;
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+2) = 0;
               }
               else if(ym[B][G][R]==2)
               {
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+0) = 255;
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+1) = 255;
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+2) = 255;
               }
               else if(ym[B][G][R]==3)
               {
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+0) =255;
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+1) =0;
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+2) = 0;
               }
               else
               {
                   CV_IMAGE_ELEM(frame_test_gray,unsigned char,i,j*3+0)=0;
                    CV_IMAGE_ELEM(frame_test_gray,unsigned char,i,j*3+1)=0;
                     CV_IMAGE_ELEM(frame_test_gray,unsigned char,i,j*3+2)=0;
               }
            }
        }
       cvShowImage("Video_Test",frame_test_gray);
       c=cvWaitKey(33);
       if(c==27) break;
   }
   cvDestroyAllWindows();
   return;
}
void video_test_hsv()
{
    char c=0;
    cvNamedWindow("Video_Test",1);
    read_hsv_file();
   while(1)
   {
       int width,height;
       frame_test=cvQueryFrame(capture);
       frame_test_gray=cvCreateImage(cvGetSize(frame_test),frame_test->depth,3);
       width=frame_test->width;
       height=frame_test->height;
       int H,S,V;
       for(int i=0;i<height;i++)
       {
           for(int j=0;j<width;j++)
           {
               H=CV_IMAGE_ELEM(frame_test,unsigned char,i,j*3+0);
               S=CV_IMAGE_ELEM(frame_test,unsigned char,i,j*3+1);
               V=CV_IMAGE_ELEM(frame_test,unsigned char,i,j*3+2);
               H=H/4;
               S=S/4;
               V=V/4;
               if(ym_hsv[H][S][V]==1)
               {
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+0) = 0;
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+1) = 255;
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+2) = 0;
               }
               else if(ym_hsv[H][S][V]==2)
               {
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+0) = 255;
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+1) = 255;
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+2) = 255;
               }
               else if(ym_hsv[H][S][V]==3)
               {
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+0) = 255;
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+1) = 0;
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+2) = 0;
               }
               else
               {
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+0) = 0;
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+1) = 0;
                   CV_IMAGE_ELEM(frame_test_gray, unsigned char, i, j*3+2) = 0;
               }
           }
       }
       cvShowImage("Video_Test",frame_test_gray);
       c=cvWaitKey(33);
       if(c==27) break;
   }
   cvDestroyAllWindows();
   return;
}
void Average_HSV()
{
    int X_Index,Y_Index;
    for(X_Index=0;X_Index<Image_Out_HSV->height;X_Index++)
        for(Y_Index=0;Y_Index<Image_Out_HSV->width;Y_Index++)
        {
            H+=CV_IMAGE_ELEM(Image_Out_HSV,unsigned char,X_Index,Y_Index*3+0);
            S+=CV_IMAGE_ELEM(Image_Out_HSV,unsigned char,X_Index,Y_Index*3+1);
            V+=CV_IMAGE_ELEM(Image_Out_HSV,unsigned char,X_Index,Y_Index*3+2);
        }
    H=(int)H/(Image_Out_HSV->width*Image_Out_HSV->height);
    S=(int)S/(Image_Out_HSV->width*Image_Out_HSV->height);
    V=(int)V/(Image_Out_HSV->width*Image_Out_HSV->height);
}
bool Save_Image()
{
    if(cvSaveImage("Image_Save.jpg",frame)==0)
        return false;
    else
        return true;
}
bool Image_In()
{
    if(!(frame=cvLoadImage("Image_Save.jpg",1)))
       return false;
    frame_temp=cvCloneImage(frame);
    cvShowImage("Video_Show",frame);
    on_choosing=1;
    video_stop=1;
    src=cvCloneImage(frame);
    dst=cvCloneImage(frame);
    cvSetMouseCallback("Video_Show",Choose_Color);
    return true;
}
