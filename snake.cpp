//
// Created by jzita on 2023/5/26.
//
#include "snake.h"

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

extern int score;
extern int speed;

void drewCell(int x, int y, int color); // ��һ������
void delCell(int x, int y); // ɾ��һ������

snake::snake()
{
    x = SNAKE_HEAD_X;
    y = SNAKE_HEAD_Y;
    next = NULL;
}
void snake::move(int direction, food* f)
{
    //����p�ڵ㣬���ڱ�����ͷ��λ��
    snake* p = new snake;
    p->x = this->x;
    p->y = this->y;
    switch (direction)
    {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
    }
    drewCell(x, y, SNAKE_HEAD);     //�����ƶ�����ͷ

    //�Ѻ���Ľڵ㶼��ǰ�ƶ�һ��
    snake* q = this->next;
    while (q != NULL)
    {
        int tempX = q->x;
        int tempY = q->y;
        q->x = p->x;
        q->y = p->y;
        p->x = tempX;
        p->y = tempY;
        q = q->next;
    }

    //�ж��Ƿ�Ե�ʳ�������β�����һ���ڵ㣬����ɾ��β���ڵ�ͼ��
    if (isEatFood(f))
    {
        f->clear();
        do
        {
            f->setX(rand() % 40+ 1);
            f->setY(rand() % 40 + 1);
        }while (f->getX() == this->getX() && f->getY() == this->getY()||(f->getX()>40||f->getX()<=0)||(f->getY()>40||f->getY()<=0));
        f->draw();
        score += 1;
        if (score % 5 == 0)
        {
            speedUp();
        }
        snake* sn = new snake;
        sn->x = p->x;
        sn->y = p->y;
        sn->next = NULL;
        snake* t = this;
        while(t->next!=NULL)
        {
            t = t->next;
        }
        t->next = sn;
    }
    else
    {
        delCell(p->x, p->y);
    }

}
bool snake::isEatSelf()        //�ж��Ƿ�Ե��Լ�
{
    snake* p = this->next;
    while (p != NULL)
    {
        if (p->x == this->x && p->y == this->y)
        {
            return true;
        }
        p = p->next;
    }
    return false;
}
bool snake::isHitWall()        //�ж��Ƿ�ײǽ
{
    if (this->x == 0 || this->x == 41 || this->y == 0 || this->y == 41)
    {
        return true;
    }
    return false;
}
bool snake::isEatFood(food* f)     //�ж��Ƿ�Ե�ʳ��
{
    if (this->x == f->x && this->y == f->y)
    {
        return true;
    }
    return false;
}
void snake::speedUp()      //����
{
    if(speed>40)speed -= 10;
}
void snake::speedDown()        //����
{
    if(speed<120)speed += 10;
}
int snake::getX()
{
    return x;
}
int snake::getY()
{
    return y;
}
snake* snake::getNext()
{
    return next;
}
void snake::setX(int x)
{
    this->x = x;
}
void snake::setY(int y)
{
    this->y = y;
}
void snake::setNext(snake* next)
{
    this->next = next;
}