/*
 *  arcBall.h
 *  marchingCubes
 *
 *  Created by Owen Grogan on 06/05/2010.
 *  Copyright 2010 School of Computer Science and Informatics. All rights reserved.
 *
 */


#ifndef ARCBALL_H
#define ARCBALL_H

#include "Vector.h"
#include"quat.h"

class arcBall{
public:
	arcBall();
	~arcBall();
    Vector screenToPoint(int x, int y, int windowWidth, int windowHeight);
	void startBall(int x, int y, int windowWidth, int windowHeight);
	void endBall(int x, int y, int windowWidth, int windowHeight);
	void updateBall(int x, int y, int windowWidth, int windowHeight);
	void getMatrix(float * matrix);
	int min(int,int);
	void reset();
private:
	quat currQuat;
    Vector v0;
};
#endif
