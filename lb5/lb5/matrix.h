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
	// конструктори
	line();
	line(int n);
	line(int n, int m);
	
	~line();
	//визначення оператор[]
	int& operator[](int n);
private:
	//наш лінійний масив
	simpleCell* deque;
	//поінтер, що допомагає рухатися по масиву
	simpleCell* pointer;
	//розмірність
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
	//конструктори
	matrix();
	matrix(int n, int m);
	matrix(int n, int m, int k);
	
	//визначення оператора[]
	line& operator[](int n);
	~matrix();
private:
	//наш масив
	simpleLine* sqeare;
	//поінтер, що допомагає рухатися по масиву
	simpleLine* pointer;
	//розмірність
	int NMax;
	int MMax;
};