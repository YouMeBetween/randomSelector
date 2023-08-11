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

CItems::CItems(string file_dir)
{
	ifstream csv_data(file_dir, ios::in);
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
	double total_weight = 0.0, choice = 0.0;
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
		choice = u(e);
	} while (fabs(choice) < 1e-6);
	for (auto iter = weight.begin(); iter != weight.end(); iter++) {
		if (choice <= *iter) {
			return items.at(distance(weight.begin(), iter)).name;
		}
	}
	return items.back().name;
}