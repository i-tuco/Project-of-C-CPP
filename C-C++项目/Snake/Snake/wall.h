#ifndef _WALL_HEAD
#define _WALL_HEAD
#include "pch.h"
#include <iostream>
using namespace std;

class Wall
{
public:
	enum
	{
		ROW = 26,//����
		COL = 26//����
	};
	Wall();
	~Wall();

	void initWall();//��ʼ������
	void draw();//�����黭������̨��
	void setWall(int x, int y, char key);//�����������ö�ά�����е�Ԫ��
	char getWall(int x, int y);//����������ȡ��ά�����е�Ԫ��

private:
	char gameArray[ROW][COL];//ά���Ķ�ά����
};

#endif // !_WALL_HEAD

