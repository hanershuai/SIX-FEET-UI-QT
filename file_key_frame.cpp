#include "file_key_frame.h"

file_key_frame::file_key_frame()
{

}
bool file_key_frame::save_file(const char *filename, QList<int *> list)
{
    FILE* fstream;
    time_t timep;
    time (&timep);
    char * c_time = ctime(&timep);
    const char * en = "\r\n";
    char length = list.length();
       fstream=fopen(filename,"w+");
       if(fstream==NULL)
       {
       printf("open file test.txt failed!\n");
       }
       else
       {
       printf("open file test.txt succeed!\n");
       fwrite(c_time, sizeof(char),24,fstream);
       fwrite(en, sizeof(char),2,fstream);
       fwrite(&length, sizeof(char),1,fstream);
       fwrite(en, sizeof(char),2,fstream);
       for(int i=0;i<list.length();i++)
       {
           fwrite(list.at(i), sizeof(int),22,fstream);
           fwrite(en, sizeof(char),2,fstream);
           //qDebug()<<"my send ="<<"="<<*(my.at(index.row())+j);
       }
       //fread(c_time, sizeof(char),24,fstream);
      // fseek(fstream,2,SEEK_CUR);
       //fgets(r_1,25,fstream);
       }
       fclose(fstream);
       return true;
}
bool file_key_frame::save_file_Txt(const char *filename,int length, int angle[24][22],int speed[10])
{
    FILE* fstream;
    time_t timep;
    time (&timep);
       fstream=fopen(filename,"w+");
       if(fstream==NULL)
       {
       printf("open file test.txt failed!\n");
       }
       else
       {
       printf("open file test.txt succeed!\n");
       fprintf(fstream,"right_kick 2018.03.08");
       fprintf(fstream,"\n");
        for(int j=0;j<length;j++)
        {
            fprintf(fstream,"// step%d 100\n512,20,",j+1);
       for(int i=2;i<=21;i++)
       {
           if(angle[j+1][0]!=2048)
           {
               fprintf(fstream,"// step%d 100\n512,20,",j+1);
               for(int k=2;k<=21;k++)

               {
                    fprintf(fstream,"%d,",angle[0][k]);
                    fprintf(fstream,"%d,",speed[0]);
                    if(k==11) fprintf(fstream,"\n");
               }
               break;
           };
           fprintf(fstream,"%d,",angle[j][i]);

           if(j<11)
           fprintf(fstream,"%d,",speed[j]);

           if(j>11)
               fprintf(fstream,"500,");

           if(i==11) fprintf(fstream,"\n");
       }
       fprintf(fstream,"\n");
        }
       }
       fclose(fstream);
       return true;
}
bool file_key_frame::save_Txt_Insert(const char *filename, int length, int angle[24][22], int speed[10])
{
    FILE* fstream;
    time_t timep;
    time (&timep);
       fstream=fopen(filename,"w+");
       if(fstream==NULL)
       {
       printf("open file test.txt failed!\n");
       }
       else
       {
       printf("open file test.txt succeed!\n");
       fprintf(fstream,"right_kick 2018.03.08");
       fprintf(fstream,"\n");
        for(int j=0;j<length;j++)
        {
            fprintf(fstream,"// step%d 20\n512,20,",j+1);
       for(int i=2;i<=21;i++)
       {
           if(angle[j+1][0]!=2048)
           {
               for(int p=1;p<=10;p++)
                    {
                   fprintf(fstream,"// step%d 20\n512,20,",j+1);
                   for(int q=2;q<=21;q++)
                   {
                        fprintf(fstream,"%d,",(int)(p*(angle[0][q]-angle[j][q])/10+angle[j][q]));
                        fprintf(fstream,"%d,",speed[0]);
                        if(q==10) fprintf(fstream,"\n");
                   }
                   fprintf(fstream,"\n");
                    }
               fprintf(fstream,"// step%d 20\n512,20,",j+1);
               for(int k=2;k<=21;k++)

               {
                    fprintf(fstream,"%d,",angle[0][k]);
                    fprintf(fstream,"%d,",speed[0]);
                    if(k==11) fprintf(fstream,"\n");
               }
               break;
           };
           fprintf(fstream,"%d,",angle[j][i]);

           if(j<11)
           fprintf(fstream,"%d,",speed[j]);

           if(j>11)
               fprintf(fstream,"500,");

           if(i==11) fprintf(fstream,"\n");
       }
       for(int m=1;m<=10;m++)
            {
           if(angle[j+1][0]!=2048) break;
           fprintf(fstream,"\n");
           fprintf(fstream,"// step%d 20\n512,20,",j+1);
           for(int n=2;n<=21;n++)
           {
                fprintf(fstream,"%d,",(int)(m*(angle[j+1][n]-angle[j][n])/10+angle[j][n]));
                fprintf(fstream,"%d,",speed[j]);
                if(n==11) fprintf(fstream,"\n");
           }
            }
       fprintf(fstream,"\n");
        }
       }
       fclose(fstream);
       return true;
}
char file_key_frame::read_file(const char *filename, QList<int *> list, int angle[24][22])
{
    FILE* fstream;
    time_t timep;
    time (&timep);
    char * c_time = ctime(&timep);//c_time is time now;
    char length = 0;//length is the number of frames;

       fstream=fopen(filename,"r+");
       if(fstream==NULL)
       {
       printf("open file test.txt failed!\n");
       }
       else
       {
       printf("open file test.txt succeed!\n");
       fread(c_time, sizeof(char),24,fstream);
       fseek(fstream,2,SEEK_CUR);
       fread(&length, sizeof(char),1,fstream);
       fseek(fstream,2,SEEK_CUR);
       qDebug()<<"length = "<<int (length);
       list.clear();
       for(int i=0;i<int (length);i++)
       {
           list.append(angle[i]);
       }
       for(int i=0;i<int (length);i++)
       {
           fread(list[i], sizeof(int),22,fstream);
           fseek(fstream,2,SEEK_CUR);
       }
       for(int i=0;i<list.length();i++)
       for(int j=0;j<22;j++)
       {
           qDebug()<<"angle = "<<i<<j<<"="<<angle[i][j];
       }
       //fread(c_time, sizeof(char),24,fstream);
      // fseek(fstream,2,SEEK_CUR);
       //fgets(r_1,25,fstream);
       }
       fclose(fstream);
       return length;
}
bool file_key_frame::save_binary_Insert(const char *filename,int length, int angle[24][22])
{
    FILE* fstream;
    time_t timep;
    time (&timep);
    char * c_time = ctime(&timep);
    const char * en = "\r\n";
    QList <int *>list;
    int angle_temp[110][22];
    for(int i=0;i<length-1;i++)
    {
        for(int j=0;j<10;j++)
        {
            /*if(i==2)
            {
               for(int n=0;n<2;n++)
               angle_temp[i*10+j][n]=2048;
               for(int k=2;k<22;k++)
               angle_temp[i*10+j][k]=angle[i][k];
            }
           else*/
           { for(int n=0;n<2;n++)
                angle_temp[i*10+j][n]=2048;
            for(int k=2;k<22;k++)
                angle_temp[i*10+j][k]=angle[i][k]+(angle[i+1][k]-angle[i][k])*j/9;
            }
        }
    }
    for(int l=0;l<22;l++)
    {
        angle_temp[(length-1)*10][l]=angle[length-1][l];
        //qDebug()<<angle_temp[(length-1)*10][l]<<endl;
    }
    for(int p=0;p<=(length-1)*10;p++)
    {
        list.append(angle_temp[p]);
    }
//    char length = list.length();
       fstream=fopen(filename,"w+");
       if(fstream==NULL)
       {
       printf("open file test.txt failed!\n");
       }
       else
       {
       length=(length-1)*10;
       printf("open file test.txt succeed!\n");
       fwrite(c_time, sizeof(char),24,fstream);
       fwrite(en, sizeof(char),2,fstream);
       fwrite(&length, sizeof(char),1,fstream);
       fwrite(en, sizeof(char),2,fstream);
        //qDebug()<<list.length()<<endl;
        //qDebug()<<"0000"<<endl;
       for(int i=0;i<list.length();i++)
       {
           fwrite(list.at(i), sizeof(int),22,fstream);
           //qDebug()<<list.at(i)<<endl;
          // qDebug()<<"0000";
           fwrite(en, sizeof(char),2,fstream);
           //qDebug()<<"my send ="<<"="<<*(my.at(index.row())+j);
       }
       //fread(c_time, sizeof(char),24,fstream);
      // fseek(fstream,2,SEEK_CUR);
       //fgets(r_1,25,fstream);
       }
       fclose(fstream);
       return true;
}
