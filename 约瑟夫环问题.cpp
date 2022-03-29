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

void CreatList(Sqlist* &L, int a[], int n) //创建顺序表

{
	L = (Sqlist*)malloc(sizeof(Sqlist));
	for (int i = 0; i < n; i++)
	{ 
		L->data[i] = a[i];

	}
	L->length = n;

}

void InitList(Sqlist*& L) //初始化顺序表

{
	L = (Sqlist*)malloc(sizeof(Sqlist));
	L->length = 0;
}

void DestoryList(Sqlist* &L) //释放顺序表空间

{
		free(L);
}

void josephus(Sqlist* &L) //解决约瑟夫环问题关键

{
	int t = 0;
	int m = 0;
	cout<<"请输入数报到第几个人出来:"<<endl;
	cin >>m;
	if (m<1||m > L->length)

	{
		cout<<"没有这么多人！"<<endl;
	}

	else
	{
		cout<<"出列顺序为："<<endl;
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
	cout << "请输入一共多少人：" << endl;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		a[i] = i + 1;
	}
	CreatList(s, a, n);
	josephus(s);
	DestoryList(s);
}