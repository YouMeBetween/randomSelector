#include <iostream>
#include <ctime>
#include <random>
#include <fstream>
#include <vector>
using namespace std;

vector<string> getItem();
string choose(vector<string> *item);

int main()
{
    vector<string> item = getItem();
    if (item.empty()) {
        return -1;
    }
    cout << choose(&item) << endl;
    return 0;
}

vector<string> getItem()
{
    ifstream fin;
    vector<string> item;
    string temp;
    fin.open("cfg.ini", ios::in);
    if (!fin.is_open()) {
        cout << "无法打开文件\n";
        return item;
    }
    while (fin >> temp) {
        item.push_back(temp);
    }
    fin.close();
    return item;
}

string choose(vector<string> *item) {
    default_random_engine e;
    uniform_int_distribution<int> u(0, item->size() - 1);
    e.seed(time(0));
    return item->at(u(e));
}
