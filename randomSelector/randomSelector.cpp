#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include "includes/items.h"
using namespace std;

int main()
{
    CItems items;
    string result = items.chooseOne();
    cout << result;
}