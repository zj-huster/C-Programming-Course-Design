/**************************************************
    Description:Mouse Library
    Creator:Zhu Jin
    Creative Time:2025.2.11
    Last Modify Time:2025.2.15
    Version:5.0
**************************************************/

#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include<Mouse.h>

//����ȫ�ֱ���
int MouseX,MouseY;
int MouseStyle;
int MouseFlag = 0;//����Ƿ���ʾ��־
void *bitmap;//���ڴ洢��������������ͼ������
union REGS regs;//����DOS�жϵ��õļĴ����ṹ
int MousePress;//��갴�����

/**************************************************
    DESCRIPTION:��ʼ�����������������������򣬲����������
    KeyIn: ��
    RETURN: ��
**************************************************/
void mouse_init()
{
    /*�����������*/
    int xmin, xmax, ymin, ymax, x_max = 625, y_max = 480;
    int retcode; //�洢����ֵ
    xmin = 2;
    xmax = x_max - 1;
    ymin = 8;
    ymax = y_max - 15;

    /*���������������Ƿ����*/
    regs.x.ax=0; //�����жϹ��ܺ�
	int86(51,&regs,&regs);// ����DOS������ж�
	retcode=regs.x.ax;
	if(retcode==0)
	{
		printf("Mouse or Mouse Driver Obsent,Please Install!");
		delay(5000);
        exit(1);  // ֱ���˳�����
	}

    /*�����������*/
    else
	{
		regs.x.ax=7;//�����жϹ��ܺ�Ϊ7��������������X��Χ
		regs.x.cx=xmin;
		regs.x.dx=xmax;
		int86(51,&regs,&regs);
		regs.x.ax=8;//�����жϹ��ܺ�Ϊ8��������������y��Χ
		regs.x.cx=ymin;
		regs.x.dx=ymax;
		int86(51,&regs,&regs);
	}

    /*��ʼ�����״̬*/
    MouseStyle = 0;
    MouseFlag = 0;
    MouseX = 320, MouseY = 240;
    bitmap = NULL;
}

/**************************************************
    DESCRIPTION: �����λ�ñ仯ʱ�ػ����
    KeyIn: int *x, int *y, int *MousePress
    RETURN: void
**************************************************/
void mouse_update(int *x, int *y, int *MousePress)
{
    int x0 = *x, y0 = *y;// ����ɵ��������
    mouse_read(x, y, MousePress); // ��ȡ�µ����״̬

    if (*x == x0 && *y == y0) {
        return; // ������λ��δ�ı䣬ֱ�ӷ���
    }

    /*���λ�øı�����������*/

    clear_mouse(x0, y0); // ����ɵ������
    save_bk(*x, *y); 
    // ������λ�õı���,��������ƶ�����λ�ú�
    //�ܹ��ָ���λ�õ�ԭʼ�������Ӷ��������ƶ�ʱ������˸����Ӱ����
    mouse_new(*x, *y, MouseStyle); // ����λ�û��������
}

/**************************************************
    DESCRIPTION:���»������(����MouseFlag��־λ���Ӷ���ǿ�˶������Ŀ��ƣ���װ�Ը�ǿ)
                �����ʽ��
                MouseStyle == 1������һ���������
                MouseStyle == 2������һ���򵥵�ˮƽ�߶�
                MouseStyle == 3������һ���򵥵Ĵ�ֱ�߶�
                Ĭ����ʽ��MouseStyle == 0��������һ���򵥵ļ�ͷ���
    KeyIn: int x,int y,int style
    RETURN: ��
**************************************************/
void mouse_new(int x,int y,int style)
{
    if(MouseFlag == 0)
	{
	    mouse_draw(x,y,style);
		MouseFlag = 1;
	}
}

/**************************************************
    DESCRIPTION: ��������
    KeyIn: int x,int y
    RETURN: ��
**************************************************/
void clear_mouse(int x,int y)
{
    if(MouseFlag == 1)
    {
		putimage(x-1,y-2,bitmap,COPY_PUT);//�ָ�����
		free(bitmap);//�ͷ��ڴ�
        bitmap = NULL;
		MouseFlag = 0;//��־λ����
		setwritemode(COPY_PUT);//�ָ�дģʽ
        MouseFlag = 0;
    }
}

/**************************************************
    DESCRIPTION: �ÿ������̬
    KeyIn: ��
    RETURN: ��
**************************************************/
void mouse_hide()
{
    if(MouseFlag == 1 && MouseStyle < 60)
    {
        clear_mouse(MouseX,MouseY);
        MouseStyle ^= 64;//�ÿ������̬����ֹ��걻�������
        MouseFlag = 0;//��־λ����
    }
}

/**************************************************
    DESCRIPTION: �ָ������̬
    KeyIn: ��
    RETURN: ��
**************************************************/
void mouse_show()
{
    if(MouseFlag == 0 && MouseStyle > 60)//�����δ��ʾ״̬�²���֮ǰ�����أ��Ż������������
    {
        MouseStyle ^= 64 ;//�ָ������̬
        mouse_read(&MouseX,&MouseY,&MousePress);//���»�ȡ�������
    	save_bk(MouseX,MouseY);//���汳��
		mouse_new(MouseX,MouseY,MouseStyle);//�ػ����
        MouseFlag = 1;
	}
}

/**************************************************
    DESCRIPTION: ���������¼��
    KeyIn: int left, int top, int right, int bottom
    RETURN: 1��ʾ���������£�0��ʾδ����
**************************************************/
int mouse_left_press_check(int left, int top, int right, int bottom)
{
    if(mouse_press(left,top,right,bottom) == 1)//����������
    {
        delay(10);//��ʱ10ms,��ֹ����󴥷�
        mouse_update(&MouseX, &MouseY, &MousePress);//�������״̬
        if(mouse_press(left,top,right,bottom) == 1)//�ٴμ���������Ƿ���
        {
            while(mouse_press(left,top,right,bottom));//�ȴ��������ͷ�
            return 1;
        }
    }
    return 0;
}

/**************************************************
    DESCRIPTION: ����Ҽ����¼��
    KeyIn: int left, int top, int right, int bottom
    RETURN: 1��ʾ����Ҽ����£�0��ʾδ����
**************************************************/
int mouse_right_press_check(int left, int top, int right, int bottom)
{
    if(mouse_press(left,top,right,bottom) == 2)//����Ҽ�����
    {
        delay(10);//��ʱ10ms,��ֹ����󴥷�
        mouse_update(&MouseX, &MouseY, &MousePress);//�������״̬
        if(mouse_press(left,top,right,bottom) == 2)//�ٴμ������Ҽ��Ƿ���
        {
            while(mouse_press(left,top,right,bottom));//�ȴ�����ͷ�
            return 1;
        }
    }
    return 0;
}

/**************************************************
    DESCRIPTION: ������˫�����
    KeyIn: int left, int top, int right, int bottom
    RETURN: 1��ʾ���˫����0��ʾδ˫��
**************************************************/
int mouse_double_press_check(int left, int top, int right, int bottom)
{
    if(mouse_press(left,top,right,bottom) == 1)
    {
        delay(90);
        mouse_update(&MouseX, &MouseY, &MousePress);
        if(mouse_press(left,top,right,bottom) != 1)
        {
            delay(100);
            mouse_update(&MouseX, &MouseY, &MousePress);
            if(mouse_press(left,top,right,bottom) == 1)
            {
                while(mouse_press(left,top,right,bottom));
                return 1;
            }
        }
    }
    return 0;
}

/**************************************************
    ����Ϊ��������������ǰ����Ҫ�����ķ�װ��
**************************************************/

/**************************************************
    DESCRIPTION: �������Ƿ���ָ���ľ��������ڷ�������¼���
    �����ݵ��״̬������Ӧ��ֵ
    KeyIn: int left, int top, int right, int bottom
    RETURN: 0��ʾδ�����-1��ʾ�ھ�������������1��ʾ��������2��ʾ�Ҽ����
**************************************************/
int mouse_press(int left, int top, int right, int bottom)
{
    int type;//��������ͣ�������ֵ

    mouse_update(&MouseX, &MouseY, &MousePress);
    //��ʱ���ܵ���mouse_read��������ȡ���״̬����Ϊ���ı�Mouse X��Mouse Y��ֵ
    //�Ӷ�ʹclear_mouse�����е�����������겻׼ȷ
    //���ԣ���ʱֻ��ʹ��mouse_update������������ͬʱ��ȡ�µ����״̬

    /*����ھ���������*/
    if(mouse_hover(left,top,right,bottom))
    {
        if(MousePress == 0)
        {
            //δ���
            type = 0;
        }
        else if(MousePress == 1)
        {
            //������
            type = 1;
        }
        else if(MousePress == 2)
        {
            //�Ҽ����
            type = 2;
        }
    }

    /*����ھ���������*/
	else if (MousePress) {
        //����ھ�����������
		return -1;
	}
	else
	{
		//����ھ���������δ���
        return 0;
	}

    return type;
}

/**************************************************
    DESCRIPTION: ��������ƶ�ʱ���ܹ���ȷ�ػָ����֮ǰ�ı�����
    �Ӷ�ʵ��������ƽ���ƶ��ͻ���
    KeyIn: int left,int top
    RETURN: ��
**************************************************/
void save_bk(int x,int y)
{
	int size;
	size=imagesize(x-1,y-2,x+11,y+17);
    //����ָ�����������ͼ���С

	bitmap=malloc(size);//Ϊͼ������ڴ�ռ�

	if(bitmap == NULL)
    {
        printf("Malloc Error");
        exit(1);
    }   
	else
    {
        getimage(x-1,y-2,x+11,y+17,bitmap);
        //����graphics.hͷ�ļ��е�һ����,������Ļ�ϲ���ָ�������ͼ�񣬲�����洢���ڴ���
    }
}

/**************************************************
    DESCRIPTION: ����Ƿ��ھ���������
    KeyIn: int left, int top, int right, int bottom
    RETURN: �ڷ���1�����ڷ���0
**************************************************/
int mouse_hover(int left, int top, int right, int bottom)
{
    if(MouseX >= left && MouseX <= right && MouseY >= top && MouseY <= bottom )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**************************************************
    DESCRIPTION: ��ȡ�µļĴ�����Ϣ(�����������Ͱ���״̬)
    KeyIn: int *x,int *y,int *MousePress
    RETURN: ��
**************************************************/
void mouse_read(int *x,int *y,int *MousePress)  
{
	regs.x.ax=3;
	int86(51,&regs,&regs);
    *x = regs.x.cx; // ����X����洢��CX�Ĵ�����
    *y = regs.x.dx; // ����Y����洢��DX�Ĵ�����
    *MousePress = (int)regs.x.bx; 
    // ��갴��״̬�洢��BX�Ĵ�����,
    //BX�Ĵ�����λ0��ʾ���״̬��0��ʾδ���£�1��ʾ���£�
    //BX�Ĵ�����λ1��ʾ�Ҽ�״̬��0��ʾδ���£�1��ʾ���£�
    //BX�Ĵ�����λ2��ʾ�м�״̬��0��ʾδ���£�1��ʾ���£�
}

/**************************************************
    DESCRIPTION: �������λ��
    KeyIn: int x,int y
    RETURN: ��
**************************************************/
void mouse_set_position(int x,int y)    
{ 
    regs.x.ax=4;
    regs.x.cx=x;
    regs.x.dx=y;
    int86(51,&regs,&regs);
}

/**************************************************
    DESCRIPTION: �����ʽ����
                MouseStyle == 1������һ���������
                MouseStyle == 2������һ���������
                MouseStyle == 3������һ���򵥵Ĵ�ֱ�߶�
                Ĭ����ʽ��MouseStyle == 0��������һ���򵥵ļ�ͷ���
    KeyIn: int style
    RETURN: ��
**************************************************/
void mouse_set_style(int style)    
{
    MouseStyle = style;
}

/**************************************************
    DESCRIPTION:����MouseStyle��ֵ���Ʋ�ͬ��ʽ�������
                �����ʽ��
                MouseStyle == 1������һ���������
                MouseStyle == 2������һ���������
                MouseStyle == 3������һ���򵥵Ĵ�ֱ�߶�
                Ĭ����ʽ��MouseStyle == 0��������һ���򵥵ļ�ͷ���
    KeyIn: int style
    RETURN: ��
**************************************************/
void mouse_draw(int x,int y,int style)
{
    setwritemode(COPY_PUT);//����дģʽΪ����ģʽ������ͼ�񸲸�ԭͼ��
    switch (style)
    {
        /*�����*/
        case 0:
        {
            setlinestyle(0,0,1);
            setcolor(WHITE);
            line(x,y,x,y+13);
            line(x+1,y+1,x+1,y+12);
            line(x+2,y+2,x+2,y+11);
            line(x+3,y+3,x+3,y+10);
            line(x+4,y+4,x+4,y+12);
            line(x+5,y+5,x+5,y+9);
            line(x+5,y+11,x+5,y+14);
            line(x+6,y+6,x+6,y+9);
            line(x+6,y+13,x+6,y+15);
            line(x+7,y+7,x+7,y+9);
            line(x+8,y+8,x+8,y+9);
            line(x+9,y+9,x+9,y+9);
            setcolor(DARKGRAY);
            line(x-1,y-1,x-1,y+14);
            line(x-1,y+14,x+3,y+11);
            line(x+3,y+11,x+3,y+12);
            line(x+3,y+12,x+4,y+13);
            line(x+4,y+13,x+4,y+14);
            line(x+4,y+14,x+7,y+17);
            line(x+7,y+17,x+7,y+13);
            line(x+7,y+13,x+6,y+12);
            line(x+6,y+12,x+6,y+11);
            line(x+6,y+11,x+5,y+10);
            line(x+5,y+10,x+11,y+10);
            line(x+11,y+10,x-1,y-2);
        
            break;
        }

        /*�������*/
        case 1:
        {
            // ���ư�ɫ�߿�
            setcolor(WHITE);
            setlinestyle(0,0,1);
            line(x-1,y+9,x-1,y+8);
            line(x,y+7,x,y+11);
            line(x+1,y+6,x+1,y+13);
            line(x+2,y+8,x+2,y+14);
            line(x+3,y-1,x+3,y+15);
            arc(x+4,y-1,0,180,1);
            line(x+4,y-2,x+4,y+15);
            line(x+5,y-1,x+5,y+16);
            arc(x+6,y+3,0,180,1);
            line(x+6,y+2,x+6,y+16);
            line(x+7,y+3,x+7,y+17);
            arc(x+8,y+5,0,180,1);
            line(x+8,y+4,x+8,y+17);
            line(x+9,y+5,x+9,y+16);
            arc(x+10,y+7,0,180,1);
            line(x+10,y+6,x+10,y+16);
            line(x+11,y+7,x+11,y+13);

            setcolor(DARKGRAY);
            line(x-1,y+9,x-1,y+8);
            line(x-1,y+8,x+1,y+6);
            line(x+1,y+6,x+3,y+10);
            line(x+3,y+10,x+3,y-1);
            arc(x+4,y-1,0,180,1);
            line(x+5,y-1,x+5,y+5);
            arc(x+6,y+3,0,180,1);
            line(x+7,y+3,x+7,y+7);
            arc(x+8,y+5,0,180,1);
            line(x+9,y+5,x+9,y+9);
            arc(x+10,y+7,0,180,1);
            line(x+11,y+7,x+11,y+13);
            arc(x+7,y+13,-90,0,4);
            line(x+7,y+17,x+3,y+15);
            line(x+3,y+15,x+1,y+13);
            line(x+1,y+13,x-1,y+9);

            break;
        }
        
        /*��ֱ��꣬�����ʹ��*/
        case 2:
        {
            setcolor(DARKGRAY);
            setlinestyle(0,0,1);
            line(x+1,y-1,x+9,y-1);
            line(x+1,y+15,x+9,y+15);
            line(x+5,y-1,x+5,y+15);

            break;
        }
            
        /*ʮ��*/
        case 3:
        {
            setcolor(WHITE);
            setlinestyle(0,0,1);
            line(x-1,y+7,x+11,y+7);
            line(x+5,y-1,x+5,y+15);

            break;
        }
    }
    MouseFlag = 1;
}
