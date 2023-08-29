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

void CItems::adjustWeights(int choice)
{
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
	csv_data << "项目,权重,最低权重,最高权重\n";
	for (auto iter = items.begin(); iter != items.end(); iter++) {
		csv_data << iter->name << "," << iter->weight << "," << iter->min_weight << "," << iter->max_weight << endl;
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
		items.push_back(temp);
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
	if (items.empty()) {
		CErrorPrompt error_prompt("没有待选项");
	}
	weight.push_back(0.0);
	if (is_weight_select) {
		double total_weight = 0.0;
		for (auto iter = items.begin(); iter != items.end(); iter++) {
			total_weight += iter->weight;
		}
		for (auto iter = items.begin(); iter != items.end(); iter++) {
			weight.push_back(iter->weight / total_weight + weight.back());
		}
	} else {
		for (size_t i = 0; i != items.size(); i++) {
			weight.push_back(1.0 / items.size() + weight.back());
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
		adjustWeights(choice);
		writeCsv();
	}
	return items.at(choice).name;
}