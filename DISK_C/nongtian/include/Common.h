#ifndef COMMON_H
#define COMMON_H

#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<bios.h>
#include<string.h>
#include<dos.h>
#include<math.h>
#include<time.h>
#include<conio.h>

#include"HZ.h"
#include"Mouse.h"

#define KEY_IN_MAX 10//宏定义：输入最大长度
#define PASSWORD_MIN_LENGTH 5//宏定义：密码最短长度

#define WELCOME 1
#define SIGN_UP 2
#define FORGET_PASSWORD 3

typedef struct
{
	int left;//输入框坐标
	int top;
	int right;
	int bottom;
	char string[20];//存储输入的字符串
	char length;//输入的最大长度
	char cursor;//字符长度，即最后一个字符的位置（从1开始计数）
	char flag;//0代表不接受键盘输入，1代表接受键盘输入
}KeyIn;

typedef struct
{
	char username[KEY_IN_MAX + 1];//用户名
	char password[KEY_IN_MAX + 1];//密码
}User;

#endif