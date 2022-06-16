#include <stdio.h>
#include <math.h>
#include "Vector.h"


// default constructor
Vector::Vector()
{ // constructor
    x = y = z = 0.0f;
} // constructor

// copy constructor
Vector::Vector(GLfloat xx, GLfloat yy, GLfloat zz)
{ // constructor
    x = xx;
    y = yy;
    z = zz;
} // constructor

// Copy another Vector & return self
Vector &Vector::operator =(Vector vector)
{ // assignment
    for (int i = 0; i < 3; i++)
        (*this)[i] = vector[i];
    return (*this);
} // assignment

// Scalar right-multiplication
Vector Vector::operator * (GLfloat scaleFactor)
{ // Scalar right-multiplication
    Vector result;
    for (int i = 0; i < 3; i++)
        result[i] = (*this)[i] * scaleFactor;
    return result;
} // Scalar right-multiplication

// Scalar right-division
Vector Vector::operator / (GLfloat scaleFactor)
{ // Scalar right-division
    Vector result;
    for (int i = 0; i < 3; i++)
        result[i] = (*this)[i] / scaleFactor;
    return result;
} // Scalar right-division

// scalar left-multiplication
Vector operator *(GLfloat scaleFactor, Vector vector)
{ // scalar left-multiplication
    Vector result;
    for (int i = 0; i < 3; i++)
        result[i] = scaleFactor * vector[i];
    return result;
} // scalar left-multiplication

// Computes the length (sqrt of sum of squares)
GLfloat Vector::length()
{ // Length()
    return sqrt(dot(*this));
} // Length()

// Return the unit (normalized) vector
Vector Vector::norm()
{ // Normalize()
    Vector result = (*this) / length();
    return result;
} // Normalize()

// Add a vector to a vector to get another vector
// Does so in Cartesian space, but leaves w-coordinate the same
Vector Vector::operator +(Vector vector)
{ // addition
    Vector result;
    for (int i = 0; i < 3; i++)
        result[i] =(*this)[i] + vector[i];
    return result;
} // addition

// Add a point to a vector to get another point
// Does so in Cartesian space, but leaves w-coordinate the same
Point Vector::operator +(Point point)
{ // addition
    Point result;
    for (int i = 0; i < 3; i++)
        result[i] =(*this)[i]*point[3] + point[i];
    result[3] = point[3];
    return result;
} // addition

// Negation (unary minus)
Vector Vector::operator -()
{ // unary minus
    return (*this) * -1;
} // unary minus

// Subtraction (returns a vector)
Vector Vector::operator - (Vector vector)
{ // minus
    Vector result;
    for (int i = 0; i < 3; i++)
        result[i] =(*this)[i] - vector[i];
    return result;
} // minus

// Compute the cross-product (this x vector)
Vector Vector::cross(Vector vector)
{ // Cross()
    Vector result;
    result.x = y * vector.z - z * vector.y;
    result.y = z * vector.x - x * vector.z;
    result.z = x * vector.y - y * vector.x;
    return result;
} // Cross()

// Dot product computes (this . vector)
GLfloat Vector::dot(Vector vector)
{ // Dot()
    return (x*vector.x + y*vector.y +
            z*vector.z);
} // Dot()

GLfloat &Vector::operator[](int i) {
        switch(i) {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        default: return z;
        }
    }

