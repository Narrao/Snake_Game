//
// Created by jzita on 2023/6/2.
//

#ifndef SNAKE_GAME_FOOD_H
#define SNAKE_GAME_FOOD_H

#include <easyx.h>
#include <cstdlib>
#include <ctime>

// �����ͼ�Ĵ�С
#define MAP_WIDTH 62
#define MAP_HEIGHT 42

// �������صĴ�С
#define PIXEL_SIZE 15


// ������ɫ
#define FOOD RED

void drewCell(int x, int y, int color); // ��һ������

class food
{
private:
    int x;
    int y;
    friend class snake;  //�����������
public:
    food()
    {
        srand((unsigned)time(NULL));
        x = rand() % (40) + 1;
        y = rand() % (40) + 1;
    }
    void draw()     //����ʳ��ͼ��
    {
        drewCell(x, y, FOOD);
    }
    void clear()    //���ʳ��ͼ��
    {
        drewCell(x, y, WHITE);
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    void setX(int x)
    {
        this->x = x;
    }
    void setY(int y)
    {
        this->y = y;
    }

};


#endif //SNAKE_GAME_FOOD_H
