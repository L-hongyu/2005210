#include<iostream>
#include<stdio.h>
#include<malloc.h>
using namespace std;
typedef struct LNode
{
	int coef;
	int exp;
	struct LNode* next;
}LinkNode;
void CreateList(LinkNode*& L) //创建单链表
{
	int m, c, e;
	LinkNode* s, * r;
	L = (LinkNode*)malloc(sizeof(LinkNode));
	r = L;
	cout << "请输入多项式的项数：" << endl;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cout << "请输入第" << i + 1 << "项的系数和指数:" ;
		cin >> c >> e;
		s = (LinkNode*)malloc(sizeof(LinkNode));
		s->coef = c;
		s->exp = e;
		r->next = s;
		r = s;
	}
	r->next = NULL;
}
int ListLength(LinkNode*& L) //求链表长度
{
	int n=0;
	LinkNode* p = L;
	while (p->next != NULL)
	{
		n++;
		p = p->next;
	}
	return(n);
}
void DispList(LinkNode* L) //输出多项式
{
	int j = 0;
	LinkNode* p = L->next;
	while (p != NULL)
	{
		cout << p->coef << "X^" << p->exp;
		j++;
		if (j<ListLength(L))
			cout << "+";
		p = p->next;
	}
	cout << endl;
}
LinkNode* ListAdd(LinkNode* p, LinkNode* q) //一元多项式的求和
{
	LinkNode* L, * s, * r;
	p = p->next;
	q = q->next;
	L= (LinkNode*)malloc(sizeof(LinkNode));
	r = L;
	while (p != NULL && q != NULL)
	{
		if (p->exp < q->exp)
		{
		s = (LinkNode*)malloc(sizeof(LinkNode));
		s->coef = q->coef;
		s->exp = q->exp;
		r->next = s;
		r = s;
		q = q->next;
		}
		else if (p->exp > q->exp)
		{
			s= (LinkNode*)malloc(sizeof(LinkNode));
			s->coef = p->coef;
			s->exp = p->exp;
			r->next = s;
			r = s;
			p = p->next;
		}
		else
		{
			s = (LinkNode*)malloc(sizeof(LinkNode));
			s->coef = p->coef + q->coef;
			s->exp = p->exp;
			if (s->coef == 0)
				free(s);
			else
			{
				r->next = s;
				r = s;
			}
			p = p->next;
			q = q->next;
		}
	}
	if (p != NULL)
		r->next = p;
	else if (q != NULL)
		r->next = q;
	else
		r->next = NULL;
	return L;
}
int main()
{
	LinkNode* P, * Q;
	cout << "请输入第一个多项式：" << endl;
	CreateList(P);
	DispList(P);
	cout << "*************************" << endl;
	cout << "请输入第二个多项式：" << endl;
	CreateList(Q);
	DispList(Q);
	LinkNode* L = ListAdd(P, Q);
	cout << "求和后的的多项式为：" << endl;
	DispList(L);
	return 0;
    
}

