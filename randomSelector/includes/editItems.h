#ifndef _EDIT_ITEMS_H_
#define _EDIT_ITEMS_H_
#include "editItemsBase.h"

using namespace std;

class CEditItems : public CEditItemsBase
{
private:
	void show();
public:
	CEditItems();
	virtual void up();
	virtual void down();
	virtual void left() {}
	virtual void right() {}
	virtual void enter(int &, int &);
};
#endif // !_EDIT_ITEMS_H_
