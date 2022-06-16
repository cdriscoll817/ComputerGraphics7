#include <stdio.h>
#include <math.h>
#include "Point.h"

// default constructor
Point::Point()
    { // constructor
    x = y = z = 0.0f;
    w = 1.0f;
    } // constructor

// Constructor
Point::Point(GLfloat xx, GLfloat yy, GLfloat zz)
    { // constructor
    x = xx;
    y = yy;
    z = zz;
    w = 1.0;
    } // constructor

// copy constructor
Point::Point(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat ww)
    { // constructor
    x = xx;
    y = yy;
    z = zz;
    w = ww;
    } // constructor

// Copy another Point & return self
Point &Point::operator = (Point point)
    { // operator =
    int i;
    for (i = 0; i < 4; i++)
        (*this)[i] = point[i];
    return (*this);
    } // operator =

// Scalar right-multiplication
Point Point::operator * (GLfloat scaleFactor)
    { // operator *
    Point result;
    int i;
    for (i = 0; i < 4; i++)
        result[i] = (*this)[i] * scaleFactor;
    return result;
    } // operator *


// Scalar right-division
Point Point::operator / (GLfloat scaleFactor)
    { // operator /
    Point result;
    int i;
    for (i = 0; i < 4; i++)
        result[i] = (*this)[i] / scaleFactor;
    return result;
    } // operator /

// Add a vector to a point to get another point
// Does so in Cartesian space, but leaves w-coordinate the same
Point Point::operator +(Vector vector)
    { // operator +
    Point result;
    int i;
    // add the vector, multiplied by w
    for (i = 0; i < 4; i++)
        result[i] = (*this)[i] + vector[i] * w;
    return result;
    } // operator +

// Negation (unary minus)
Point Point::operator -()
    { // operator -
    Point result;
    int i;
    // note that the w coordinate is unchanged
    // either that, or we could flip w instead
    for (i = 0; i < 3; i++)
        result[i] = -(*this)[i];
    return result;
    } // operator -

// Subtract a vector from a point
Point Point::operator -(Vector vector)
    { // operator -
    Point result;
    int i;
    // subtract the vector, multiplied by w
    for (i = 0; i < 4; i++)
        result[i] = (*this)[i] - vector[i] * w;
    return result;
    } // operator -

// Subtraction (returns a vector)
Vector Point::operator - (Point point)
    { // operator -
    Vector result;
    int i;
    for (i = 0; i < 3; i++)
        result[i] = (*this)[i] / w - point[i] / point.w;
    return result;
    } // operator -

// Divide through by homogeneous coordinate (if a point)
Point Point::DeHomogenize()
    { // DeHomogenize()
    Point result;
    int i;
    for (i = 0; i < 3; i++)
        result[i] = (*this)[i] / w;
    w = 0.0;
    return result;
    } // DeHomogenize()

GLfloat &Point::operator[](int i) {
    switch(i) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
    default: return w;
    }
}

// Scalar left-multiplication
Point operator * (Point point, GLfloat scaleFactor)
    { // operator *
    Point result;
    int i;
    for (i = 0; i < 4; i++)
        result[i] = point[i] * scaleFactor;
    return result;
    } // operator *
