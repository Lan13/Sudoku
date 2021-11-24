#include<iostream>
#include<vector>
#include<string>
#include<graphics.h>
#include<conio.h>
#include"sudoku.h"
//下面1~9之间的第几个格子
int MouseNumber = 0;
extern int count_temp;
int flag_input = 0;
extern bool input_noerror;
void Sudoku::Drawimage()
{
	setbkcolor(0xFFB6C1);
	cleardevice();
	Grain();
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 0);
	setlinecolor(0x5555FF);
	int x = 60;
	int y = 120;

	// 绘制九宫格，左上角坐标为（x ，y）每隔40画一条横线，并画一条竖线
	for (int i = 0; i <= 9; i++)
	{
		line(x, y + i * 40, 420, y + i * 40);
		line(x + i * 40, y, x + i * 40, 480);
	}

	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 3);
	setlinecolor(0xFF5555);

	// 分割为九份，左上角坐标为（x , y）每隔120画一条横线，并画一条竖线
	for (int i = 0; i < 4; i++)
	{
		line(x, y + i * 120, 420, y + i * 120);
		line(x + i * 120, y, x + i * 120, 480);
	}

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, _T("consolas"));
	outtextxy(40, 490, _T("Select a Number "));

	line(40, 520, 440, 520);
	line(40, 560, 440, 560);
	for (int i = 0; i <= 10; i++)
	{
		line(40 + 40 * i, 520, 40 + 40 * i, 560);
	}

	// 给框格内填入数字
	for (int i = 0; i <= 9; i++)
	{
		setbkmode(TRANSPARENT);
		Outtext(i, 40 + 40 * i + 12, 522);
	}
//	settextcolor(0xf4b1a4);
	iEXIT();
	iINPUT();
	iSAVE();
	iSHOW();
	iHINT();
	iSOLVE();
	iGENERATE();
	iRAND();

	settextstyle(20, 0, _T("consolas"));
	outtextxy(60, 99, _T("SUDOKU: "));
}

void Sudoku::Grain()
{
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 2);
	setlinecolor(0xb82727);
	line(61, 486, 0, 547);
	line(94, 486, 0, 580);
	line(140, 486, 7, 619);
	line(158, 486, 15, 629);
	line(170, 491, 24, 638);
	line(170, 491, 212, 491);
	line(212, 491, 280, 560);
	line(280, 560, 400, 560);
	line(400, 560, 480, 480);
	line(228, 486, 271, 530);
	line(271, 530, 352, 530);
	line(352, 530, 396, 486);
	line(40, 640, 105, 575);
	line(105, 575, 114, 575);
	line(114, 575, 168, 520);
	line(168, 520, 220, 520);
	line(220, 520, 300, 600);
	line(300, 600, 360, 600);
	setfillcolor(WHITE);
	solidcircle(360, 600, 4);
	line(60, 640, 110, 590);
	line(110, 590, 119, 590);
	line(119, 590, 177, 530);
	line(177, 530, 211, 530);
	line(211, 530, 290, 608);
	line(290, 608, 290, 632);
	solidcircle(290, 632, 4);
	circle(137, 593, 3);
	line(139, 591, 179, 551);
	line(179, 551, 213, 551);
	line(213, 551, 242, 582);
	line(242, 582, 242, 605);
	solidcircle(242, 605, 4);
	circle(159, 592, 3);
	line(161, 589, 171, 579);
	line(171, 579, 213, 579);
	line(213, 579, 220, 585);
	line(220, 585, 220, 592);
	circle(220, 595, 3);
	circle(110, 600, 3);
	line(113, 604, 128, 619);
	line(128, 619, 260, 619);
	line(260, 619, 280, 639);
	line(280, 639, 339, 639);
	line(339, 639, 379, 600);
	line(379, 600, 379, 576);
	circle(379, 573, 3);
	circle(77, 637, 3);
	line(80, 633, 95, 619);
	line(95, 619, 117, 619);
	line(117, 619, 125, 626);
	line(125, 626, 210, 626);
	line(210, 626, 222, 640);
	line(88, 640, 93, 634);
	line(93, 634, 199, 634);
	line(199, 634, 202, 640);
	line(358, 639, 397, 599);
	line(397, 599, 438, 599);
	line(438, 599, 470, 568);
	circle(472, 565, 3);
	line(379, 639, 398, 619);
	line(398, 619, 420, 619);
	circle(423, 619, 3);
	circle(426, 568, 3);
	line(429, 565, 480, 516);
	line(458, 638, 467, 630);
	line(467, 630, 480, 630);
	line(0, 184, 26, 210);
	line(26, 210, 26, 369);
	line(26, 369, 0, 393);
	line(0, 205, 7, 211);
	line(7, 211, 7, 270);
	circle(7, 273, 3);
	line(0, 463, 5, 457);
	line(5, 457, 5, 430);
	line(5, 430, 51, 383);
	line(51, 174, 40, 163);
	line(40, 163, 40, 16);
	circle(40, 13, 3);
	line(52, 0, 69, 18);
	line(69, 18, 69, 52);
	circle(69, 55, 3);
	line(257, 0, 144, 111);
	line(144, 111, 144, 120);
	line(310, 0, 190, 120);
	line(238, 120, 263, 94);
	line(263, 94, 329, 94);
	line(329, 94, 424, 0);
	line(423, 461, 423, 421);
	line(423, 421, 445, 397);
	circle(451, 392, 3);
	line(420, 358, 480, 358);
	line(420, 136, 480, 74);
	line(420, 186, 443, 186);
	line(443, 186, 480, 147);
	line(420, 207, 450, 206);
	line(450, 206, 480, 179);
	line(420, 254, 480, 254);
	line(420, 261, 480, 261);
	// 粗白线

	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 4);
	line(70, 120, 70, 107);
	line(70, 107, 138, 40);
	line(138, 40, 138, 0);
	line(133, 120, 133, 95);
	line(212, 120, 331, 0);
	line(420, 168, 429, 168);
	line(429, 168, 480, 117);
	line(420, 227, 462, 227);
	line(462, 227, 480, 208);
	line(0, 145, 45, 190);
	line(45, 190, 45, 368);
	line(45, 368, 0, 412);
	line(133, 95, 227, 0);
	line(344, 120, 460, 0);
	line(119, 486, 0, 605);

	setlinecolor(0xf4b1a4);
	line(420, 268, 480, 268);
	line(48, 471, 0, 520);
	circle(464, 612, 3);
	line(467, 609, 480, 597);
}

void Sudoku::Outtext(int i, int x, int y)
{
	settextstyle(36, 0, _T("consolas"));
	switch (i)
	{
	case 0: settextcolor(0xFFFFFF); outtextxy(x, y, _T(" ")); break;
	case 1: settextcolor(0xEFFFFE); outtextxy(x, y, _T("1")); break;
	case 2: settextcolor(0xDFFFFD); outtextxy(x, y, _T("2")); break;
	case 3: settextcolor(0xCFFFFC); outtextxy(x, y, _T("3")); break;
	case 4: settextcolor(0xBFFFFB); outtextxy(x, y, _T("4")); break;
	case 5: settextcolor(0xAFFFFA); outtextxy(x, y, _T("5")); break;
	case 6: settextcolor(0x9FFFF9); outtextxy(x, y, _T("6")); break;
	case 7: settextcolor(0x8FFFF8); outtextxy(x, y, _T("7")); break;
	case 8: settextcolor(0x7FFFF7); outtextxy(x, y, _T("8")); break;
	case 9: settextcolor(0x6FFFF6); outtextxy(x, y, _T("9")); break;
	}
}

void Sudoku::Reshape(int number, COLORREF color)
{
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
	setlinecolor(color);
	switch (number)
	{
	case 0: rectangle(40 + 40 * 0, 520, 80 + 40 * 0, 560); break;
	case 1: rectangle(40 + 40 * 1, 520, 80 + 40 * 1, 560); break;
	case 2: rectangle(40 + 40 * 2, 520, 80 + 40 * 2, 560); break;
	case 3: rectangle(40 + 40 * 3, 520, 80 + 40 * 3, 560); break;
	case 4: rectangle(40 + 40 * 4, 520, 80 + 40 * 4, 560); break;
	case 5: rectangle(40 + 40 * 5, 520, 80 + 40 * 5, 560); break;
	case 6: rectangle(40 + 40 * 6, 520, 80 + 40 * 6, 560); break;
	case 7: rectangle(40 + 40 * 7, 520, 80 + 40 * 7, 560); break;
	case 8: rectangle(40 + 40 * 8, 520, 80 + 40 * 8, 560); break;
	case 9: rectangle(40 + 40 * 9, 520, 80 + 40 * 9, 560); break;
	}
}

int Sudoku::MouseMessage(int *myx, int *myy)
{
	MOUSEMSG m;
	bool T = true;
	while (T)
	{

		m = GetMouseMsg();													// 获取一个鼠标消息
		setlinecolor(RED);
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (m.x >= 40 && m.x <= 440 && m.y >= 520 && m.y <= 560)		// 如果左键按下的范围在下方选择的范围内
			{
				if (MouseNumber >= 0)										// 如果这个鼠标已经过数，继续点击，需要使得画过的颜色复原
				{
					Reshape(MouseNumber, 0xFF5555);
				}
				Reshape((m.x - 40) / 40, RED);
				MouseNumber = (m.x - 40) / 40;
			}

			if (m.x >= 60 && m.x <= 420 && m.y >= 120 && m.y <= 480)		// 坐标点在九宫格内就将给点坐标按地址值传出
			{
				*myx = m.x;
				*myy = m.y;
				T = false;
			}

			if (m.x >= 390 && m.x <= 470 && m.y >= 10 && m.y <= 50)		// 确定键按按下
			{
				setlinecolor(RED);
				settextcolor(RED);
				iEXIT();
				Reshape(MouseNumber, 0xFF5555);
				settextstyle(20, 0, _T("consolas"));
				outtextxy(120, 99, _T("                  "));
				break;
			}

			if (m.x >= 145 && m.x <= 225 && m.y >= 10 && m.y <= 50)		// 确定键按按下
			{
				setlinecolor(RED);
				settextcolor(RED);
				iRAND();
				Reshape(MouseNumber, 0xFF5555);
				settextstyle(20, 0, _T("consolas"));
				outtextxy(120, 99, _T("                  "));
				break;
			}

			if (m.x >= 0 && m.x <= 90 && m.y >= 580 && m.y <= 620)			// 提示符按下
			{
				settextcolor(RED);
				setlinecolor(RED);
				iINPUT();
				Reshape(MouseNumber, 0xFF5555);
				settextstyle(20, 0, _T("consolas"));
				outtextxy(120, 99, _T("                  "));
				break;
			}
			if (m.x >= 100 && m.x <= 180 && m.y >= 580 && m.y <= 620)		// 清屏按下
			{
				setlinecolor(RED);
				settextcolor(RED);
				iSAVE();
				Reshape(MouseNumber, 0xFF5555);
				settextstyle(20, 0, _T("consolas"));
				outtextxy(120, 99, _T("                  "));
				break;
			}
			if (m.x >= 190 && m.x <= 270 && m.y >= 580 && m.y <= 620)
			{
				setlinecolor(RED);
				settextcolor(RED);
				iSHOW();
				Reshape(MouseNumber, 0xFF5555);
				settextstyle(20, 0, _T("consolas"));
				outtextxy(120, 99, _T("                  "));
				break;
			}
			if (m.x >= 280 && m.x <= 360 && m.y >= 580 && m.y <= 620)
			{
				setlinecolor(RED);
				settextcolor(RED);
				iHINT();
				Reshape(MouseNumber, 0xFF5555);
				settextstyle(20, 0, _T("consolas"));
				outtextxy(120, 99, _T("                  "));
				break;
			}
			if (m.x >= 370 && m.x <= 470 && m.y >= 580 && m.y <= 620)
			{
				setlinecolor(RED);
				settextcolor(RED);
				iSOLVE();
				Reshape(MouseNumber, 0xFF5555);
				settextstyle(20, 0, _T("consolas"));
				outtextxy(120, 99, _T("                  "));
				break;
			}
		case WM_LBUTTONUP:													// 左键抬起
			if (m.x >= 390 && m.x <= 470 && m.y >= 10 && m.y <= 50)		// 确定键抬起
			{
				setlinecolor(0xFF5555);
				settextcolor(0xf4b1a4);
				iEXIT();
				MouseNumber = 10;
				Exit();
				return MouseNumber;
			}

			if (m.x >= 145 && m.x <= 225 && m.y >= 10 && m.y <= 50)		// 确定键抬起
			{
				setlinecolor(0xFF5555);
				settextcolor(0xf4b1a4);
				iRAND();
				MouseNumber = 10;
				Rand();
				return MouseNumber;
			}

			if (m.x >= 0 && m.x <= 90 && m.y >= 580 && m.y <= 620)		
			{
				setlinecolor(0xFF5555);
				settextcolor(0xf4b1a4);
				iINPUT();
				while (1)
				{
					Input();
					if (flag_input)
						break;
				}
				MouseNumber = 10;
				return MouseNumber;
			}

			if (m.x >= 100 && m.x <= 180 && m.y >= 580 && m.y <= 620)
			{
				setlinecolor(0xFF5555);
				settextcolor(0xf4b1a4);
				iSAVE();
				Save();
				MouseNumber = 10;
				return MouseNumber;
			}

			if (m.x >= 190 && m.x <= 270 && m.y >= 580 && m.y <= 620)
			{
				setlinecolor(0xFF5555);
				settextcolor(0xf4b1a4);
				iSHOW();
				Show();
				MouseNumber = 10;
				return MouseNumber;
			}
			if (m.x >= 280 && m.x <= 360 && m.y >= 580 && m.y <= 620)
			{
				setlinecolor(0xFF5555);
				settextcolor(0xf4b1a4);
				iHINT();
				Hint();
				MouseNumber = 10;
				return MouseNumber;
			}
			if (m.x >= 370 && m.x <= 470 && m.y >= 580 && m.y <= 620)
			{
				setlinecolor(0xFF5555);
				settextcolor(0xf4b1a4);
				iSOLVE();
				Solve();
				MouseNumber = 10;
				return MouseNumber;
			}
			
		}
	}

	return MouseNumber;
}

int Sudoku::Num_MouseMessage(int *myx, int *myy)
{
	MOUSEMSG m;
	bool T = true;
	while (T)
	{
		m = GetMouseMsg();													// 获取一个鼠标消息
		setlinecolor(RED);
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (m.x >= 40 && m.x <= 440 && m.y >= 520 && m.y <= 560)		// 如果左键按下的范围在下方选择的范围内
			{
				if (MouseNumber >= 0)										// 如果这个鼠标已经过数，继续点击，需要使得画过的颜色复原
				{
					Reshape(MouseNumber, 0xFF5555);
				}
				Reshape((m.x - 40) / 40, RED);
				MouseNumber = (m.x - 40) / 40;
			}

			if (m.x >= 60 && m.x <= 420 && m.y >= 120 && m.y <= 480)		// 坐标点在九宫格内就将给点坐标按地址值传出
			{
				*myx = m.x;
				*myy = m.y;
				T = false;

			}
			if (m.x >= 235 && m.x <= 380 && m.y >= 10 && m.y <= 50)
			{
				setlinecolor(RED);
				settextcolor(RED);
				iGENERATE();
				Reshape(MouseNumber, 0xFF5555);
				settextstyle(20, 0, _T("consolas"));
				outtextxy(120, 99, _T("                  "));
				MouseNumber = 10;
				if (Generate(count_temp))   //此时停止input
				{
					flag_input = 1;
					break;
				}
			}
		}
		if (flag_input)
			break;
	}
	return MouseNumber;
}

void Sudoku::iEXIT()
{
	setbkmode(TRANSPARENT);
	rectangle(390, 10, 470, 50);
	setbkmode(TRANSPARENT);
	settextstyle(36, 0, _T("consolas"));
	outtextxy(394, 12, _T("Exit"));
}

void Sudoku::iGENERATE()
{
	setbkmode(TRANSPARENT);
	rectangle(235, 10, 380, 50);
	setbkmode(TRANSPARENT);
	settextstyle(36, 0, _T("consolas"));
	outtextxy(239, 12, _T("Gerenate"));
}

void Sudoku::iRAND()
{
	setbkmode(TRANSPARENT);
	rectangle(145, 10, 225, 50);
	setbkmode(TRANSPARENT);
	settextstyle(36, 0, _T("consolas"));
	outtextxy(149, 12, _T("Rand"));
}

void Sudoku::iINPUT()
{
	setbkmode(TRANSPARENT);
	rectangle(0, 580, 90, 620);
	setbkmode(TRANSPARENT);
	settextstyle(36, 0, _T("consolas"));
	outtextxy(4, 582, _T("Input"));
}

void Sudoku::iSAVE()
{
	setbkmode(TRANSPARENT);
	rectangle(100, 580, 180, 620);
	setbkmode(TRANSPARENT);
	settextstyle(36, 0, _T("consolas"));
	outtextxy(104, 582, _T("Save"));
}

void Sudoku::iSHOW()
{
	setbkmode(TRANSPARENT);
	rectangle(190, 580, 270, 620);
	setbkmode(TRANSPARENT);
	settextstyle(36, 0, _T("consolas"));
	outtextxy(194, 582, _T("Show"));
}

void Sudoku::iHINT()
{
	setbkmode(TRANSPARENT);
	rectangle(280, 580, 360, 620);
	setbkmode(TRANSPARENT);
	settextstyle(36, 0, _T("consolas"));
	outtextxy(284, 582, _T("Hint"));
}

void Sudoku::iSOLVE()
{
	setbkmode(TRANSPARENT);
	rectangle(370, 580, 470, 620);
	setbkmode(TRANSPARENT);
	settextstyle(36, 0, _T("consolas"));
	outtextxy(374, 582, _T("Solve"));
}

void Sudoku::Set(int n, int x, int y)
{
	int myx, myy;
	myx = ((x - 60) / 40) * 40 + 60 + 12;
	myy = ((y - 120) / 40) * 40 + 120 + 2;
//	setbkmode(OPAQUE);
//	Outtext(n, myx, myy);
	int i, j;
	//数独九宫格的i j
	j = (x - 60) / 40 + 1;
	i = (y - 120) / 40 + 1;
	int house;
	int num_occupy, num_row, num_col, num_house;

	num_occupy = (i - 1) * 9 + j;
	num_row = (i - 1) * 9 + n + 81;
	num_col = (j - 1) * 9 + n + 162;
	house = int((i - 1) / 3) * 3 + int((j - 1) / 3) + 1;
	num_house = (house - 1) * 9 + n + 243;
	
	if (i >= 1 && i <= 9 && j >= 1 && j <= 9 && n >= 1 && n <= 9)
	{
		if (flag[num_occupy] != 0 || flag[num_row] != 0 || flag[num_col] != 0 || flag[num_house] != 0
			|| (i == j && diaflag[n] != 0) || (i + j == 10 && diaflag[n + 9] != 0))
//		if (flag[num_occupy] != 0 || flag[num_row] != 0 || flag[num_col] != 0 || flag[num_house] != 0)
		{
			const LPCWSTR set = L"Set Error! The same number has been set!";
			MessageBox(NULL, set, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
			input_noerror = false;
			return;
		}
		else     //可以填入
		{
			flag[num_occupy] = 1;
			flag[num_row] = 1;
			flag[num_col] = 1;
			flag[num_house] = 1;
			if (i == j)
				diaflag[n] = 1;
			if (i + j == 10)
				diaflag[n + 9] = 1;
			setbkmode(OPAQUE);
			Outtext(n, myx, myy);
		}
		sudoku[i][j] = n;
	}
	else    //用的 delete
	{
		if (i >= 1 && i <= 9 && j >= 1 && j <= 9 && flag[num_occupy] != 3)
		{
			num_row = (i - 1) * 9 + sudoku[i][j] + 81;
			num_col = (j - 1) * 9 + sudoku[i][j] + 162;
			num_house = (house - 1) * 9 + sudoku[i][j] + 243;
			flag[num_occupy] = 0;
			flag[num_row] = 0;
			flag[num_col] = 0;
			flag[num_house] = 0;
			if (i == j)
				diaflag[sudoku[i][j]] = 0;
			if (i + j == 10)
				diaflag[sudoku[i][j] + 9] = 0;
			setbkmode(OPAQUE);
			Outtext(n, myx, myy);
			sudoku[i][j] = n;
		}
	}

}