#ifndef ITERATOR_H
#define ITERATOR_H

#include <string>
#include <algorithm>
using namespace std;

template <typename T>
class Array {
    T* Xarray;
    int len;
    int max_size;

public:
    class Iterator;
    class ConstIterator;

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

    class Iterator {
        T* cur;
        T* end;

    public:
        Iterator(T* first, T* last) : cur(first), end(last) {
            while (cur != end && !isPalindrome(*cur)) {
                ++cur;
            }
        }

        Iterator& operator++() {
            do {
                ++cur;
            } while (cur != end && !isPalindrome(*cur));
            return *this;
        }

        T& operator+(int n) { return *(cur + n); }
        T& operator-(int n) { return *(cur - n); }

        bool operator!=(const Iterator& it) const { return cur != it.cur; }
        bool operator==(const Iterator& it) const { return cur == it.cur; }
        T& operator*() const { return *cur; }

        bool isPalindrome(const T& word) const {
            string str = word;
            string reversed = str;
            reverse(reversed.begin(), reversed.end());
            return str == reversed;
        }
    };

    class ConstIterator {
        const T* cur;
        const T* end;

    public:
        ConstIterator(const T* first, const T* last) : cur(first), end(last) {
            while (cur != end && !isPalindrome(*cur)) {
                ++cur;
            }
        }

        ConstIterator& operator++() {
            do {
                ++cur;
            } while (cur != end && !isPalindrome(*cur));
            return *this;
        }

        const T& operator+(int n) const { return *(cur + n); }
        const T& operator-(int n) const { return *(cur - n); }

        bool operator!=(const ConstIterator& it) const { return cur != it.cur; }
        bool operator==(const ConstIterator& it) const { return cur == it.cur; }
        const T& operator*() const { return *cur; }

        bool isPalindrome(const T& word) const {
            string str = word;
            string reversed = str;
            reverse(reversed.begin(), reversed.end());
            return str == reversed;
        }
    };
};

template <typename T>
ostream& operator<<(ostream& s, const Array<T>& n) {
    for (int i = 0; i < n.Size(); ++i) {
        s << n[i] << " ";
    }
    return s;
}

#endif ITERATOR_H