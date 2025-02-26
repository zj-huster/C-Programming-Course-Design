#include "Common.h"
#include "Forget.h"
#include "Log.h"

/*与注册完全相同，只是改变账号的判断规则，存在账号执行下去，不存在则不执行下去*/
void forget_password(int *flag)
{
    KeyIn Account = { 300, 170 + 3, 550, 180+20-2 , "", KEY_IN_MAX, 0, 0 };
    KeyIn Password = { 300,180+50 +2,550,180 + 80-2 ,"", KEY_IN_MAX,0,0 };
    KeyIn Confirm = { 300, 180+110 + 2, 550, 180+80+60-2 , "", KEY_IN_MAX, 0, 0 };

    /**************************************************
        画面初始化
    **************************************************/
   mouse_set_style(0);//设置鼠标样式为箭头
   mouse_hide();//隐藏鼠标光标,防止鼠标被绘制的图像遮挡
   cleardevice();//清屏
   setfillstyle(SOLID_FILL,WHITE);
   bar(0,0,640,480);//绘制白色背景

   /**************************************************
        画面文字
    **************************************************/
   hz(250,170,"账号",24, 24, BLACK);
   hz(250,180+50,"密码",24, 24, BLACK);
   hz(200,180+110,"确认密码",24, 24, BLACK);//界面文字

   setcolor(BLACK);
   setlinestyle(0,0,3);    
   line(300,180+20,550,180+20);
   line(300,180+80,550,180+80);
   line(300,180+80+60,550,180+80+60);//输入框横线

   setfillstyle(1,CYAN);
   bar(320,360,520,400);
   hz(390,370,"注册",24, 32, WHITE);
   hz(500,330,"返回登录",16, 16, DARKGRAY);//功能按钮的文字

   mouse_show();//显示鼠标

   /**************************************************
        主循环
    **************************************************/
   while(1)
   {
        mouse_update(&MouseX, &MouseY, &MousePress);

        /**************************************************
            功能按钮点击事件
        **************************************************/
        //注册
        if(mouse_left_press_check(320, 360, 520, 400) == 1)
        {
            //判断用户名是否存在
            if (judge_account(Account.string) == 0) 
            {
                //用户名不存在，注册失败，提示用户重新输入
                mouse_hide();
                setfillstyle(SOLID_FILL, WHITE);
                bar(200, 322, 499, 348);
                hz(280, 330, "账号不存在", 16, 16, RED);
                delay(1000);
                mouse_show();
            }else
            {
                //用户名存在，继续判断密码
                //密码是否超过5位数
                if (judge_password_length(Password.string) == 0)
                {
                    //密码少于5位数，注册失败，提示用户重新输入
                    mouse_hide();
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(200, 322, 499, 348);
                    hz(280, 330, "密码须在五位以上", 16, 16, RED);
                    delay(1000);
                    mouse_show();
                }else
                {
                    //两次输入的密码超过5位数
                    //再判断两次输入的密码是否一致
                    if (strcmp(Password.string, Confirm.string) == 0)
                    {
                        //两次输入的密码一致
                        //将用户名和密码写入文件
                        overwrite_user_info(Account.string, Password.string);
                        mouse_hide();
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(200, 322, 499, 348);
                        hz(280, 330, "成功！", 16, 16, GREEN);
                        delay(1000);
                        mouse_show();
                        *flag = WELCOME;
                        break;
                    }else
                    {
                        //两次输入的密码不一致，注册失败，提示用户重新输入
                        mouse_hide();
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(200, 322, 499, 348);
                        hz(280, 330, "两次输入的密码不一致", 16, 16, RED);
                        delay(1000);
                        mouse_show();
                    }
                }
            }
        }
        else if (mouse_hover(320, 360, 520, 400) == 1)
        {
            //鼠标悬停在注册按钮上
            setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
            setcolor(YELLOW);
            rectangle(320-2, 360-2, 520+2, 400+2);
        }
        else if (mouse_hover(320, 360, 520, 400) == 0) 
        {
            //鼠标离开注册按钮
            setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
            setcolor(WHITE);
            rectangle(320 - 2, 360 - 2, 520 + 2, 400 + 2);
        }
        
        //返回登录
        if (mouse_left_press_check(500, 330, 570, 350) == 1)
        {
			*flag = WELCOME;
			break;
		}
        else if(mouse_hover(500, 330, 570, 350) == 1)
        {
            //鼠标悬停在返回登录按钮上
            setcolor(BLACK); 
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(500-1, 350, 570, 350);
        }
        else if(mouse_hover(500, 330, 570, 350) == 0)
        {
            //鼠标悬停在返回登录按钮上
            setcolor(WHITE); 
            setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
            line(500-1, 350, 570, 350);
        }

        /**************************************************
            鼠标悬停事件检测
        **************************************************/
        /*检测是否悬停在输入框上方，若是则设置鼠标为竖线型,不是则设置为箭头型*/
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
            文本框输入事件
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