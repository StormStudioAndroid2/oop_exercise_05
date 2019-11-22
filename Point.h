#pragma once

#include <numeric>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

template <typename T>
struct Point {
    T x;
    T y;
};
template <typename T>
Point<T> operator+(Point<T> left, Point<T> right) {
     Point<T> p;
    p.x = left.x+right.x;
    p.y = left.y+right.y;
        return p;

}

template <typename T>
 Point<T> operator+( Point<T> left, int right) {
     Point<T> p;
    p.x = left.x+right;
    p.y = left.y+right;
        return p;

}

template <typename T>
 Point<T> operator-( Point<T> left,  Point<T> right) {
     Point<T> p;
    p.x = left.x-right.x;
    p.y = left.y-right.y;
        return p;

}

template <typename T>
 Point<T> operator-(Point<T> left, double right) {
     Point<T> p;
    p.x = left.x-right;
    p.y = left.y-right;
        return p;

}

template <typename T>
 Point<T> operator/( Point<T> left, double right) {
    Point<T> p;
    p.x = left.x/right;
    p.y = left.y/right;
        return p;

}

template <typename T>
 Point<T> operator*(Point<T> left, double right) {
     Point<T> p;
    p.x = left.x*right;
    p.y = left.y*right;
    return p;
}
template <typename T>
double length( Point<T> left,  Point<T> right) {
    return sqrt((left.x-right.x)*(left.x-right.x)+(left.y-right.y)*(left.y-right.y));
}
template <typename T>
bool IsOrthogonal( Point<T> a,  Point<T> b,  Point<T> c)
{
    return (b.x - a.x) * (b.x - c.x) + (b.y - a.y) * (b.y - c.y) == 0;
}
template <typename T>

bool IsParallel( Point<T> a,  Point<T> b,  Point<T> c,  Point<T> d)
{
     Point<T> a1 = a-b; 
     Point<T> a2 = c-d;  
    return ((a1.x*a2.x+a1.y*a2.y)/(length(a,b)*length(c,d))<=-1 || (a1.x*a2.x+a1.y*a2.y)/(length(a,b)*length(c,d))>=1);
}

template <typename T>
int IsRectangle( Point<T> a,  Point<T> b,  Point<T> c,  Point<T> d)
{
    return
        IsOrthogonal(a, b, c) &&
        IsOrthogonal(b, c, d) &&
        IsOrthogonal(c, d, a);
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Point<T>& p) {
    return os << p.x << " " << p.y;
}

template <typename T>
std::istream& operator >> (std::istream& is, Point<T>& p) {
    return is >> p.x >> p.y;
}