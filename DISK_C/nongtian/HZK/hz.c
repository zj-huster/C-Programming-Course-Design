/**************************************************
    Description:Han Zi Library
    Creator:Zhu Jin
    Creative Time:2025.2.15
    Last Modify Time:2025.2.15
    Version:2.0
**************************************************/

/**************************************************
    DESCRIPTION:汉字库显示函数，显示指定汉字字符串
    KeyIn:  x 和 y：指定汉字显示的起始坐标
            s：指向要显示的汉字字符串，汉字以GB2312编码存储,每个汉字占两个字节
            flag：指定汉字的点阵大小，可以是16、24、32或48
            part：指定每个汉字之间的间隔，即汉字之间的空白区域的宽度
            color：指定汉字的颜色
    RETURN: 无
**************************************************/

#include <graphics.h> 
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"HZ.h"

void hz(int x, int y, char *s, int flag, int part, int color)
{
    FILE *hzk_p = NULL;//用于打开和操作汉字点阵库文件
    unsigned char qm, wm;//存储汉字的区码和位码
    unsigned long offset;
    //存储汉字在汉字库中的偏移量。汉字点阵库文件中，每个汉字的点阵数据存储在特定的位置
    //偏移位置由区码和位码计算得出，用于快速定位到文件中对应汉字的点阵数据
    unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    //用于提取汉字点阵数据中的每个点的信息
    int i, j, pos;
    //用于循环计数（行和列的遍历）

    switch (flag)
    {
        case 16:
        {
            char mat[32];   // 用于存储16×16点阵数据，每个字节表示8个像素，16×16点阵需要32字节
            int x0 = x;     // 保存初始的x坐标, 用于换行
            int y0 = y;     // 保存初始的y坐标, 用于换行

            hzk_p = fopen("HZK\\HZ16", "rb"); // 打开16×16点阵文件, 以二进制方式读取
            if (hzk_p == NULL)
            {
                settextjustify(LEFT_TEXT,TOP_TEXT);//设置左对齐，上对齐
				settextstyle(GOTHIC_FONT,HORIZ_DIR,3);//设置字体样式，横向排列，字号
                outtextxy(10, 10, "Can't open hzk16 file!Press any key to exit...");
                getch();
                exit(1);
            }
            while ( *s ) {
                //当未到字符串结束时并且未超出屏幕宽度时
                while (x < (640 - flag) && *s ) {
                    /*处理单个汉字*/
                    y=y0; // 每个汉字的绘制起始纵坐标
                    //在 GB2312 编码中，一个汉字由两个字节表示，这两个字节分别代表区码和位码
                    //第一个字节（s[0]）：表示区码。
                    //第二个字节（s[1]）：表示位码。
                    //转换为从 1 开始的索引（汉字点阵库文件中的数据是按从 1 开始的索引存储的），
                    //需要减去 0xA0（十进制的 160）
                    qm = s[0] - 0xA0; // 区码
                    wm = s[1] - 0xA0; // 位码
                    offset = (94 * (qm - 1) + (wm - 1)) * 32L; // 计算偏移量

                    //读取点阵数据
                    fseek(hzk_p, offset, SEEK_SET); // 定位到文件中的偏移位置
                    fread(mat, 32, 1, hzk_p);// 读取32字节（16*16点阵，8个像素一个字节）数据到数组mat

                    //绘制点阵
                    for (i = 0; i < 16; i++) {
                        pos = 2 * i; // 当前行的起始位置（每行16个像素，两个字节）
                        for (j = 0; j < 16; j++) {
                            if ((mask[j % 8] & mat[pos + j / 8]) != NULL) {
                                putpixel(x + j, y, color);
                            }
                        }
                        y++;
                    }

                    //更新绘制位置
                    x += part; // 更新x坐标，向右移动part个像素
                    s += 2;// 指向下一个汉字，字符串指针向后移动2个字节
                }
                x = x0;//横坐标复位
                y0 += flag + 10; //纵坐标换行，两行汉字之间的竖直间隔为10，汉字高度为flag
            }

            fclose(hzk_p);

            break;
        }

        case 24 :
        {
            char mat[72];
            int y0=y;
            int x0=x;

            hzk_p = fopen("HZK\\Hzk24k","rb");

            if (hzk_p == NULL)
            {
                settextjustify(LEFT_TEXT,TOP_TEXT);//设置左对齐，上对齐
                settextstyle(GOTHIC_FONT,HORIZ_DIR,3);//设置字体样式，横向排列，字号
                outtextxy(10, 10, "Can't open hzk24 file!Press any key to exit...");
                getch();
                exit(1);

            }
            while( *s )
            {
                while( x < (640-flag) && *s)
                {
                    y=y0;
                    qm = s[0] - 0xA0; // 区码
                    wm = s[1] - 0xA0; // 位码
                    offset = (94 * (qm - 1) + (wm - 1)) * 72L; // 计算偏移量
                    fseek(hzk_p,offset,SEEK_SET);
                    fread (mat,72,1,hzk_p);
                    for (i=0;i<24;i++)
                    {
                        pos=3*i;
                        for (j=0;j<24;j++)
                        {
                            if ((mask[j%8]&mat[pos+j/8])!=NULL)
                                putpixel(x+j,y,color);

                        }
                        y++;
                    }
                    x+=part;
                    s+=2;
                }
                x = x0;
                y0 += flag + 10;
            }

            fclose(hzk_p);

            break;
        }

		case 32 :
        {
            char mat[128];
            int y0=y;
            int x0=x;

            hzk_p = fopen("HZK\\HZK32S","rb");
            if(hzk_p==NULL)
            {
                settextjustify(LEFT_TEXT,TOP_TEXT);
                settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
                outtextxy(10,10,"Can't open hzk32 file!Press any key to quit...");
                getch();
                exit(1);

            }
            while( *s )
            {
                while ( x < 640-flag && *s)
                {
                    y=y0;
                    qm=s[0]-0xa0;
                    wm=s[1]-0xa0;
                    offset=(94*(qm-1)+(wm-1))*128L;

                    fseek(hzk_p,offset,SEEK_SET);
                    fread (mat,128,1,hzk_p);

                    for(i=0;i<32;i++)
                    {
                        pos=4*i;
                        for(j=0;j<32;j++)
                        {
                            if((mask[j%8]&mat[pos+j/8])!=NULL)
                            {
                                putpixel(x+j,y,color);
                            }
                        }

                        y++;
                    }
                    x += part;
                    s += 2;

                }
                x = x0;
                y0 += flag+10;
            }

            fclose(hzk_p);

            break;
        }

		case 48:
        {
            char mat[288];
            int y0=y;
            int x0=x;

            hzk_p = fopen("HZK\\Hzk48k","rb");
            if(hzk_p == NULL)
            {
                settextjustify(LEFT_TEXT,TOP_TEXT);
                settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
                outtextxy(10,10,"Can't open hzk48 file!Press any key to quit...");
                getch();
                exit(1);

            }
            while( *s )
            {
                while ( x < 640-flag && *s)
                {
                    y=y0;
                    qm=s[0]-0xa0;
                    wm=s[1]-0xa0;
                    offset=(94*(qm-1)+(wm-1))*288L;

                    fseek(hzk_p,offset,SEEK_SET);
                    fread (mat,288,1,hzk_p);

                    for(i=0;i<48;i++)
                    {
                        pos=6*i;
                        for(j=0;j<48;j++)
                        {
                            if((mask[j%8]&mat[pos+j/8])!=NULL)
                            {
                                putpixel(x+j,y,color);
                            }
                        }
                        y++;
                    }
                    x += part;
                    s += 2;

                }
                x = x0;
                y0 += flag+10;
            }

            fclose(hzk_p);

            break;
        }
    } 
}