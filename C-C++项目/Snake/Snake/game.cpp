// Snake.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "wall.h"
#include "snake.h"
#include "food.h"
#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

void gotoxy3(HANDLE hOutMain, int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOutMain, pos);
}
HANDLE hOutMain = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
	bool isDead = false;//死亡标志
	char preKey = NULL;//上一次运行的方向

	srand((unsigned int)time(NULL));//随机数种子
	Wall wall;//墙对象
	wall.initWall();//初始化墙
	wall.draw();//打印墙

	Food food(wall);//食物
	food.setFood();//设置食物

	Snake snake(wall);//蛇对象
	snake.initSnake();//初始化蛇
	//测试
	
	gotoxy3(hOutMain, 0, wall.ROW);
	
	while (isDead != true)
	{
		char key = _getch();

		if (preKey == NULL && key == snake.LEFT)//初始激活不能用左
		{
			continue;
		}
		do {
			if (key == snake.UP || key == snake.DOWN || key == snake.LEFT || key == snake.RIGHT)
			{
				//判断是否和上一个方向有冲突
				if ((key == snake.LEFT&&preKey == snake.RIGHT) ||
					(key == snake.RIGHT&&preKey == snake.LEFT) ||
					(key == snake.UP&&preKey == snake.DOWN) ||
					(key == snake.DOWN&&preKey == snake.UP))
				{
					key = preKey;//有冲突当前的方向为上一次方向
				}
				else
				{
					//无冲突更新上一次方向
					preKey = key;
				}
				//移动蛇
				if (snake.move(key) == true)
				{
					//system("cls");//清屏
					//wall.draw();//重新绘制蛇
					gotoxy3(hOutMain, 0, wall.ROW);
					cout << "得分：" << snake.getScore() << "分" << endl;
					Sleep(snake.getSleepTime());//睡眠
				}
				else
				{
					//死亡处理
					isDead = true;
					break;
				}
			}
			else
			{
				key = preKey;
			}
		} while (!_kbhit());//当没有键盘输入时返回0
		
	}
	cout << "得分：" << snake.getScore() << "分" << endl;

	system("pause");
	return 0;
}
