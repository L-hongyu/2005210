#include<iostream>
#include<malloc.h>
using namespace std;
#define maxsize 100
typedef int dataType;
typedef struct
{
	dataType data[maxsize];
	int length;
}Sqlist;

void CreatList(Sqlist* &L, int a[], int n) //����˳���

{
	L = (Sqlist*)malloc(sizeof(Sqlist));
	for (int i = 0; i < n; i++)
	{ 
		L->data[i] = a[i];

	}
	L->length = n;

}

void InitList(Sqlist*& L) //��ʼ��˳���

{
	L = (Sqlist*)malloc(sizeof(Sqlist));
	L->length = 0;
}

void DestoryList(Sqlist* &L) //�ͷ�˳���ռ�

{
		free(L);
}

void josephus(Sqlist* &L) //���Լɪ������ؼ�

{
	int t = 0;
	int m = 0;
	cout<<"�������������ڼ����˳���:"<<endl;
	cin >>m;
	if (m<1||m > L->length)

	{
		cout<<"û����ô���ˣ�"<<endl;
	}

	else
	{
		cout<<"����˳��Ϊ��"<<endl;
		for (int q = L->length; q >= 1; q--)
		{
			t = (t + m - 1) % q;
			cout<<" "<<L->data[t];
			for (int j = t + 1; j <= q - 1; j++)
			L->data[j - 1] = L->data[j];
		}
	}

}

void main()

{
	Sqlist *s;
	InitList(s);
	int a[100];
	int n = 0;
	cout << "������һ�������ˣ�" << endl;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		a[i] = i + 1;
	}
	CreatList(s, a, n);
	josephus(s);
	DestoryList(s);
}