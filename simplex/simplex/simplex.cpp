#include "simplex.h"

Simplex::Simplex()
{
	//unusual constructor
	cout << "enter N (count variables)\n";
	cin >> N;
	cout << "enter M (count equations)\n";
	cin >> M;
	M++;
	cout << "enter main function\'s rates\n";
	for (int i = 0; i < N; i++)
	{
		otherx[i] = i+1;//array ������ ������� ������
		cin >> matrix[0][i];
		matrix[0][i] = 0 - matrix[0][i];
	}
	cin >> matrix[0][N];
	otherx[N++] = 0;
	cout << "enter equations\'s rates in matrix\n";
	for (int i = 0; i < M; i++)
		basicx[i] = 0; //����� ������ ������� ������ �� �� = 0
	for (int i = 1; i < M; i++)
		for (int j = 0; j < N; j++)
			cin >> matrix[i][j];
}

void Simplex::�hangeTheRules(point mainElem)//���������� ������� �� �������� ������� ��������� �������� 
{
	//���� ������ � �������� ����� ������� ��������� ��������
	int c = basicx[mainElem.K]; 
	basicx[mainElem.K] = otherx[mainElem.L];
	otherx[mainElem.L] = c;
	// ��������� ������� ������� �� ���������
	matrix[mainElem.K][mainElem.L] = 1 / matrix[mainElem.K][mainElem.L];
	
	//���� ������� �� �� ������ �������� �� ���������� � ��� �������� ����� ����������� ����
	//�� �� ������������ �� ������ �[i][j]=M[i][j]-(M[i][l]*M[k][j])/M[k][l] �� M[k][l] �������� ���� ������� � ��������� ������� 
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (i != mainElem.K && j != mainElem.L)
				matrix[i][j] = matrix[i][j] - 
				(matrix[i][mainElem.L] * matrix[mainElem.K][j] * matrix[mainElem.K][mainElem.L]);

	//�������� �� ���� ���������� ������������ �� �������� �������� ��������
	for (int i = 0; i < N; i++)
		if (i != mainElem.L)
			matrix[mainElem.K][i] *= matrix[mainElem.K][mainElem.L];
	//�������� �� ���� �������� ������������ �� ��'���� �������� ��������
	for (int i = 0; i < M; i++)
		if (i != mainElem.K)
			matrix[i][mainElem.L] *= 0 - matrix[mainElem.K][mainElem.L];
}

point Simplex::checkAdmissibility()//�������� �� ����'����� ����� � ����� �������� ������� ����� �������������� �������
{
	//����� ���������� ��'������ �������� ������� ���� ����������� � ���� ����������
	//� ��������� ��'����� ������ ������ ���������
	point rez;
	rez.K = 0;
	rez.L = 0;
	for (int i = 1; i < M; i++)
		if (matrix[i][N - 1] - matrix[rez.K][N - 1] < -0.0001 && matrix[rez.K][N - 1] < 0) rez.K = i;
	if (!rez.K) return rez;
	for (int i = 0; i < N-1; i++)
		if (matrix[rez.K][i] - matrix[rez.K][rez.L] < -0.0001) rez.L = i;
	if (matrix[rez.K][rez.L] > -0.0001) rez.L = 0;
	//���� ��������� �������� �� ��������� ����������� ���� ������� M[0][0] 
	return rez;
}

point Simplex::checkOptimality()//�������� �� ������������� ����� � ����� �������� ������� ����� �������������� �������
{
	//����� ���������� ��'������ �������� M[i][j]/M[i][N-1] ���� ����������� � ���� dthnbrfks
	//� ��������� ��'����� ������ ������ ���������
	point rez;
	rez.K = 1;
	rez.L = 0;
	for (int i = 1; i < N - 1; i++)
		if (matrix[0][i] - matrix[0][rez.L] < -0.0001 && matrix[0][rez.L] < 0) rez.L = i;
	if (matrix[0][rez.L]>-0.0001) return rez;
	float min = infim;
	for (int i = 1; i < M; i++)
		if (matrix[rez.K][i] > 0 && matrix[rez.K][N - 1] / matrix[rez.K][i] - min < -0.0001)
		{ 
			rez.K = i; 
			min = matrix[rez.K][N - 1] / matrix[rez.K][i]; 
		}
	if (min - infim > -0.0001) rez.L = 0;
	//���� ��������� �������� �� ��������� ����������� ���� ������� M[�][0]
	//���� �=0 �� �� ����'����
	return rez;
}

void Simplex::findSolution()
{
	//����� �����'����
	bool flag = true; //�� ����� ������������ ����� � �������������� �������
	bool step = true; //���� ���� ����� (1 ����'����)/(������������ ����'����)
	bool solution = false;//�� � ����'����
	point mainElem = {0, 0};
	while (flag)
	{
		if (step)//����� 1 ����'����
		{
			mainElem = checkAdmissibility();// ������� ������� ����� �������������� �������
			if (!mainElem.K) step = false; //�������� �� ���� ������� � ������� � ������� �� ���������� ����� ���� �� ���
			else if (!mainElem.L)//�������� �� ������ � ����'����
			{
				cout << "there is no solution\n";
				flag = false;
			}
		}
		if (!step)
		{
			mainElem = checkOptimality();// ������� ������� ����� �������������� �������
			if (matrix[0][mainElem.L]>-0.0001) //�������� �� ���� ������� � ����������� ������� � ���������� ������ ���� �� ���
			{ 
				flag = false; 
				solution = true; 
			}
			else if (matrix[mainElem.K][mainElem.L]<-0.0001)//����'���� �����
			{
				cout << "function unlimited\n";
				flag = false;
			}
		}
		if (flag) �hangeTheRules(mainElem);// �� ������ ������������ �������
	}
	if (solution) //���� � ����'���� ������� ����
	{
		for (int i = 1; i < M; i++)
			if (basicx[i]) cout << "x" << basicx[i] << "=" << matrix[i][N - 1] << " ";
		cout << "\nother variables = 0\n";
		cout << "funcion = " << matrix[0][N - 1]<<endl;
	}
}