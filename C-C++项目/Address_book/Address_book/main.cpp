#include <iostream>
#include <string>
using namespace std;

#define MAX 1000

//联系人结构体
struct Person
{
	string m_Name;//姓名
	int m_Sex;//性别 1.男，2.女
	int m_Age;//年龄
	string m_Phone;//电话
	string m_Addr;//住址
};

//通讯录结构体
struct Addressbooks
{
	struct Person personArray[MAX];//通讯录中保存的联系人数组
	int m_Size;//通讯录中人员个数
};
//菜单界面
void showMenu()
{
	cout << "********************************" << endl;
	cout << "**********1.添加联系人**********" << endl;
	cout << "**********2.显示联系人**********" << endl;
	cout << "**********3.删除联系人**********" << endl;
	cout << "**********4.查找联系人**********" << endl;
	cout << "**********5.修改联系人**********" << endl;
	cout << "**********6.清空联系人**********" << endl;
	cout << "**********0.退出通讯录**********" << endl;
	cout << "********************************" << endl;
}

//添加联系人
void addPerson(Addressbooks *abs)
{
	//判断通讯录是否满
	if (abs->m_Size == MAX)
	{
		cout << "通讯录已满，无法添加！" << endl;
		return;
	}
	else
	{
		//添加具体联系人

		//姓名
		string name;
		cout << "请输入姓名：";
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;
		//性别
		cout << "请输入性别：" << endl;
		cout << "1---男" << endl;
		cout << "2---女" << endl;
		int sex = 0;

		while (true)
		{
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "输入有误，请重新输入！" << endl;
		}
		
		//年龄
		cout << "请输入年龄：";
		int age = 0;
		cin >> age;
		abs->personArray[abs->m_Size].m_Age = age;

		//电话
		cout << "请输入联系电话：";
		string phone;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		//地址
		cout << "请输入家庭住址：";
		string addr;
		cin >> addr;
		abs->personArray[abs->m_Size].m_Addr = addr;

		//更新通讯录人数
		abs->m_Size++;

		cout << "添加成功" << endl;

		system("pause");//按任意键继续
		system("cls");//清屏
	}
}


//显示联系人
void showPerson(Addressbooks *abs)
{
	if (abs->m_Size == 0)
	{
		cout << "当前记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < abs->m_Size; i++)
		{
			cout << "姓名：" << abs->personArray[i].m_Name << "\t";
			cout << "性别：" << (abs->personArray[i].m_Sex == 1 ?"男":"女")<< "\t";
			cout << "年龄：" << abs->personArray[i].m_Age << "\t";
			cout << "电话：" << abs->personArray[i].m_Phone << "\t";
			cout << "地址：" << abs->personArray[i].m_Addr << endl;
		}
	}
	system("pause");//按任意键继续
	system("cls");//清屏
}

//检查联系人是否存在,返回联系人所在数组中的具体位置，否则返回-1
int isExist(Addressbooks *abs, string name)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		if (abs->personArray[i].m_Name == name)
		{
			return i;
		}
	}
	return -1;
	
}

//删除联系人
void deletePerson(Addressbooks *abs)
{
	cout << "请输入需要删除的联系人姓名：";
	string name;
	cin >> name;
	int ret = isExist(abs, name);

	if (ret != -1)
	{
		//查找到此人，删除
		for (int i = ret; i < abs->m_Size; i++)
		{
			//数据前移
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_Size--;
		cout << "删除成功！" << endl;
	}
	else
	{
		cout << "查无此人！" << endl;
	}

	system("pause");//按任意键继续
	system("cls");//清屏
}

//查找联系人
void findPerson(Addressbooks *abs)
{
	cout << "请输入您要查找的联系人：";
	string name;
	cin >> name;
	
	int ret = isExist(abs, name);
	if (ret != -1)
	{
		cout << "姓名：" << abs->personArray[ret].m_Name << "\t";
		cout << "性别：" << (abs->personArray[ret].m_Sex == 1 ? "男" : "女") << "\t";
		cout << "年龄：" << abs->personArray[ret].m_Age << "\t";
		cout << "电话：" << abs->personArray[ret].m_Phone << "\t";
		cout << "地址：" << abs->personArray[ret].m_Addr << endl;
	}
	else
	{
		cout << "查无此人！" << endl;
	}

	system("pause");//按任意键继续
	system("cls");//清屏
}

//修改联系人
void modifyPerson(Addressbooks *abs)
{
	cout << "请输入您要修改的联系人姓名：";
	string name;
	cin >> name;

	int ret = isExist(abs, name);

	if (ret != -1)
	{
		cout << "姓名：";
		string name;
		cin >> name;
		abs->personArray[ret].m_Name = name;

		cout << "性别：" << endl;
		cout << "1---男" << endl;
		cout << "2---女" << endl;
		int sex = 0;

		while (true)
		{
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[ret].m_Sex = sex;
				break;
			}
			cout << "输入有误，请重新输入！" << endl;
		}

		cout << "年龄：";
		int age = 0;
		cin >> age;
		abs->personArray[ret].m_Age = age;

		cout << "电话：";
		string phone;
		cin >> phone;
		abs->personArray[ret].m_Phone = phone;

		cout << "地址：";
		string addr;
		cin >> addr;
		abs->personArray[ret].m_Addr = addr;

		cout << "修改成功！" << endl;
	}
	else
	{
		cout << "查无此人！" << endl;
	}

	system("pause");//按任意键继续
	system("cls");//清屏
}

//清空通讯录
void cleanPerson(Addressbooks *abs)
{
	abs->m_Size = 0;
	cout << "通讯录已清空！" << endl;

	system("pause");//按任意键继续
	system("cls");//清屏
}
int main()
{
	int select = 0;
	Addressbooks abs;
	abs.m_Size = 0;
	//showMenu();
	while (true)
	{
		showMenu();
		cout << "请选择：";
		cin >> select;
		switch (select)
		{
		case 1://1.添加
			addPerson(&abs);
			break;
		case 2://2.显示
			showPerson(&abs);
			break;
		case 3://3.删除
			deletePerson(&abs);
			break;
		case 4://4.查找
			findPerson(&abs);
			break;
		case 5://5.修改
			modifyPerson(&abs);
			break;
		case 6://6.清空
			cleanPerson(&abs);
			break;
		case 0://0.退出
			cout << "欢迎下次使用！" << endl;
			system("pause");
			return 0;
			break;
		default:
			break;
		}
	}
	
	system("pause");
	return 0;
}