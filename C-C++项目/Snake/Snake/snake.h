#ifndef _SNAKE_HEAD
#define _SNAKE_HEAD
#include "pch.h"
#include "wall.h"
#include <iostream>
#include <Windows.h>
using namespace std;


struct Point
{
	//������
	int x;
	int y;

	//ָ����
	Point *next;
};



class Snake
{
public:
	enum
	{
		UP = 'w',
		DOWN = 's',
		LEFT = 'a',
		RIGHT = 'd'
	};

	Snake(Wall &tmpWall);
	~Snake();

	//��ʼ����
	void initSnake();
	//������
	void destroyPoint();
	//����߽ڵ�
	void addPoint(int x, int y);
	//�ƶ��߷���
	bool move(char key);
	//ɾ��β�ڵ�
	void delPoint();
	//��ȡ���ƶ�ʱ��
	int getSleepTime();
	//��ȡ�ߵĳ���
	int countList();
	//��ȡ����
	int getScore();

	void gotoxy(HANDLE hOut, int x, int y)
	{
		COORD pos;
		pos.X = x;
		pos.Y = y;
		SetConsoleCursorPosition(hOut, pos);
	}
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

private:
	//��ͷ�ڵ�
	Point *pHead;
	Wall &wall;
};
#endif // !_SNAKE_HEAD

