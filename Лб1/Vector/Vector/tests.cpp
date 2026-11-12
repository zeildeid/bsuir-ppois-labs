#include <UnitTest++/UnitTest++.h>
#include <sstream>
#include <clocale>
#include "Vector.h"

using namespace std;

// 1. Тест конструктора по умолчанию
TEST(TestDefaultConstructor) {
    Vector v;
    CHECK_CLOSE(0.0, v.getVx(), 0.001);
    CHECK_CLOSE(0.0, v.getVy(), 0.001);
    CHECK_CLOSE(0.0, v.getVz(), 0.001);
    CHECK_CLOSE(0.0, v.length(), 0.001);
}

// 2. Тест конструктора по двум точкам
TEST(TestPointsConstructor) {
    Point p1(1, 2, 3);
    Point p2(4, 6, 3);
    Vector v(p1, p2);
    CHECK(v.getStart() == p1);
    CHECK(v.getEnd() == p2);
    CHECK_CLOSE(5.0, v.length(), 0.001);
}

// 3. Тест конструктора по 6 координатам
TEST(TestSixCoordsConstructor) {
    Vector v(1, 1, 1, 2, 3, 4);
    CHECK_CLOSE(1.0, v.getVx(), 0.001);
    CHECK_CLOSE(2.0, v.getVy(), 0.001);
    CHECK_CLOSE(3.0, v.getVz(), 0.001);
}

// 4. Тест конструктора по 3 координатам
TEST(TestThreeCoordsConstructor) {
    Vector v(3, 0, 4);
    CHECK_CLOSE(3.0, v.getVx(), 0.001);
    CHECK_CLOSE(0.0, v.getVy(), 0.001);
    CHECK_CLOSE(4.0, v.getVz(), 0.001);
    CHECK_CLOSE(5.0, v.length(), 0.001);
}

// 5. Тест конструктора копирования
TEST(TestCopyConstructor) {
    Vector v1(0, 0, 0, 3, 4, 0);
    Vector v2(v1);
    CHECK(v1 == v2);
    v2.setEnd(Point(10, 10, 10));
    CHECK(v1 != v2);
}

// 6. Тест оператора присваивания
TEST(TestAssignment) {
    Vector v1(1, 2, 3, 4, 5, 6);
    Vector v2;
    v2 = v1;
    CHECK(v1 == v2);
}

// 7. Тест самоприсваивания
TEST(TestSelfAssignment) {
    Vector v1(0, 0, 0, 3, 4, 0);
    v1 = v1;
    CHECK_CLOSE(5.0, v1.length(), 0.001);
}

// 8. Тест геттеров и сеттеров точек
TEST(TestGettersSetters) {
    Vector v;
    Point s(1, 1, 1);
    Point e(4, 5, 1);
    v.setStart(s);
    v.setEnd(e);
    CHECK(v.getStart() == s);
    CHECK(v.getEnd() == e);
    CHECK(v.getStart() != v.getEnd());
}

// 9. Тест пересчета длины после модификации точек
TEST(TestLengthCalculation) {
    Vector v(3, 4, 0);
    CHECK_CLOSE(5.0, v.length(), 0.001);
    v.setEnd(Point(0, 0, 10));
    CHECK_CLOSE(10.0, v.length(), 0.001);
}

// 10. Тест сложения векторов (+)
TEST(TestPlus) {
    Vector v1(1, 2, 3);
    Vector v2(4, 5, 6);
    Vector res = v1 + v2;
    CHECK_CLOSE(5.0, res.getVx(), 0.001);
    CHECK_CLOSE(7.0, res.getVy(), 0.001);
    CHECK_CLOSE(9.0, res.getVz(), 0.001);
}

// 11. Тест сложения с присваиванием (+=)
TEST(TestPlusEqual) {
    Vector v1(1, 2, 3);
    Vector v2(1, 1, 1);
    v1 += v2;
    CHECK_CLOSE(2.0, v1.getVx(), 0.001);
    CHECK_CLOSE(3.0, v1.getVy(), 0.001);
    CHECK_CLOSE(4.0, v1.getVz(), 0.001);
}

// 12. Тест вычитания векторов (-)
TEST(TestMinus) {
    Vector v1(5, 7, 9);
    Vector v2(1, 2, 3);
    Vector res = v1 - v2;
    CHECK_CLOSE(4.0, res.getVx(), 0.001);
    CHECK_CLOSE(5.0, res.getVy(), 0.001);
    CHECK_CLOSE(6.0, res.getVz(), 0.001);
}

// 13. Тест вычитания с присваиванием (-=)
TEST(TestMinusEqual) {
    Vector v1(5, 5, 5);
    Vector v2(5, 5, 5);
    v1 -= v2;
    CHECK_CLOSE(0.0, v1.length(), 0.001);
}

// 14. Тест векторного произведения (*)
TEST(TestCrossProduct) {
    Vector v1(1, 0, 0);
    Vector v2(0, 1, 0);
    Vector res = v1 * v2;
    CHECK_CLOSE(0.0, res.getVx(), 0.001);
    CHECK_CLOSE(0.0, res.getVy(), 0.001);
    CHECK_CLOSE(1.0, res.getVz(), 0.001);
}

// 15. Тест векторного произведения с присваиванием (*=)
TEST(TestCrossProductEqual) {
    Vector v1(1, 2, 3);
    Vector v2(4, 5, 6);
    v1 *= v2;
    CHECK_CLOSE(-3.0, v1.getVx(), 0.001);
    CHECK_CLOSE(6.0, v1.getVy(), 0.001);
    CHECK_CLOSE(-3.0, v1.getVz(), 0.001);
}

// 16. Тест векторного произведения параллельных векторов
TEST(TestCrossProductParallel) {
    Vector v1(1, 2, 3);
    Vector v2(2, 4, 6);
    Vector res = v1 * v2;
    CHECK_CLOSE(0.0, res.length(), 0.001);
}

// 17. Тест умножения вектора на число
TEST(TestMultNumber) {
    Vector v(1, -2, 3);
    Vector res = v * 2.0;
    CHECK_CLOSE(2.0, res.getVx(), 0.001);
    CHECK_CLOSE(-4.0, res.getVy(), 0.001);
    CHECK_CLOSE(6.0, res.getVz(), 0.001);
}

// 18. Тест умножения вектора на отрицательное число
TEST(TestMultNegativeNumber) {
    Vector v(1, -2, 3);
    Vector res = v * -3.0;
    CHECK_CLOSE(-3.0, res.getVx(), 0.001);
    CHECK_CLOSE(6.0, res.getVy(), 0.001);
    CHECK_CLOSE(-9.0, res.getVz(), 0.001);
}

// 19. Тест умножения на число с присваиванием (*=)
TEST(TestMultNumberEqual) {
    Vector v(2, 3, 4);
    v *= 2.0;
    CHECK_CLOSE(4.0, v.getVx(), 0.001);
    CHECK_CLOSE(6.0, v.getVy(), 0.001);
    CHECK_CLOSE(8.0, v.getVz(), 0.001);
}

// 20. Тест деления вектора на число (/) и (/=)
TEST(TestDivNumber) {
    Vector v(4, 8, 12);
    Vector res = v / 4.0;
    CHECK_CLOSE(1.0, res.getVx(), 0.001);
    CHECK_CLOSE(2.0, res.getVy(), 0.001);
    CHECK_CLOSE(3.0, res.getVz(), 0.001);

    v /= 2.0;
    CHECK_CLOSE(2.0, v.getVx(), 0.001);
}

// 21. Тест деления вектора на ноль (исключение const char*)
TEST(TestDivByZeroNumber) {
    Vector v(1, 2, 3);
    CHECK_THROW(v / 0.0, const char*);
    CHECK_THROW(v /= 0.0, const char*);
}

// 22. Тест деления двух векторов
TEST(TestDivVectors) {
    Vector v1(10, 20, 30);
    Vector v2(2, 5, 10);
    Vector res = v1 / v2;
    CHECK_CLOSE(5.0, res.getVx(), 0.001);
    CHECK_CLOSE(4.0, res.getVy(), 0.001);
    CHECK_CLOSE(3.0, res.getVz(), 0.001);
    v1 /= v2;
    CHECK(v1 == res);
}

// 23. Тест деления на вектор с нулевой координатой (исключение const char*)
TEST(TestDivVectorsByZero) {
    Vector v1(10, 20, 30);
    Vector v2(2, 0, 10);
    CHECK_THROW(v1 / v2, const char*);
    CHECK_THROW(v1 /= v2, const char*);
}

// 24. Тест косинуса угла сонаправленных векторов
TEST(TestCosAngleSame) {
    Vector v1(1, 2, 3);
    Vector v2(2, 4, 6);
    CHECK_CLOSE(1.0, v1.cosAngle(v2), 0.001);
    CHECK_CLOSE(1.0, v1 ^ v2, 0.001);
}

// 25. Тест косинуса угла перпендикулярных векторов
TEST(TestCosAnglePerpendicular) {
    Vector v1(1, 0, 0);
    Vector v2(0, 5, 0);
    CHECK_CLOSE(0.0, v1.cosAngle(v2), 0.001);
}

// 26. Тест косинуса угла противоположных векторов
TEST(TestCosAngleOpposite) {
    Vector v1(3, -4, 0);
    Vector v2(-6, 8, 0);
    CHECK_CLOSE(-1.0, v1 ^ v2, 0.001);
}

// 27. Тест косинуса угла с нулевым вектором (исключение const char*)
TEST(TestCosAngleZero) {
    Vector v1(1, 2, 3);
    Vector zero;
    CHECK_THROW(v1.cosAngle(zero), const char*);
}

// 28. Тест операторов == и !=
TEST(TestEqualNotEqual) {
    Vector v1(0, 0, 0, 1, 2, 3);
    Vector v2(5, 5, 5, 6, 7, 8);
    Vector v3(0, 0, 0, 1, 2, 4);
    CHECK(v1 == v2);
    CHECK(v1 != v3);
}

// 29. Тест сравнения > и >=
TEST(TestGreater) {
    Vector vLong(3, 4, 0);
    Vector vShort(1, 0, 0);
    Vector vEq(5, 0, 0);
    CHECK(vLong > vShort);
    CHECK(vLong >= vShort);
    CHECK(vLong >= vEq);
}

// 30. Тест сравнения < и <=
TEST(TestLess) {
    Vector vShort(0, 2, 0);
    Vector vLong(0, 0, 4);
    Vector vEq(2, 0, 0);
    CHECK(vShort < vLong);
    CHECK(vShort <= vLong);
    CHECK(vShort <= vEq);
}

// 31. Тест ввода через метод read()
TEST(TestReadMethod) {
    Vector v;
    stringstream ss("1 2 3 4 5 6");
    v.read(ss);
    CHECK_CLOSE(3.0, v.getVx(), 0.001);
    CHECK_CLOSE(3.0, v.getVy(), 0.001);
    CHECK_CLOSE(3.0, v.getVz(), 0.001);
}

// 32. Тест некорректного ввода через read()
TEST(TestBadReadInput) {
    Vector v(1, 2, 3);
    stringstream ss("abc def");
    v.read(ss);
    CHECK(ss.fail());
    CHECK_CLOSE(1.0, v.getVx(), 0.001);
}

// 33. Тест метода toString
TEST(TestToString) {
    Vector v(1, 2, 3);
    string str = v.toString();
    CHECK(!str.empty());
}

// 34. Тест статического счетчика объектов
TEST(TestStaticCount) {
    int c = Vector::getCount();
    {
        Vector v1;
        Vector v2(v1);
        CHECK_EQUAL(c + 2, Vector::getCount());
    }
    CHECK_EQUAL(c, Vector::getCount());
}

int main() {
    setlocale(LC_ALL, "Russian");
    return UnitTest::RunAllTests();
}