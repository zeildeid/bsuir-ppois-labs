#include <UnitTest++/UnitTest++.h>
#include <sstream>
#include <clocale>
#include "Set.h"

using namespace std;

// 1. Тест конструктора по умолчанию
TEST(TestDefaultConstructor) {
    Set s;
    CHECK(s.isEmpty());
    CHECK_EQUAL(0, s.cardinality());
    CHECK_EQUAL("{}", s.toString());
}

// 2. Тест конструктора из строкового литерала
TEST(TestStringLiteralConstructor) {
    Set s("{a, b, c}");
    CHECK(!s.isEmpty());
    CHECK_EQUAL(3, s.cardinality());
    CHECK(s["a"]);
    CHECK(s["b"]);
    CHECK(s["c"]);
}

// 3. Тест конструктора из std::string со сложной вложенностью
TEST(TestStdStringComplexConstructor) {
    string input = "{a, b, c, {a, b}, {}, {a, {c}}}";
    Set s(input);
    CHECK_EQUAL(6, s.cardinality());
    CHECK(s["a"]);
    CHECK(s["{a, b}"]);
    CHECK(s["{}"]);
    CHECK(s["{a, {c}}"]);
}

// 4. Тест игнорирования дубликатов (канторовское множество)
TEST(TestNoDuplicatesInSet) {
    Set s("{a, a, b, b, {c}, {c}}");
    CHECK_EQUAL(3, s.cardinality());
    CHECK(s["a"]);
    CHECK(s["b"]);
    CHECK(s["{c}"]);
}

// 5. Тест независимости от порядка элементов
TEST(TestOrderIndependence) {
    Set s1("{a, b, {1, 2}}");
    Set s2("{{2, 1}, b, a}");
    CHECK(s1 == s2);
}

// 6. Тест конструктора копирования (глубокое копирование)
TEST(TestCopyConstructor) {
    Set s1("{x, y}");
    Set s2(s1);
    CHECK(s1 == s2);
    s2.add("z");
    CHECK(s1 != s2);
    CHECK_EQUAL(2, s1.cardinality());
    CHECK_EQUAL(3, s2.cardinality());
}

// 7. Тест оператора присваивания
TEST(TestAssignmentOperator) {
    Set s1("{a, {b}}");
    Set s2;
    s2 = s1;
    CHECK(s1 == s2);
}

// 8. Тест самоприсваивания
TEST(TestSelfAssignment) {
    Set s("{a, b, c}");
    s = s;
    CHECK_EQUAL(3, s.cardinality());
    CHECK(s["a"]);
}

// 9. Тест добавления строкового элемента
TEST(TestAddStringElement) {
    Set s;
    s.add(string("alpha"));
    s.add("beta");
    CHECK_EQUAL(2, s.cardinality());
    CHECK(s["alpha"]);
    CHECK(s["beta"]);
}

// 10. Тест добавления подмножества объектом Set
TEST(TestAddSubsetObject) {
    Set s("{a}");
    Set sub("{b, c}");
    s.add(sub);
    CHECK_EQUAL(2, s.cardinality());
    CHECK(s[sub]);
}

// 11. Тест повторного добавления уже существующего элемента
TEST(TestAddExistingElementDoesNotChangeSize) {
    Set s("{a, b}");
    s.add("a");
    s.add("{x}");
    s.add(Set("{x}"));
    CHECK_EQUAL(3, s.cardinality());
}

// 12. Тест удаления обычного элемента
TEST(TestRemoveAtom) {
    Set s("{a, b, c}");
    s.remove("b");
    CHECK_EQUAL(2, s.cardinality());
    CHECK(!s["b"]);
    CHECK(s["a"]);
    CHECK(s["c"]);
}

// 13. Тест удаления единственного элемента (переход в пустое множество)
TEST(TestRemoveLastElementMakesEmpty) {
    Set s("{only}");
    s.remove("only");
    CHECK(s.isEmpty());
    CHECK_EQUAL(0, s.cardinality());
}

// 14. Тест удаления вложенного множества
TEST(TestRemoveSubset) {
    Set s("{a, {b, c}, {}}");
    s.remove(Set("{b, c}"));
    CHECK_EQUAL(2, s.cardinality());
    CHECK(!s["{b, c}"]);
    CHECK(s["{}"]);
}

// 15. Тест удаления несуществующего элемента
TEST(TestRemoveNonExistent) {
    Set s("{a, b}");
    s.remove("z");
    s.remove(Set("{x}"));
    CHECK_EQUAL(2, s.cardinality());
}

// 16. Тест оператора принадлежности [] для строк
TEST(TestBracketOperatorAtoms) {
    Set s("{cat, dog}");
    CHECK(s["cat"]);
    CHECK(s[string("dog")]);
    CHECK(!s["bird"]);
    CHECK(!s[""]);
}

// 17. Тест оператора принадлежности [] для подмножеств
TEST(TestBracketOperatorSubsets) {
    Set s("{a, {b, c}}");
    Set sub("{c, b}");
    CHECK(s[sub]);
    CHECK(!s[Set("{a}")]);
}

// 18. Тест объединения двух множеств (+)
TEST(TestUnionOperator) {
    Set s1("{a, b, {x}}");
    Set s2("{b, c, {x}, {y}}");
    Set res = s1 + s2;
    CHECK_EQUAL(5, res.cardinality());
    CHECK(res["a"]);
    CHECK(res["b"]);
    CHECK(res["c"]);
    CHECK(res["{x}"]);
    CHECK(res["{y}"]);
}

// 19. Тест объединения с присваиванием (+=)
TEST(TestUnionAssignmentOperator) {
    Set s1("{a}");
    Set s2("{b}");
    s1 += s2;
    CHECK_EQUAL(2, s1.cardinality());
    CHECK(s1["a"]);
    CHECK(s1["b"]);
}

// 20. Тест объединения с пустым множеством
TEST(TestUnionWithEmptySet) {
    Set s1("{a, b}");
    Set emptySet;
    CHECK((s1 + emptySet) == s1);
}

// 21. Тест пересечения двух множеств (*)
TEST(TestIntersectionOperator) {
    Set s1("{a, b, {1, 2}}");
    Set s2("{b, c, {2, 1}}");
    Set res = s1 * s2;
    CHECK_EQUAL(2, res.cardinality());
    CHECK(res["b"]);
    CHECK(res["{1, 2}"]);
    CHECK(!res["a"]);
}

// 22. Тест пересечения с присваиванием (*=)
TEST(TestIntersectionAssignmentOperator) {
    Set s1("{a, b, c}");
    Set s2("{b, d}");
    s1 *= s2;
    CHECK_EQUAL(1, s1.cardinality());
    CHECK(s1["b"]);
}

// 23. Тест пересечения непересекающихся множеств
TEST(TestDisjointIntersection) {
    Set s1("{a, b}");
    Set s2("{c, d}");
    Set res = s1 * s2;
    CHECK(res.isEmpty());
}

// 24. Тест разности двух множеств (-)
TEST(TestDifferenceOperator) {
    Set s1("{a, b, {c}}");
    Set s2("{b, {c}, d}");
    Set res = s1 - s2;
    CHECK_EQUAL(1, res.cardinality());
    CHECK(res["a"]);
    CHECK(!res["b"]);
}

// 25. Тест разности с присваиванием (-=)
TEST(TestDifferenceAssignmentOperator) {
    Set s1("{1, 2, 3}");
    Set s2("{2}");
    s1 -= s2;
    CHECK_EQUAL(2, s1.cardinality());
    CHECK(s1["1"]);
    CHECK(s1["3"]);
}

// 26. Тест вычитания множества из самого себя (A - A = {})
TEST(TestDifferenceSelfIsEmpty) {
    Set s("{a, b, {c}}");
    Set res = s - s;
    CHECK(res.isEmpty());
}

// 27. Тест булеана пустого множества P({}) = {{}}
TEST(TestBooleanOfEmptySet) {
    Set emptySet;
    Set b = emptySet.boolean();
    CHECK_EQUAL(1, b.cardinality());
    CHECK(b[emptySet]);
}

// 28. Тест булеана множества из 2 элементов (мощность 2^2 = 4)
TEST(TestBooleanOfTwoElements) {
    Set s("{a, b}");
    Set b = s.boolean();
    CHECK_EQUAL(4, b.cardinality());
    CHECK(b["{}"]);
    CHECK(b["{a}"]);
    CHECK(b["{b}"]);
    CHECK(b["{a, b}"]);
}

// 29. Тест булеана множества с вложенным множеством (мощность 2^3 = 8)
TEST(TestBooleanOfThreeElements) {
    Set s("{a, b, {c}}");
    Set b = s.boolean();
    CHECK_EQUAL(8, b.cardinality());
    CHECK(b["{}"]);
    CHECK(b["{{c}}"]);
    CHECK(b["{a, b, {c}}"]);
}

// 30. Тест операторов равенства (==) и неравенства (!=)
TEST(TestEqualityAndInequality) {
    Set s1("{a, b}");
    Set s2("{b, a}");
    Set s3("{a, c}");
    CHECK(s1 == s2);
    CHECK(s1 != s3);
}

// 31. Тест потокового вывода (<<) и ввода (>>)
TEST(TestStreamOperators) {
    Set sOut("{a, b, {c, d}}");
    stringstream ss;
    ss << sOut;

    Set sIn;
    ss >> sIn;
    CHECK(sOut == sIn);
}

// 32. Тест метода toString
TEST(TestToString) {
    Set s("{a, b}");
    string str1 = s.toString();
    string str2 = s.toString();
    CHECK_EQUAL(str1, str2);
    s.add("c");
    string str3 = s.toString();
    CHECK(str1 != str3);
}

// 33. Тест обработки пустых строк и пробелов
TEST(TestEmptyStringHandling) {
    Set s("   ");
    CHECK(s.isEmpty());
    s.add("");
    s.add("   ");
    s.remove("");
    CHECK(s.isEmpty());
    CHECK(!s[""]);
}

int main() {
    setlocale(LC_ALL, "Russian");
    return UnitTest::RunAllTests();
}