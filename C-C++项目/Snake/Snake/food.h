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
	
	void setFood();//����ʳ��
	void gotoxy2(HANDLE hOutFood, int x, int y)
	{
		COORD pos;
		pos.X = x;
		pos.Y = y;
		SetConsoleCursorPosition(hOutFood, pos);
	}
	HANDLE hOutFood = GetStdHandle(STD_OUTPUT_HANDLE);

private:
	int foodX;//ʳ��x����
	int foodY;//ʳ��y����
	Wall &wall;//ǽģ������
};

#endif // !_FOOD_HEAD

