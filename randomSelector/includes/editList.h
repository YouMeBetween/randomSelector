#ifndef _EDIT_LIST_H_
#define _EDIT_LIST_H_
#include "editListBase.h"

using namespace std;

class CEditList : public CEditListBase
{
private:
	void show();
	void removeList(int &, int &);
	void quit(int &, int &);
public:
	CEditList();
	virtual void down();
	virtual void enter(int &, int &);
};
#endif // !_EDIT_LIST_H_
