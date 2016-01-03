#include <iostream>

using namespace std;

const int nMax = 10;
const float infim = 2000000000;

struct point
{
	int L;
	int K;
};

class Simplex
{
	int N;
	int M;
	int basicx[nMax];//масив номерів базових змінних
	int otherx[nMax];//array номерів допоміжних змінних
	float matrix[nMax][nMax];
public:
	Simplex();
	~Simplex(){}
	void findSolution();
private:
	// перебудова матриці
	void сhangeTheRules(point mainElem);
	//пошук елемента відноно якого перебудовуємо
	point checkAdmissibility();
	point checkOptimality();
};
