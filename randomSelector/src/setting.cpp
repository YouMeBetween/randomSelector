#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>
#include "../includes/setting.h"
#include "../includes/index.h"
#include "../includes/errorPrompt.h"
using namespace std;

constexpr int FIRST_LINE = 3;
constexpr int LAST_LINE = 7;
constexpr int FINAL_LINE = 8;
constexpr int WEIGHT_SELECT_LINE = 3;
constexpr int DYNAMIC_WEIGHT_LINE = 4;
constexpr int ITEMS_SETUP_LINE = 5;
constexpr int ITEMS_LIST_SETTING = 6;
constexpr int BACK_LINE = 7;
constexpr int ON_OFF_OFFSET = 21;
constexpr int ARROW_OFFSET = 2;

map<string, vector<int>> on_off_pos = {
	{"weightSelect", {ON_OFF_OFFSET, WEIGHT_SELECT_LINE}},
	{"dynamicWeight", {ON_OFF_OFFSET, DYNAMIC_WEIGHT_LINE}}
};
map<int, string> line_to_name = {
	{WEIGHT_SELECT_LINE, "weightSelect"},
	{DYNAMIC_WEIGHT_LINE, "dynamicWeight"}
};

void CSetting::onOffShow(string index)
{
	string value = setting_map[index];
	gotoxy(on_off_pos[index].at(0), on_off_pos[index].at(1));
	cout << (value == "true" ? "开" : "关");
}

void CSetting::show()
{
	system("cls");
	cout << "********************************\n";
	cout << "*           设置界面           *\n";
	cout << "********************************\n";
	cout << "*   1.根据权重选择  <  >       *\n";
	cout << "*   2.动态权重      <  >       *\n";
	cout << "*   3.选项设置                 *\n";
	cout << "*   4.选项列表设置             *\n";
	cout << "*   5.返回                     *\n";
	cout << "********************************\n";
	for (auto iter = on_off_pos.begin(); iter != on_off_pos.end(); iter++) {
		onOffShow(iter->first);
	}
	return;
}

void CSetting::getSetting()
{
	ifstream setting_data("res/setting.ini", ios::in);
	string line, word;
	istringstream sin;
	vector<string> words;
	if (!setting_data.is_open()) {
		cout << "无法打开文件\n";
		exit(1);
	}
	while (getline(setting_data, line)) {
		sin.clear();
		sin.str(line);
		words.clear();
		while (getline(sin, word, ':')) {
			words.push_back(word);
		}
		setting_map[words[0]] = words[1];
	}
	setting_data.close();
}

void CSetting::onOffToggle(string index)
{
	setting_map[index] = setting_map[index] == "true" ? "false" : "true";
	if (setItem("res/setting.ini", index, setting_map[index])) {
		CErrorPrompt error_prompt("写入设置文件失败");
	}
	onOffShow(index);
	if (index == "weightSelect" && setting_map[index] == "false" && setting_map["dynamicWeight"] == "true") {
		onOffToggle("dynamicWeight");
	} else if (index == "dynamicWeight" && setting_map[index] == "true" && setting_map["weightSelect"] == "false") {
		onOffToggle("weightSelect");
	}
}

CSetting::CSetting()
{
	line = 0;
	getSetting();
	show();
	gotoxy(ARROW_OFFSET, FIRST_LINE);
	cout << ">";
	gotoxy(0, FINAL_LINE);
}

CSetting::CSetting(int x)
{
	line = max(min(x, LAST_LINE), FIRST_LINE);
	getSetting();
	show();
	gotoxy(ARROW_OFFSET, line);
	cout << ">";
	gotoxy(0, FINAL_LINE);
}

void CSetting::moveCursor(int target)
{
	gotoxy(ARROW_OFFSET, line);
	cout << " ";
	line = target;
	gotoxy(ARROW_OFFSET, line);
	cout << ">";
	return;
}

void CSetting::up()
{
	if (line > FIRST_LINE) {
		moveCursor(line - 1);
	}
	return;
}

void CSetting::down()
{
	if (line < LAST_LINE) {
		moveCursor(line + 1);
	}
	return;
}

void CSetting::left()
{
	if (line_to_name.find(line) != line_to_name.end()) {
		onOffToggle(line_to_name[line]);
	}
}

void CSetting::right()
{
	if (line_to_name.find(line) != line_to_name.end()) {
		onOffToggle(line_to_name[line]);
	}
}

void CSetting::enter(int &next_interface, int &cursor_line)
{
	switch (line)
	{
		case ITEMS_SETUP_LINE: {
			nextInterfaceSet(next_interface, cursor_line, ITEMS_SETUP_INDEX, NO_LINE);
			break;
		}
		case ITEMS_LIST_SETTING: {
			nextInterfaceSet(next_interface, cursor_line, ITEMS_LIST_SETTING_INDEX, NO_LINE);
			break;
		}
		case BACK_LINE: {
			nextInterfaceSet(next_interface, cursor_line, MAIN_MENU_INDEX, SETTING_LINE_IN_MAIN_MENU);
			break;
		}
		default: break;
	}
}