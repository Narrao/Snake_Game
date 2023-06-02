//
// Created by jzita on 2023/5/26.
//

#ifndef SNAKE_GAME_SNAKE_H
#define SNAKE_GAME_SNAKE_H
#include "food.h"

class snake
{
private:
    int x;
    int y;
    snake* next;
public:
    snake();
    void move(int direction, food* f);
    bool isEatSelf();        //�ж��Ƿ�Ե��Լ�
    bool isHitWall();        //�ж��Ƿ�ײǽ
    bool isEatFood(food* f);     //�ж��Ƿ�Ե�ʳ��
    void speedUp();      //����
    void speedDown();        //����
    int getX();
    int getY();
    snake* getNext();
    void setX(int x);
    void setY(int y);
    void setNext(snake* next);
};

#endif //SNAKE_GAME_SNAKE_H
