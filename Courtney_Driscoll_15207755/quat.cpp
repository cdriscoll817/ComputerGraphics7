/*
 *  quat.cpp
 *  marchingCubes
 *
 *  Created by Owen Grogan on 06/05/2010.
 *  Copyright 2010 School of Computer Science and Informatics. All rights reserved.
 *
 */

#include "quat.h"
#include<iostream>
#include<cmath>

quat::quat():real(1.0f),imag(Vector(0,0,0)){
}
quat::~quat(){
}
quat::quat(float* matrix){	
	real = std::sqrt(1.0+matrix[0]+matrix[5]+matrix[10])/2.0;
	float w4 = 4.0*real;
    imag=Vector((matrix[6] - matrix[9])/w4,
				 (matrix[8] - matrix[2])/w4,
				 (matrix[1] - matrix[4])/w4);
}
quat::quat(float w,float x, float y, float z){
    imag.x = x,imag.y = y,imag.z = z,real = w;
}
quat::quat(Vector v, float w){
	imag = v ,real = w;
}
quat::quat(float w, Vector v){
	imag = v,real = w;
}
Vector quat::getImag(){
	return imag;
}

float quat::getReal(){
	return real; 
}
quat quat::mult(quat q){
    return quat(((real*q.getReal())-(imag.dot(q.getImag()))),
                ((real*q.getImag())+(q.getReal()*imag)+(imag.cross(q.getImag()))));
}

quat quat::conj()
{	
    return quat(real,-imag.x,-imag.y,-imag.z);
}

float quat::sumSquare(){
    return (real*real+imag.x*imag.x+
            imag.y*imag.y+imag.z*imag.z);
}

quat quat::inverse(){
	return quat(real/sumSquare(),conj().getImag()/sumSquare());
}

void quat::toMatrix(float* matrix){
	float treal = real;
    matrix[0] = 1.0f-((2.0f*imag.y*imag.y)+(2.0f*imag.z*imag.z));
    matrix[4] = 2.0f*((imag.x*imag.y)-(imag.z*treal));
    matrix[8] = 2.0f*((imag.x*imag.z)+(imag.y*treal));
					  
    matrix[1] = 2.0f*((imag.x*imag.y)+(imag.z*treal));
    matrix[5] = 1.0f-((2.0f*imag.x*imag.x)+(2.0f*imag.z*imag.z));
    matrix[9] = 2.0f*((imag.y*imag.z)-(imag.x*treal));
					  
    matrix[2] = 2.0f*((imag.x*imag.z)-(imag.y*treal));
    matrix[6] = 2.0f*((imag.y*imag.z)+(imag.x*treal));
    matrix[10] = 1.0f-((2.0f*imag.y*imag.y)+(2.0f*imag.x*imag.x));
}
