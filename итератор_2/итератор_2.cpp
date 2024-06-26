#include <fstream>
#include <iostream>
#include <string>
#include "iterator.h"
using namespace std;


int main() {
    Array<string> arr;

    ifstream file("data.txt");
    if (!file) {
        cout << "Файл не найден!" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        arr.pushBack(line);
    }

    for (auto it = arr.Front(); it != arr.Back(); ++it) {
        cout << *it << endl;
    }

    return 0;
}
