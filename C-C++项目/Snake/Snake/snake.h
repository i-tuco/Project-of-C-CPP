#ifndef _SNAKE_HEAD
#define _SNAKE_HEAD
#include "pch.h"
#include "wall.h"
#include <iostream>
#include <Windows.h>
using namespace std;


struct Point
{
	//数据域
	int x;
	int y;

	//指针域
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

	//初始化蛇
	void initSnake();
	//销毁蛇
	void destroyPoint();
	//添加蛇节点
	void addPoint(int x, int y);
	//移动蛇方法
	bool move(char key);
	//删除尾节点
	void delPoint();
	//获取蛇移动时间
	int getSleepTime();
	//获取蛇的长度
	int countList();
	//获取分数
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
	//蛇头节点
	Point *pHead;
	Wall &wall;
};
#endif // !_SNAKE_HEAD

