#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include "../includes/editListBase.h"
#include "../includes/errorPrompt.h"
#include "../includes/index.h"
using namespace std;

void CEditListBase::addCsv()
{
	ofstream csv_data("res/" + name + ".csv", ios::out);
	csv_data << "��Ŀ,Ȩ��,���Ȩ��,���Ȩ��,����\n";
	csv_data.close();
}

CEditListBase::CEditListBase()
{
	line = FIRST_LINE_IN_EDIT_LIST_BASE;
	name = "";
}

void CEditListBase::up()
{
	if (line > FIRST_LINE_IN_EDIT_LIST_BASE) {
		moveCursor(line - 1);
	}
}

void CEditListBase::moveCursor(int target)
{
	gotoxy(ARROW_OFFSET_IN_EDIT_LIST_BASE, line);
	cout << " ";
	line = target;
	gotoxy(ARROW_OFFSET_IN_EDIT_LIST_BASE, line);
	cout << ">";
}

void CEditListBase::setName()
{
	gotoxy(INPUT_OFFSET_IN_EDIT_LIST_BASE, NAME_LINE_IN_EDIT_LIST_BASE);
	cout << "               ";
	gotoxy(INPUT_OFFSET_IN_EDIT_LIST_BASE, NAME_LINE_IN_EDIT_LIST_BASE);
	showCursor();
	cin >> name;
	hideCursor();
}

void CEditListBase::confirm(int &next_interface, int &cursor_line, bool is_add)
{
	int page;
	vector<string> files;
	if (name == "") {
		gotoxy(PROMPT_OFFSET_IN_EDIT_LIST_BASE, CONFIRM_LINE_IN_EDIT_LIST_BASE);
		cout << "                   ";
		gotoxy(PROMPT_OFFSET_IN_EDIT_LIST_BASE, CONFIRM_LINE_IN_EDIT_LIST_BASE);
		cout << "δ��������";
		return;
	}
	if (is_add) {
		addCsv();
	} else {
		string item_want_edit = getItem("res/cfg.ini", "itemWantEdit");
		if (rename(("res/" + item_want_edit + ".csv").c_str(), ("res/" + name + ".csv").c_str())) {
			CErrorPrompt error_prompt("�������ļ�ʧ��");
		}
	}
	get_need_file("res", files, ".csv");
	auto iter = find(files.begin(), files.end(), name);
	page = distance(files.begin(), iter) / LIST_PER_PAGE_IN_ITEMS_LIST_SETTING;
	if (setItem("res/cfg.ini", "page", to_string(page))) {
		CErrorPrompt error_prompt("��cfg.ini�ļ�ʧ��");
	}
	nextInterfaceSet(next_interface, cursor_line, ITEMS_LIST_SETTING_INDEX, NO_LINE);
}