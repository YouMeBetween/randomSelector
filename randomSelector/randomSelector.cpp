#include <conio.h>
#include <Windows.h>
#include "includes/interfaceBase.h"
#include "includes/mainMenu.h"
using namespace std;

void hideCursor();

int main()
{
    char ch;
    CInterfaceBase *interface_base;
    CMainMenu main_menu;
    interface_base = &main_menu;
    hideCursor();
    while (1) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 72) {
                interface_base->up();
            } else if (ch == 80) {
                interface_base->down();
            } else if (ch == 13) {
                interface_base->enter();
            }
        }
    }
}

void hideCursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(handle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &cursorInfo);
}