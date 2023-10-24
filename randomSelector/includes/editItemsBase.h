#ifndef _EDIT_ITEMS_BASE_H_
#define _EDIT_ITEMS_BASE_H_
#include <string>
#include "interfaceBase.h"

using namespace std;

constexpr int FIRST_LINE = 3;
constexpr int NAME_LINE = 3;
constexpr int WEIGHT_LINE = 4;
constexpr int MIN_WEIGHT_LINE = 5;
constexpr int MAX_WEIGHT_LINE = 6;
constexpr int CONFIRM_LINE = 7;
constexpr int ARROW_OFFSET = 2;
constexpr int INPUT_OFFSET = 16;
constexpr int PROMPT_OFFSET = 12;

class CEditItemsBase : public CInterfaceBase
{
public:
	CEditItemsBase();
	virtual void up() {}
	virtual void down() {}
	virtual void left() {}
	virtual void right() {}
	virtual void enter(int &, int &) {}
protected:
	int line;
	string name;
	int weight;
	int min_weight;
	int max_weight;
	void moveCursor(int);
	void setName();
	void weightRangeCheck();
	void setWeight();
	void setMinWeight();
	void setMaxWeight();
	void confirm(int &, int &);
};
#endif // !_EDIT_ITEM_BASE_H_
