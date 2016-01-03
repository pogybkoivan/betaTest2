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
		otherx[i] = i+1;//array номерів базових змінних
		cin >> matrix[0][i];
		matrix[0][i] = 0 - matrix[0][i];
	}
	cin >> matrix[0][N];
	otherx[N++] = 0;
	cout << "enter equations\'s rates in matrix\n";
	for (int i = 0; i < M; i++)
		basicx[i] = 0; //масив номерів базових змінних які не = 0
	for (int i = 1; i < M; i++)
		for (int j = 0; j < N; j++)
			cin >> matrix[i][j];
}

void Simplex::сhangeTheRules(point mainElem)//перебудова матриці за правилом відносно вибраного елемента 
{
	//своп базової і допоміжної змінної відносно вибраного елемента
	int c = basicx[mainElem.K]; 
	basicx[mainElem.K] = otherx[mainElem.L];
	otherx[mainElem.L] = c;
	// вибрааний елемент змінюємо на обернений
	matrix[mainElem.K][mainElem.L] = 1 / matrix[mainElem.K][mainElem.L];
	
	//якщо елемент не має спільної вертикалі чи горизонталі з тим відностно якого проводяться зміни
	//то він вираховується по формулі М[i][j]=M[i][j]-(M[i][l]*M[k][j])/M[k][l] де M[k][l] вибраний нами елемент в початковій матриці 
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (i != mainElem.K && j != mainElem.L)
				matrix[i][j] = matrix[i][j] - 
				(matrix[i][mainElem.L] * matrix[mainElem.K][j] * matrix[mainElem.K][mainElem.L]);

	//елементи на одній горизонталі домножаються на обернене значення елемента
	for (int i = 0; i < N; i++)
		if (i != mainElem.L)
			matrix[mainElem.K][i] *= matrix[mainElem.K][mainElem.L];
	//елементи не одній вертикалі домножаються на від'ємне обернене значення
	for (int i = 0; i < M; i++)
		if (i != mainElem.K)
			matrix[i][mainElem.L] *= 0 - matrix[mainElem.K][mainElem.L];
}

point Simplex::checkAdmissibility()//перевірка на розв'язніть умови і пошук елемента відносно якого перебудовується матриця
{
	//пошук найменшого від'ємного елемента матриці який знаходиться в одній горизонталі
	//з найменшим від'ємним крайнім правим елементом
	point rez;
	rez.K = 0;
	rez.L = 0;
	for (int i = 1; i < M; i++)
		if (matrix[i][N - 1] - matrix[rez.K][N - 1] < -0.0001 && matrix[rez.K][N - 1] < 0) rez.K = i;
	if (!rez.K) return rez;
	for (int i = 0; i < N-1; i++)
		if (matrix[rez.K][i] - matrix[rez.K][rez.L] < -0.0001) rez.L = i;
	if (matrix[rez.K][rez.L] > -0.0001) rez.L = 0;
	//якщо потрібного елемента не виявилося результатом буде елемент M[0][0] 
	return rez;
}

point Simplex::checkOptimality()//перевірка на оптимальнысть умови і пошук елемента відносно якого перебудовується матриця
{
	//пошук найменшого від'ємного відношеня M[i][j]/M[i][N-1] який знаходиться в одній dthnbrfks
	//з найменшим від'ємним крайнім верхнім елементом
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
	//якщо потрібного елемента не виявилося результатом буде елемент M[і][0]
	//якщо і=0 то це розв'язок
	return rez;
}

void Simplex::findSolution()
{
	//пошук рірозв'язку
	bool flag = true; //чи варто продовжувати пошук і перебудовувати матрицю
	bool step = true; //який етап пошук (1 розв'язку)/(оптимального розв'язку)
	bool solution = false;//чи є розв'язок
	point mainElem = {0, 0};
	while (flag)
	{
		if (step)//пошук 1 розв'язку
		{
			mainElem = checkAdmissibility();// елемент відносно якого перебудовується матриця
			if (!mainElem.K) step = false; //перевірки чи дана матриця є рішенням і перехід до наступного крору якщо це так
			else if (!mainElem.L)//перевірка чи взагалі є розв'язок
			{
				cout << "there is no solution\n";
				flag = false;
			}
		}
		if (!step)
		{
			mainElem = checkOptimality();// елемент відносно якого перебудовується матриця
			if (matrix[0][mainElem.L]>-0.0001) //перевірки чи дана матриця є оптимальним рішенням і завершення пошуку якщо це так
			{ 
				flag = false; 
				solution = true; 
			}
			else if (matrix[mainElem.K][mainElem.L]<-0.0001)//розв'язків безліч
			{
				cout << "function unlimited\n";
				flag = false;
			}
		}
		if (flag) сhangeTheRules(mainElem);// чи птрібно перебудувати матрицю
	}
	if (solution) //якщо є розв'язок вивести його
	{
		for (int i = 1; i < M; i++)
			if (basicx[i]) cout << "x" << basicx[i] << "=" << matrix[i][N - 1] << " ";
		cout << "\nother variables = 0\n";
		cout << "funcion = " << matrix[0][N - 1]<<endl;
	}
}