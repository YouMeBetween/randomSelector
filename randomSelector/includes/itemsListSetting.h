#ifndef _ITEMS_LIST_SETTING_H
#define _ITEMS_LIST_SETTING_H
#include <vector>
#include <string>
#include "interfaceBase.h"

using namespace std;

class CItemsListSetting : public CInterfaceBase
{
private:
	int line;
	int column;
	int page;
	vector<string> list_name;
	void show();
	void displayLists(int);
	void optionLineMoveCursor(int);
	void itemsLineMoveCursor(int);
	void pageTurningMoveCursor(int, int);
public:
	CItemsListSetting();
	virtual void up();
	virtual void down();
	virtual void left();
	virtual void right();
	virtual void enter(int &, int &);
};
#endif // !_ITEMS_LIST_SETTING_H
