#include "matrix.h"
//������������
line::line()//������ �����
{
	NMax = 0;
	deque = NULL;
	pointer = NULL;
}

line::line(int n)//����� ���������� � ���������� 0
{
	NMax = n;
	deque = NULL;
	for (int i = n; i > 0; --i)
	{
		simpleCell* N = new simpleCell;
		N->leftLink = NULL;
		N->rightLink = deque;
		N->data = 0;
		N->index = i;
		if (deque) deque->leftLink = N;
		deque = N;
	}
	pointer = deque;
}

line::line(int n, int m)//����� ��������� � ���������� �
{
	NMax = n;
	deque = NULL;
	for (int i = n; i > 0; --i)
	{
		simpleCell* N = new simpleCell;
		N->leftLink = NULL;
		N->rightLink = deque;
		N->data = m;
		N->index = i;
		if (deque) deque->leftLink = N;
		deque = N;
	}
	pointer = deque;
}

int& line::operator[](int n)//��������[]
{
	//�������� �����
	if (!pointer) { cout << "Empty line!!!"; return n; }
	if (n < 0){ cout << "Uncorect number!!!"; return n; }
	if (n > NMax){ cout << "Uncorect number!!!"; return n; }
	//��� �� ������ � ��������� ������ ��������� � ��������� 
	if (n > pointer->index)
		while (n != pointer->index)
			pointer = pointer->rightLink;
	else
		while (n != pointer->index)
			pointer = pointer->leftLink;
	return pointer->data;
}

//������������
matrix::matrix()//������ �����
{
	NMax = 0;
	MMax = 0;
	sqeare = NULL;
	pointer = sqeare;
}

matrix::matrix(int n, int m)//����� �*� ���������� 0
{
	NMax = n;
	MMax = m;
	sqeare = NULL;
	for (int i = MMax - 1; i >= 0; i--)
	{
		simpleLine* N = new simpleLine;
		N->topLink = NULL;
		N->bottomLink = sqeare;
		N->index = i;
		N->data = new line(NMax);
		sqeare = N;
	}
	pointer = sqeare;
}

matrix::matrix(int n, int m, int k)//����� �*� ���������� �
{
	NMax = n;
	MMax = m;
	sqeare = NULL;
	for (int i = MMax - 1; i >= 0; i--)
	{
		simpleLine* N = new simpleLine;
		N->topLink = NULL;
		N->bottomLink = sqeare;
		N->index = i;
		N->data = new line(NMax, k);
		sqeare = N;
	}
	pointer = sqeare;
}

line& matrix::operator[](int n)
{
	//�������� �����
	if (!pointer) { cout << "Empty line!!!"; return *pointer->data; }
	if (n < 0){ cout << "Uncorect number!!!"; return *pointer->data; }
	if (n > NMax){ cout << "Uncorect number!!!"; return *pointer->data; }
	//��� �� ������ � ������ ��������� ����� 
	if (n > pointer->index)
		while (n != pointer->index)
			pointer = pointer->bottomLink;
	else
		while (n != pointer->index)
			pointer = pointer->topLink;
	return *pointer->data;
}

matrix::~matrix()
{
	while (sqeare)
	{
		simpleLine* temp = sqeare;
		sqeare = sqeare->bottomLink;
		delete temp;
	}
	delete sqeare;
}

line::~line()
{
	while (deque)
	{
		simpleCell* temp = deque;
		deque = deque->rightLink;
		delete temp;
	}
	delete deque;
}