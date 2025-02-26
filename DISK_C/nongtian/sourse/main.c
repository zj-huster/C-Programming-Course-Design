#include "Common.h"
#include "Main.h"

void main()
{
    int flag = WELCOME;
    int driver = VGA;
	int mode = VGAHI;
    initgraph(&driver,&mode,"C:\\BORLANDC\\BGI");
    mouse_init();//≥ı ºªØ Û±Í

    while(1)
    {
        switch (flag)
        {
            case WELCOME:
                welcome(&flag);
                break;

            case SIGN_UP:
                sign_up(&flag);
                break;

            case FORGET_PASSWORD:
                forget_password(&flag);
                break;

            default:
                break;
        }
    }
}