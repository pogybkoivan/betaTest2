#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

class Brezenhem
{
public:
	Brezenhem(){}
	~Brezenhem(){}
	static vector<POINT> genereteVec(POINT firstP, POINT secondP); //вектор точок нової прямої
private:
	static void sortPoint(POINT &firstP, POINT &secondP); //сортування з якої точки почати побудову прямої
};