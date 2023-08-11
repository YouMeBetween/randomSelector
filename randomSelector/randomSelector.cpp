#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include "includes/items.h"
using namespace std;

string choose(vector<string> *item);

int main()
{
    CItems items("res/cfg.csv");
    string result = items.chooseOne();
    cout << result;
}

string choose(vector<string> *item) {
    default_random_engine e;
    uniform_int_distribution<int> u(0, item->size() - 1);
    e.seed(time(0));
    return item->at(u(e));
}
