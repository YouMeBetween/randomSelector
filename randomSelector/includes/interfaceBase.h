#ifndef _INTERFACE_BASE_H_
#define _INTERFACE_BASE_H_
#include <string>
#include <vector>

using namespace std;

class CInterfaceBase
{
public:
	CInterfaceBase() {}
	virtual void up() {}
	virtual void down() {}
	virtual void left() {}
	virtual void right() {}
	virtual void enter(int &, int &) {}
protected:
	void gotoxy(int, int);
	string getItem(string, string);
	int setItem(string, string, string);
	void nextInterfaceSet(int &, int &, int, int);
	void showCursor();
	void hideCursor();
	void get_need_file(string, vector<string> &, string);
};
#endif // !_INTERFACE_BASE_H_
