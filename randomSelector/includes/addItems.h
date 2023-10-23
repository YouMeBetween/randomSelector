#ifndef _ADD_ITEMS_H_
#define _ADD_ITEMS_H_
#include "interfaceBase.h"

using namespace std;

class CAddItems : public CInterfaceBase
{
private:
	int line;
	string name;
	int weight;
	int min_weight;
	int max_weight;
	void show();
	void moveCursor(int);
	void setName();
	void setWeight();
	void setMinWeight();
	void setMaxWeight();
	void confirm(int &, int &);
public:
	CAddItems();
	virtual void up();
	virtual void down();
	virtual void left() {}
	virtual void right() {}
	virtual void enter(int &, int &);
};
#endif // !_ADD_ITEMS_H_
