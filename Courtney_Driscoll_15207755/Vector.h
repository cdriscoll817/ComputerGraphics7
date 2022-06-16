#ifndef VECTOR_H
#define VECTOR_H

// forward declaration for mutually recursive inclusion
class Vector;

#include <GL/glu.h>
#include <stdio.h>
#include "Point.h"

class Vector
    { // class Vector
    public:
    GLfloat x, y, z;

    // default constructor
    Vector();

    // copy constructor
    Vector(GLfloat x, GLfloat y, GLfloat z);

    // Copy another Vector & return self
    Vector &operator =(Vector vector);

    // Scalar right-multiplication
    Vector operator * (GLfloat scaleFactor);

    // Scalar right-division
    Vector operator / (GLfloat scaleFactor);

    // Add a point to a vector to get another point
    // Does so in Cartesian space, but leaves w-coordinate the same
    Point operator +(Point point);

    // Add a vector to a vector to get another vector
    // Does so in Cartesian space, but leaves w-coordinate the same
    Vector operator +(Vector vector);

    // Negation (unary minus)
    Vector operator -();

    // Subtraction (returns a vector)
    Vector operator - (Vector vector);

    // Computes the length (sqrt of sum of squares)
    GLfloat length();

    // Return the unit (normalized) vector
    Vector norm();

    // Compute the cross-product (this x vector)
    Vector cross(Vector other);

    // Dot product computes (this . vector)
    GLfloat dot(Vector other);

    // Returns the component from an index
    float &operator[](int);
    }; // class Vector

// scalar left-multiplication
Vector operator *(GLfloat scaleFactor, Vector vector);

#endif
