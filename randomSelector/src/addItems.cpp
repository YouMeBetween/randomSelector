#include <iostream>
#include <cstdlib>
#include "../includes/addItems.h"
using namespace std;

constexpr int FIRST_LINE = 3;

void CAddItems::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*          ���Ӵ�ѡ��          *\n";
	cout << "********************************\n";
	cout << "* > 1.����                     *\n";
	cout << "*   2.Ȩ��                     *\n";
	cout << "*   3.���Ȩ��                 *\n";
	cout << "*   4.���Ȩ��                 *\n";
	cout << "*   5.ȷ��                     *\n";
	cout << "*   6.ȡ��                     *\n";
	cout << "********************************\n";
}

CAddItems::CAddItems()
{
	line = FIRST_LINE;
	show();
}