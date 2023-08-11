#ifndef _ITEMS_H_
#define _ITEMS_H

#include <string>
#include <vector>
using namespace std;

typedef struct Item {
	string name;
	int weight{};
	Item() {}
};

class CItems
{
private:
	vector<Item> items;
public:
	CItems(string);
	vector<Item> getItems();
	string chooseOne();
};
#endif // !_ITEMS_H_
