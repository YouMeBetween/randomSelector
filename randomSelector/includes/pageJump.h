#ifndef _PAGE_JUMP_H_
#define _PAGE_JUMP_H_
#include "interfaceBase.h"

using namespace std;

class CPageJump : public CInterfaceBase
{
	int type;
	void show();
public:
	CPageJump(int);
	virtual void up() {}
	virtual void down() {}
	virtual void left() {}
	virtual void right() {}
	virtual void enter(int &, int &) {}
};
#endif // !_PAGE_JUMP_H_
