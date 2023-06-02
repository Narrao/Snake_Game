//
// Created by jzita on 2023/6/2.
//

#ifndef SNAKE_GAME_MDATA_H
#define SNAKE_GAME_MDATA_H
#include <vector>
#include <string>

using namespace std;

class mdata
{
private:
    string filename;        //�ļ���
    vector<int> score;      //�洢����
public:
    mdata(string filename);       //��ʼ���ļ���
    void read();     //��ȡ�ļ�������������򴴽��ļ�
    void write();        //д���ļ�
    istream& operator<<(int s);     //�������
    void msort();        //����
    void show();     //��ʾ����
    void clear();        //�������
};


#endif //SNAKE_GAME_MDATA_H
