#include"Common.h"
#include"Sign_up.h"
#include"Log.h"

void sign_up(int *flag)
{
    KeyIn Account = { 300, 170 + 3, 550, 180+20-2 , "", KEY_IN_MAX, 0, 0 };
    KeyIn Password = { 300,180+50 +2,550,180 + 80-2 ,"", KEY_IN_MAX,0,0 };
    KeyIn Confirm = { 300, 180+110 + 2, 550, 180+80+60-2 , "", KEY_IN_MAX, 0, 0 };

    /**************************************************
        �����ʼ��
    **************************************************/
   mouse_set_style(0);//���������ʽΪ��ͷ
   mouse_hide();//���������,��ֹ��걻���Ƶ�ͼ���ڵ�
   cleardevice();//����
   setfillstyle(SOLID_FILL,WHITE);
   bar(0,0,640,480);//���ư�ɫ����

   /**************************************************
        ��������
    **************************************************/
   hz(250,170,"�˺�",24, 24, BLACK);
   hz(250,180+50,"����",24, 24, BLACK);
   hz(200,180+110,"ȷ������",24, 24, BLACK);//��������

   setcolor(BLACK);
   setlinestyle(0,0,3);    
   line(300,180+20,550,180+20);
   line(300,180+80,550,180+80);
   line(300,180+80+60,550,180+80+60);//��������

   setfillstyle(1,CYAN);
   bar(320,360,520,400);
   hz(390,370,"ע��",24, 32, WHITE);
   hz(500,330,"���ص�¼",16, 16, DARKGRAY);//���ܰ�ť������

   mouse_show();//��ʾ���

   /**************************************************
        ��ѭ��
    **************************************************/
   while(1)
   {
        mouse_update(&MouseX, &MouseY, &MousePress);

        /**************************************************
            ���ܰ�ť����¼�
        **************************************************/
        //ע��
        if(mouse_left_press_check(320, 360, 520, 400) == 1)
        {
            if (judge_account(Account.string) == 1) {
                
            }
        }
        else if (mouse_hover(320, 360, 520, 400) == 1)
        {
            //�����ͣ��ע�ᰴť��
            setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
            setcolor(YELLOW);
            rectangle(320-2, 360-2, 520+2, 400+2);
        }
        else if (mouse_hover(320, 360, 520, 400) == 0) 
        {
            //����뿪ע�ᰴť
            setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
            setcolor(WHITE);
            rectangle(320 - 2, 360 - 2, 520 + 2, 400 + 2);
        }
        
        //���ص�¼
        if (mouse_left_press_check(500, 330, 570, 350) == 1)
        {
			*flag = WELCOME;
			break;
		}
        else if(mouse_hover(500, 330, 570, 350) == 1)
        {
            //�����ͣ�ڷ��ص�¼��ť��
            setcolor(BLACK); 
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(500-1, 350, 570, 350);
        }
        else if(mouse_hover(500, 330, 570, 350) == 0)
        {
            //�����ͣ�ڷ��ص�¼��ť��
            setcolor(WHITE); 
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(500-1, 350, 570, 350);
        }

        /**************************************************
            �����ͣ�¼����
        **************************************************/
        /*����Ƿ���ͣ��������Ϸ����������������Ϊ������,����������Ϊ��ͷ��*/
        if (mouse_hover(300, 170 + 5, 550, 180 + 20) == 1 || 
        mouse_hover(300, 180 + 50 + 4, 550, 180 + 80) == 1|| 
        mouse_hover(300, 180 + 110 + 4, 550, 180 + 140) == 1)
        {
            mouse_set_style(2);
        }
        else if (mouse_hover(300, 170 + 5, 550, 180 + 20) == 0 || 
        mouse_hover(300, 180 + 50 + 4, 550, 180 + 80) == 0|| 
        mouse_hover(300, 180 + 110 + 4, 550, 180 + 140) == 0)
        {
            mouse_set_style(0);
        }

        /**************************************************
            �ı��������¼�
        **************************************************/
       if (mouse_left_press_check(300, 170+5, 550,180+20) == 1)
       {
           input_string(300+2,170+5, &Account, 7, 0);
       }
       if (mouse_left_press_check(300, 180+50+4, 550, 180 +  80) == 1)
       { 
           input_string(300+2, 180 + 50 + 4, &Password, 7, 1);
       }
       if (mouse_left_press_check(300, 180 + 110 + 4, 550, 180 + 140) == 1)
       {
           input_string(300 + 2, 180 + 110 + 4, &Confirm, 7, 1);
       }
   }
}