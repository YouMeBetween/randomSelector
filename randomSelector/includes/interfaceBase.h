#ifndef _INTERFACE_BASE_H_
#define _INTERFACE_BASE_H_

using namespace std;

class CInterfaceBase
{
public:
	CInterfaceBase() {}
	virtual void up() {}
	virtual void down() {}
	virtual void enter() {}
protected:
	void gotoxy(int, int);
};
#endif // !_INTERFACE_BASE_H_
