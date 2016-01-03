#include "matrix.h"

int main()
{
	matrix M(5, 5);
	M[3][2] = 2;
	cout << M[-1][2] << M[3][3] << endl;
	system("pause");
	return 0;
}