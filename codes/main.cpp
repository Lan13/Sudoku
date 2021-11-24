#include<iostream>
#include<string>
#include<graphics.h>
#include<conio.h>
#include"sudoku.h"
using namespace std;
extern int MouseNumber;
extern bool generated;
int main()
{
	Sudoku Sugame;
	initgraph(480, 640);
	Sugame.Drawimage();
	settextcolor(BLACK);
	MOUSEMSG m;
	while (true)
	{
		int m_x, m_y, number;
		number = Sugame.MouseMessage(&m_x,&m_y);
		if (number == 10)
		{
			MouseNumber = 0;
		}
		if(generated)
			Sugame.Set(number, m_x, m_y);
		if (Sugame.Win())
			break;
	}
	closegraph();
	return 0;
}