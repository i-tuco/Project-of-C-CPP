#ifndef _FOOD_HEAD
#define _FOOD_HEAD
#include "pch.h"
#include "wall.h"
#include <iostream>
#include <Windows.h>
using namespace std;

class Food
{
public:
	Food(Wall &tmpWall);
	
	void setFood();//设置食物
	void gotoxy2(HANDLE hOutFood, int x, int y)
	{
		COORD pos;
		pos.X = x;
		pos.Y = y;
		SetConsoleCursorPosition(hOutFood, pos);
	}
	HANDLE hOutFood = GetStdHandle(STD_OUTPUT_HANDLE);

private:
	int foodX;//食物x坐标
	int foodY;//食物y坐标
	Wall &wall;//墙模块引用
};

#endif // !_FOOD_HEAD

