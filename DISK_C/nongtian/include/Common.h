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

#define KEY_IN_MAX 10//�궨�壺������󳤶�
#define PASSWORD_MIN_LENGTH 5//�궨�壺������̳���

#define WELCOME 1
#define SIGN_UP 2
#define FORGET_PASSWORD 3

typedef struct
{
	int left;//���������
	int top;
	int right;
	int bottom;
	char string[20];//�洢������ַ���
	char length;//�������󳤶�
	char cursor;//�ַ����ȣ������һ���ַ���λ�ã���1��ʼ������
	char flag;//0�������ܼ������룬1������ܼ�������
}KeyIn;

typedef struct
{
	char username[KEY_IN_MAX + 1];//�û���
	char password[KEY_IN_MAX + 1];//����
}User;

#endif