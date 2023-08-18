#ifndef _SETTING_H_
#define _SETTING_H_
#include <string>
#include <map>
#include "interfaceBase.h"

using namespace std;

class CSetting : public CInterfaceBase
{
private:
	int line;
	map<string, string> setting_map;
	void onOffShow(string);
	void show();
	void getSetting();
	void onOffToggle(string);
public:
	CSetting();
	CSetting(int);
	void moveCursor(int);
	virtual void up();
	virtual void down();
	virtual void left();
	virtual void right();
	virtual void enter(int &, int &);
};
#endif // !_SETTING_H_
