#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
//单链表的结构定义 
typedef struct LNode
{
	int data;			
	struct LNode* next;	
}LNode;					

//头插法建立单链表
void createlistF(LNode*& L, int a[], int n)
{
	LNode* s;
	int i;
	L = (LNode*)malloc(sizeof(LNode));
	L->next = NULL;
	for (i = 0; i < n; ++i)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = a[i];
		s->next = L->next;	
		L->next = s;			

	}

}

//打印链表数据 
void printfList(LNode* L)
{
	LNode* temp = L;
	int count = 0;
	cout << "表中的元素为:" << endl;
	while (temp->next)
	{
		temp = temp->next;
		cout << temp->data << endl;
		count++;
		if (count % 5 == 0)
		{
			cout << endl << endl;
		}
	}
	cout << endl << endl;

}

int main()
{
	LNode* L;
	int n;
	cout << "请输入数组的个数：" << endl;
	cin >> n ;
	int a[100];
	cout<<"请输入数组中的数："<<endl;;
	for (int i = 0; i < n; ++i)
	{
		cin>>a[i];
	}

	//测试头插法建立链表
	createlistF(L, a, n);

	//查看建立后的链表 
	printfList(L);

	return 0;
}
