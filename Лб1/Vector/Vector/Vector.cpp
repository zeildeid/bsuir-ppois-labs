#include "Vector.h"
using namespace std;

int Vector::count = 0;

bool Point::operator==(const Point& other) const {
    double eps = 0.000001;
    if (fabs(this->x - other.x) < eps &&
        fabs(this->y - other.y) < eps &&
        fabs(this->z - other.z) < eps) {
        return true;
    }
    return false;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

Vector::Vector() {
    coords = new double[6];
    for (int i = 0; i < 6; i++) {
        coords[i] = 0.0;
    }
    count++;
}

Vector::Vector(const Point& start, const Point& end) {
    coords = new double[6];
    coords[0] = start.x;
    coords[1] = start.y;
    coords[2] = start.z;
    coords[3] = end.x;
    coords[4] = end.y;
    coords[5] = end.z;
    count++;
}

Vector::Vector(double x1, double y1, double z1, double x2, double y2, double z2) {
    coords = new double[6];
    coords[0] = x1;
    coords[1] = y1;
    coords[2] = z1;
    coords[3] = x2;
    coords[4] = y2;
    coords[5] = z2;
    count++;
}

Vector::Vector(double x, double y, double z) {
    coords = new double[6];
    coords[0] = 0.0;
    coords[1] = 0.0;
    coords[2] = 0.0;
    coords[3] = x;
    coords[4] = y;
    coords[5] = z;
    count++;
}

Vector::Vector(const Vector& other) {
    coords = new double[6];
    for (int i = 0; i < 6; i++) {
        coords[i] = other.coords[i];
    }
    count++;
}

Vector::~Vector() {
    delete[] coords;
    count--;
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }

    for (int i = 0; i < 6; i++) {
        this->coords[i] = other.coords[i];
    }

    return *this;
}

Point Vector::getStart() const {
    return Point(coords[0], coords[1], coords[2]);
}

Point Vector::getEnd() const {
    return Point(coords[3], coords[4], coords[5]);
}

void Vector::setStart(const Point& start) {
    coords[0] = start.x;
    coords[1] = start.y;
    coords[2] = start.z;
}

void Vector::setEnd(const Point& end) {
    coords[3] = end.x;
    coords[4] = end.y;
    coords[5] = end.z;
}

double Vector::getVx() const {
    return coords[3] - coords[0];
}

double Vector::getVy() const {
    return coords[4] - coords[1];
}

double Vector::getVz() const {
    return coords[5] - coords[2];
}

double Vector::length() const {
    double vx = getVx();
    double vy = getVy();
    double vz = getVz();
    return sqrt(vx * vx + vy * vy + vz * vz);
}

double Vector::cosAngle(const Vector& other) const {
    double len1 = this->length();
    double len2 = other.length();

    if (len1 == 0.0 || len2 == 0.0) {
        throw "Ошибка: нельзя найти угол с нулевым вектором!";
    }

    double scalarProd = this->getVx() * other.getVx() +
        this->getVy() * other.getVy() +
        this->getVz() * other.getVz();

    double result = scalarProd / (len1 * len2);

    if (result > 1.0) result = 1.0;
    if (result < -1.0) result = -1.0;

    return result;
}

double Vector::operator^(const Vector& other) const {
    return this->cosAngle(other);
}

Vector Vector::operator+(const Vector& other) const {
    double new_x2 = coords[3] + other.getVx();
    double new_y2 = coords[4] + other.getVy();
    double new_z2 = coords[5] + other.getVz();

    return Vector(coords[0], coords[1], coords[2], new_x2, new_y2, new_z2);
}

Vector& Vector::operator+=(const Vector& other) {
    coords[3] += other.getVx();
    coords[4] += other.getVy();
    coords[5] += other.getVz();
    return *this;
}

Vector Vector::operator-(const Vector& other) const {
    double new_x2 = coords[3] - other.getVx();
    double new_y2 = coords[4] - other.getVy();
    double new_z2 = coords[5] - other.getVz();

    return Vector(coords[0], coords[1], coords[2], new_x2, new_y2, new_z2);
}

Vector& Vector::operator-=(const Vector& other) {
    coords[3] -= other.getVx();
    coords[4] -= other.getVy();
    coords[5] -= other.getVz();
    return *this;
}

Vector Vector::operator*(const Vector& other) const {
    double ax = this->getVx();
    double ay = this->getVy();
    double az = this->getVz();

    double bx = other.getVx();
    double by = other.getVy();
    double bz = other.getVz();

    double cx = ay * bz - az * by;
    double cy = az * bx - ax * bz;
    double cz = ax * by - ay * bx;

    return Vector(coords[0], coords[1], coords[2],
        coords[0] + cx, coords[1] + cy, coords[2] + cz);
}

Vector& Vector::operator*=(const Vector& other) {
    *this = *this * other;
    return *this;
}

Vector Vector::operator*(double number) const {
    double new_x2 = coords[0] + getVx() * number;
    double new_y2 = coords[1] + getVy() * number;
    double new_z2 = coords[2] + getVz() * number;

    return Vector(coords[0], coords[1], coords[2], new_x2, new_y2, new_z2);
}

Vector& Vector::operator*=(double number) {
    coords[3] = coords[0] + getVx() * number;
    coords[4] = coords[1] + getVy() * number;
    coords[5] = coords[2] + getVz() * number;
    return *this;
}

Vector Vector::operator/(double number) const {
    if (fabs(number) < 0.000001) {
        throw "Ошибка: деление вектора на ноль!";
    }

    double new_x2 = coords[0] + getVx() / number;
    double new_y2 = coords[1] + getVy() / number;
    double new_z2 = coords[2] + getVz() / number;

    return Vector(coords[0], coords[1], coords[2], new_x2, new_y2, new_z2);
}

Vector& Vector::operator/=(double number) {
    if (fabs(number) < 0.000001) {
        throw "Ошибка: деление вектора на ноль!";
    }

    coords[3] = coords[0] + getVx() / number;
    coords[4] = coords[1] + getVy() / number;
    coords[5] = coords[2] + getVz() / number;
    return *this;
}

Vector Vector::operator/(const Vector& other) const {
    if (fabs(other.getVx()) < 0.000001 ||
        fabs(other.getVy()) < 0.000001 ||
        fabs(other.getVz()) < 0.000001) {
        throw "Ошибка: деление на нулевую координату вектора!";
    }

    double new_x2 = coords[0] + getVx() / other.getVx();
    double new_y2 = coords[1] + getVy() / other.getVy();
    double new_z2 = coords[2] + getVz() / other.getVz();

    return Vector(coords[0], coords[1], coords[2], new_x2, new_y2, new_z2);
}

Vector& Vector::operator/=(const Vector& other) {
    *this = *this / other;
    return *this;
}

bool Vector::operator==(const Vector& other) const {
    double eps = 0.000001;
    if (fabs(this->getVx() - other.getVx()) < eps &&
        fabs(this->getVy() - other.getVy()) < eps &&
        fabs(this->getVz() - other.getVz()) < eps) {
        return true;
    }
    return false;
}

bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

bool Vector::operator>(const Vector& other) const {
    return this->length() > other.length() + 0.000001;
}

bool Vector::operator>=(const Vector& other) const {
    return this->length() >= other.length() - 0.000001;
}

bool Vector::operator<(const Vector& other) const {
    return this->length() < other.length() - 0.000001;
}

bool Vector::operator<=(const Vector& other) const {
    return this->length() <= other.length() + 0.000001;
}

istream& Vector::read(istream& is) {
    double x1, y1, z1, x2, y2, z2;
    if (is >> x1 >> y1 >> z1 >> x2 >> y2 >> z2) {
        coords[0] = x1;
        coords[1] = y1;
        coords[2] = z1;
        coords[3] = x2;
        coords[4] = y2;
        coords[5] = z2;
    }
    return is;
}

string Vector::toString() const {
    string res = "Начало: (" + to_string(coords[0]) + ", " + to_string(coords[1]) + ", " + to_string(coords[2]) + ") ";
    res += "Конец: (" + to_string(coords[3]) + ", " + to_string(coords[4]) + ", " + to_string(coords[5]) + ") ";
    res += "Координаты вектора: [" + to_string(getVx()) + ", " + to_string(getVy()) + ", " + to_string(getVz()) + "]";
    return res;
}

int Vector::getCount() {
    return count;
}