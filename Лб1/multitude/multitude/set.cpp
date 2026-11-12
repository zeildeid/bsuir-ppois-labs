#include "Set.h"
using namespace std;

string Set::trim(const string& s) const {
    int start = 0;
    while (start < (int)s.length() && (s[start] == ' ' || s[start] == '\t' || s[start] == '\n' || s[start] == '\r')) {
        start++;
    }
    int end = (int)s.length() - 1;
    while (end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\n' || s[end] == '\r')) {
        end--;
    }
    if (start > end) {
        return "";
    }
    return s.substr(start, end - start + 1);
}

void Set::parseFromString(const string& str) {
    string s = trim(str);
    if (s.empty()) {
        return;
    }
    if (s.front() == '{' && s.back() == '}') {
        s = s.substr(1, s.length() - 2);
    }

    string currentToken = "";
    int braceDepth = 0;

    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c == '{') {
            braceDepth++;
            currentToken += c;
        }
        else if (c == '}') {
            braceDepth--;
            currentToken += c;
        }
        else if (c == ',' && braceDepth == 0) {
            string token = trim(currentToken);
            if (!token.empty()) {
                if (token.front() == '{' && token.back() == '}') {
                    Set sub(token);
                    this->add(sub);
                }
                else {
                    this->add(token);
                }
            }
            currentToken = "";
        }
        else {
            currentToken += c;
        }
    }
    string token = trim(currentToken);
    if (!token.empty()) {
        if (token.front() == '{' && token.back() == '}') {
            Set sub(token);
            this->add(sub);
        }
        else {
            this->add(token);
        }
    }
}

Set::Set() {
    atoms = nullptr;
    atomsCount = 0;
    subsets = nullptr;
    subsetsCount = 0;
}

Set::Set(const string& str) {
    atoms = nullptr;
    atomsCount = 0;
    subsets = nullptr;
    subsetsCount = 0;

    parseFromString(str);
}

Set::Set(const Set& other) {
    this->atomsCount = other.atomsCount;
    if (this->atomsCount > 0) {
        this->atoms = new string[this->atomsCount];
        for (int i = 0; i < this->atomsCount; i++) {
            this->atoms[i] = other.atoms[i];
        }
    }
    else {
        this->atoms = nullptr;
    }

    this->subsetsCount = other.subsetsCount;
    if (this->subsetsCount > 0) {
        this->subsets = new Set[this->subsetsCount];
        for (int i = 0; i < this->subsetsCount; i++) {
            this->subsets[i] = other.subsets[i];
        }
    }
    else {
        this->subsets = nullptr;
    }
}

Set::~Set() {
    delete[] atoms;
    delete[] subsets;
}

Set& Set::operator=(const Set& other) {
    if (this == &other) {
        return *this;
    }

    delete[] this->atoms;
    delete[] this->subsets;

    this->atomsCount = other.atomsCount;
    if (this->atomsCount > 0) {
        this->atoms = new string[this->atomsCount];
        for (int i = 0; i < this->atomsCount; i++) {
            this->atoms[i] = other.atoms[i];
        }
    }
    else {
        this->atoms = nullptr;
    }

    this->subsetsCount = other.subsetsCount;
    if (this->subsetsCount > 0) {
        this->subsets = new Set[this->subsetsCount];
        for (int i = 0; i < this->subsetsCount; i++) {
            this->subsets[i] = other.subsets[i];
        }
    }
    else {
        this->subsets = nullptr;
    }

    return *this;
}

bool Set::isEmpty() const {
    return (atomsCount == 0 && subsetsCount == 0);
}

int Set::cardinality() const {
    return atomsCount + subsetsCount;
}

void Set::add(const string& element) {
    string clean = trim(element);
    if (clean.empty()) {
        return;
    }

    if (clean.front() == '{' && clean.back() == '}') {
        Set sub(clean);
        this->add(sub);
        return;
    }
    if ((*this)[clean]) {
        return;
    }

    string* newAtoms = new string[atomsCount + 1];
    for (int i = 0; i < atomsCount; i++) {
        newAtoms[i] = atoms[i];
    }
    newAtoms[atomsCount] = clean;

    delete[] atoms;
    atoms = newAtoms;
    atomsCount++;
}

void Set::add(const Set& subset) {
    if ((*this)[subset]) {
        return;
    }

    Set* newSubsets = new Set[subsetsCount + 1];
    for (int i = 0; i < subsetsCount; i++) {
        newSubsets[i] = subsets[i];
    }
    newSubsets[subsetsCount] = subset;

    delete[] subsets;
    subsets = newSubsets;
    subsetsCount++;
}

void Set::remove(const string& element) {
    string clean = trim(element);
    if (clean.empty()) {
        return;
    }

    if (clean.front() == '{' && clean.back() == '}') {
        Set sub(clean);
        this->remove(sub);
        return;
    }

    int index = -1;
    for (int i = 0; i < atomsCount; i++) {
        if (atoms[i] == clean) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return;
    }

    if (atomsCount == 1) {
        delete[] atoms;
        atoms = nullptr;
        atomsCount = 0;
    }
    else {
        string* newAtoms = new string[atomsCount - 1];
        int j = 0;
        for (int i = 0; i < atomsCount; i++) {
            if (i != index) {
                newAtoms[j] = atoms[i];
                j++;
            }
        }
        delete[] atoms;
        atoms = newAtoms;
        atomsCount--;
    }
}

void Set::remove(const Set& subset) {
    int index = -1;
    for (int i = 0; i < subsetsCount; i++) {
        if (subsets[i] == subset) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return;
    }

    if (subsetsCount == 1) {
        delete[] subsets;
        subsets = nullptr;
        subsetsCount = 0;
    }
    else {
        Set* newSubsets = new Set[subsetsCount - 1];
        int j = 0;
        for (int i = 0; i < subsetsCount; i++) {
            if (i != index) {
                newSubsets[j] = subsets[i];
                j++;
            }
        }
        delete[] subsets;
        subsets = newSubsets;
        subsetsCount--;
    }
}

bool Set::operator[](const string& element) const {
    string clean = trim(element);
    if (clean.empty()) {
        return false;
    }

    if (clean.front() == '{' && clean.back() == '}') {
        Set sub(clean);
        return (*this)[sub];
    }

    for (int i = 0; i < atomsCount; i++) {
        if (atoms[i] == clean) {
            return true;
        }
    }
    return false;
}

bool Set::operator[](const Set& subset) const {
    for (int i = 0; i < subsetsCount; i++) {
        if (subsets[i] == subset) {
            return true;
        }
    }
    return false;
}

Set Set::operator+(const Set& other) const {
    Set result(*this);
    for (int i = 0; i < other.atomsCount; i++) {
        result.add(other.atoms[i]);
    }
    for (int i = 0; i < other.subsetsCount; i++) {
        result.add(other.subsets[i]);
    }
    return result;
}

Set& Set::operator+=(const Set& other) {
    *this = *this + other;
    return *this;
}

Set Set::operator*(const Set& other) const {
    Set result;
    for (int i = 0; i < this->atomsCount; i++) {
        if (other[this->atoms[i]]) {
            result.add(this->atoms[i]);
        }
    }
    for (int i = 0; i < this->subsetsCount; i++) {
        if (other[this->subsets[i]]) {
            result.add(this->subsets[i]);
        }
    }
    return result;
}

Set& Set::operator*=(const Set& other) {
    *this = *this * other;
    return *this;
}

Set Set::operator-(const Set& other) const {
    Set result;
    for (int i = 0; i < this->atomsCount; i++) {
        if (!other[this->atoms[i]]) {
            result.add(this->atoms[i]);
        }
    }
    for (int i = 0; i < this->subsetsCount; i++) {
        if (!other[this->subsets[i]]) {
            result.add(this->subsets[i]);
        }
    }
    return result;
}

Set& Set::operator-=(const Set& other) {
    *this = *this - other;
    return *this;
}

Set Set::boolean() const {
    Set result;
    int total = this->cardinality();

    int powerSetCount = 1 << total;

    for (int mask = 0; mask < powerSetCount; mask++) {
        Set sub;
        for (int i = 0; i < atomsCount; i++) {
            if ((mask & (1 << i)) != 0) {
                sub.add(atoms[i]);
            }
        }
        for (int j = 0; j < subsetsCount; j++) {
            if ((mask & (1 << (atomsCount + j))) != 0) {
                sub.add(subsets[j]);
            }
        }
        result.add(sub);
    }
    return result;
}

bool Set::operator==(const Set& other) const {
    if (this->atomsCount != other.atomsCount || this->subsetsCount != other.subsetsCount) {
        return false;
    }

    for (int i = 0; i < this->atomsCount; i++) {
        if (!other[this->atoms[i]]) {
            return false;
        }
    }

    for (int i = 0; i < this->subsetsCount; i++) {
        if (!other[this->subsets[i]]) {
            return false;
        }
    }

    return true;
}

bool Set::operator!=(const Set& other) const {
    return !(*this == other);
}

string Set::toString() const {
    string res = "{";
    bool first = true;

    for (int i = 0; i < atomsCount; i++) {
        if (!first) {
            res += ", ";
        }
        res += atoms[i];
        first = false;
    }

    for (int i = 0; i < subsetsCount; i++) {
        if (!first) {
            res += ", ";
        }
        res += subsets[i].toString();
        first = false;
    }

    res += "}";
    return res;
}

ostream& operator<<(ostream& os, const Set& s) {
    os << s.toString();
    return os;
}

istream& operator>>(istream& is, Set& s) {
    string line;
    if (getline(is, line)) {
        s = Set(line);
    }
    return is;
}