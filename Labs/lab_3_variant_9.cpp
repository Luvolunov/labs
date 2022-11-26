#include <tgmath.h>
#include <stdio.h>
#define PI 3.14159265
// Класс координат вершины, который просто содержит в себе x и y
class Coords {
public:
    Coords(int x, int y);
    int x;
    int y;
};

Coords::Coords(int cX, int cY) {
    x = cX;
    y = cY;
};
// Класс треугольника с методами и перегрузкой операторов
class Triangle {
public:
    Triangle(Coords *first, Coords *second, Coords *third);
    Coords *firstApex;
    Coords *secondApex;
    Coords *thirdApex;
    bool operator== (Triangle triangle);
    Triangle operator*= (int size);
    float getPerimeter();
    float getArea();
    float getSmallestAngle();
};

Triangle::Triangle(Coords *first, Coords *second, Coords *third) {
    firstApex = first;
    secondApex = second;
    thirdApex = third;
};
// Через присваивание *= делается масштабирование треугольника - просто координаты умножаются на переданный размер
Triangle Triangle::operator*= (int size) {
    firstApex->x *= size;
    firstApex->y *= size;
    secondApex->x *= size;
    secondApex->y *= size;
    thirdApex->x *= size;
    thirdApex->y *= size;
    return *this;
}
// Функция, которая вычисляет длину вектора по координатам точек
float getSideSize(Coords firstApex, Coords secondApex) {
    return sqrt(pow(firstApex.x - secondApex.x, 2) + pow(firstApex.y - secondApex.y, 2));
}
// Логическое сравнивание через сравнение длин сторон треугольников
bool Triangle::operator== (Triangle triangle) {
    float firstTriangleSide1 = getSideSize(*firstApex, *secondApex);
    float firstTriangleSide2 = getSideSize(*secondApex, *thirdApex);
    float firstTriangleSide3 = getSideSize(*thirdApex, *firstApex);
    
    float secondTriangleSide1 = getSideSize(*triangle.firstApex, *triangle.secondApex);
    float secondTriangleSide2 = getSideSize(*triangle.secondApex, *triangle.thirdApex);
    float secondTriangleSide3 = getSideSize(*triangle.thirdApex, *triangle.firstApex);
    if (firstTriangleSide1 != secondTriangleSide1
        && firstTriangleSide1 != secondTriangleSide2
        && firstTriangleSide1 != secondTriangleSide3) {
        return false;
    }
    if (firstTriangleSide2 != secondTriangleSide1
        && firstTriangleSide2 != secondTriangleSide2
        && firstTriangleSide2 != secondTriangleSide3) {
        return false;
    }
    if (firstTriangleSide3 != secondTriangleSide1
        && firstTriangleSide3 != secondTriangleSide2
        && firstTriangleSide3 != secondTriangleSide3) {
        return false;
    }
    return true;
};
// Метод для вычисления периметра треугольника
float Triangle::getPerimeter() {
    float triangleSide1 = getSideSize(*firstApex, *secondApex);
    float triangleSide2 = getSideSize(*secondApex, *thirdApex);
    float triangleSide3 = getSideSize(*thirdApex, *firstApex);
    return triangleSide1 + triangleSide2 + triangleSide3;
}
// Метод для вычисления площади треугольника
float Triangle::getArea() {
    float triangleSide1 = getSideSize(*firstApex, *secondApex);
    float triangleSide2 = getSideSize(*secondApex, *thirdApex);
    float triangleSide3 = getSideSize(*thirdApex, *firstApex);
    
    float halfPerimeter = getPerimeter() / 2;
    return sqrt(
            halfPerimeter *
            (halfPerimeter - triangleSide1) *
            (halfPerimeter - triangleSide2) *
            (halfPerimeter - triangleSide3)
          );
}
// Метод для нахождения наименьшего угла
float Triangle::getSmallestAngle() {
    float a = getSideSize(*firstApex, *secondApex);
    float b = getSideSize(*secondApex, *thirdApex);
    float c = getSideSize(*thirdApex, *firstApex);
    float cosA = (pow(a, 2) + pow(c, 2) - pow(b, 2)) / (2 * a * c);
    float cosB = (pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b);
    float cosC = (pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2 * b * c);
    float angleA = acos(cosA) * 180 / PI;
    float angleB = acos(cosB) * 180 / PI;
    float angleC = acos(cosC) * 180 / PI;
    
    if (angleA < angleB && angleA < angleC) return angleA;
    if (angleB < angleA && angleB < angleC) return angleB;
    return angleC;
}


int main(int argc, char *argv[]) {
    Coords firstApex = { 0, 0 };
    Coords secondApex = { 0, 3 };
    Coords thirdApex = { 4, 0 };
    Triangle triangle1 = { &firstApex, &secondApex, &thirdApex };
    
    Coords firstApex1 = { 0, 0 };
    Coords secondApex1 = { 0, 3 };
    Coords thirdApex1 = { 4, 0 };
    Triangle triangle2 = { &secondApex1, &thirdApex1, &firstApex1 };
    
    printf("%f", triangle1.getSmallestAngle());
    return 0;
}
