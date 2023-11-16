#ifndef _ITEMS_SETUP_H_
#define _ITEMS_SETUP_H_
#include <vector>
#include "interfaceBase.h"
#include "items.h"

using namespace std;

class CItemsSetup : public CInterfaceBase
{
private:
	int line;
	int column;
	int page;
	CItems items;
	void show();
	void displayItems(int);
	void optionLineMoveCursor(int);
	void itemsLineMoveCursor(int);
	void pageTurningMoveCursor(int, bool);
public:
	CItemsSetup();
	virtual void up();
	virtual void down();
	virtual void left();
	virtual void right();
	virtual void enter(int &, int &);
};
#endif // !_ITEMS_SETUP_H_
