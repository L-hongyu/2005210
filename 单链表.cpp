#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
//������Ľṹ���� 
typedef struct LNode
{
	int data;			
	struct LNode* next;	
}LNode;					

//ͷ�巨����������
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

//��ӡ�������� 
void printfList(LNode* L)
{
	LNode* temp = L;
	int count = 0;
	cout << "���е�Ԫ��Ϊ:" << endl;
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
	cout << "����������ĸ�����" << endl;
	cin >> n ;
	int a[100];
	cout<<"�����������е�����"<<endl;;
	for (int i = 0; i < n; ++i)
	{
		cin>>a[i];
	}

	//����ͷ�巨��������
	createlistF(L, a, n);

	//�鿴����������� 
	printfList(L);

	return 0;
}
