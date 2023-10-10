#ifndef _PAGE_JUMP_H_
#define _PAGE_JUMP_H_
#include "interfaceBase.h"

using namespace std;

class CPageJump : public CInterfaceBase
{
	int line;
	int type;
	void show();
	void setTargetPage();
	void moveCursor(int);
public:
	CPageJump(int);
	virtual void up();
	virtual void down();
	virtual void left() {}
	virtual void right() {}
	virtual void enter(int &, int &);
};
#endif // !_PAGE_JUMP_H_
