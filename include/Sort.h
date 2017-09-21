#include <list>
#include "Shapes.h"
#include "Media.h"

class Sort{

public :
  static void sortByIncreasingPerimeter(std::list<Shape *> * shapeList);
  static void sortByDecreasingPerimeter(std::list<Shape *> * shapeList);
  static void sortByIncreasingArea(std::list<Shape *> * shapeList);
  static void sortByDecreasingArea(std::list<Shape *> * shapeList);
  static void sortByIncreasingCompactness(std::list<Shape *> * shapeList);
  // Compactness = area/perimeter
  static bool sortByIncreasingPerimeterCompare(const Shape *s1, const Shape *s2);
  static bool sortByDecreasingPerimeterCompare(const Shape *s1, const Shape *s2);
  static bool sortByIncreasingAreaCompare(const Shape *s1, const Shape *s2);
  static bool sortByDecreasingAreaCompare(const Shape *s1, const Shape *s2);
  static bool sortByIncreasingCompactnessCompare(const Shape *s1, const Shape *s2);
};
