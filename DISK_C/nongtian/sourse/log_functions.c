#include "Common.h"
#include "Log.h"

/**************************************************
    DESCRIPTION:��������뺯��
    KeyIn: int x, int y, KeyIn* word, int size, int mode
    mode������ģʽ��0 ��ʾ��ͨģʽ��ֱ����ʾ�������ݣ�1 ��ʾ����ģʽ������������ * ��ʾ
    RETURN: ��
**************************************************/
void input_string(int x, int y, KeyIn* word, int size, int mode)
{
    //������̻���
    while (kbhit()) {  // �����̻������Ƿ��а����¼�
        getch();       // �ӻ������ж�ȡ����������
    }
    //�����״̬����Ϊ������꣬��ʾ������ڼ���״̬
    mouse_set_style(1);
    //���ܼ�������
    word->flag = 1;

    while (1)
    {
        mouse_update(&MouseX, &MouseY, &MousePress);//λ�ñ仯���ػ����
        delay(50);//����ѭ���ٶȣ�������ߵ� CPU ռ����

        input_line(x, y,word,size);//����������ʾ

        /*�������봦��*/
        if (word->flag == 1)
        {
            if (kbhit())//�������Ƿ��а������£�����а������£����ط���ֵ
			{
                char t;
				t = getch();

                //�����˸��
                if (t == '\b' && word->cursor > 0)
                {
                    (word->string)[word->cursor - 1] = '\0';//ɾ��һ���ַ�
                    (word->cursor)--;//�α�����
                }
                //������ͨ�ַ�����
                else if (t >= '!' && t <= '~' && (word->cursor < word->length))
                {
                    (word->string)[word->cursor] = t;//����һ���ַ�
                    (word->string)[word->cursor + 1] = '\0';//�ַ���������
                    (word->cursor)++;//�α�����
                }

                mouse_hide();//��������꣬�л������ʱ��Ҫ��mouse_hide���mouse_show

                //�������������ݣ��Ա����»��������������
                setfillstyle(SOLID_FILL, WHITE);
                bar(word->left , word->top , word->right , word->bottom);

                //���ı�����
                settextjustify(LEFT_TEXT, TOP_TEXT);
                settextstyle(SMALL_FONT, HORIZ_DIR, size);

                if(mode == 0)//��ͨģʽ��ʾ
                {
                    //�ı���ʾ
                    outtextxy(x, y, word->string);
                    //����������ʾ
                    input_line(x, y,word,size);

                }
                else
                {
                    //����ģʽ��ʾ
                    int i;
					for (i = 0; i < word->cursor; i++)
					{
						outtextxy(x + i * (2 * size - 2), y, "*");
					}
                    //����������ʾ
                    input_line(x, y,word,size);
                }

                mouse_show();//��ʾ�����
            }
        }

        /*�ж����봦��*/
        //��������������˳������
        if(mouse_press(word->left, word->top, word->right, word->bottom) == -1)
        {
            //�����������
			setcolor(WHITE);
			setlinestyle(0, 0, 1);
			line(x + (word->cursor) * (2 * size - 2) + 2, 
            y, x + (word->cursor) * (2 * size - 2) + 2, y + 2 * (2 * size - 2));
            //�˳������
            word->flag = 0;
            break;
        }

        //�����ʽ�����ã����������Ϊ��ֱ��꣬��������Ϊ�������
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
    DESCRIPTION: ����������ʾ����
    KeyIn: int x, int y, KeyIn* word, int size, int mode
    RETURN: ��
**************************************************/
void input_line(int x, int y, KeyIn* word, int size)
{
    setcolor(DARKGRAY);
    setlinestyle(0, 0, 1);
    line(x + (word->cursor) * (2 * size - 2) + 2, 
    y, x + (word->cursor) * (2 * size - 2) + 2, y + 2 * (2 * size - 2));
}

/**************************************************
    DESCRIPTION: �ж��û����Ƿ��Ѿ�����
    KeyIn: char* account
    RETURN: 0 �����ڣ�1 ����
**************************************************/
int judge_account(char* account)
{

}

/**************************************************
    DESCRIPTION: �ж������Ƿ���ȷ
    KeyIn: char* account, char* password
    RETURN: 0 ����1 ��ȷ
**************************************************/
int judge_password(char* account, char* password)
{

}