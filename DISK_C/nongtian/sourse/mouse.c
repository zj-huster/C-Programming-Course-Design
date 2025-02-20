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

//定义全局变量
int MouseX,MouseY;
int MouseStyle;
int MouseFlag = 0;//鼠标是否显示标志
void *bitmap;//用于存储鼠标光标所在区域的图像数据
union REGS regs;//用于DOS中断调用的寄存器结构
int MousePress;//鼠标按键检测

/**************************************************
    DESCRIPTION:初始化鼠标驱动程序，设置鼠标活动区域，并绘制鼠标光标
    KeyIn: 无
    RETURN: 无
**************************************************/
void mouse_init()
{
    /*鼠标活动区域设置*/
    int xmin, xmax, ymin, ymax, x_max = 625, y_max = 480;
    int retcode; //存储返回值
    xmin = 2;
    xmax = x_max - 1;
    ymin = 8;
    ymax = y_max - 15;

    /*检测鼠标驱动程序是否存在*/
    regs.x.ax=0; //设置中断功能号
	int86(51,&regs,&regs);// 调用DOS中鼠标中断
	retcode=regs.x.ax;
	if(retcode==0)
	{
		printf("Mouse or Mouse Driver Obsent,Please Install!");
		delay(5000);
        exit(1);  // 直接退出程序
	}

    /*设置鼠标活动区域*/
    else
	{
		regs.x.ax=7;//设置中断功能号为7，设置鼠标活动区域的X范围
		regs.x.cx=xmin;
		regs.x.dx=xmax;
		int86(51,&regs,&regs);
		regs.x.ax=8;//设置中断功能号为8，设置鼠标活动区域的y范围
		regs.x.cx=ymin;
		regs.x.dx=ymax;
		int86(51,&regs,&regs);
	}

    /*初始化鼠标状态*/
    MouseStyle = 0;
    MouseFlag = 0;
    MouseX = 320, MouseY = 240;
    bitmap = NULL;
}

/**************************************************
    DESCRIPTION: 当鼠标位置变化时重绘鼠标
    KeyIn: int *x, int *y, int *MousePress
    RETURN: void
**************************************************/
void mouse_update(int *x, int *y, int *MousePress)
{
    int x0 = *x, y0 = *y;// 保存旧的鼠标坐标
    mouse_read(x, y, MousePress); // 读取新的鼠标状态

    if (*x == x0 && *y == y0) {
        return; // 如果鼠标位置未改变，直接返回
    }

    /*如果位置改变则更新鼠标光标*/

    clear_mouse(x0, y0); // 清除旧的鼠标光标
    save_bk(*x, *y); 
    // 保存新位置的背景,在鼠标光标移动到新位置后，
    //能够恢复该位置的原始背景，从而避免光标移动时出现闪烁或重影现象
    mouse_new(*x, *y, MouseStyle); // 在新位置绘制鼠标光标
}

/**************************************************
    DESCRIPTION:重新绘制鼠标(引入MouseFlag标志位，从而加强了对鼠标光标的控制，封装性更强)
                光标样式：
                MouseStyle == 1：绘制一个手势鼠标
                MouseStyle == 2：绘制一个简单的水平线段
                MouseStyle == 3：绘制一个简单的垂直线段
                默认样式（MouseStyle == 0）：绘制一个简单的箭头光标
    KeyIn: int x,int y,int style
    RETURN: 无
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
    DESCRIPTION: 清除鼠标光标
    KeyIn: int x,int y
    RETURN: 无
**************************************************/
void clear_mouse(int x,int y)
{
    if(MouseFlag == 1)
    {
		putimage(x-1,y-2,bitmap,COPY_PUT);//恢复背景
		free(bitmap);//释放内存
        bitmap = NULL;
		MouseFlag = 0;//标志位清零
		setwritemode(COPY_PUT);//恢复写模式
        MouseFlag = 0;
    }
}

/**************************************************
    DESCRIPTION: 置空鼠标形态
    KeyIn: 无
    RETURN: 无
**************************************************/
void mouse_hide()
{
    if(MouseFlag == 1 && MouseStyle < 60)
    {
        clear_mouse(MouseX,MouseY);
        MouseStyle ^= 64;//置空鼠标形态，防止鼠标被错误绘制
        MouseFlag = 0;//标志位清零
    }
}

/**************************************************
    DESCRIPTION: 恢复鼠标形态
    KeyIn: 无
    RETURN: 无
**************************************************/
void mouse_show()
{
    if(MouseFlag == 0 && MouseStyle > 60)//鼠标在未显示状态下并且之前被隐藏，才会重新显现鼠标
    {
        MouseStyle ^= 64 ;//恢复鼠标形态
        mouse_read(&MouseX,&MouseY,&MousePress);//重新获取鼠标坐标
    	save_bk(MouseX,MouseY);//保存背景
		mouse_new(MouseX,MouseY,MouseStyle);//重绘鼠标
        MouseFlag = 1;
	}
}

/**************************************************
    DESCRIPTION: 鼠标左键按下检测
    KeyIn: int left, int top, int right, int bottom
    RETURN: 1表示鼠标左键按下，0表示未按下
**************************************************/
int mouse_left_press_check(int left, int top, int right, int bottom)
{
    if(mouse_press(left,top,right,bottom) == 1)//鼠标左键按下
    {
        delay(10);//延时10ms,防止鼠标误触发
        mouse_update(&MouseX, &MouseY, &MousePress);//更新鼠标状态
        if(mouse_press(left,top,right,bottom) == 1)//再次检测鼠标左键是否按下
        {
            while(mouse_press(left,top,right,bottom));//等待鼠标左键释放
            return 1;
        }
    }
    return 0;
}

/**************************************************
    DESCRIPTION: 鼠标右键按下检测
    KeyIn: int left, int top, int right, int bottom
    RETURN: 1表示鼠标右键按下，0表示未按下
**************************************************/
int mouse_right_press_check(int left, int top, int right, int bottom)
{
    if(mouse_press(left,top,right,bottom) == 2)//鼠标右键按下
    {
        delay(10);//延时10ms,防止鼠标误触发
        mouse_update(&MouseX, &MouseY, &MousePress);//更新鼠标状态
        if(mouse_press(left,top,right,bottom) == 2)//再次检测鼠标右键是否按下
        {
            while(mouse_press(left,top,right,bottom));//等待鼠标释放
            return 1;
        }
    }
    return 0;
}

/**************************************************
    DESCRIPTION: 鼠标左键双击检测
    KeyIn: int left, int top, int right, int bottom
    RETURN: 1表示鼠标双击，0表示未双击
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
    后面为辅助函数（便于前面主要函数的封装）
**************************************************/

/**************************************************
    DESCRIPTION: 检测鼠标是否在指定的矩形区域内发生点击事件，
    并根据点击状态返回相应的值
    KeyIn: int left, int top, int right, int bottom
    RETURN: 0表示未点击，-1表示在矩形区域外点击，1表示左键点击，2表示右键点击
**************************************************/
int mouse_press(int left, int top, int right, int bottom)
{
    int type;//鼠标点击类型，做返回值

    mouse_update(&MouseX, &MouseY, &MousePress);
    //此时不能调用mouse_read函数来获取鼠标状态，因为这会改变Mouse X，Mouse Y的值
    //从而使clear_mouse函数中的清除光标的坐标不准确
    //所以，此时只能使用mouse_update函数更新鼠标的同时获取新的鼠标状态

    /*鼠标在矩形区域内*/
    if(mouse_hover(left,top,right,bottom))
    {
        if(MousePress == 0)
        {
            //未点击
            type = 0;
        }
        else if(MousePress == 1)
        {
            //左键点击
            type = 1;
        }
        else if(MousePress == 2)
        {
            //右键点击
            type = 2;
        }
    }

    /*鼠标在矩形区域外*/
	else if (MousePress) {
        //鼠标在矩形区域外点击
		return -1;
	}
	else
	{
		//鼠标在矩形区域外未点击
        return 0;
	}

    return type;
}

/**************************************************
    DESCRIPTION: 在鼠标光标移动时，能够正确地恢复光标之前的背景，
    从而实现鼠标光标的平滑移动和绘制
    KeyIn: int left,int top
    RETURN: 无
**************************************************/
void save_bk(int x,int y)
{
	int size;
	size=imagesize(x-1,y-2,x+11,y+17);
    //计算指定矩形区域的图像大小

	bitmap=malloc(size);//为图像分配内存空间

	if(bitmap == NULL)
    {
        printf("Malloc Error");
        exit(1);
    }   
	else
    {
        getimage(x-1,y-2,x+11,y+17,bitmap);
        //属于graphics.h头文件中的一部分,它从屏幕上捕获指定区域的图像，并将其存储到内存中
    }
}

/**************************************************
    DESCRIPTION: 鼠标是否在矩形区域内
    KeyIn: int left, int top, int right, int bottom
    RETURN: 在返回1，不在返回0
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
    DESCRIPTION: 获取新的寄存器信息(更新鼠标坐标和按键状态)
    KeyIn: int *x,int *y,int *MousePress
    RETURN: 无
**************************************************/
void mouse_read(int *x,int *y,int *MousePress)  
{
	regs.x.ax=3;
	int86(51,&regs,&regs);
    *x = regs.x.cx; // 鼠标的X坐标存储在CX寄存器中
    *y = regs.x.dx; // 鼠标的Y坐标存储在DX寄存器中
    *MousePress = (int)regs.x.bx; 
    // 鼠标按键状态存储在BX寄存器中,
    //BX寄存器的位0表示左键状态（0表示未按下，1表示按下）
    //BX寄存器的位1表示右键状态（0表示未按下，1表示按下）
    //BX寄存器的位2表示中键状态（0表示未按下，1表示按下）
}

/**************************************************
    DESCRIPTION: 设置鼠标位置
    KeyIn: int x,int y
    RETURN: 无
**************************************************/
void mouse_set_position(int x,int y)    
{ 
    regs.x.ax=4;
    regs.x.cx=x;
    regs.x.dx=y;
    int86(51,&regs,&regs);
}

/**************************************************
    DESCRIPTION: 鼠标样式设置
                MouseStyle == 1：绘制一个手势鼠标
                MouseStyle == 2：绘制一个输入框光标
                MouseStyle == 3：绘制一个简单的垂直线段
                默认样式（MouseStyle == 0）：绘制一个简单的箭头光标
    KeyIn: int style
    RETURN: 无
**************************************************/
void mouse_set_style(int style)    
{
    MouseStyle = style;
}

/**************************************************
    DESCRIPTION:根据MouseStyle的值绘制不同样式的鼠标光标
                光标样式：
                MouseStyle == 1：绘制一个手势鼠标
                MouseStyle == 2：绘制一个输入框光标
                MouseStyle == 3：绘制一个简单的垂直线段
                默认样式（MouseStyle == 0）：绘制一个简单的箭头光标
    KeyIn: int style
    RETURN: 无
**************************************************/
void mouse_draw(int x,int y,int style)
{
    setwritemode(COPY_PUT);//设置写模式为覆盖模式，即新图像覆盖原图像
    switch (style)
    {
        /*简单鼠标*/
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

        /*手势鼠标*/
        case 1:
        {
            // 绘制白色边框
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
        
        /*竖直光标，输入框使用*/
        case 2:
        {
            setcolor(DARKGRAY);
            setlinestyle(0,0,1);
            line(x+1,y-1,x+9,y-1);
            line(x+1,y+15,x+9,y+15);
            line(x+5,y-1,x+5,y+15);

            break;
        }
            
        /*十字*/
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
