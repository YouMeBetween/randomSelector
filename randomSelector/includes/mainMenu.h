#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_
#include "interfaceBase.h"

using namespace std;

class CMainMenu : public CInterfaceBase
{
private:
	int line;
	void printMenu();
	void startChoose();
	void quit();
public:
	CMainMenu();
	CMainMenu(int);
	void moveCursor(int);
	virtual void up();
	virtual void down();
	virtual void left() {}
	virtual void right() {}
	virtual void enter(int &, int &);
};
#endif // !_MAIN_MENU_H_
