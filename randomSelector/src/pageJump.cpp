#include <iostream>
#include <cstdlib>
#include "../includes/pageJump.h"
using namespace std;

void CPageJump::show()
{
	system("cls");
	cout << "********************************\n";
	if (type == 0) {
		cout << "*     ��������Ҫ��������Ŀ     *\n";
	} else {
		cout << "*     ��������Ҫ��ת��ҳ��     *\n";
	}
	cout << "*                              *\n";
	cout << "*             ȷ��             *\n";
	cout << "********************************\n";
}

CPageJump::CPageJump(int input_type)
{
	type = input_type;
	show();
}