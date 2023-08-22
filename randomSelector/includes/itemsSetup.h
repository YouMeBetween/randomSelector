#ifndef _ITEMS_SETUP_H_
#define _ITEMS_SETUP_H_
#include "interfaceBase.h"

using namespace std;

class CItemsSetup : public CInterfaceBase
{
private:
	int line;
	int column;
	void show();
	void optionLineMoveCursor(int);
public:
	CItemsSetup();
	virtual void up() {}
	virtual void down() {}
	virtual void left();
	virtual void right();
	virtual void enter(int &, int &);
};
#endif // !_ITEMS_SETUP_H_
