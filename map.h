//
// Created by jzita on 2023/5/26.
//
#ifndef SNAKE_GAME_MAP_H
#define SNAKE_GAME_MAP_H

class map
{
private:
    int width;
    int height;
public:
    map(int w, int h);      //��ʼ����ͼ��С
    void start();     //����ʼ����
    //��Ϸ����
    void game();
    //��Ϸ˵������
    void explain();
    //��Ϸ��������
    void endgame();
    //��ʷ�ɼ�����
    void log();
};


#endif //SNAKE_GAME_MAP_H
