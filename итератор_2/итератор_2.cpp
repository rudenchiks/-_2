#include <fstream>
#include <iostream>
#include <string>
#include "iterator.h"
using namespace std;

template <typename T>
class Array : public ArrayIterator<T> {
    T* Xarray;
    int len;
    int max_size;

public:
    using Iterator = typename ArrayIterator<T>::Iterator;
    using ConstIterator = typename ArrayIterator<T>::ConstIterator;

    Array() {
        len = 0;
        Xarray = new T[1];
        max_size = 1;
    }

    ~Array() { delete[] Xarray; }

    // Конструктор перемещения
    Array(Array&& other) noexcept : Xarray(other.Xarray), len(other.len), max_size(other.max_size) {
        other.Xarray = nullptr;
        other.len = 0;
        other.max_size = 0;
    }

    // Оператор перемещения
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] Xarray;

            Xarray = other.Xarray;
            len = other.len;
            max_size = other.max_size;

            other.Xarray = nullptr;
            other.len = 0;
            other.max_size = 0;
        }
        return *this;
    }

    void pushBack(const T& value) {
        if (len >= max_size) addMemory();
        Xarray[len] = value;
        len++;
    }

    void addMemory() {
        max_size *= 2;
        T* tmp = Xarray;
        Xarray = new T[max_size];
        for (int i = 0; i < len; ++i)
            Xarray[i] = tmp[i];
        delete[] tmp;
    }

    T& operator[](const int Li) {
        return Xarray[Li];
    }

    ConstIterator cbegin() const {
        return ConstIterator(&Xarray[0], &Xarray[len]);
    }

    ConstIterator cend() const {
        return ConstIterator(&Xarray[len], &Xarray[len]);
    }

    Iterator Front() {
        return Iterator(&Xarray[0], &Xarray[len]);
    }

    Iterator Back() {
        return Iterator(&Xarray[len], &Xarray[len]);
    }

    void Fill(const int Xi) {
        for (int i = 0; i < len; ++i) {
            Xarray[i] = Xi;
        }
    }

    size_t max() const {
        return max_size;
    }

    int Size() const {
        return len;
    }

    void Resize(const int S) {
        T* Rarray = new T[S];

        for (int i = 0; i < len; i++) {
            Rarray[i] = Xarray[i];
        }

        delete[] Xarray;
        Xarray = new T[S];

        for (int i = 0; i < S; i++) {
            Xarray[i] = Rarray[i];
        }

        len = S;
    }

    Array& operator+(Array a) {
        const int lenn = len + a.Size();
        T* x = new T[lenn];

        for (int i = 0; i < len; i++) {
            x[i] = Xarray[i];
        }

        for (int i = len, g = 0; i < lenn; i++, g++) {
            x[i] = a[g];
        }

        len = lenn;
        delete[] Xarray;
        Xarray = new T[len];

        for (int i = 0; i < len; i++) {
            Xarray[i] = x[i];
        }
        return *this;
    }

    void operator=(const Array& x) {
        if (this != &x) {
            T* XXarr = new T[x.Size()];

            for (int i = 0; i < x.Size(); i++) {
                XXarr[i] = x[i];
            }

            delete[] Xarray;
            len = x.Size();
            Xarray = new T[len];

            for (int i = 0; i < len; ++i) {
                Xarray[i] = XXarr[i];
            }
        }
    }

    void swap(Array& other) noexcept {
        swap(Xarray, other.Xarray);
        swap(len, other.len);
        swap(max_size, other.max_size);
    }

    template<typename T2>
    friend ostream& operator<<(ostream& s, const Array<T2>& n);
};

template <typename T>
ostream& operator<<(ostream& s, const Array<T>& n) {
    for (int i = 0; i < n.Size(); ++i) {
        s << n[i] << " ";
    }
    return s;
}

int main() {
    Array<string> arr;
    //Array<const char*> arr2;

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

    //список из файла
    //rvalue конструктор

    return 0;
}
