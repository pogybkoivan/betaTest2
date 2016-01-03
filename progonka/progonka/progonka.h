#include <iostream>
#include <vector>

using namespace std;

struct rect
{
	int start;
	int end;
};

struct cell
{
	rect r;
	float**  &matrix;
	float*  &func;
	int max;
};

class progonka
{
public:
	static void calculate(rect R, float**  &matrix, float*  &func, int max);//�������� ������ �������
	progonka();
	~progonka(){}
	void calculate();//���������� �������� �񳺿 �������
private:
	int NMax;
	float** Matrix;//�������
	float*  Func;//������ �������� �����
	void problematic_dots(rect R1,rect R2); //���������� ������ �����(���������� ���������� ��������)
	void print();
};