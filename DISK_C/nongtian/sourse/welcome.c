#include "Common.h"
#include "Welcome.h"
#include "Log.h"

void welcome(int *flag)
{
    KeyIn Account = {280,180+30,550,180+57,"", KEY_IN_MAX ,0,0};
    KeyIn Password = {280,180+110,550,180+80+57,"", KEY_IN_MAX ,0,0 };

    /**************************************************
        画面初始化
    **************************************************/
    mouse_set_style(0);//设置鼠标样式为箭头
    mouse_hide();//隐藏鼠标光标,防止鼠标被绘制的图像遮挡
    cleardevice();//清屏
    setfillstyle(SOLID_FILL,WHITE);
    bar(0,0,640,480);//绘制白色背景

    /**************************************************
        画面绘制
    **************************************************/
    hz(540,150,"账号登录",16, 16, LIGHTGRAY);
    hz(280,180,"账号",24, 24, BLACK);
    hz(280,180+80,"密码",24, 24, BLACK);

    setcolor(BLACK);
    setlinestyle(0,0,3);    
    line(280,180+60,550,180+60);
    line(280,180+80+60,550,180+80+60);

    setfillstyle(SOLID_FILL,CYAN);
    bar(320,360,520,400);
    hz(390,370,"登录",24, 32, WHITE);
    hz(500,330,"忘记密码",16, 16, DARKGRAY);
    hz(320,410,"游客登录",16, 16, BLACK);
    hz(485,410,"注册",16, 16, BLACK);
    hz(542,453,"退出登录",24, 24, BLACK);

    mouse_show();//显示鼠标光标

    while(1)
    {
        mouse_update(&MouseX, &MouseY, &MousePress);

        /*退出登录*/
        if(mouse_left_press_check(540, 450, 640, 480) == 1)
        {
            //左键单击退出登录按钮
            closegraph();
            delay(500);
            exit(0);
        }


        /*登录*/
        if(mouse_left_press_check(320, 360, 520, 400) == 1)
        {
            if(judge_account(Account.string) == 0)
            {
                /*账号错误*/
                //清除旧的提示信息，显示新的提示信息
                setfillstyle(SOLID_FILL, WHITE);
                bar(200, 322, 499, 348);
                hz(280, 330, "账号不存在", 16, 16, RED);
            }
            else 
            {
                /*账号正确*/
                //检测密码
                if(judge_password(Account.string,Password.string) == 0)
                {
                    /*密码错误*/
                    //清除旧的提示信息，显示新的提示信息
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(200, 322, 499, 348);
                    hz(280, 330, "密码错误", 16, 16, RED);
                }
                else
                {
                    /*密码正确*/
                    bar(200, 322, 499, 348);
                    hz(280, 330, "成功！", 16, 16, GREEN);
                    delay(500);
                    //进入主界面
                    break;
                }
            }
        }
        else if(mouse_hover(320, 360, 520, 400) == 1)
        {
            //鼠标悬停在登录按钮上
            setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
            setcolor(YELLOW);
            rectangle(320-2, 360-2, 520+2, 400+2);
        }
        else if (mouse_hover(320, 360, 520, 400) == 0) 
        {
            //鼠标离开登录按钮
            setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
            setcolor(WHITE);
            rectangle(320 - 2, 360 - 2, 520 + 2, 400 + 2);
        }


        /*游客登录*/
        if(mouse_left_press_check(320, 410, 420, 440) == 1)
        {
            //左键单击游客登录按钮
            break;
        }
        else if (mouse_hover(320, 410, 420, 440) == 1) 
        {
            //鼠标悬停在游客登录按钮上
            setcolor(BLACK); 
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(320, 430, 320+16*4,430);
        }
        else if (mouse_hover(320, 410, 420, 440) == 0)
        {
            //鼠标离开游客登录按钮
            setcolor(WHITE); 
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(320, 430, 320+16*4,430);
        }


        /*注册*/
        if(mouse_left_press_check(485, 410, 585, 440) == 1)
        {
            //左键单击注册按钮
            *flag = SIGN_UP;
            break;
        }
        else if (mouse_hover(485, 410, 585, 440) == 1)
        {
            //鼠标悬停在注册按钮上
            setcolor(BLACK); 
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(485, 430, 485 + 2 * 16, 430);
        }
        else if (mouse_hover(485, 410, 585, 440) == 0)
        {
            //鼠标离开注册按钮
            setcolor(WHITE);
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(485, 430, 485 + 2 * 16, 430);
        }


        /*忘记密码*/
        if(mouse_left_press_check(500, 330, 600, 350) == 1)
        {
            //左键单击忘记密码按钮
            *flag = FORGET_PASSWORD;
            break;
        }
        else if (mouse_hover(500, 330, 600, 350) == 1)
        {
            //鼠标悬停在忘记密码按钮上
            setcolor(BLACK); 
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(500-1, 350, 564-2, 350);
        }
        else if (mouse_hover(500, 330, 600, 350) == 0)
        {
            //鼠标离开忘记密码按钮
            setcolor(WHITE); 
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(500-1, 350, 564-2, 350);
        }

        /*检测是否悬停在账号或密码输入框上方，若是则设置鼠标为竖线型,不是则设置为箭头型*/
        if (mouse_hover(280, 180 + 24, 550, 180 + 60) == 1|| mouse_hover(280, 180 + 80 + 24, 550, 180 + 60 + 80) == 1)
        {
            MouseStyle = 2;
        }
        else if (mouse_hover(280, 180 + 24, 550, 180 + 60) == 0|| mouse_hover(280, 180 + 80 + 24, 550, 180 + 60 + 80) == 0)
        {
            MouseStyle = 0;
        }

        /*检测是否在账号输入框内输入*/
        if (mouse_left_press_check(280,180+24,550,180+60) == 1)
        {
            //左键单击账号输入框
            input_string(282, 180 + 32, &Account, 7, 0);
        }
        /*检测是否在密码输入框内输入*/
        if (mouse_left_press_check(280,180+80+24,550,180+60+80) == 1)
        {
            //左键单击密码输入框
            input_string(282, 180 + 80 + 32, &Password, 7, 1);
        }
    }
}