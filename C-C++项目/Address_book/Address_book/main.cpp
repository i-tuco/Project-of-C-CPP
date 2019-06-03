#include <iostream>
#include <string>
using namespace std;

#define MAX 1000

//��ϵ�˽ṹ��
struct Person
{
	string m_Name;//����
	int m_Sex;//�Ա� 1.�У�2.Ů
	int m_Age;//����
	string m_Phone;//�绰
	string m_Addr;//סַ
};

//ͨѶ¼�ṹ��
struct Addressbooks
{
	struct Person personArray[MAX];//ͨѶ¼�б������ϵ������
	int m_Size;//ͨѶ¼����Ա����
};
//�˵�����
void showMenu()
{
	cout << "********************************" << endl;
	cout << "**********1.�����ϵ��**********" << endl;
	cout << "**********2.��ʾ��ϵ��**********" << endl;
	cout << "**********3.ɾ����ϵ��**********" << endl;
	cout << "**********4.������ϵ��**********" << endl;
	cout << "**********5.�޸���ϵ��**********" << endl;
	cout << "**********6.�����ϵ��**********" << endl;
	cout << "**********0.�˳�ͨѶ¼**********" << endl;
	cout << "********************************" << endl;
}

//�����ϵ��
void addPerson(Addressbooks *abs)
{
	//�ж�ͨѶ¼�Ƿ���
	if (abs->m_Size == MAX)
	{
		cout << "ͨѶ¼�������޷���ӣ�" << endl;
		return;
	}
	else
	{
		//��Ӿ�����ϵ��

		//����
		string name;
		cout << "������������";
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;
		//�Ա�
		cout << "�������Ա�" << endl;
		cout << "1---��" << endl;
		cout << "2---Ů" << endl;
		int sex = 0;

		while (true)
		{
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "�����������������룡" << endl;
		}
		
		//����
		cout << "���������䣺";
		int age = 0;
		cin >> age;
		abs->personArray[abs->m_Size].m_Age = age;

		//�绰
		cout << "��������ϵ�绰��";
		string phone;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		//��ַ
		cout << "�������ͥסַ��";
		string addr;
		cin >> addr;
		abs->personArray[abs->m_Size].m_Addr = addr;

		//����ͨѶ¼����
		abs->m_Size++;

		cout << "��ӳɹ�" << endl;

		system("pause");//�����������
		system("cls");//����
	}
}


//��ʾ��ϵ��
void showPerson(Addressbooks *abs)
{
	if (abs->m_Size == 0)
	{
		cout << "��ǰ��¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < abs->m_Size; i++)
		{
			cout << "������" << abs->personArray[i].m_Name << "\t";
			cout << "�Ա�" << (abs->personArray[i].m_Sex == 1 ?"��":"Ů")<< "\t";
			cout << "���䣺" << abs->personArray[i].m_Age << "\t";
			cout << "�绰��" << abs->personArray[i].m_Phone << "\t";
			cout << "��ַ��" << abs->personArray[i].m_Addr << endl;
		}
	}
	system("pause");//�����������
	system("cls");//����
}

//�����ϵ���Ƿ����,������ϵ�����������еľ���λ�ã����򷵻�-1
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

//ɾ����ϵ��
void deletePerson(Addressbooks *abs)
{
	cout << "��������Ҫɾ������ϵ��������";
	string name;
	cin >> name;
	int ret = isExist(abs, name);

	if (ret != -1)
	{
		//���ҵ����ˣ�ɾ��
		for (int i = ret; i < abs->m_Size; i++)
		{
			//����ǰ��
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_Size--;
		cout << "ɾ���ɹ���" << endl;
	}
	else
	{
		cout << "���޴��ˣ�" << endl;
	}

	system("pause");//�����������
	system("cls");//����
}

//������ϵ��
void findPerson(Addressbooks *abs)
{
	cout << "��������Ҫ���ҵ���ϵ�ˣ�";
	string name;
	cin >> name;
	
	int ret = isExist(abs, name);
	if (ret != -1)
	{
		cout << "������" << abs->personArray[ret].m_Name << "\t";
		cout << "�Ա�" << (abs->personArray[ret].m_Sex == 1 ? "��" : "Ů") << "\t";
		cout << "���䣺" << abs->personArray[ret].m_Age << "\t";
		cout << "�绰��" << abs->personArray[ret].m_Phone << "\t";
		cout << "��ַ��" << abs->personArray[ret].m_Addr << endl;
	}
	else
	{
		cout << "���޴��ˣ�" << endl;
	}

	system("pause");//�����������
	system("cls");//����
}

//�޸���ϵ��
void modifyPerson(Addressbooks *abs)
{
	cout << "��������Ҫ�޸ĵ���ϵ��������";
	string name;
	cin >> name;

	int ret = isExist(abs, name);

	if (ret != -1)
	{
		cout << "������";
		string name;
		cin >> name;
		abs->personArray[ret].m_Name = name;

		cout << "�Ա�" << endl;
		cout << "1---��" << endl;
		cout << "2---Ů" << endl;
		int sex = 0;

		while (true)
		{
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[ret].m_Sex = sex;
				break;
			}
			cout << "�����������������룡" << endl;
		}

		cout << "���䣺";
		int age = 0;
		cin >> age;
		abs->personArray[ret].m_Age = age;

		cout << "�绰��";
		string phone;
		cin >> phone;
		abs->personArray[ret].m_Phone = phone;

		cout << "��ַ��";
		string addr;
		cin >> addr;
		abs->personArray[ret].m_Addr = addr;

		cout << "�޸ĳɹ���" << endl;
	}
	else
	{
		cout << "���޴��ˣ�" << endl;
	}

	system("pause");//�����������
	system("cls");//����
}

//���ͨѶ¼
void cleanPerson(Addressbooks *abs)
{
	abs->m_Size = 0;
	cout << "ͨѶ¼����գ�" << endl;

	system("pause");//�����������
	system("cls");//����
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
		cout << "��ѡ��";
		cin >> select;
		switch (select)
		{
		case 1://1.���
			addPerson(&abs);
			break;
		case 2://2.��ʾ
			showPerson(&abs);
			break;
		case 3://3.ɾ��
			deletePerson(&abs);
			break;
		case 4://4.����
			findPerson(&abs);
			break;
		case 5://5.�޸�
			modifyPerson(&abs);
			break;
		case 6://6.���
			cleanPerson(&abs);
			break;
		case 0://0.�˳�
			cout << "��ӭ�´�ʹ�ã�" << endl;
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