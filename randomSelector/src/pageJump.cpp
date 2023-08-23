#include <iostream>
#include <cstdlib>
#include "../includes/pageJump.h"
using namespace std;

void CPageJump::show()
{
	system("cls");
	cout << "********************************\n";
	if (type == 0) {
		cout << "*     请输入想要搜索的条目     *\n";
	} else {
		cout << "*     请输入想要跳转的页面     *\n";
	}
	cout << "*                              *\n";
	cout << "*             确认             *\n";
	cout << "********************************\n";
}

CPageJump::CPageJump(int input_type)
{
	type = input_type;
	show();
}