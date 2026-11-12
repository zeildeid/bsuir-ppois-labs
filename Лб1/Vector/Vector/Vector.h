#pragma once

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct Point {
    double x;
    double y;
    double z;

    Point(double x = 0.0, double y = 0.0, double z = 0.0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
};

class Vector {
private:
    double* coords;
    static int count;

public:
    Vector();
    Vector(const Point& start, const Point& end);
    Vector(double x1, double y1, double z1, double x2, double y2, double z2);
    Vector(double x, double y, double z);
    Vector(const Vector& other);
    ~Vector();

    Vector& operator=(const Vector& other);
    Point getStart() const;
    Point getEnd() const;
    void setStart(const Point& start);
    void setEnd(const Point& end);
    double getVx() const;
    double getVy() const;
    double getVz() const;
    double length() const;
    double cosAngle(const Vector& other) const;
    double operator^(const Vector& other) const;

    Vector operator+(const Vector& other) const;
    Vector& operator+=(const Vector& other);
    Vector operator-(const Vector& other) const;
    Vector& operator-=(const Vector& other);
    Vector operator*(const Vector& other) const;
    Vector& operator*=(const Vector& other);
    Vector operator*(double number) const;
    Vector& operator*=(double number);
    Vector operator/(double number) const;
    Vector& operator/=(double number);
    Vector operator/(const Vector& other) const;
    Vector& operator/=(const Vector& other);

    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
    bool operator>(const Vector& other) const;
    bool operator>=(const Vector& other) const;
    bool operator<(const Vector& other) const;
    bool operator<=(const Vector& other) const;

    istream& read(istream& is);
    string toString() const;
    static int getCount();
};