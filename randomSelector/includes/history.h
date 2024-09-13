#ifndef _HISTORY_
#define _HISTORY_
#include "interfaceBase.h"

using namespace std;

class CHistory : public CInterfaceBase
{
private:
	void show();
public:
	CHistory();
	virtual void up() {}
	virtual void down() {}
	virtual void left() {}
	virtual void right() {}
	virtual void enter(int &, int &);
};
#endif // !_HISTORY_
