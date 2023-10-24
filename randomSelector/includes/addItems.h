#ifndef _ADD_ITEMS_H_
#define _ADD_ITEMS_H_
#include "editItemsBase.h"

using namespace std;

class CAddItems : public CEditItemsBase
{
private:
	void show();
public:
	CAddItems();
	virtual void up();
	virtual void down();
	virtual void left() {}
	virtual void right() {}
	virtual void enter(int &, int &);
};
#endif // !_ADD_ITEMS_H_
