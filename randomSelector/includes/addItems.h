#ifndef _ADD_ITEMS_H_
#define _ADD_ITEMS_H_
#include "interfaceBase.h"

using namespace std;

class CAddItems : public CInterfaceBase
{
private:
	int line;
	void show();
public:
	CAddItems();
	virtual void up() {}
	virtual void down() {}
	virtual void left() {}
	virtual void right() {}
	virtual void enter(int &, int &) {}
};
#endif // !_ADD_ITEMS_H_
