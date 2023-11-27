#ifndef _ADD_LIST_H_
#define _ADD_LIST_H_
#include "editListBase.h"

using namespace std;

class CAddList : public CEditListBase
{
private:
	void show();
public:
	CAddList();
	virtual void down();
	virtual void enter(int &, int &);
};
#endif // !_ADD_LIST_H_
