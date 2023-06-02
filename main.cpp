#include "snake.h"
#include "food.h"
#include "map.h"
#include "mdata.h"
#include <easyx.h>

#include <iostream>
#include <thread>


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

// ��Ϸ��ʼ����
int score = 0;
int speed = 120;
int direction = RIGHT;

void drewCell(int x, int y, int color); // ��һ������
void delCell(int x, int y); // ɾ��һ������
void up();  //����ϼ�
void down();  //����¼�
void mleft();  //������
void mright();  //����Ҽ�
void esc();  //���esc��

int main()
{
    //��ʼ������
    initgraph(MAP_WIDTH * PIXEL_SIZE, MAP_HEIGHT * PIXEL_SIZE);
    map m(MAP_WIDTH, MAP_HEIGHT);

    //�����̣߳����ڼ�����������
    thread t1(up);
    thread t2(down);
    thread t3(mleft);
    thread t4(mright);
    thread t5(esc);

    //���뿪ʼ����
    m.start();

    closegraph();
    return 0;
}

void drewCell(int x, int y, int color)
{
    setfillcolor(color);
    fillrectangle(x * PIXEL_SIZE, y * PIXEL_SIZE, (x + 1) * PIXEL_SIZE, (y + 1) * PIXEL_SIZE);

}

void delCell(int x, int y)
{
    setfillcolor(BLACK);
    clearrectangle(x * PIXEL_SIZE, y * PIXEL_SIZE, (x + 1) * PIXEL_SIZE, (y + 1) * PIXEL_SIZE);
}

void up()
{
    while (true)
    {
        if(GetAsyncKeyState(VK_UP)&0x8000)
        {
            if(direction != DOWN)
            {
                direction = UP;
            }
        }
    }
}

void down()
{
    while(true)
    {
        if(GetAsyncKeyState(VK_DOWN)&0x8000)
        {
            if(direction != UP)
            {
                direction = DOWN;
            }
        }
    }
}

void mleft()
{
    while (true)
    {
        if(GetAsyncKeyState(VK_LEFT)&0x8000)
        {
            if(direction != RIGHT)
            {
                direction = LEFT;
            }
        }
    }
}

void mright()
{
    while (true)
    {
        if(GetAsyncKeyState(VK_RIGHT)&0x8000)
        {
            if(direction != LEFT)
            {
                direction = RIGHT;
            }
        }
    }
}

void esc()
{
    while (true)
    {
        if(GetAsyncKeyState(VK_ESCAPE)&0x8000)
        {
            exit(0);
        }
    }
}