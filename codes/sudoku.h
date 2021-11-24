#pragma once
#include<iostream>
#include<string>
#include<graphics.h>
#include<conio.h>
#include<vector>
using namespace std;
class Sudoku
{
private:
	//3是初始的，2是dfs中填的，1是已填的，0是未填的
	int flag[325] = { 0 };
	//对角线  在这里只需考虑对角线有没有相同数字
	int diaflag[19] = { 0 };
	int sudoku[10][10] = { 0 };
public:
	void Print();
	void Exit();
	void Input();
	void Rand();
	bool Generate(int count);
	void Solve();
	void Hint();
	void Save();
	void Show();
	void dfs(int x, int y);
	bool IDdfs(int x, int y, int dep, int maxdep);
	void Drawimage();
	void Grain();
	void Outtext(int i, int x, int y);
	void Reshape(int number, COLORREF color);
	int MouseMessage(int *myx, int *myy);
	int Num_MouseMessage(int *myx, int *myy);
	void iRAND();
	void iEXIT();
	void iINPUT();
	void iSAVE();
	void iSHOW();
	void iHINT();
	void iSOLVE();
	void iGENERATE();
	void Set(int n, int x, int y);
	bool Win();
	void GetFileName(string path, vector<string>& files);
	void Wchar_tToString(string & szDst, wchar_t*wchar);
	LPCWSTR StringToLPCWSTR(std::string orig);
};