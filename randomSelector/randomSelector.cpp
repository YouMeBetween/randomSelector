#include <conio.h>
#include <Windows.h>
#include "includes/items.h"
#include "includes/mainMenu.h"
using namespace std;

void hideCursor();

int main()
{
    char ch;
    CMainMenu main_menu;
    hideCursor();
    while (1) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 72) {
                main_menu.up();
            } else if (ch == 80) {
                main_menu.down();
            } else if (ch == 13) {
                main_menu.enter();
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