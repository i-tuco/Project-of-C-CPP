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
		ROW = 26,//行数
		COL = 26//列数
	};
	Wall();
	~Wall();

	void initWall();//初始化数组
	void draw();//将数组画到控制台中
	void setWall(int x, int y, char key);//根据索引设置二维数组中的元素
	char getWall(int x, int y);//根据索引获取二维数组中的元素

private:
	char gameArray[ROW][COL];//维护的二维数组
};

#endif // !_WALL_HEAD

