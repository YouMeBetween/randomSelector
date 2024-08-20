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
	bool on_off{};
	Item() {}
};

class CItems
{
private:
	vector<Item> items;
	vector<Item> items_to_select;
	void adjustWeights(string);
	void writeCsv();
	string getItem(string, string);
	bool getOnOffSetting(string);
public:
	CItems();
	vector<Item> getItems();
	string chooseOne();
	void addOne(Item);
	void modifyOne(string, Item);
	void removeOne(string);
	void switchOne(string);
	int getIndex(string);
	int size();
	bool empty();
	Item at(int);
};
#endif // !_ITEMS_H_
