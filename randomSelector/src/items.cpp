#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include "../includes/items.h"
#include "../includes/errorPrompt.h"
using namespace std;

constexpr int MIN_WEIGHT = 1;

void CItems::adjustWeights(string choice_name)
{
	auto iter = find_if(items.begin(), items.end(), [choice_name](Item item) { return item.name == choice_name; });
	int choice = distance(items.begin(), iter);
	if (items.at(choice).min_weight == 0 || items.at(choice).min_weight <= items.at(choice).weight / 2) {
		items.at(choice).weight /= 2;
	}
	if (items.at(choice).weight <= MIN_WEIGHT) {
		for (auto iter = items.begin(); iter != items.end(); iter++) {
			if (iter->max_weight == 0 || iter->max_weight >= iter->weight * 2) {
				iter->weight *= 2;
			}
		}
	}
}

void CItems::writeCsv()
{
	ofstream csv_data("res/cfg.csv", ios::out);
	csv_data << "项目,权重,最低权重,最高权重,开关\n";
	for (auto iter = items.begin(); iter != items.end(); iter++) {
		csv_data << iter->name << "," << iter->weight << "," << iter->min_weight << "," << iter->max_weight << ","
				 << iter->on_off << endl;
	}
	csv_data.close();
}

string CItems::getItem(string file, string index)
{
	ifstream ini_data(file, ios::in);
	string line, word, result = "异常";
	istringstream sin;
	vector<string> words;
	if (!ini_data.is_open()) {
		return "异常";
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
		}
	}
	ini_data.close();
	return result;
}

bool CItems::getOnOffSetting(string index)
{
	string ret = getItem("res/setting.ini", index);
	if (ret == "异常") {
		CErrorPrompt error_prompt("读取设置文件失败");
	}
	return ret == "true";
}

CItems::CItems()
{
	ifstream csv_data("res/cfg.csv", ios::in);
	string line, word;
	istringstream sin;
	vector<string> words;
	Item temp;
	if (!csv_data.is_open()) {
		CErrorPrompt error_prompt("读取项目文件失败");
	}
	getline(csv_data, line);
	while (getline(csv_data, line)) {
		sin.clear();
		sin.str(line);
		words.clear();
		while (getline(sin, word, ',')) {
			words.push_back(word);
		}
		temp.name = words[0];
		temp.weight = stoi(words[1]);
		temp.min_weight = stoi(words[2]);
		temp.max_weight = stoi(words[3]);
		temp.on_off = static_cast<bool>(stoi(words[4]));
		items.push_back(temp);
		if (temp.on_off) {
			items_to_select.push_back(temp);
		}
	}
	csv_data.close();
}

vector<Item> CItems::getItems()
{
	return items;
}

string CItems::chooseOne()
{
	double random_result = 0.0;
	int choice = -1;
	bool is_weight_select = getOnOffSetting("weightSelect");
	bool is_dynamic_weight = getOnOffSetting("dynamicWeight");
	vector<double> weight;
	default_random_engine e;
	uniform_real_distribution<double> u(0, 1);
	if (items_to_select.empty()) {
		CErrorPrompt error_prompt("没有待选项");
	}
	weight.push_back(0.0);
	if (is_weight_select) {
		double total_weight = 0.0;
		for (auto iter = items_to_select.begin(); iter != items_to_select.end(); iter++) {
			total_weight += iter->weight;
		}
		for (auto iter = items_to_select.begin(); iter != items_to_select.end(); iter++) {
			weight.push_back(iter->weight / total_weight + weight.back());
		}
	} else {
		for (size_t i = 0; i != items_to_select.size(); i++) {
			weight.push_back(1.0 / items_to_select.size() + weight.back());
		}
	}
	weight.erase(weight.begin());
	e.seed(time(0));
	do {
		random_result = u(e);
	} while (fabs(random_result) < 1e-6);
	for (auto iter = weight.begin(); iter != weight.end(); iter++) {
		if (random_result <= *iter) {
			choice = distance(weight.begin(), iter);
			break;
		}
	}
	if (is_weight_select && is_dynamic_weight) {
		adjustWeights(items_to_select.at(choice).name);
		writeCsv();
	}
	return items_to_select.at(choice).name;
}

void CItems::addOne(Item item)
{
	items.push_back(item);
	writeCsv();
}

void CItems::modifyOne(string name, Item item)
{
	auto iter = find_if(items.begin(), items.end(), [name](Item item) { return item.name == name; });
	if (iter == items.end()) {
		return;
	}
	*iter = item;
	writeCsv();
}

void CItems::removeOne(string name)
{
	for (auto iter = items.begin(); iter != items.end(); iter++) {
		if (iter->name == name) {
			items.erase(iter);
			break;
		}
	}
	writeCsv();
}

void CItems::switchOne(string name)
{
	auto it = find_if(items.begin(), items.end(), [name](Item item) { return item.name == name; });
	if (it == items.end()) {
		return;
	} else {
		it->on_off = !it->on_off;
		writeCsv();
	}
}

int CItems::getIndex(string name)
{
	auto it = find_if(items.begin(), items.end(), [name](Item item) { return item.name == name; });
	if (it == items.end()) {
		return -1;
	} else {
		return distance(items.begin(), it);
	}
}

int CItems::size()
{
	return items.size();
}

Item CItems::at(int index)
{
	return items.at(index);
}