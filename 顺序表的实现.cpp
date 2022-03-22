#include<iostream>
#include<memory.h>
#define MAXSIZE 10
using namespace std;

typedef struct {
	int* elem;
	int length;
}SqList;

bool List_Init(SqList& L) //����һ�������Ա�
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

bool List_Insert(SqList& L, int i, int e) //����
{
	if (i<1 || i>L.length + 1)
	{
		return false;//����λ�ò��Ϸ�
	}
	if (L.length >= MAXSIZE)//˳���ռ�����
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

bool GetElem(SqList L, int i, int& e) //ȡԪ��
{
	if (i<1 || i>L.length)
	{
		cout << "����λ�ò��Ϸ�" << endl;
		return false;
	}
	e = L.elem[i - 1];
	return true;
}

bool Delete_List(SqList& L, int i) //ɾ��
{                                   
	if (i<1 || i>L.length)
	{
		cout << "�����±겻�Ϸ�" << endl;
		return false;
	}
	else
	{
		for (int j = i; j < L.length; j++)
		{
			L.elem[j - 1] = L.elem[j];
		}
		L.length--;
		cout << "ɾ���ɹ���" << endl;
	}
	return true;
}

int LocateElem(SqList L, int e) //����
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
	cout << "====================" << endl << "(1).����һ�������Ա�:" << endl << endl;
	SqList L;
	if (!List_Init(L))
	{
		cout << "(Failure)��������ʧ��!" << endl << endl;
	}
	else
	{
		cout << "(Success)���������ɹ�!" << endl << endl;;


		cout << "====================" << endl << "(2).�Զ���һ��˳���:" << endl << endl;
		int n, e1;
		cout << "����˳�����n:"; cin >> n;
		cout << "����������n��ֵ(�Կո�ָ�):";
		for (int i = 1; i <= n; i++)
		{
			cin >> e1;
			List_Insert(L, i, e1);
		}
		cout << "��ǰ˳���Ϊ��";
		for (int i = 1; i <= L.length; i++)
		{
			int tem;
			GetElem(L, i, tem);
			cout << tem << " ";
		}
		cout << endl;


		cout << "====================" << endl << "(3).����:" << endl << endl;
		int i, e2, temp;
		cout << "���������λ��:";
		cin >> i;
		cout << "���������ֵ:";
		cin >> e2;
		temp = List_Insert(L, i, e2);
		if (temp)
		{
			cout << "����ɹ�!" << endl;
		}
		else if (!temp)
		{
			cout << "����ʧ�ܣ�\n";
			if (temp == false)
			{

				cout << "˳���ռ�����" << endl;
			}
			else
			{
				cout << "����λ�ò��Ϸ�" << endl;
			}
		}
		cout << "��ǰ˳���Ϊ��";
		for (int i = 1; i <= L.length; i++)
		{
			int e;
			GetElem(L, i, e);
			cout << e << " ";
		}
		cout << endl;

		cout << "====================" << endl << "(4).ɾ��:" << endl << endl;
		int l;
		cout << "������Ҫɾ��Ԫ�ص�λ�ã�"; cin >> l;
		Delete_List(L, l);

		cout << "��ǰ˳���Ϊ��";
		for (int i = 1; i <= L.length; i++)
		{
			int e;
			GetElem(L, i, e);
			cout << e << " ";
		}
		cout << endl;

		cout << "====================" << endl << "(5).����:" << endl << endl;
		cout << "������Ҫ���ҵ�ֵ:";
		int e3;
		cin >> e3;
		temp = LocateElem(L, e3);
		if (!temp)
		{
			cout << "(Sorry)˳�����û�����ֵ" << endl;
		}
		else
		{
			cout << "���ҳɹ���Ԫ��λ��Ϊ��" << temp << endl << endl;
		}

		delete[]L.elem;
		cout << "====================" << endl << "�������ͷţ�" << endl << endl;
	}
	return 0;
}

	
	





