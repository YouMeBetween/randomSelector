#ifndef _EDIT_ITEMS_BASE_H_
#define _EDIT_ITEMS_BASE_H_
#include <string>
#include "interfaceBase.h"
#include "items.h"

using namespace std;

constexpr int FIRST_LINE_IN_EDIT_ITEMS_BASE = 3;
constexpr int NAME_LINE_IN_EDIT_ITEMS_BASE = 3;
constexpr int WEIGHT_LINE_IN_EDIT_ITEMS_BASE = 4;
constexpr int MIN_WEIGHT_LINE_IN_EDIT_ITEMS_BASE = 5;
constexpr int MAX_WEIGHT_LINE_IN_EDIT_ITEMS_BASE = 6;
constexpr int CONFIRM_LINE_IN_EDIT_ITEMS_BASE = 7;
constexpr int ARROW_OFFSET_IN_EDIT_ITEMS_BASE = 2;
constexpr int INPUT_OFFSET_IN_EDIT_ITEMS_BASE = 16;
constexpr int PROMPT_OFFSET_IN_EDIT_ITEMS_BASE = 12;

class CEditItemsBase : public CInterfaceBase
{
public:
	CEditItemsBase();
	virtual void up();
	virtual void down() {}
	virtual void left() {}
	virtual void right() {}
	virtual void enter(int &, int &) {}
protected:
	int line;
	Item item;
	void moveCursor(int);
	void setName();
	void weightRangeCheck();
	void setWeight();
	void setMinWeight();
	void setMaxWeight();
	void confirm(int &, int &, bool);
};
#endif // !_EDIT_ITEM_BASE_H_
