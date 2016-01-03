#include <iostream>

using namespace std;

struct simpleCell
{
	simpleCell* leftLink;
	simpleCell* rightLink;
	int data;
	int index;
};

class line
{
public:
	// ������������
	line();
	line(int n);
	line(int n, int m);
	
	~line();
	//���������� ��������[]
	int& operator[](int n);
private:
	//��� ������ �����
	simpleCell* deque;
	//������, �� �������� �������� �� ������
	simpleCell* pointer;
	//���������
	int NMax;
};

struct simpleLine
{
	simpleLine* topLink;
	simpleLine* bottomLink;
	line *data;
	int index;
};

class matrix
{
public:
	//������������
	matrix();
	matrix(int n, int m);
	matrix(int n, int m, int k);
	
	//���������� ���������[]
	line& operator[](int n);
	~matrix();
private:
	//��� �����
	simpleLine* sqeare;
	//������, �� �������� �������� �� ������
	simpleLine* pointer;
	//���������
	int NMax;
	int MMax;
};