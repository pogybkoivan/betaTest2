#include "Brezenhem.h"

void Brezenhem::sortPoint(POINT &firstP, POINT &secondP) //сортує точки по х координаті
{														 //для того щоб рисувати завжди зліва направо
	if (firstP.x > secondP.x)
	{
		POINT temp = secondP;
		secondP = firstP;
		firstP = temp;
	}
}

vector<POINT> Brezenhem::genereteVec(POINT firstP, POINT secondP)
{
	sortPoint(firstP, secondP); //сортування по х координаті
	int dX = secondP.x - firstP.x; //різниця в х
	int dY = secondP.y - firstP.y; //різниця в у
	int b = secondP.y*firstP.x - secondP.x*firstP.y; //деяка допоміжна констаннта
	int i = 0;
	if (dX > dY && dX + dY > 0) // вибір в яку сторону більше витягнута наша пяма
// якщо по х
	{
		vector<POINT> vec(dX + 1); // вектор точок нашої прямої
		vec[i] = firstP;
		while (i < dX)
		{
			vec[i + 1] = vec[i];
			vec[i + 1].x++;
			if (dY > 0) // вибір куди спрямована ввех чи вниз
	//вверх
				if (2 * (dY * vec[i + 1].x - dX * vec[i].y - b) - dX > 0) vec[i + 1].y++; //відповідний прорахунок у кординати наступної точки
				else;
			else
	//вниз
				if (2 * (dY * vec[i + 1].x - dX * vec[i].y - b) - dX < 0) vec[i + 1].y--; //відповідний прорахунок у кординати наступної точки
			i++;
		}
		return vec;
	}
//якщо по у
	else
	{
		if (dY > 0) //костиль для взначення потрібної кількості точок лінії
			i = dY + 1;
		else
			i = 1 - dY;
		vector<POINT> vec(i + 1); // вектор точок нашої прямої
		i = 0;
		vec[i] = firstP;
		while (dY + i < 0 || i < dY)
		{
			vec[i + 1] = vec[i];
			if (dY > 0) // вибір куди спрямована ввех чи вниз + calculate x
			{
				vec[i + 1].y++;
				if (2 * (dX * vec[i + 1].y - dY * vec[i].x + b) - dY > 0) vec[i + 1].x++;
			}
			else
			{
				vec[i + 1].y--;
				if (2 * (dX * vec[i + 1].y - dY * vec[i].x + b) - dY < 0) vec[i + 1].x++;
			}
			i++;
		}
		return vec;
	}
}