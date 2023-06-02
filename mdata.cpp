//
// Created by jzita on 2023/6/2.
//

#include <easyx.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <tchar.h>
#include "mdata.h"

// �������صĴ�С
#define PIXEL_SIZE 15

using namespace std;
mdata::mdata(string filename)       //��ʼ���ļ���
{
this->filename = filename;
}
void mdata::read()     //��ȡ�ļ�������������򴴽��ļ�
{
    ifstream in(filename);
    if(!in)
    {
        ofstream out(filename);
        if(!out)
        {
            cout<<"�����ļ�ʧ�ܣ�"<<endl;
            exit(1);
        }
    }
    int temp;
    while(in>>temp)
    {
        score.push_back(temp);
    }
    in.close();
}
void mdata::write()        //д���ļ�
{
    ofstream out(filename);
    if(!out)
    {
        cout<<"���ļ�ʧ�ܣ�"<<endl;
        exit(1);
    }
    for(int i=0;i<score.size();i++)
    {
        out<<score[i]<<endl;
    }
    out.close();
}
istream& mdata::operator<<(int s)     //�������
{
    score.push_back(s);
}
void mdata::msort()        //����
{
    sort(score.begin(),score.end(),greater<int>());
}
void mdata::show()     //��ʾ����
{

    for(int i=10;i<score.size()*2+10;i+=2)
    {
        outtextxy(15*PIXEL_SIZE,i*PIXEL_SIZE,_T("��"));
        TCHAR str[10];
        _stprintf_s(str,_T("%d"),(i-8)/2);
        outtextxy(17*PIXEL_SIZE,i*PIXEL_SIZE,str);
        outtextxy(19*PIXEL_SIZE,i*PIXEL_SIZE,_T("����"));
        _stprintf_s(str,_T("%d"),score[(i-8)/2-1]);
        outtextxy(21*PIXEL_SIZE,i*PIXEL_SIZE,str);
    }
}
void mdata::clear()        //�������
{
    score.clear();
}