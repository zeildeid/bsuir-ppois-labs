#pragma once

#include <iostream>
#include <string>

using namespace std;

class Set {
private:
    string* atoms;
    int atomsCount;

    Set* subsets;
    int subsetsCount;

    string trim(const string& s) const;
    void parseFromString(const string& str);

public:
    Set();
    Set(const string& str);
    Set(const Set& other);
    ~Set();

    Set& operator=(const Set& other);
    bool isEmpty() const;
    int cardinality() const;

    void add(const string& element);
    void add(const Set& subset);

    void remove(const string& element);
    void remove(const Set& subset);

    bool operator[](const string& element) const;
    bool operator[](const Set& subset) const;

    Set operator+(const Set& other) const;
    Set& operator+=(const Set& other);
    Set operator*(const Set& other) const;
    Set& operator*=(const Set& other);
    Set operator-(const Set& other) const;
    Set& operator-=(const Set& other);

    Set boolean() const;

    bool operator==(const Set& other) const;
    bool operator!=(const Set& other) const;

    string toString() const;
};

ostream& operator<<(ostream& os, const Set& s);
istream& operator>>(istream& is, Set& s);