#include "include/Sort.h"
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList){
    shapeList->sort(sortByIncreasingPerimeterCompare);
}
bool Sort::sortByIncreasingPerimeterCompare(const Shape *s1, const Shape *s2){
    return s1->perimeter() < s2->perimeter();
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList){
    shapeList->sort(sortByDecreasingPerimeterCompare);
}
bool Sort::sortByDecreasingPerimeterCompare(const Shape *s1, const Shape *s2){
    return s1->perimeter() > s2->perimeter();
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList){
    shapeList->sort(sortByIncreasingAreaCompare);
}
bool Sort::sortByIncreasingAreaCompare(const Shape *s1, const Shape *s2){
    return s1->area() < s2->area();
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList){
    shapeList->sort(sortByDecreasingAreaCompare);
}
bool Sort::sortByDecreasingAreaCompare(const Shape *s1, const Shape *s2){
    return s1->area() > s2->area();
}

void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList){
    shapeList->sort(sortByIncreasingCompactnessCompare);
}
bool Sort::sortByIncreasingCompactnessCompare(const Shape *s1, const Shape *s2){
    return (s1->area())/(s1->perimeter()) < (s1->area())/(s1->perimeter());
}
