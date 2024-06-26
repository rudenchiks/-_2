#ifndef ITERATOR_H
#define ITERATOR_H

#include <string>
#include <algorithm>
using namespace std;

template <typename T>
class Array;

template <typename T>
class ArrayIterator {
public:
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

#endif // ITERATOR_H
