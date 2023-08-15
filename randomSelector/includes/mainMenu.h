#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

using namespace std;

class CMainMenu
{
private:
	int line;
	void gotoxy(int, int);
	void printMenu();
	void startChoose();
	void quit();
public:
	CMainMenu();
	CMainMenu(int);
	void up();
	void down();
	void enter();
};
#endif // !_MAIN_MENU_H_
