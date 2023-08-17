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
	virtual void up();
	virtual void down();
	virtual int enter();
};
#endif // !_MAIN_MENU_H_
