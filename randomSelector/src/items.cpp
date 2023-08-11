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
	double total_weight = 0.0, random_result = 0.0;
	int choice = -1;
	vector<double> weight;
	default_random_engine e;
	uniform_real_distribution<double> u(0, 1);
	for (auto iter = items.begin(); iter != items.end(); iter++) {
		total_weight += iter->weight;
	}
	if (fabs(total_weight) < 1e-6) {
		return "没有选项";
	}
	weight.push_back(0.0);
	for (auto iter = items.begin(); iter != items.end(); iter++) {
		weight.push_back(iter->weight / total_weight + weight.back());
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
	this->adjustWeights(choice);
	this->writeCsv();
	return items.at(choice).name;
}