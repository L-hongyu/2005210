#include<iostream>
#include<stdio.h>
using namespace std;
#define MAX 100
typedef struct LNode 
{
	int data;
	struct LNode* next;
}LNode, * LinkList;

int InitList(LinkList& L)
{
	L = new LNode;
	L->next = NULL;
	return 1;
}

int ListLength(LinkList& L) 
{
	LNode* p;
	p = L->next;
	int length = 0;
	while (p) 
	{
		length++;
		p = p->next;
	}
	return length;
}

void TraveList(LinkList L) 
{
	LNode* p;
	p = L->next;
	while (p)
	{
	    cout<<" "<< p->data;
		p = p->next;
	}
	cout<<endl;
}

void CreateList(LinkList& L, int n)
{
	L = new LNode;
	L->next = NULL;
	LNode* r;
	r = L;
	for (int i = 0; i < n; i++) 
	{
		cout<<"�������"<< i + 1<<"��Ԫ�ص�ֵ:";
		LNode* s;
		s = new LNode;
		cin>>s->data;
		s->next = NULL;
		r->next = s;
		r = s;
	}
}

void DiffSet(LinkList& L1, LinkList& L2, LinkList& L3) 
{
	LNode* pa, * pb, * pc,*p;
	pa = L1->next;
	pb = L2->next;
	pc = L3 = L1;

	while (pa && pb) 
	{
		if (pa->data < pb->data)
		{
			p = pa;
			pa = pa->next;
			delete p;
		}
		else if (pa->data > pb->data)
		{
			p = pb;
			pb = pb->next;
			delete p;
		}
		else  
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
			p = pb;
			pb = pb->next;
			delete p;
		}
	}
	while (pa)
	{
		p = pa;
		pa = pa->next;
		delete p;
	}
	while (pb)
	{
		p = pb;
		pb = pb->next;
		delete p;
	}
	pc->next = NULL;
}

int main()
{
	LinkList L1, L2, L3;

	if (InitList(L1))
	{
		cout<<"L1��ʼ���ɹ�!"<<endl;
	}
	else 
	{
		cout<<"L1��ʼ��ʧ��!"<<endl;
	}
	if (InitList(L2)) 
	{
		cout<<"L2��ʼ���ɹ�!"<<endl;
	}
	else 
	{
		cout<<"L2��ʼ��ʧ��!"<<endl;
	}
	if (InitList(L3)) 
	{
		cout<<"L3��ʼ���ɹ�!"<<endl;
	}
	else 
	{
		cout<<"L3��ʼ��ʧ��!"<<endl;
	}
	cout<<"������L1�ĳ���:";
	int n1;
	cin>>n1;
	CreateList(L1, n1);
	TraveList(L1);
	cout<<"������L2�ĳ���:";
	int n2;
	cin>>n2;
	CreateList(L2, n2);
	TraveList(L2);
	DiffSet(L1, L2, L3);
	cout<<"�����������Ԫ��Ϊ:";
	TraveList(L3);
}