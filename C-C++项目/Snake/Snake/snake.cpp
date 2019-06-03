#include "pch.h"
#include "food.h"
#include "wall.h"
#include "snake.h"

Snake::Snake(Wall &tmpWall) :wall(tmpWall)//��ʼ���б��ȡǽ����
{
	pHead = NULL;//����ʱͷ�ڵ�Ϊ��
}

Snake::~Snake()
{

}

void Snake::initSnake()
{
	//����ԭ���Ľڵ�
	destroyPoint();
	//��ʼ���ߣ���ͷ��2������
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
	//�����½ڵ�
	Point *newP = new Point;
	if (newP == NULL)
	{
		return;
	}
	//�½ڵ㸳ֵ
	newP->x = x;
	newP->y = y;
	newP->next = NULL;
	//�޸�ԭʼ��ͷΪ����
	if (pHead != NULL)
	{
		//���õ�ǰ��ͷ���Ϊ����
		wall.setWall(pHead->x, pHead->y, '=');
		gotoxy(hOut, pHead->y * 2, pHead->x);
		cout << "=";
	}
	//�µĽڵ���ӵ�����ͷ����������û��ͷ�ڵ㣬�½ڵ㶼����ͷ���
	newP->next = pHead;
	pHead = newP;
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy(hOut, pHead->y * 2, pHead->x);
	cout << "@";
}

bool Snake::move(char key)
{
	//Wall wall;//ǽ����
	//wall.initWall();//��ʼ��ǽ
	//Food food(wall);//ʳ��
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

	//�жϳԵ��������Ƿ���β��
	Point *pre = pHead;
	Point *cur = pHead->next;
	bool rool = false;
	//�ҵ�β�ڵ�
	while (cur->next != NULL)
	{
		pre = pre->next;
		cur = pre->next;
	}
	if (cur->x == x && cur->y == y)
	{
		rool = true;//rool��ʾ�Ƿ���ѭ��״̬
	}
	else
	{
		if (wall.getWall(x, y) == '=' || wall.getWall(x, y) == '*')
		{
			//��ʾ�����������һ��
			addPoint(x, y);
			delPoint();
			system("cls");
			wall.draw();
			cout << "�÷֣�" << getScore() << "��" << endl;
			cout << "GameOver!" << endl;
			return false;
		}
	}

	if (wall.getWall(x, y) == '#')
	{
		addPoint(x, y);
		
		//��������ʳ��
		food.setFood();
	}
	//�ж�β�ڵ㣬��β�ڵ㲻���������ж�
	else
	{
		if (rool)
		{
			//�����ƶ�
			addPoint(x, y);
			delPoint();
			wall.setWall(x, y, '@');
			gotoxy(hOut, y * 2, x);
			cout << "@";
		}
		else
		{
			//�����ƶ�
			addPoint(x, y);
			delPoint();
		}
	}
	
	return true;
}

void Snake::delPoint()
{
	//�����ڵ�����ɾ��
	if (pHead == NULL || pHead->next == NULL)
	{
		return;
	}
	//��������ʱ�ڵ㣬һ����ǰһ���ڵ�pre��һ���ǵ�ǰ�ڵ�cur
	Point *pre = pHead;
	Point *cur = pHead->next;
	while (cur->next != NULL)//ִ�е���һ����Ϊ�գ���ѭ��
	{
		pre = pre->next;
		cur = pre->next;
	}
	//β�ڵ��޸�����
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
	int size = countList();//��ȡ�ߵĳ���
	score = (size - 3) * 100;//��ȥ�߳�ʼ����

	return score;
}