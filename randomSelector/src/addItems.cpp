#include <iostream>
#include <cstdlib>
#include "../includes/addItems.h"
using namespace std;

constexpr int FIRST_LINE = 3;

void CAddItems::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*          增加待选项          *\n";
	cout << "********************************\n";
	cout << "* > 1.名称                     *\n";
	cout << "*   2.权重                     *\n";
	cout << "*   3.最低权重                 *\n";
	cout << "*   4.最低权重                 *\n";
	cout << "*   5.确认                     *\n";
	cout << "*   6.取消                     *\n";
	cout << "********************************\n";
}

CAddItems::CAddItems()
{
	line = FIRST_LINE;
	show();
}