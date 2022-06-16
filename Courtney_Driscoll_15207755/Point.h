#ifndef Point_H
#define Point_H

// forward declaration for mutually recursive inclusion
class Point;

#include <GL/glu.h>
#include <stdio.h>
#include "Vector.h"

// Assume that we carry EVERYTHING in explicit homogeneous coordinates
class Point
    { // class Point
    public:
    GLfloat x,y,z,w;

    // default constructor
    Point();

    //constructor
    Point(GLfloat x, GLfloat y, GLfloat z);

    // copy constructor
    Point(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

    // Copy another Point & return self
    Point &operator = (Point point);

    // Scalar right-multiplication
    Point operator * (GLfloat scaleFactor);

    // Scalar right-division
    Point operator / (GLfloat scaleFactor);

    // Add a vector to a point to get another point
    // Does so in Cartesian space, but leaves w-coordinate the same
    Point operator +(Vector vector);

    // Negation (unary minus)
    Point operator -();

    // Subtract a vector from a point
    Point operator -(Vector vector);

    // Subtraction (returns a vector)
    Vector operator - (Point point);

    // Divide through by homogeneous coordinate (if a point)
    Point DeHomogenize();

    // Returns the component from an index
    float &operator[](int);

    }; // class Point

// Scalar left-multiplication
Point operator * (Point point, GLfloat scaleFactor);

#endif
