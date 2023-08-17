#include <conio.h>
#include <Windows.h>
#include "includes/interfaceBase.h"
#include "includes/mainMenu.h"
#include "includes/resultShow.h"
using namespace std;

void hideCursor();
void switchInterface(CInterfaceBase *&, int &);

int main()
{
    char ch;
    int next_interface = 0;
    CInterfaceBase *interface_base;
    CMainMenu *main_menu = new CMainMenu;
    interface_base = main_menu;
    hideCursor();
    while (1) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 72) {
                interface_base->up();
            } else if (ch == 80) {
                interface_base->down();
            } else if (ch == 13) {
                next_interface = interface_base->enter();
            }
        }
        if (next_interface) {
            switchInterface(interface_base, next_interface);
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

void switchInterface(CInterfaceBase *&interface_base, int &next_interface)
{
    delete interface_base;
    switch (next_interface)
    {
        default:
        case 1: {
            CMainMenu *main_menu = new CMainMenu;
            interface_base = main_menu;
            break;
        }
        case 2: {
            CResultShow *result_show = new CResultShow;
            interface_base = result_show;
            break;
        }
    }
    next_interface = 0;
}