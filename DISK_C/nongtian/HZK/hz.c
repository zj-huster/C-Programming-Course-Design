/**************************************************
    Description:Han Zi Library
    Creator:Zhu Jin
    Creative Time:2025.2.15
    Last Modify Time:2025.2.15
    Version:2.0
**************************************************/

/**************************************************
    DESCRIPTION:���ֿ���ʾ��������ʾָ�������ַ���
    KeyIn:  x �� y��ָ��������ʾ����ʼ����
            s��ָ��Ҫ��ʾ�ĺ����ַ�����������GB2312����洢,ÿ������ռ�����ֽ�
            flag��ָ�����ֵĵ����С��������16��24��32��48
            part��ָ��ÿ������֮��ļ����������֮��Ŀհ�����Ŀ��
            color��ָ�����ֵ���ɫ
    RETURN: ��
**************************************************/

#include <graphics.h> 
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"HZ.h"

void hz(int x, int y, char *s, int flag, int part, int color)
{
    FILE *hzk_p = NULL;//���ڴ򿪺Ͳ������ֵ�����ļ�
    unsigned char qm, wm;//�洢���ֵ������λ��
    unsigned long offset;
    //�洢�����ں��ֿ��е�ƫ���������ֵ�����ļ��У�ÿ�����ֵĵ������ݴ洢���ض���λ��
    //ƫ��λ���������λ�����ó������ڿ��ٶ�λ���ļ��ж�Ӧ���ֵĵ�������
    unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    //������ȡ���ֵ��������е�ÿ�������Ϣ
    int i, j, pos;
    //����ѭ���������к��еı�����

    switch (flag)
    {
        case 16:
        {
            char mat[32];   // ���ڴ洢16��16�������ݣ�ÿ���ֽڱ�ʾ8�����أ�16��16������Ҫ32�ֽ�
            int x0 = x;     // �����ʼ��x����, ���ڻ���
            int y0 = y;     // �����ʼ��y����, ���ڻ���

            hzk_p = fopen("HZK\\HZ16", "rb"); // ��16��16�����ļ�, �Զ����Ʒ�ʽ��ȡ
            if (hzk_p == NULL)
            {
                settextjustify(LEFT_TEXT,TOP_TEXT);//��������룬�϶���
				settextstyle(GOTHIC_FONT,HORIZ_DIR,3);//����������ʽ���������У��ֺ�
                outtextxy(10, 10, "Can't open hzk16 file!Press any key to exit...");
                getch();
                exit(1);
            }
            while ( *s ) {
                //��δ���ַ�������ʱ����δ������Ļ���ʱ
                while (x < (640 - flag) && *s ) {
                    /*����������*/
                    y=y0; // ÿ�����ֵĻ�����ʼ������
                    //�� GB2312 �����У�һ�������������ֽڱ�ʾ���������ֽڷֱ���������λ��
                    //��һ���ֽڣ�s[0]������ʾ���롣
                    //�ڶ����ֽڣ�s[1]������ʾλ�롣
                    //ת��Ϊ�� 1 ��ʼ�����������ֵ�����ļ��е������ǰ��� 1 ��ʼ�������洢�ģ���
                    //��Ҫ��ȥ 0xA0��ʮ���Ƶ� 160��
                    qm = s[0] - 0xA0; // ����
                    wm = s[1] - 0xA0; // λ��
                    offset = (94 * (qm - 1) + (wm - 1)) * 32L; // ����ƫ����

                    //��ȡ��������
                    fseek(hzk_p, offset, SEEK_SET); // ��λ���ļ��е�ƫ��λ��
                    fread(mat, 32, 1, hzk_p);// ��ȡ32�ֽڣ�16*16����8������һ���ֽڣ����ݵ�����mat

                    //���Ƶ���
                    for (i = 0; i < 16; i++) {
                        pos = 2 * i; // ��ǰ�е���ʼλ�ã�ÿ��16�����أ������ֽڣ�
                        for (j = 0; j < 16; j++) {
                            if ((mask[j % 8] & mat[pos + j / 8]) != NULL) {
                                putpixel(x + j, y, color);
                            }
                        }
                        y++;
                    }

                    //���»���λ��
                    x += part; // ����x���꣬�����ƶ�part������
                    s += 2;// ָ����һ�����֣��ַ���ָ������ƶ�2���ֽ�
                }
                x = x0;//�����긴λ
                y0 += flag + 10; //�����껻�У����к���֮�����ֱ���Ϊ10�����ָ߶�Ϊflag
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
                settextjustify(LEFT_TEXT,TOP_TEXT);//��������룬�϶���
                settextstyle(GOTHIC_FONT,HORIZ_DIR,3);//����������ʽ���������У��ֺ�
                outtextxy(10, 10, "Can't open hzk24 file!Press any key to exit...");
                getch();
                exit(1);

            }
            while( *s )
            {
                while( x < (640-flag) && *s)
                {
                    y=y0;
                    qm = s[0] - 0xA0; // ����
                    wm = s[1] - 0xA0; // λ��
                    offset = (94 * (qm - 1) + (wm - 1)) * 72L; // ����ƫ����
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