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
	int basicx[nMax];//����� ������ ������� ������
	int otherx[nMax];//array ������ ��������� ������
	float matrix[nMax][nMax];
public:
	Simplex();
	~Simplex(){}
	void findSolution();
private:
	// ���������� �������
	void �hangeTheRules(point mainElem);
	//����� �������� ������ ����� ������������
	point checkAdmissibility();
	point checkOptimality();
};
