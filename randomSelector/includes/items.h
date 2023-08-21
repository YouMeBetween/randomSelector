#ifndef _ITEMS_H_
#define _ITEMS_H_

#include <string>
#include <vector>
using namespace std;

typedef struct Item {
	string name;
	int weight{};
	int min_weight{};
	int max_weight{};
	Item() {}
};

class CItems
{
private:
	vector<Item> items;
	void adjustWeights(int);
	void writeCsv();
	string getItem(string, string);
	bool getOnOffSetting(string);
public:
	CItems();
	vector<Item> getItems();
	string chooseOne();
};
#endif // !_ITEMS_H_
