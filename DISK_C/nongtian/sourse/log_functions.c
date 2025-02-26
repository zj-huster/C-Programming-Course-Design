#include "Common.h"
#include "Log.h"

/**************************************************
    DESCRIPTION:输入框输入函数
    KeyIn: int x, int y, KeyIn* word, int size, int mode
    mode：输入模式：0 表示普通模式，直接显示输入内容；1 表示密码模式，输入内容用 * 显示
    RETURN: 无
**************************************************/
void input_string(int x, int y, KeyIn* word, int size, int mode)
{
    //清楚键盘缓存
    while (kbhit()) {  // 检查键盘缓冲区是否有按键事件
        getch();       // 从缓冲区中读取并丢弃按键
    }
    //将鼠标状态设置为手势鼠标，表示输入框处于激活状态
    mouse_set_style(1);
    //接受键盘输入
    word->flag = 1;

    while (1)
    {
        mouse_update(&MouseX, &MouseY, &MousePress);//位置变化则重绘鼠标
        delay(50);//减少循环速度，避免过高的 CPU 占用率

        input_line(x, y,word,size);//输入竖线显示

        /*键盘输入处理*/
        if (word->flag == 1)
        {
            if (kbhit())//检测键盘是否有按键按下，如果有按键按下，返回非零值
			{
                char t;
				t = getch();

                //处理退格键
                if (t == '\b' && word->cursor > 0)
                {
                    (word->string)[word->cursor - 1] = '\0';//删除一个字符
                    (word->cursor)--;//游标左移
                }
                //处理普通字符输入
                else if (t >= '!' && t <= '~' && (word->cursor < word->length))
                {
                    (word->string)[word->cursor] = t;//增加一个字符
                    (word->string)[word->cursor + 1] = '\0';//字符串结束符
                    (word->cursor)++;//游标右移
                }

                mouse_hide();//隐藏鼠标光标，有画面绘制时都要用mouse_hide结合mouse_show

                //清除旧输入框内容，以便重新绘制输入框中内容
                setfillstyle(SOLID_FILL, WHITE);
                bar(word->left , word->top , word->right , word->bottom);

                //新文本输入
                settextjustify(LEFT_TEXT, TOP_TEXT);
                settextstyle(SMALL_FONT, HORIZ_DIR, size);

                if(mode == 0)//普通模式显示
                {
                    //文本显示
                    outtextxy(x, y, word->string);
                    //输入竖线显示
                    input_line(x, y,word,size);

                }
                else
                {
                    //密码模式显示
                    int i;
					for (i = 0; i < word->cursor; i++)
					{
						outtextxy(x + i * (2 * size - 2), y, "*");
					}
                    //输入竖线显示
                    input_line(x, y,word,size);
                }

                mouse_show();//显示鼠标光标
            }
        }

        /*中断输入处理*/
        //在输入框外点击，退出输入框
        if(mouse_press(word->left, word->top, word->right, word->bottom) == -1)
        {
            //清除输入竖线
			setcolor(WHITE);
			setlinestyle(0, 0, 1);
			line(x + (word->cursor) * (2 * size - 2) + 2, 
            y, x + (word->cursor) * (2 * size - 2) + 2, y + 2 * (2 * size - 2));
            //退出输入框
            word->flag = 0;
            break;
        }

        //鼠标样式的设置：在输入框中为竖直光标，其他区域为手势鼠标
        if(mouse_hover(word->left, word->top, word->right, word->bottom) == 1)
        {
            mouse_set_style(2);
        }
        else
        {
            mouse_set_style(1);
        }
    }
}

/**************************************************
    DESCRIPTION: 输入竖线显示函数
    KeyIn: int x, int y, KeyIn* word, int size, int mode
    RETURN: 无
**************************************************/
void input_line(int x, int y, KeyIn* word, int size)
{
    setcolor(DARKGRAY);
    setlinestyle(0, 0, 1);
    line(x + (word->cursor) * (2 * size - 2) + 2, 
    y, x + (word->cursor) * (2 * size - 2) + 2, y + 2 * (2 * size - 2));
}

/**************************************************
    DESCRIPTION: 判断用户名是否已经存在
    KeyIn: char* account
    RETURN: 0 不存在，1 存在
**************************************************/
int judge_account(char* account)
{
    FILE* fp;
    int length = 0;
    int i = 0;
    User * user = NULL;

    if ((fp = fopen("database\\UserInfo.dat", "rb")) == NULL)
    {
        closegraph();
        printf("\nUserInfo.dat error file");
        delay(3000);
        exit(1); // 打开失败，退出程序
    }

    /*计算用户数量*/
    fseek(fp, 0, SEEK_END);
    length = ftell(fp) / sizeof(User); // 账户数量

    for (i = 0; i < length; i++)
    {
        /*分配空间*/
        if ((user = (User*)malloc(sizeof(User))) == NULL)
		{
			closegraph();
			printf("memory error JudgeSameName");
			delay(3000);
			exit(1);//分配空间不足，退出程序
		}
        /*读取数据*/
        fseek(fp, i * sizeof(User), SEEK_SET);
		fread(user, sizeof(User), 1, fp);
        /*判断用户名是否相同*/
        if (strcmp(user->username, account) == 0)
        {
            /*关闭文件*/
            if (fclose(fp) != 0)
            {
                closegraph();
                printf("\nError in closing file UserInfo.");
                delay(3000);
                exit(1);
            }
            /*释放空间*/
            free(user);
            user = NULL;
            //存在相同的用户名 (返回 1)
            return 1;
        }else
        {
            free(user);
            user = NULL;
        }
    }
    /*关闭文件*/
    if (fclose(fp)!= 0)
    {
        closegraph();
        printf("\nError in closing file UserInfo.");
        delay(3000);
        exit(1);
    }
    return 0; // 不存在相同的用户名 (返回 0)
}

/**************************************************
    DESCRIPTION: 判断密码是否正确
    KeyIn: char* account, char* password
    RETURN: 0 错误，1 正确
**************************************************/
int judge_password(char* account, char* password)
{
    FILE* fp;
    int length = 0;
    int i = 0;
    User * user = NULL;

    if ((fp = fopen("database\\UserInfo.dat", "rb")) == NULL)
    {
        closegraph();
        printf("\nUserInfo.dat error file");
        delay(3000);
        exit(1); // 打开失败，退出程序
    }

    /*计算用户数量*/
    fseek(fp, 0, SEEK_END);
    length = ftell(fp) / sizeof(User); // 账户数量

    for (i = 0; i < length; i++)
    {
        /*分配空间*/
        if ((user = (User*)malloc(sizeof(User))) == NULL)
		{
			closegraph();
			printf("memory error JudgeSameName");
			delay(3000);
			exit(1);//分配空间不足，退出程序
		}
        /*读取数据*/
        fseek(fp, i * sizeof(User), SEEK_SET);
		fread(user, sizeof(User), 1, fp);
        /*判断用户名是否相同*/
        if (strcmp(user->username, account) == 0)
        {
            /*判断密码是否相同*/
            if (strcmp(user->password, password) == 0)
            {
                /*关闭文件*/
                if (fclose(fp)!= 0)
                {
                    closegraph();
                    printf("\nError in closing file UserInfo.");
                    delay(3000);
                    exit(1);
                }
                /*释放空间*/
                free(user);
                user = NULL;
                // 存在相同的用户名和密码 (返回 1)
                return 1;
            }
        }
    }
    /*关闭文件*/
    if (fclose(fp)!= 0)
    {
        closegraph();
        printf("\nError in closing file UserInfo.");
        delay(3000);
        exit(1);
    }
    /*释放空间*/
    free(user);
    user = NULL;
    return 0; // 不存在相同的用户名和密码 (返回 0)
}

/**************************************************
    DESCRIPTION: 密码不少于5位
    KeyIn: char* password
    RETURN: 0 密码少于5位，1 表示符合要求
**************************************************/
int judge_password_length(char* password)
{
    int i;
    for (i = 0; i < 13; i++)
    {
        if (password[i] == '\0')
        {
            break;
        }
    }
    //密码不超过五位则不符合要求
    if (i < PASSWORD_MIN_LENGTH)
    {
        return 0;
    }else
    {
        return 1;
    }
}

/**************************************************
    DESCRIPTION: 账户信息写入文件
    KeyIn: char *account, char *password
    RETURN: 无
**************************************************/
void write_user_info(char *account, char *password)
{
    FILE* fp;
	User* user = NULL;

	int i;

	if ((fp = fopen("database\\UserInfo.dat", "rb+")) == NULL)
	{
        closegraph();
		printf("\nUserInfo.dat error file");
		delay(3000);
		exit(1);//打开失败，退出程序
	}else
    {
        if ((user = (User*)malloc(sizeof(User))) == NULL)
        {
            closegraph();
            printf("memory error WrUserInf");
            delay(3000);
            exit(1);//分配空间不足，退出程序
        }else
        {
            //写入账户信息
            strcpy(user->username, account);
            strcpy(user->password, password);
            fseek(fp, 0, SEEK_END);
            fwrite(user, sizeof(User), 1, fp);
            if (fclose(fp) != 0)//关闭文件
            {
                closegraph();
                printf("\nError in closing file UserInfo.");
                delay(3000);
                exit(1);
            }
            free(user);
            user = NULL;
        }
    }
}

/**************************************************
    DESCRIPTION: 忘记密码后覆写用户信息
    KeyIn: char *account, char *password
    RETURN: 无
**************************************************/
void overwrite_user_info(char *account, char *password)
{
    FILE* fp;
	User* user = NULL;

	int i;
    int length;

	if ((fp = fopen("database\\UserInfo.dat", "rb+")) == NULL)
	{
        closegraph();
		printf("\nUserInfo.dat error file");
		delay(3000);
		exit(1);//打开失败，退出程序
	}else
    {
        if ((user = (User*)malloc(sizeof(User))) == NULL)
        {
            closegraph();
            printf("memory error WrUserInf");
            delay(3000);
            exit(1);//分配空间不足，退出程序
        }else
        {
            /*重新写入账户信息*/

            //计算用户数量
            fseek(fp, 0, SEEK_END);
            length = ftell(fp) / sizeof(User); // 账户数量
            for (i = 0; i < length; i++)
            {
                //找到用户位置
                fseek(fp, i * sizeof(User), SEEK_SET);
                fread(user, sizeof(User), 1, fp);
                if (strcmp(user->username, account) == 0)
                {
                    //重新写入
                    fseek(fp, i * sizeof(User), SEEK_SET);//复位到目标用户位置，在fread时后移了一位
                    strcpy(user->username, account);
                    strcpy(user->password, password);
                    fwrite(user, sizeof(User), 1, fp);
                }
            }

            /*关闭文件，释放空间*/
            if (fclose(fp) != 0)//关闭文件
            {
                closegraph();
                printf("\nError in closing file UserInfo.");
                delay(3000);
                exit(1);
            }
            free(user);
            user = NULL;
        }
    }
}