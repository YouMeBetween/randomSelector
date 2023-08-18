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
using namespace std;

constexpr int FIRST_OPTION_LINE = 3;
constexpr int FINAL_LINE = 7;
constexpr int MAX_INDEX = 2;
constexpr int THIS_WEIGHT_SELECT_INDEX = 0;
constexpr int THIS_DYNAMIC_WEIGHT_INDEX = 1;
constexpr int THIS_BACK_INDEX = 2;
constexpr int ON_OFF_OFFSET = 21;
constexpr int ARROW_OFFSET = 2;

map<string, vector<int>> on_off_pos = {
	{"weight_select", {ON_OFF_OFFSET, FIRST_OPTION_LINE + THIS_WEIGHT_SELECT_INDEX}},
	{"dynamic_weight", {ON_OFF_OFFSET, FIRST_OPTION_LINE + THIS_DYNAMIC_WEIGHT_INDEX}}
};
map<int, string> line_to_name = {
	{0, "weight_select"},
	{1, "dynamic_weight"}
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
	cout << "*   3.返回                     *\n";
	cout << "********************************\n";
	onOffShow("weight_select");
	onOffShow("dynamic_weight");
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
	setItem("res/setting.ini", index, setting_map[index]);
	onOffShow(index);
}

CSetting::CSetting()
{
	line = 0;
	getSetting();
	show();
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE);
	cout << ">";
	gotoxy(0, FINAL_LINE);
}

CSetting::CSetting(int x)
{
	line = max(min(x, MAX_INDEX), 0);
	getSetting();
	show();
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE + line);
	cout << ">";
	gotoxy(0, FINAL_LINE);
}

void CSetting::moveCursor(int target)
{
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE + line);
	cout << " ";
	line = target;
	gotoxy(ARROW_OFFSET, FIRST_OPTION_LINE + line);
	cout << ">";
	return;
}

void CSetting::up()
{
	if (line > 0) {
		moveCursor(line - 1);
	}
	return;
}

void CSetting::down()
{
	if (line < MAX_INDEX) {
		moveCursor(line + 1);
	}
	return;
}

void CSetting::left()
{
	onOffToggle(line_to_name[line]);
}

void CSetting::right()
{
	onOffToggle(line_to_name[line]);
}

void CSetting::enter(int &next_interface, int &cursor_line)
{
	switch (line)
	{
		case THIS_BACK_INDEX: {
			nextInterfaceSet(next_interface, cursor_line, MAIN_MENU_INDEX, SETTING_LINE_IN_MAIN_MENU);
			break;
		}
		default: break;
	}
}