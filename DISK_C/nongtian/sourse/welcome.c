#include "Common.h"
#include "Welcome.h"
#include "Log.h"

void welcome(int *flag)
{
    KeyIn Account = {280,180+30,550,180+57,"", KEY_IN_MAX ,0,0};
    KeyIn Password = {280,180+110,550,180+80+57,"", KEY_IN_MAX ,0,0 };

    /**************************************************
        �����ʼ��
    **************************************************/
    mouse_set_style(0);//���������ʽΪ��ͷ
    mouse_hide();//���������,��ֹ��걻���Ƶ�ͼ���ڵ�
    cleardevice();//����
    setfillstyle(SOLID_FILL,WHITE);
    bar(0,0,640,480);//���ư�ɫ����

    /**************************************************
        �������
    **************************************************/
    hz(540,150,"�˺ŵ�¼",16, 16, LIGHTGRAY);
    hz(280,180,"�˺�",24, 24, BLACK);
    hz(280,180+80,"����",24, 24, BLACK);

    setcolor(BLACK);
    setlinestyle(0,0,3);    
    line(280,180+60,550,180+60);
    line(280,180+80+60,550,180+80+60);

    setfillstyle(SOLID_FILL,CYAN);
    bar(320,360,520,400);
    hz(390,370,"��¼",24, 32, WHITE);
    hz(500,330,"��������",16, 16, DARKGRAY);
    hz(320,410,"�ο͵�¼",16, 16, BLACK);
    hz(485,410,"ע��",16, 16, BLACK);
    hz(542,453,"�˳���¼",24, 24, BLACK);

    mouse_show();//��ʾ�����

    while(1)
    {
        mouse_update(&MouseX, &MouseY, &MousePress);

        /*�˳���¼*/
        if(mouse_left_press_check(540, 450, 640, 480) == 1)
        {
            //��������˳���¼��ť
            closegraph();
            delay(500);
            exit(0);
        }


        /*��¼*/
        if(mouse_left_press_check(320, 360, 520, 400) == 1)
        {
            if(judge_account(Account.string) == 0)
            {
                /*�˺Ŵ���*/
                //����ɵ���ʾ��Ϣ����ʾ�µ���ʾ��Ϣ
                setfillstyle(SOLID_FILL, WHITE);
                bar(200, 322, 499, 348);
                hz(280, 330, "�˺Ų�����", 16, 16, RED);
            }
            else 
            {
                /*�˺���ȷ*/
                //�������
                if(judge_password(Account.string,Password.string) == 0)
                {
                    /*�������*/
                    //����ɵ���ʾ��Ϣ����ʾ�µ���ʾ��Ϣ
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(200, 322, 499, 348);
                    hz(280, 330, "�������", 16, 16, RED);
                }
                else
                {
                    /*������ȷ*/
                    bar(200, 322, 499, 348);
                    hz(280, 330, "�ɹ���", 16, 16, GREEN);
                    delay(500);
                    //����������
                    break;
                }
            }
        }
        else if(mouse_hover(320, 360, 520, 400) == 1)
        {
            //�����ͣ�ڵ�¼��ť��
            setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
            setcolor(YELLOW);
            rectangle(320-2, 360-2, 520+2, 400+2);
        }
        else if (mouse_hover(320, 360, 520, 400) == 0) 
        {
            //����뿪��¼��ť
            setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
            setcolor(WHITE);
            rectangle(320 - 2, 360 - 2, 520 + 2, 400 + 2);
        }


        /*�ο͵�¼*/
        if(mouse_left_press_check(320, 410, 420, 440) == 1)
        {
            //��������ο͵�¼��ť
            break;
        }
        else if (mouse_hover(320, 410, 420, 440) == 1) 
        {
            //�����ͣ���ο͵�¼��ť��
            setcolor(BLACK); 
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(320, 430, 320+16*4,430);
        }
        else if (mouse_hover(320, 410, 420, 440) == 0)
        {
            //����뿪�ο͵�¼��ť
            setcolor(WHITE); 
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(320, 430, 320+16*4,430);
        }


        /*ע��*/
        if(mouse_left_press_check(485, 410, 585, 440) == 1)
        {
            //�������ע�ᰴť
            *flag = SIGN_UP;
            break;
        }
        else if (mouse_hover(485, 410, 585, 440) == 1)
        {
            //�����ͣ��ע�ᰴť��
            setcolor(BLACK); 
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(485, 430, 485 + 2 * 16, 430);
        }
        else if (mouse_hover(485, 410, 585, 440) == 0)
        {
            //����뿪ע�ᰴť
            setcolor(WHITE);
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(485, 430, 485 + 2 * 16, 430);
        }


        /*��������*/
        if(mouse_left_press_check(500, 330, 600, 350) == 1)
        {
            //��������������밴ť
            *flag = FORGET_PASSWORD;
            break;
        }
        else if (mouse_hover(500, 330, 600, 350) == 1)
        {
            //�����ͣ���������밴ť��
            setcolor(BLACK); 
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(500-1, 350, 564-2, 350);
        }
        else if (mouse_hover(500, 330, 600, 350) == 0)
        {
            //����뿪�������밴ť
            setcolor(WHITE); 
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(500-1, 350, 564-2, 350);
        }

        /*����Ƿ���ͣ���˺Ż�����������Ϸ����������������Ϊ������,����������Ϊ��ͷ��*/
        if (mouse_hover(280, 180 + 24, 550, 180 + 60) == 1|| mouse_hover(280, 180 + 80 + 24, 550, 180 + 60 + 80) == 1)
        {
            MouseStyle = 2;
        }
        else if (mouse_hover(280, 180 + 24, 550, 180 + 60) == 0|| mouse_hover(280, 180 + 80 + 24, 550, 180 + 60 + 80) == 0)
        {
            MouseStyle = 0;
        }

        /*����Ƿ����˺������������*/
        if (mouse_left_press_check(280,180+24,550,180+60) == 1)
        {
            //��������˺������
            input_string(282, 180 + 32, &Account, 7, 0);
        }
        /*����Ƿ������������������*/
        if (mouse_left_press_check(280,180+80+24,550,180+60+80) == 1)
        {
            //����������������
            input_string(282, 180 + 80 + 32, &Password, 7, 1);
        }
    }
}