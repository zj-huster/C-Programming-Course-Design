#ifndef MOUSE_H
#define MOUSE_H

//外部参照型变量声明
extern int MouseX;
extern int MouseY;
extern int MouseFlag;
extern int MouseStyle;
extern int MousePress;
extern void *bitmap;
extern union REGS regs;

void mouse_init();
void mouse_update(int *x, int *y, int *MousePress);
void mouse_hide();
void mouse_show();
void mouse_new(int x,int y,int style);
int mouse_press(int left, int top, int right, int bottom);
int mouse_hover(int left, int top, int right, int bottom);
void save_bk(int left, int top);
void mouse_draw(int x,int y,int style);
void mouse_read(int *x, int *y, int *buttons);
void clear_mouse(int x, int y);
void mouse_set_position(int x,int y);
void mouse_set_style(int style);
int mouse_left_press_check(int left, int top, int right, int bottom);
int mouse_right_press_check(int left, int top, int right, int bottom);
int mouse_double_press_check(int left, int top, int right, int bottom);

#endif