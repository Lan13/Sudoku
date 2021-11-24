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
	//3�ǳ�ʼ�ģ�2��dfs����ģ�1������ģ�0��δ���
	int flag[325] = { 0 };
	//�Խ���  ������ֻ�迼�ǶԽ�����û����ͬ����
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