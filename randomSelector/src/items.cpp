#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include "../includes/items.h"
using namespace std;

void CItems::adjustWeights(int choice)
{
	items.at(choice).weight /= 2;
	if (items.at(choice).weight <= 2) {
		for (auto iter = items.begin(); iter != items.end(); iter++) {
			iter->weight *= 2;
		}
	}
}

void CItems::writeCsv()
{
	ofstream csv_data("res/cfg.csv", ios::out);
	csv_data << "项目,权重\n";
	for (auto iter = items.begin(); iter != items.end(); iter++) {
		csv_data << iter->name << "," << iter->weight << endl;
	}
	csv_data.close();
}

string CItems::getItem(string file, string index)
{
	ifstream ini_data(file, ios::in);
	string line, word, result = "未找到";
	istringstream sin;
	vector<string> words;
	if (!ini_data.is_open()) {
		cout << "无法打开文件\n";
		exit(1);
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

CItems::CItems()
{
	ifstream csv_data("res/cfg.csv", ios::in);
	string line, word;
	istringstream sin;
	vector<string> words;
	Item temp;
	if (!csv_data.is_open()) {
		cout << "无法打开文件\n";
		exit(1);
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
	bool is_weight_select = getItem("res/setting.ini", "weightSelect") == "true";
	bool is_dynamic_weight = getItem("res/setting.ini", "dynamicWeight") == "true";
	vector<double> weight;
	default_random_engine e;
	uniform_real_distribution<double> u(0, 1);
	if (items.empty()) {
		return "没有选项";
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