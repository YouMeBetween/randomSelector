#include <iostream>
#include <string>
#include <cstdlib>
#include "../includes/resultShow.h"
using namespace std;

constexpr int HORIZONTAL_LENGTH = 32;

void CResultShow::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*       计算机替你选择了       *\n";
	cout << "*                              *\n";
	cout << "********************************\n";
	cout << "*           > 确定             *\n";
	cout << "********************************\n";
	return;
}

CResultShow::CResultShow()
{
	string choice = getItem("choice");
	show();
	gotoxy((HORIZONTAL_LENGTH - choice.size()) / 2, 2);
	cout << choice;
}

int CResultShow::enter()
{
	return 1;
}