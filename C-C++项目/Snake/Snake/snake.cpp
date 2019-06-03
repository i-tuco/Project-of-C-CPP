#include "pch.h"
#include "food.h"
#include "wall.h"
#include "snake.h"

Snake::Snake(Wall &tmpWall) :wall(tmpWall)//初始化列表获取墙对象
{
	pHead = NULL;//构造时头节点为空
}

Snake::~Snake()
{

}

void Snake::initSnake()
{
	//销毁原来的节点
	destroyPoint();
	//初始化蛇，蛇头和2段蛇身
	addPoint(5, 3);
	addPoint(5, 4);
	addPoint(5, 5);
}

void Snake::destroyPoint()
{
	Point *pCur = pHead;
	while (pHead != NULL)
	{
		pCur = pHead->next;
		delete pHead;
		pHead = pCur;
	}
}

void Snake::addPoint(int x, int y)
{
	//创建新节点
	Point *newP = new Point;
	if (newP == NULL)
	{
		return;
	}
	//新节点赋值
	newP->x = x;
	newP->y = y;
	newP->next = NULL;
	//修改原始的头为身子
	if (pHead != NULL)
	{
		//设置当前的头结点为身子
		wall.setWall(pHead->x, pHead->y, '=');
		gotoxy(hOut, pHead->y * 2, pHead->x);
		cout << "=";
	}
	//新的节点添加到链表头部，不管有没有头节点，新节点都会是头结点
	newP->next = pHead;
	pHead = newP;
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy(hOut, pHead->y * 2, pHead->x);
	cout << "@";
}

bool Snake::move(char key)
{
	//Wall wall;//墙对象
	//wall.initWall();//初始化墙
	//Food food(wall);//食物
	Food food(wall);
	int x = pHead->x;
	int y = pHead->y;

	switch (key)
	{
	case UP:
		x--;
		break;
	case DOWN:
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	default:
		return true;
	}

	//判断吃到的身子是否是尾巴
	Point *pre = pHead;
	Point *cur = pHead->next;
	bool rool = false;
	//找到尾节点
	while (cur->next != NULL)
	{
		pre = pre->next;
		cur = pre->next;
	}
	if (cur->x == x && cur->y == y)
	{
		rool = true;//rool表示是否是循环状态
	}
	else
	{
		if (wall.getWall(x, y) == '=' || wall.getWall(x, y) == '*')
		{
			//显示蛇死亡的最后一步
			addPoint(x, y);
			delPoint();
			system("cls");
			wall.draw();
			cout << "得分：" << getScore() << "分" << endl;
			cout << "GameOver!" << endl;
			return false;
		}
	}

	if (wall.getWall(x, y) == '#')
	{
		addPoint(x, y);
		
		//重新设置食物
		food.setFood();
	}
	//判断尾节点，是尾节点不进入死亡判断
	else
	{
		if (rool)
		{
			//正常移动
			addPoint(x, y);
			delPoint();
			wall.setWall(x, y, '@');
			gotoxy(hOut, y * 2, x);
			cout << "@";
		}
		else
		{
			//正常移动
			addPoint(x, y);
			delPoint();
		}
	}
	
	return true;
}

void Snake::delPoint()
{
	//两个节点以上删除
	if (pHead == NULL || pHead->next == NULL)
	{
		return;
	}
	//用两个临时节点，一个是前一个节点pre，一个是当前节点cur
	Point *pre = pHead;
	Point *cur = pHead->next;
	while (cur->next != NULL)//执行的下一个不为空，就循环
	{
		pre = pre->next;
		cur = pre->next;
	}
	//尾节点修改内容
	wall.setWall(cur->x, cur->y, ' ');
	gotoxy(hOut, cur->y * 2, cur->x);
	cout << " ";
	delete cur;
	cur = NULL;
	pre->next = NULL;
}

int Snake::getSleepTime()
{
	int sTime = 0;
	int size = countList();
	if (size < 5)
	{
		sTime = 300;
	}
	else if (size >= 5 && size <= 100)
	{
		sTime = 200;
	}
	else
	{
		sTime = 100;
	}

	return sTime;
}

int Snake::countList()
{
	int size = 0;
	Point *curP = pHead;
	while (curP != NULL)
	{
		size++;
		curP = curP->next;
	}

	return size;
}

int Snake::getScore()
{
	int score = 0;
	int size = countList();//获取蛇的长度
	score = (size - 3) * 100;//减去蛇初始长度

	return score;
}