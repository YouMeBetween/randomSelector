#ifndef _SETTING_H_
#define _SETTING_H_
#include <string>
#include "interfaceBase.h"

using namespace std;

class CSetting : public CInterfaceBase
{
private:
	int line;
	void onOffShow(string, int, int);
	void show();
public:
	CSetting();
	CSetting(int);
	void moveCursor(int);
	virtual void up();
	virtual void down();
	virtual void enter(int &, int &);
};
#endif // !_SETTING_H_
