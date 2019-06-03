#include "pch.h"
#include "food.h"

Food::Food(Wall &tmpWall) :wall(tmpWall)
{

}

void Food::setFood()
{
	while (1)
	{
		//ʳ������λ��
		foodX = rand() % (wall.ROW - 2) + 1;
		foodY = rand() % (wall.COL - 2) + 1;
		//�����ǰλ���ǿ������򣬿�������Ϊʳ�ﲢ���˳�ѭ�����������ѭ��
		if (wall.getWall(foodX, foodY) == ' ')
		{
			wall.setWall(foodX, foodY, '#');
			gotoxy2(hOutFood, foodY * 2, foodX);
			cout << "#";
			break;
		}
	}
}