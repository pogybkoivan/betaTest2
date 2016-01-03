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
	static void calculate(rect R, float**  &matrix, float*  &func, int max);//прогонка ділянки матриці
	progonka();
	~progonka(){}
	void calculate();//паралельна прогонка всієї матриці
private:
	int NMax;
	float** Matrix;//матриця
	float*  Func;//вектор значення рядків
	void problematic_dots(rect R1,rect R2); //прибирання зайвих рядків(результата паралельної прогонки)
	void print();
};