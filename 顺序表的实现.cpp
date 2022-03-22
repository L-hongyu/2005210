#include<iostream>
#include<memory.h>
#define MAXSIZE 10
using namespace std;

typedef struct {
	int* elem;
	int length;
}SqList;

bool List_Init(SqList& L) //构造一个空线性表
{
	L.elem = new int[MAXSIZE];
	memset(L.elem, 0, sizeof(L));
	if (!L.elem)
	{
		return false;
	}
	L.length = 0;
	return true;
}

bool List_Insert(SqList& L, int i, int e) //插入
{
	if (i<1 || i>L.length + 1)
	{
		return false;//插入位置不合法
	}
	if (L.length >= MAXSIZE)//顺序表空间已满
	{
		return false;
	}
	for (int j = L.length - 1; j >= i - 1; j--)
	{
		L.elem[j + 1] = L.elem[j];
	}
	L.elem[i - 1] = e;
	L.length++;
	return true;
}

bool GetElem(SqList L, int i, int& e) //取元素
{
	if (i<1 || i>L.length)
	{
		cout << "访问位置不合法" << endl;
		return false;
	}
	e = L.elem[i - 1];
	return true;
}

bool Delete_List(SqList& L, int i) //删除
{                                   
	if (i<1 || i>L.length)
	{
		cout << "输入下标不合法" << endl;
		return false;
	}
	else
	{
		for (int j = i; j < L.length; j++)
		{
			L.elem[j - 1] = L.elem[j];
		}
		L.length--;
		cout << "删除成功！" << endl;
	}
	return true;
}

int LocateElem(SqList L, int e) //查找
{
	for (int i = 0; i < L.length; i++)
	{
		if (L.elem[i] == e)
		{
			return i + 1;
		}
	}
	return 0;
}

int main()
{
	cout << "====================" << endl << "(1).构造一个空线性表:" << endl << endl;
	SqList L;
	if (!List_Init(L))
	{
		cout << "(Failure)空链表创建失败!" << endl << endl;
	}
	else
	{
		cout << "(Success)空链表创建成功!" << endl << endl;;


		cout << "====================" << endl << "(2).自定义一个顺序表:" << endl << endl;
		int n, e1;
		cout << "输入顺序表长度n:"; cin >> n;
		cout << "请依次输入n个值(以空格分隔):";
		for (int i = 1; i <= n; i++)
		{
			cin >> e1;
			List_Insert(L, i, e1);
		}
		cout << "当前顺序表为：";
		for (int i = 1; i <= L.length; i++)
		{
			int tem;
			GetElem(L, i, tem);
			cout << tem << " ";
		}
		cout << endl;


		cout << "====================" << endl << "(3).插入:" << endl << endl;
		int i, e2, temp;
		cout << "请输入插入位置:";
		cin >> i;
		cout << "请输入插入值:";
		cin >> e2;
		temp = List_Insert(L, i, e2);
		if (temp)
		{
			cout << "插入成功!" << endl;
		}
		else if (!temp)
		{
			cout << "插入失败！\n";
			if (temp == false)
			{

				cout << "顺序表空间已满" << endl;
			}
			else
			{
				cout << "插入位置不合法" << endl;
			}
		}
		cout << "当前顺序表为：";
		for (int i = 1; i <= L.length; i++)
		{
			int e;
			GetElem(L, i, e);
			cout << e << " ";
		}
		cout << endl;

		cout << "====================" << endl << "(4).删除:" << endl << endl;
		int l;
		cout << "请输入要删除元素的位置："; cin >> l;
		Delete_List(L, l);

		cout << "当前顺序表为：";
		for (int i = 1; i <= L.length; i++)
		{
			int e;
			GetElem(L, i, e);
			cout << e << " ";
		}
		cout << endl;

		cout << "====================" << endl << "(5).查找:" << endl << endl;
		cout << "请输入要查找的值:";
		int e3;
		cin >> e3;
		temp = LocateElem(L, e3);
		if (!temp)
		{
			cout << "(Sorry)顺序表中没有这个值" << endl;
		}
		else
		{
			cout << "查找成功，元素位置为：" << temp << endl << endl;
		}

		delete[]L.elem;
		cout << "====================" << endl << "链表已释放！" << endl << endl;
	}
	return 0;
}

	
	





