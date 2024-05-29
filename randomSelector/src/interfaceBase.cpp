#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <Windows.h>
#include <io.h>
#include "../includes/interfaceBase.h"

using namespace std;

void CInterfaceBase::gotoxy(int x, int y)
{
	COORD pos = { x, y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
	return;
}

string CInterfaceBase::getItem(string file, string index)
{
	ifstream ini_data(file, ios::in);
	string line, word, result = "“Ï≥£";
	istringstream sin;
	vector<string> words;
	if (!ini_data.is_open()) {
		return "“Ï≥£";
	}
	while (getline(ini_data, line)) {
		sin.clear();
		sin.str(line);
		words.clear();
		while (getline(sin, word, ':')) {
			words.push_back(word);
		}
		if (words[0] == index) {
			result = words[1];
			break;
		}
	}
	ini_data.close();
	return result;
}

int CInterfaceBase::setItem(string file, string index, string value)
{
	map<string, string> ini_map;
	ifstream ini_data_in(file, ios::in);
	string line, word;
	istringstream sin;
	vector<string> words;
	if (!ini_data_in.is_open()) {
		return -1;
	}
	while (getline(ini_data_in, line)) {
		sin.clear();
		sin.str(line);
		words.clear();
		while (getline(sin, word, ':')) {
			words.push_back(word);
		}
		ini_map[words[0]] = words[1];
	}
	ini_data_in.close();
	ini_map[index] = value;
	ofstream ini_data_out(file, ios::out);
	for (auto iter = ini_map.begin(); iter != ini_map.end(); iter++) {
		ini_data_out << iter->first << ":" << iter->second << endl;
	}
	ini_data_out.close();
	return 0;
}

void CInterfaceBase::nextInterfaceSet(int &next_interface, int &cursor_line, int next_interface_target,
									  int cursor_line_target)
{
	next_interface = next_interface_target;
	cursor_line = cursor_line_target;
	return;
}

void CInterfaceBase::showCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = true;
	SetConsoleCursorInfo(handle, &cursorInfo);
}

void CInterfaceBase::hideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &cursorInfo);
}

void CInterfaceBase::get_need_file(string path, vector<string> &file, string ext)
{
	intptr_t file_handle = 0;
	struct _finddata_t file_info;
	string name, temp;
	file.clear();
	if ((file_handle = _findfirst(temp.assign(path).append("/*" + ext).c_str(), &file_info)) != -1) {
		do {
			name = file_info.name;
			file.push_back(name.substr(0, name.rfind(".")));
		} while (_findnext(file_handle, &file_info) == 0);
		_findclose(file_handle);
	}
}