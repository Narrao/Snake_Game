//
// Created by jzita on 2023/5/26.
//
#include "snake.h"
#include "map.h"
#include "mdata.h"
#include "food.h"
#include <easyx.h>
#include <iostream>

// �����ͼ�Ĵ�С
#define MAP_WIDTH 62
#define MAP_HEIGHT 42

// �������صĴ�С
#define PIXEL_SIZE 15


// ������ɫ
#define FOOD RED
#define SNAKE_HEAD WHITE

// �����ߵ��ƶ�����
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// ������ͷ�ĳ�ʼλ��
#define SNAKE_HEAD_X 20
#define SNAKE_HEAD_Y 20

using namespace std;

extern int score;
extern int speed;
extern int direction;

void delCell(int x, int y); // ɾ��һ������

map::map(int w, int h)       //��ʼ����ͼ��С
{
    width = w;
    height = h;
}
void map::start()        //����ʼ����
{
    //չʾ����ͼƬ
    IMAGE image;
    TCHAR imagePath[] = _T("./R.png");
    loadimage(&image, imagePath);
    cout<<imagePath<<endl;
    putimage(18.5*PIXEL_SIZE,4*PIXEL_SIZE, &image);

    // settextcolor(0x800000);
    // outtextxy(27*PIXEL_SIZE,10*PIXEL_SIZE,_T("̰        ��        ��"));

    //չʾ�˵�
    settextcolor(RED);
    outtextxy(17*PIXEL_SIZE,20*PIXEL_SIZE,_T("1.��ʼ��Ϸ"));
    outtextxy(24*PIXEL_SIZE,20*PIXEL_SIZE,_T("2.��Ϸ˵��"));
    outtextxy(31*PIXEL_SIZE,20*PIXEL_SIZE,_T("3.��ʷ�ɼ�"));
    outtextxy(38*PIXEL_SIZE,20*PIXEL_SIZE,_T("4.�˳���Ϸ"));
    settextcolor(YELLOW);
    outtextxy(27*PIXEL_SIZE,30*PIXEL_SIZE,_T("�밴���ּ�ѡ��"));
    settextcolor(WHITE);
    outtextxy(40*PIXEL_SIZE,35*PIXEL_SIZE,_T("����̴ 2022141460178"));

    //�����������룬����������ת����ͬ�Ľ���
    while(true)
    {
        if(GetAsyncKeyState('1') & 0x8000)
        {
            cleardevice();
            game();
            break;
        }
        if(GetAsyncKeyState('2') & 0x8000)
        {
            cleardevice();
            explain();
            break;
        }
        if(GetAsyncKeyState('3') & 0x8000)
        {
            cleardevice();
            log();
            break;
        }
        if(GetAsyncKeyState('4') & 0x8000)
        {
            closegraph();
            exit(0);
            break;
        }
    }
}

//��Ϸ����
void map::game()
{
    //������Ϸ�߽�
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID | PS_ENDCAP_FLAT);
    line(1*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE, 1*PIXEL_SIZE);       // �ϱ߽���
    line(1*PIXEL_SIZE, 1*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE);     // ��߽���
    line(1*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE); // �±߽���
    line(41*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE);   // �ұ߽���

    //չʾ��Ϸ��Ϣ��˵��
    outtextxy(45*PIXEL_SIZE,5*PIXEL_SIZE,_T("�÷֣�"));
    TCHAR str[10];
    _stprintf_s(str,_T("%d"),score);
    outtextxy(48*PIXEL_SIZE,5*PIXEL_SIZE,str);
    outtextxy(45*PIXEL_SIZE,10*PIXEL_SIZE,_T("ÿ��ʳ��÷֣�1"));
    outtextxy(45*PIXEL_SIZE,15*PIXEL_SIZE,_T("����ײǽ������ײ�Լ���"));
    outtextxy(45*PIXEL_SIZE,20*PIXEL_SIZE,_T("�÷���������ߵ��ƶ�����"));
    outtextxy(45*PIXEL_SIZE,25*PIXEL_SIZE,_T("F1�����٣�F2�����٣�"));
    outtextxy(45*PIXEL_SIZE,30*PIXEL_SIZE,_T("���ո����ͣ����BACK��������"));
    outtextxy(45*PIXEL_SIZE,35*PIXEL_SIZE,_T("��ESC���˳���"));

    // ��ʼ���ߺ�ʳ��
    snake* head = new snake;
    snake* p = new snake;
    head->setX(21);
    head->setY(20);
    p->setNext(NULL);
    head->setNext(p);
    food food;
    do
    {
        food.setX(rand() % 40+ 1);
        food.setY(rand() % 40 + 1);
    }while (food.getX() == head->getX() && food.getY() == head->getY()||(food.getX()>40||food.getX()<=0)||(food.getY()>40||food.getY()<=0));
    food.draw();
    head->move(direction,&food);

    //�����������룬��������ִ�в�ͬ�Ĳ���
    while(true)
    {
        if(GetAsyncKeyState(VK_SPACE)&0x8000)  //��ͣ
        {
            while(true)
            {
                if(GetAsyncKeyState(VK_BACK)&0x8000)
                {
                    break;
                }
            }
        }
        if(GetAsyncKeyState(VK_F1)&0x8000)      //����
        {
            head->speedUp();
        }
        if(GetAsyncKeyState(VK_F2)&0x8000)      //����
        {
            head->speedDown();
        }
        if(head->isEatSelf()||head->isHitWall())        //�ж��Ƿ������Ϸ
        {
            while(head->getNext()!=NULL)
            {
                snake* p = head->getNext();
                head->setNext(p->getNext());
                delete p;
            }
            cleardevice();
            endgame();
        }

        head->move(direction,&food);    //�ƶ���

        //ˢ�µ÷�
        delCell(48,5);
        TCHAR str[10];
        _stprintf_s(str,_T("%d"),score);
        outtextxy(48*PIXEL_SIZE,5*PIXEL_SIZE,str);

        //�ָ����ܱ�ɾ���ı߽���
        line(1*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE, 1*PIXEL_SIZE);       // �ϱ߽���
        line(1*PIXEL_SIZE, 1*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE);     // ��߽���
        line(1*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE); // �±߽���
        line(41*PIXEL_SIZE, 1*PIXEL_SIZE, 41*PIXEL_SIZE, 41*PIXEL_SIZE);   // �ұ߽���

        //��ʱ�Կ����ߵ��ƶ��ٶ�
        Sleep(speed);
    }


}

//��Ϸ˵������
void map::explain()
{
    outtextxy(27*PIXEL_SIZE,10*PIXEL_SIZE,_T("��Ϸ˵����"));
    outtextxy(27*PIXEL_SIZE,15*PIXEL_SIZE,_T("1.����ײǽ������ײ�Լ���"));
    outtextxy(27*PIXEL_SIZE,20*PIXEL_SIZE,_T("2.�÷���������ߵ��ƶ�����"));
    outtextxy(27*PIXEL_SIZE,25*PIXEL_SIZE,_T("3.F1�����٣�F2�����٣�"));
    outtextxy(27*PIXEL_SIZE,30*PIXEL_SIZE,_T("4.���ո����ͣ����ESC���˳���"));
    outtextxy(27*PIXEL_SIZE,35*PIXEL_SIZE,_T("5.���ո�����أ�"));
    while (true)
    {
        if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            cleardevice();
            start();
            break;
        }
    }
}

//��Ϸ��������
void map::endgame()
{
    outtextxy(27*PIXEL_SIZE,10*PIXEL_SIZE,_T("��Ϸ������"));
    outtextxy(27*PIXEL_SIZE,20*PIXEL_SIZE,_T("�÷֣�"));
    TCHAR str[10];
    _stprintf_s(str,_T("%d"),score);
    outtextxy(30*PIXEL_SIZE,20*PIXEL_SIZE,str);
    outtextxy(27*PIXEL_SIZE,24*PIXEL_SIZE,score);
    outtextxy(27*PIXEL_SIZE,25*PIXEL_SIZE,_T("��ESC���˳���"));
    outtextxy(27*PIXEL_SIZE,30*PIXEL_SIZE,_T("���ո���ص����˵���"));

    //�ѵ÷�д���ļ�
    mdata d("score.txt");
    d.read();
    d<<score;
    d.msort();
    d.write();

    while (true)
    {
        if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            score = 0;
            speed = 120;
            direction = RIGHT;
            cleardevice();
            start();
            break;
        }
    }

}

//��ʷ�ɼ�����
void map::log()
{
    settextstyle(20,0,_T("����"));
    outtextxy(27*PIXEL_SIZE,3*PIXEL_SIZE,_T("��ʷ�ɼ���"));

    //��ȡ�ļ��е����ݲ��������ʾ
    mdata d("score.txt");
    d.read();
    d.msort();
    d.show();

    outtextxy(27*PIXEL_SIZE,38*PIXEL_SIZE,_T("��C��������м�¼��"));
    outtextxy(27*PIXEL_SIZE,40*PIXEL_SIZE,_T("���ո�����أ�"));
    while (true)
    {
        if(GetAsyncKeyState('C') & 0x8000)
        {
            d.clear();
            d.write();
            cleardevice();
            log();
            break;
        }
        if(GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            cleardevice();
            start();
            break;
        }
    }
}