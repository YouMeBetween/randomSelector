#ifndef _INTERFACE_BASE_H_
#define _INTERFACE_BASE_H_
#include <string>

using namespace std;

class CInterfaceBase
{
public:
	CInterfaceBase() {}
	virtual void up() {}
	virtual void down() {}
	virtual void enter(int &, int &) {}
protected:
	void gotoxy(int, int);
	string getItem(string);
	void setItem(string, string);
};
#endif // !_INTERFACE_BASE_H_