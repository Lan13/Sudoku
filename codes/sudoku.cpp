#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<fstream>
#include<graphics.h>
#include<conio.h>
#include"sudoku.h"
#include<io.h>
#include<ctime>
#include<stdlib.h>
using namespace std;
int hint_row = 0, hint_col = 0, hint_num = 0;//表示没有提示值
bool flag_hint = true; //默认已经提示 当我们需要提示的时候 将其改为false
string game_name[100];

extern int flag_input;
extern int MouseNumber;
int game_cnt = 1;
//有几个temp
int count_temp = 0;        
//solve打印一次
int has_print = 0;
bool generated = false;
//如果没有错误的话
bool input_noerror = true;

void Sudoku::Input()
{
	int x, y, sudoku_temp;
	sudoku_temp = Num_MouseMessage(&x, &y);
	int i, j;
	j = (x - 60) / 40 + 1;
	i = (y - 120) / 40 + 1;
	int house;
	int num_occupy, num_row, num_col, num_house;
	if (i >= 1 && i <= 9 && j >= 1 && j <= 9)
	{
		Set(sudoku_temp, x, y);
		if (sudoku_temp >= 1 && sudoku_temp <= 9)
		{
			if (input_noerror == true)
			{
				count_temp++;
				num_occupy = (i - 1) * 9 + j;
				flag[num_occupy] = 3;
				num_row = (i - 1) * 9 + sudoku_temp + 81;
				flag[num_row] = 3;
				num_col = (j - 1) * 9 + sudoku_temp + 162;
				flag[num_col] = 3;
				house = int((i - 1) / 3) * 3 + int((j - 1) / 3) + 1;
				num_house = (house - 1) * 9 + sudoku_temp + 243;
				flag[num_house] = 3;
				if (i == j)
					diaflag[sudoku_temp] = 3;
				if (i + j == 10)
					diaflag[sudoku_temp + 9] = 3;
			}
			input_noerror = true;
		}
		if (sudoku_temp == 10)
			MouseNumber = 0;
	}

}

void Sudoku::Print()
{
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			Outtext(sudoku[i][j], 60 + (j - 1) * 40 + 12, 120 + (i - 1) * 40 + 2);
		}
	}
}

void Sudoku::Exit()
{
	const LPCWSTR goodbye = L"Goodbye!";
	MessageBox(NULL, goodbye, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
	int time_flag = 0;
	clock_t start, finish;
	start = clock();
	for (int j = 1; j <= 30; j++)
	{
		if (time_flag == 1)
			break;
		for (int i = 1; i <= 12000000; i++)
		{
			finish = clock();
			if ((finish - start) / CLOCKS_PER_SEC > 4)
			{
				time_flag = 1;
				break;
			}
		}
	}
	exit(0);
}

void Sudoku::Hint()
{
	flag_hint = false;
	dfs(1, 1);
	if (hint_row != 0 && hint_col != 0 && hint_num != 0)
	{
		sudoku[hint_row][hint_col] = hint_num;
		const LPCWSTR hint = L"One hint";
		MessageBox(NULL, hint, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
		int house;
		int num_occupy, num_row, num_col, num_house;
		num_occupy = (hint_row - 1) * 9 + hint_col;
		flag[num_occupy] = 3;
		num_row = (hint_row - 1) * 9 + hint_num + 81;
		flag[num_row] = 3;
		num_col = (hint_col - 1) * 9 + hint_num + 162;
		flag[num_col] = 3;
		house = int((hint_row - 1) / 3) * 3 + int((hint_col - 1) / 3) + 1;
		num_house = (house - 1) * 9 + hint_num + 243;
		flag[num_house] = 3;
		if (hint_row == hint_col)
			diaflag[hint_num] = 3;
		if (hint_row + hint_col == 10)
			diaflag[hint_num + 9] = 3;
		Print();
	}
	else
	{
		const LPCWSTR hint = L"Seems no answer";
		MessageBox(NULL, hint, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
	}
	hint_row = hint_col = hint_num = 0;
	flag_hint = true;
}

bool Sudoku::Generate(int count)
{
	if (count_temp >= 17)
	{
		const LPCWSTR goodbye = L"Accept! And begin your game! ";
		MessageBox(NULL, goodbye, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
		count_temp = 0;
		generated = true;
		return true;
	}
	else
	{
		const LPCWSTR goodbye = L"Illegal input";
		MessageBox(NULL, goodbye, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
		memset(flag, 0, sizeof(flag));
		memset(sudoku, 0, sizeof(sudoku));
		memset(diaflag, 0, sizeof(diaflag));
		count_temp = 0;
		Drawimage();
		return false;
	}
}

//对于随机产生的多解的数独，是不能很好的使用hint的
void Sudoku::Rand()
{
	int house;
	int num_occupy, num_row, num_col, num_house;
	int i, j, sudoku_temp;
	srand((int)time(0));
	while (count_temp < 18)
	{
		i = rand() % 9 + 1;
		j = rand() % 9 + 1;
		sudoku_temp = rand() % 9 + 1;
		num_occupy = (i - 1) * 9 + j;
		num_row = (i - 1) * 9 + sudoku_temp + 81;
		num_col = (j - 1) * 9 + sudoku_temp + 162;
		house = int((i - 1) / 3) * 3 + int((j - 1) / 3) + 1;
		num_house = (house - 1) * 9 + sudoku_temp + 243;
		if (flag[num_occupy] == 0 && flag[num_row] == 0 && flag[num_house] == 0 && flag[num_col] == 0)
		{
			if ((i == j && diaflag[sudoku_temp] == 0 && (i != 5 && j != 5)) ||
				(i + j == 10 && diaflag[sudoku_temp + 9] == 0) && (i != 5 && j != 5) ||
				(i == 5 && j == 5 && diaflag[sudoku_temp] == 0 && diaflag[sudoku_temp + 9] == 0))
			{
				flag[num_occupy] = 3;
				flag[num_row] = 3;
				flag[num_col] = 3;
				flag[num_house] = 3;
				if (i == j)
					diaflag[sudoku_temp] = 3;
				if (i + j == 10)
					diaflag[sudoku_temp + 9] = 3;
				sudoku[i][j] = sudoku_temp;
				count_temp++;
			}
			else if (i != j && i + j != 10)
			{
				flag[num_occupy] = 3;
				flag[num_row] = 3;
				flag[num_col] = 3;
				flag[num_house] = 3;
				sudoku[i][j] = sudoku_temp;
				count_temp++;
			}
		}
	}
	Generate(count_temp);
	Print();
}

void Sudoku::Save()
{

	LPCWSTR save = L"input your record name";
	MessageBox(NULL, save, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
	//是否有相同名字的文件 1没有 0有
	int samename_flag = 0;

	string path = "D:\\vs2017 c code\\图形化界面数独";                         //指定文件目录
	vector<string> filesName;

	GetFileName(path, filesName);                   //获取文件名

	for (size_t i = 0; i < filesName.size(); i++)            //将文件名写入到文本中
	{
		string temp = filesName[i].c_str();
		int len = temp.length();
		string last3 = temp.substr(len - 3, len);
		if (last3 == "txt")
		{
			game_name[game_cnt] = filesName[i].c_str();
			game_cnt++;
		}
	}


	// 输入一个合法的保存名 直到可以保存为止
	while (samename_flag == 0)
	{
//		cin >> game_name[game_cnt];
		wchar_t s[100];
		InputBox(s, 100, L"input your game name", NULL, NULL, 300, 150, false);
		Wchar_tToString(game_name[game_cnt], s);
		samename_flag = 1;
		for (int i = 1; i < game_cnt; i++)
			if (game_name[game_cnt] + ".txt" == game_name[i])
			{
				save = L"the same name has been recorded,please input new game name";
				MessageBox(NULL, save, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
				samename_flag = 0;
				break;
			}
	}
	time_t nowtime;
	struct tm*p;
	time(&nowtime);
	p = localtime(&nowtime);
	string ntime;
	ntime = to_string(p->tm_year+1900) +"."+ to_string(p->tm_mon+1) +"."+ to_string(p->tm_mday) + 
		"." + to_string(p->tm_hour) + ":" + to_string(p->tm_min) ;
	fstream foi;
	foi.open(game_name[game_cnt] + ".txt" , ios::out);
	if (foi.is_open())
	{
		game_cnt++;
		foi << ntime << endl;
		for (int i = 1; i <= 9; i++)
		{
			for (int j = 1; j <= 9; j++)
				foi << sudoku[i][j] << " ";
			foi << endl;
		}
		foi.close();
		save = L"your game state has been recorded successfully";
		MessageBox(NULL, save, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
	}
	else
	{
		game_name[game_cnt] = "save() error";
		save = L"save error";
		MessageBox(NULL, save, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
	}


}

void Sudoku::Show()
{
	game_cnt = 1;
	string sudoku_time[100];
	
	string path = "D:\\vs2017 c code\\图形化界面数独";                         //指定文件目录
	vector<string> filesName;

	GetFileName(path, filesName);                   //获取文件名

	for (size_t i = 0; i < filesName.size(); i++)            
	{
		string temp = filesName[i].c_str();
		int len = temp.length();
		string last3 = temp.substr(len - 3, len);
		if (last3 == "txt")
		{
			game_name[game_cnt] = filesName[i].c_str();
			game_cnt++;
		}
	}
	for (int i = 1; i <= game_cnt - 1; i++)
	{
		fstream foi;
		foi.open(game_name[i], ios::in);
		if (foi.is_open())
		{
			foi >> sudoku_time[i];
		}
		foi.close();
	}

	LPCWSTR show;
	string temp;
	for (int i = 0; i <= game_cnt - 1; i++)
	{
		if (i == 0)
		{
			temp = "0-new game\n";
		}
		else
		{
			temp += to_string(i) + "-" + game_name[i] + "-" + sudoku_time[i]+"\n";
		}
	}
	temp += "press the record code to load game\n";
	show = StringToLPCWSTR(temp);

	int load_game;
	wchar_t s[100];
	InputBox(s, 100, show, NULL, NULL, 300, 150, false);
	load_game = _wtoi(s);
	while (load_game > game_cnt - 1)
	{
		MessageBox(NULL, L"please input the right number", _T("Sudoku"), MB_OK | MB_ICONASTERISK);
		wchar_t s[100];
		InputBox(s, 100, show, NULL, NULL, 300, 150, false);
		load_game = _wtoi(s);
	}
	if (load_game == 0)
	{

		memset(flag, 0, sizeof(flag));
		memset(diaflag, 0, sizeof(diaflag));
		memset(sudoku, 0, sizeof(sudoku));
		count_temp = 0;
		show = L"please input the new sudoku";
		MessageBox(NULL, show, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
		Drawimage();
		generated = false;
		flag_input = 0;
	}
	else
	{
		Drawimage();
		memset(flag, 0, sizeof(flag));
		memset(diaflag, 0, sizeof(diaflag));
		memset(sudoku, 0, sizeof(sudoku));
		count_temp = 0;

		fstream foi;
		foi.open(game_name[load_game], ios::in);
		if (foi.is_open())
		{
			string temp;         //去掉保存的时间
			foi >> temp;
			for (int i = 1; i <= 9; i++)
				for (int j = 1; j <= 9; j++)
				{
					foi >> sudoku[i][j];
				}
			for(int i=1;i<=9;i++)
				for (int j = 1; j <= 9; j++)
				{
					if (sudoku[i][j] != 0)
					{
						int house;
						int num_occupy, num_row, num_col, num_house;
						int sudoku_temp = sudoku[i][j];
						num_occupy = (i - 1) * 9 + j;
						flag[num_occupy] = 3;
						num_row = (i - 1) * 9 + sudoku_temp + 81;
						flag[num_row] = 3;
						num_col = (j - 1) * 9 + sudoku_temp + 162;
						flag[num_col] = 3;
						house = int((i - 1) / 3) * 3 + int((j - 1) / 3) + 1;
						num_house = (house - 1) * 9 + sudoku_temp + 243;
						flag[num_house] = 3;
						count_temp++;
						if (i == j)
							diaflag[sudoku_temp] = 3;
						if (i + j == 10)
							diaflag[sudoku_temp + 9] = 3;
					}
				}
			foi.close();

			show = L"last sudoku is";
			MessageBox(NULL, show, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
			Generate(count_temp);
			Print();
		}
	}
}

void Sudoku::Solve()
{
	string solve = "1-dfs\n2-IDdfs\nplease choose one solution";
	wchar_t s[100];
	LPCWSTR temp;
	temp = StringToLPCWSTR(solve);
	InputBox(s, 100, temp, NULL, NULL, 300, 150, false);
	int choice = _wtoi(s);
	LPCWSTR answer = L"The answer is";
	if (choice == 1 || choice == 2)
	{
		MessageBox(NULL, answer, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
		if (choice == 1)
			dfs(1, 1);
		else if (choice == 2)
		{
			int maxdep = 1;
			while (!IDdfs(1, 1, 1, maxdep))
			{
				maxdep++;
				if (maxdep > 81)
					break;
			}
		}
	}
	else
	{
		answer = L"please input correct choice";
		MessageBox(NULL, answer, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
	}
}

bool Sudoku::Win()
{
	for (int i = 1; i <= 81; i++)
		if (flag[i] == 0)
			return false;
	const LPCWSTR win = L"You Win!";
	MessageBox(NULL, win, _T("Sudoku"), MB_OK | MB_ICONASTERISK);
	return true;
}

void Sudoku::dfs(int x, int y)
{
	if (has_print == 0)
	{
		 if (sudoku[x][y] != 0)//9*9中不为零的数直接跳过 
		 {
			if (x == 9 && y == 9)
			{
				if (flag_hint == false)
				{
					for (int i = 1; i <= 9; i++)
					{
						if (flag_hint == true)
							break;
						for (int j = 1; j <= 9; j++)
						{
							if (flag[(i - 1) * 9 + j] == 2 || flag[(i - 1) * 9 + j] == 1)
							{
								hint_row = i;
								hint_col = j;
								hint_num = sudoku[i][j];
								flag_hint = true;
								break;
							}
						}
					}
				}
				else
				{
					has_print = 1;
					Print();//搜索结束后输出
				}
				return;
			}
			if (y == 9) //行到顶端后搜索列 
				dfs(x + 1, 1);
			else //搜索行 
				dfs(x, y + 1);
		 }
		if (sudoku[x][y] == 0) //首先这里是没有填写的
		{
			for (int sudoku_temp = 1; sudoku_temp <= 9; sudoku_temp++)
			{
				int num_occupy, num_row, num_col, num_house;
				int house;
				num_occupy = (x - 1) * 9 + y;
				num_row = (x - 1) * 9 + sudoku_temp + 81;
				num_col = (y - 1) * 9 + sudoku_temp + 162;
				house = int((x - 1) / 3) * 3 + int((y - 1) / 3) + 1;
				num_house = (house - 1) * 9 + sudoku_temp + 243;
				//首先行列宫都没有重复的，再判断主次对角线有无重复，若有则跳过，没有则填
				if (flag[num_row] == 0 && flag[num_col] == 0 && flag[num_house] == 0)
				{
					//当主次对角线没有相同数字时 我可以让他填入
					if ((x == y && diaflag[sudoku_temp] == 0 && (x != 5 && y != 5)) ||
						(x + y == 10 && diaflag[sudoku_temp + 9] == 0) && (x != 5 && y != 5) ||
						(x == 5 && y == 5 && diaflag[sudoku_temp] == 0 && diaflag[sudoku_temp + 9] == 0))
					{
						if (x == y && diaflag[sudoku_temp] != 3 && (x != 5 && y != 5))
							diaflag[sudoku_temp] = 2;
						if (x + y == 10 && diaflag[sudoku_temp + 9] != 3 && (x != 5 && y != 5))
							diaflag[sudoku_temp + 9] = 2;
						if (x == 5 && y == 5 && diaflag[sudoku_temp] != 3 && diaflag[sudoku_temp + 9] != 3)
						{
							diaflag[sudoku_temp] = 2;
							diaflag[sudoku_temp + 9] = 2;
						}
						sudoku[x][y] = sudoku_temp;
						flag[num_occupy] = flag[num_row] = flag[num_col] = flag[num_house] = 2;

						if (x == 9 && y == 9)
						{
							if (flag_hint == false)
							{
								for (int i = 1; i <= 9; i++)
								{
									if (flag_hint == true)
										break;
									for (int j = 1; j <= 9; j++)
									{
										if (flag[(i - 1) * 9 + j] == 2 || flag[(i - 1) * 9 + j] == 1)
										{
											hint_row = i;
											hint_col = j;
											hint_num = sudoku[i][j];
											flag_hint = true;
											break;
										}
									}
								}
							}
							else
							{
								has_print = 1;
								Print();
							}
							return;
						}
						if (y == 9)
							dfs(x + 1, 1);
						else
							dfs(x, y + 1);
						sudoku[x][y] = 0;//当前格退出 
						flag[num_occupy] = flag[num_row] = flag[num_col] = flag[num_house] = 0;
						if (x == y && diaflag[sudoku_temp] == 2 && (x != 5 && y != 5))
							diaflag[sudoku_temp] = 0;
						if (x + y == 10 && diaflag[sudoku_temp + 9] == 2 && (x != 5 && y != 5))
							diaflag[sudoku_temp + 9] = 0;
						if (x == 5 && y == 5 && diaflag[sudoku_temp] == 2 && diaflag[sudoku_temp + 9] == 2)
						{
							diaflag[sudoku_temp] = 0;
							diaflag[sudoku_temp + 9] = 0;
						}
					}
					//当主次对角线有相同数字 或者 不是在对角线上 
					//那么对角线的就不能填了，不是对角线的就可以继续填入
					else if (x != y && x + y != 10)
					{
						sudoku[x][y] = sudoku_temp;
						flag[num_occupy] = flag[num_row] = flag[num_col] = flag[num_house] = 2;
						if (x == 9 && y == 9)
						{
							if (flag_hint == false)
							{
								for (int i = 1; i <= 9; i++)
								{
									if (flag_hint == true)
										break;
									for (int j = 1; j <= 9; j++)
									{
										if (flag[(i - 1) * 9 + j] == 2)
										{
											hint_row = i;
											hint_col = j;
											hint_num = sudoku[i][j];
											flag_hint = true;
											break;
										}
									}
								}
							}
							else
							{
								has_print = 1;
								Print();
							}
							return;
						}
						if (y == 9)
							dfs(x + 1, 1);
						else
							dfs(x, y + 1);
						sudoku[x][y] = 0;//当前格退出 
						flag[num_occupy] = flag[num_row] = flag[num_col] = flag[num_house] = 0;
					}
				}
			}
		}
	}
}

bool Sudoku::IDdfs(int x, int y, int dep, int maxdep)
{
	if (dep > maxdep)
		return false;
	
	if (sudoku[x][y] != 0)   //不等于0的直接跳过
	{
		if (x == 9 && y == 9)
		{
			Print();
			return true;
		}
		if (y == 9) //行到顶端后搜索列 
		{
			if (IDdfs(x + 1, 1, dep + 1, maxdep))
				return true;
		}
		else //搜索行 
			if (IDdfs(x, y + 1, dep + 1, maxdep))
				return true;
	}
	if (sudoku[x][y] == 0) //首先这里是没有填写的
	{
		for (int sudoku_temp = 1; sudoku_temp <= 9; sudoku_temp++)
		{
			int num_occupy, num_row, num_col, num_house;
			int house;
			num_occupy = (x - 1) * 9 + y;
			num_row = (x - 1) * 9 + sudoku_temp + 81;
			num_col = (y - 1) * 9 + sudoku_temp + 162;
			house = int((x - 1) / 3) * 3 + int((y - 1) / 3) + 1;
			num_house = (house - 1) * 9 + sudoku_temp + 243;
			//首先行列宫都没有重复的，再判断主次对角线有无重复，若有则跳过，没有则填
			if (flag[num_row] == 0 && flag[num_col] == 0 && flag[num_house] == 0)
			{
				//当主次对角线没有相同数字时 我可以让他填入
				if ((x == y && diaflag[sudoku_temp] == 0 && (x != 5 && y != 5)) ||
					(x + y == 10 && diaflag[sudoku_temp + 9] == 0) && (x != 5 && y != 5) ||
					(x == 5 && y == 5 && diaflag[sudoku_temp] == 0 && diaflag[sudoku_temp + 9] == 0))
				{
					if (x == y && diaflag[sudoku_temp] != 3 && (x != 5 && y != 5))
						diaflag[sudoku_temp] = 2;
					if (x + y == 10 && diaflag[sudoku_temp + 9] != 3 && (x != 5 && y != 5))
						diaflag[sudoku_temp + 9] = 2;
					if (x == 5 && y == 5 && diaflag[sudoku_temp] != 3 && diaflag[sudoku_temp + 9] != 3)
					{
						diaflag[sudoku_temp] = 2;
						diaflag[sudoku_temp + 9] = 2;
					}
					sudoku[x][y] = sudoku_temp;
					flag[num_occupy] = flag[num_row] = flag[num_col] = flag[num_house] = 2;
					if (x == 9 && y == 9)
					{
						Print();
						return true;
					}
					if (y == 9)      //列满后搜索下一行
						if (IDdfs(x + 1, 1, dep + 1, maxdep))
							return true;
						else
						{
							sudoku[x][y] = 0;//当前格退出 
							flag[num_occupy] = flag[num_row] = flag[num_col] = flag[num_house] = 0;
							if (x == y && diaflag[sudoku_temp] == 2 && (x != 5 && y != 5))
								diaflag[sudoku_temp] = 0;
							if (x + y == 10 && diaflag[sudoku_temp + 9] == 2 && (x != 5 && y != 5))
								diaflag[sudoku_temp + 9] = 0;
							if (x == 5 && y == 5 && diaflag[sudoku_temp] == 2 && diaflag[sudoku_temp + 9] == 2)
							{
								diaflag[sudoku_temp] = 0;
								diaflag[sudoku_temp + 9] = 0;
							}
						}
					else           //搜索下一列
						if (IDdfs(x, y + 1, dep + 1, maxdep))
							return true;
						else
						{
							sudoku[x][y] = 0;//当前格退出 
							flag[num_occupy] = flag[num_row] = flag[num_col] = flag[num_house] = 0;
							if (x == y && diaflag[sudoku_temp] == 2 && (x != 5 && y != 5))
								diaflag[sudoku_temp] = 0;
							if (x + y == 10 && diaflag[sudoku_temp + 9] == 2 && (x != 5 && y != 5))
								diaflag[sudoku_temp + 9] = 0;
							if (x == 5 && y == 5 && diaflag[sudoku_temp] == 2 && diaflag[sudoku_temp + 9] == 2)
							{
								diaflag[sudoku_temp] = 0;
								diaflag[sudoku_temp + 9] = 0;
							}
						}

				}
				//当主次对角线有相同数字 或者 不是在对角线上 
				//那么对角线的就不能填了，不是对角线的就可以继续填入
				else if (x != y && x + y != 10)
				{
					sudoku[x][y] = sudoku_temp;
					flag[num_occupy] = flag[num_row] = flag[num_col] = flag[num_house] = 2;

					if (x == 9 && y == 9)
					{
						Print();
						return true;
					}
					if (y == 9)
						if (IDdfs(x + 1, 1, dep + 1, maxdep))
							return true;
						else
						{
							sudoku[x][y] = 0;//当前格退出 
							flag[num_occupy] = flag[num_row] = flag[num_col] = flag[num_house] = 0;
						}
					else
						if (IDdfs(x, y + 1, dep + 1, maxdep))
							return true;
						else
						{
							sudoku[x][y] = 0;//当前格退出 
							flag[num_occupy] = flag[num_row] = flag[num_col] = flag[num_house] = 0;
						}
				}
			}
		}
	}
	return false;
}

void Sudoku::GetFileName(string path, vector<string>& filesName)
{

	long hFile = 0;                 //文件句柄 
	struct _finddata_t fileinfo;        //定义文件信息结构体
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))   //判断文件属性是否是子目录
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					GetFileName(p.assign(path).append("\\").append(fileinfo.name), filesName);
			}
			else
				filesName.push_back(fileinfo.name);
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);

	}
}

void Sudoku::Wchar_tToString(string& szDst, wchar_t*wchar)
{
	wchar_t * wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);//WideCharToMultiByte的运用
	char *psText;  // psText为char*的临时数组，作为赋值给std::string的中间变量
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);//WideCharToMultiByte的再次运用
	szDst = psText;// std::string赋值
	delete[]psText;// psText的清除
}

LPCWSTR Sudoku::StringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}