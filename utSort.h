#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
#include "include/Shapes.h"
#include <gtest/gtest.h>
#include <iostream>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

const double _epsilon = 0.01;

TEST (Sort, sortByIncreasingPerimeter) {
    //Rectangle r1(1, 1, 1, 1);
    //Rectangle r2(1, 1, 2, 2);
    //Rectangle r3(1, 1, 3, 3);
    Rectangle r1(0, 0, 1, 1);
    Circle c1(0, 0, 1);
    //Triangle t1(0, 0, 4, 0, 0, 3);
    vertex v1,v2,v3;
    v1.x = 0;
    v1.y = 0;
    v2.x = 4;
    v2.y = 0;
    v3.x = 0;
    v3.y = 3;
    Triangle t1(v1,v2,v3,"");

    list<Shape*> *l1 = new list<Shape*>();

    l1->push_back(&r1);
    l1->push_back(&c1);
    l1->push_back(&t1);
    Sort::sortByIncreasingPerimeter(l1);

    list<Shape *>::iterator it = l1->begin();
    ASSERT_NEAR(4, (*it)->perimeter(), _epsilon);
    it++;
    ASSERT_NEAR(6.28, (*it)->perimeter(), _epsilon);
    it++;
    ASSERT_NEAR(12, (*it)->perimeter(), _epsilon);
}

TEST (Sort, sortByDecreasingPerimeter) {
    Rectangle r1(0, 0, 1, 1);
    Circle c1(0, 0, 1);
    vertex v1,v2,v3;
    v1.x = 0;
    v1.y = 0;
    v2.x = 4;
    v2.y = 0;
    v3.x = 0;
    v3.y = 3;
    Triangle t1(v1,v2,v3,"");

    list<Shape*> *l1 = new list<Shape*>();

    l1->push_back(&r1);
    l1->push_back(&c1);
    l1->push_back(&t1);
    Sort::sortByDecreasingPerimeter(l1);

    list<Shape *>::iterator it = l1->begin();
    ASSERT_NEAR(12, (*it)->perimeter(), _epsilon);
    it++;
    ASSERT_NEAR(6.28, (*it)->perimeter(), _epsilon);
    it++;
    ASSERT_NEAR(4, (*it)->perimeter(), _epsilon);
}

TEST (Sort, sortByIncreasingArea) {
    Rectangle r1(0, 0, 1, 1);
    Circle c1(0, 0, 1);

    vertex v1,v2,v3;
    v1.x = 0;
    v1.y = 0;
    v2.x = 4;
    v2.y = 0;
    v3.x = 0;
    v3.y = 3;
    Triangle t1(v1,v2,v3,"");

    list<Shape*> *l1 = new list<Shape*>();

    l1->push_back(&r1);
    l1->push_back(&c1);
    l1->push_back(&t1);
    Sort::sortByIncreasingArea(l1);

    list<Shape *>::iterator it = l1->begin();
    ASSERT_NEAR(1, (*it)->area(), _epsilon);
    it++;
    ASSERT_NEAR(3.14, (*it)->area(), _epsilon);
    it++;
    ASSERT_NEAR(6, (*it)->area(), _epsilon);
}

TEST (Sort, sortByDecreasingArea) {
    Rectangle r1(0, 0, 1, 1);
    Circle c1(0, 0, 1);

    vertex v1,v2,v3;
    v1.x = 0;
    v1.y = 0;
    v2.x = 4;
    v2.y = 0;
    v3.x = 0;
    v3.y = 3;
    Triangle t1(v1,v2,v3,"");

    list<Shape*> *l1 = new list<Shape*>();

    l1->push_back(&r1);
    l1->push_back(&c1);
    l1->push_back(&t1);
    Sort::sortByDecreasingArea(l1);

    list<Shape *>::iterator it = l1->begin();
    ASSERT_NEAR(6, (*it)->area(), _epsilon);
    it++;
    ASSERT_NEAR(3.14, (*it)->area(), _epsilon);
    it++;
    ASSERT_NEAR(1, (*it)->area(), _epsilon);
}

TEST (Sort, sortByIncreasingCompactness) {
    Rectangle r1(0, 0, 1, 1);
    Circle c1(0, 0, 1);

    vertex v1,v2,v3;
    v1.x = 0;
    v1.y = 0;
    v2.x = 4;
    v2.y = 0;
    v3.x = 0;
    v3.y = 3;
    Triangle t1(v1,v2,v3,"");

    list<Shape*> *l1 = new list<Shape*>();

    l1->push_back(&r1);
    l1->push_back(&c1);
    l1->push_back(&t1);
    Sort::sortByIncreasingArea(l1);
    Sort::sortByIncreasingPerimeter(l1);

    list<Shape *>::iterator it = l1->begin();
    ASSERT_NEAR(0.25, (*it)->area()/(*it)->perimeter(), _epsilon);
    it++;
    ASSERT_NEAR(0.5, (*it)->area()/(*it)->perimeter(), _epsilon);
    it++;
    ASSERT_NEAR(0.5, (*it)->area()/(*it)->perimeter(), _epsilon);
}

#endif
