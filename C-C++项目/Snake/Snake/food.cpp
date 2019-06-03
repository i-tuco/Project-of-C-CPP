#include "pch.h"
#include "food.h"

Food::Food(Wall &tmpWall) :wall(tmpWall)
{

}

void Food::setFood()
{
	while (1)
	{
		//食物的随机位置
		foodX = rand() % (wall.ROW - 2) + 1;
		foodY = rand() % (wall.COL - 2) + 1;
		//如果当前位置是可行区域，可以设置为食物并且退出循环，否则继续循环
		if (wall.getWall(foodX, foodY) == ' ')
		{
			wall.setWall(foodX, foodY, '#');
			gotoxy2(hOutFood, foodY * 2, foodX);
			cout << "#";
			break;
		}
	}
}