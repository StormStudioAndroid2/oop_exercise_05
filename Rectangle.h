#pragma once
#include "Point.h"
#include <vector>
template <typename T>

class Rectangle {
    public:
    Point<T> points[4];
    Rectangle<T>() = default;
    Rectangle(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);
    double getSquare() const;
    Point<T> getCenter() const;
    void scan(std::istream &is);
    void print(std::ostream& os) const;
}; 


template <typename T>
Rectangle<T>::Rectangle(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4) {
       if (IsRectangle(p1,p2,p3,p4)) {

    } else if (IsRectangle(p2, p3, p1, p4)) {
        std::swap(p2, p1); std::swap(p3,p2);
    } else if (IsRectangle(p3, p1, p2, p4)) {
        std::swap(p3, p1); std::swap(p3,p2);
    } else {
        throw std::logic_error("not rectangle");
    }
    this->points[0] = p1;
    this->points[1] = p2;
    this->points[2] = p3;
    this->points[3] = p4; 
    }

    template <typename T>
double Rectangle<T>::getSquare() const {
    
	return length(this->points[0],this->points[1])*length(this->points[0],this->points[3]);
}
template <typename T>
void Rectangle<T>::print(std::ostream& os) const {
    os << "Rectangle p1: ";
    for (int i = 0; i < 4; ++i) {
        os << this->points[i] << "p" << i+1 <<" ";
    }
    os << std::endl;
}
template <typename T>
void Rectangle<T>::scan(std::istream &is) {
    Point<T> p1,p2,p3,p4;
    is >> p1 >> p2 >> p3 >> p4;
    *this = Rectangle(p1,p2,p3,p4);
}

template <typename T>
Point<T> Rectangle<T>::getCenter() const {

    Point<T> p;
    p.x = 0;
    p.y = 0;
    for (size_t i = 0; i < 4; ++i) {
        p = p+(points[i]/4);
    }
    return p;
}

