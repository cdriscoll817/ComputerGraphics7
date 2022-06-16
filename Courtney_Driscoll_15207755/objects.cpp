#include <cmath>

#include "objects.h"
#include "Point.h"
#include "Vector.h"

// Colour Palete
GLfloat black_colour[]	= { 0.0, 0.0, 0.0, 1.0 };
GLfloat white_colour[]	= { 1.0, 1.0, 1.0, 1.0 };
GLfloat grey_colour[]	= { 0.9, 0.9, 0.9, 1.0 };

const double pi = 3.14159265;

/*
 *  Implement all the subsequent functions routines for drawing geometric primitives
 *  platonic solids
 */
void drawTetrahedron(){
    Point vertices[4] = { Point( -1.0, -1.0, -1.0 ),
        Point( -1.0,  1.0,  1.0 ),
        Point(  1.0, -1.0,  1.0 ),
        Point(  1.0,  1.0, -1.0 ) };
    
    int faces[4][3] = { { 0,  2,  1},
        { 1,  3,  0},
        { 2,  3,  1},
        { 3,  2,  0}
    };
    
    glBegin(GL_TRIANGLES);
	for (int face = 0; face < 4; face++){ // per face
	    Vector v = vertices[faces[face][1]] - vertices[faces[face][0]];
	    Vector w = vertices[faces[face][2]] - vertices[faces[face][0]];
	    Vector normal = v.cross(w).norm();
	    glNormal3f(normal.x, normal.y, normal.z);
	    glVertex3f(vertices[faces[face][0]].x, vertices[faces[face][0]].y, vertices[faces[face][0]].z);
	    glVertex3f(vertices[faces[face][1]].x, vertices[faces[face][1]].y, vertices[faces[face][1]].z);
	    glVertex3f(vertices[faces[face][2]].x, vertices[faces[face][2]].y, vertices[faces[face][2]].z);
    } // per face
    glEnd();
}

void drawCube(){
    
    /**
     TO DO
     */

    Point vertices[8] = {Point(-1.0,-1.0,-1.0),
                         Point(-1.0,-1.0,1.0),
                         Point(-1.0,1.0,-1.0),
                         Point(-1.0,1.0,1.0),
                         Point(1.0,-1.0,-1.0),
                         Point(1.0,-1.0,1.0),
                         Point(1.0,1.0,-1.0),
                         Point(1.0,1.0,1.0)};
    int faces[12][3] = {{0,1,3},
                        {0,3,2},
                        {0,2,4},
                        {2,6,4},
                        {0,4,1},
                        {1,4,5},
                        {1,5,7},
                        {1,7,3},
                        {5,4,6},
                        {5,6,7},
                        {2,3,7},
                        {2,7,6}};
    glBegin(GL_TRIANGLES);
    for (int face = 0; face < 12; face++){ // per face
        Vector v = vertices[faces[face][1]] - vertices[faces[face][0]];
        Vector w = vertices[faces[face][2]] - vertices[faces[face][0]];
        Vector normal = v.cross(w).norm();
        glNormal3f(normal.x, normal.y, normal.z);
        glVertex3f(vertices[faces[face][0]].x, vertices[faces[face][0]].y, vertices[faces[face][0]].z);
        glVertex3f(vertices[faces[face][1]].x, vertices[faces[face][1]].y, vertices[faces[face][1]].z);
        glVertex3f(vertices[faces[face][2]].x, vertices[faces[face][2]].y, vertices[faces[face][2]].z);
    } // per face
    glEnd();
}

void drawOctahedron(){
    
    Point vertices[6] = { Point( -1.0,  0.0,  0.0 ),
        Point(  0.0, -1.0,  0.0 ),
        Point(  0.0,  0.0, -1.0 ),
        Point(  1.0,  0.0,  0.0 ),
        Point(  0.0,  1.0,  0.0 ),
        Point(  0.0,  0.0,  1.0 )
    };
    
    int faces[8][3] = { { 3,  4,  5 },
        { 4,  0,  5 },
        { 0,  1,  5 },
        { 1,  3,  5 },
        { 0,  4,  2 },
        { 4,  3,  2 },
        { 3,  1,  2 },
        { 1,  0,  2 }
    };
    
    glBegin(GL_TRIANGLES);
	for (int face = 0; face < 8; face++){ // per face
	    Vector v = vertices[faces[face][1]] - vertices[faces[face][0]];
	    Vector w = vertices[faces[face][2]] - vertices[faces[face][0]];
	    Vector normal = v.cross(w).norm();
	    glNormal3f(normal.x, normal.y, normal.z);
	    glVertex3f(vertices[faces[face][0]].x, vertices[faces[face][0]].y, vertices[faces[face][0]].z);
	    glVertex3f(vertices[faces[face][1]].x, vertices[faces[face][1]].y, vertices[faces[face][1]].z);
	    glVertex3f(vertices[faces[face][2]].x, vertices[faces[face][2]].y, vertices[faces[face][2]].z);
	} // per face
    glEnd();
    
}

void drawDodecahedron(){
    glutSolidDodecahedron();
}

void drawIcosahedron(){
    glutSolidIcosahedron();
}


void drawCylinder(float radius, float height, int nSegments){
    
    glBegin(GL_TRIANGLES);
	for(float i = 0.0; i <= nSegments; i+=1.0f){ /* theta loop */
	    float theta     = (2.0f*pi*i)/(float)nSegments;
	    float nextTheta = (2.0f*pi*(i+1.0))/(float)nSegments;
	    
	    float x1 = cos(theta)*radius,     y1 = sin(theta)*radius;
	    float x2 = cos(nextTheta)*radius, y2 = sin(nextTheta)*radius;
	    
	    // first triangle of the panel
	    glNormal3f(x1,y1,0.0f); glVertex3f(x1,y1,0.0f);
	    glNormal3f(x2,y2,1.0f); glVertex3f(x2,y2,height);
	    glNormal3f(x1,y1,1.0f); glVertex3f(x1,y1,height);
	    
	    // second triangle of the panel
	    glNormal3f(x1,y1,0.0f); glVertex3f(x1,y1,0.0f);
	    glNormal3f(x2,y2,0.0f); glVertex3f(x2,y2,0.0f);
	    glNormal3f(x2,y2,1.0f); glVertex3f(x2,y2,height);
	    
	    // for a closed cylinder bottom triangle
	    glNormal3f(0.0f,0.0f,-1.0f); glVertex3f(x1,y1,0.0f);
	    glNormal3f(0.0f,0.0f,-1.0f); glVertex3f(x2,y2,0.0f);
	    glNormal3f(0.0f,0.0f,-1.0f); glVertex3f(0.0f,0.0f,0.0f);
	    
	    // top triangle
	    glNormal3f(0.0f,0.0f,1.0f); glVertex3f(x1,y1,height);
	    glNormal3f(0.0f,0.0f,1.0f); glVertex3f(x2,y2,height);
	    glNormal3f(0.0f,0.0f,1.0f); glVertex3f(0.0f,0.0f,height);
	} /* theta loop */
    
    glEnd();
}

void drawSphere(float radius, int nSegments, int nSlices){
    
    /**
     TO DO
     */

    glBegin(GL_QUADS);
    float theta = (2*M_PI)/(float)nSlices;
    float phi = M_PI/(float)nSegments;

    for( float tempTheta = -M_PI; tempTheta < M_PI; tempTheta += theta){
        for (float tempPhi = -M_PI/2; tempPhi < M_PI/2; tempPhi += phi){

            float x = cos(tempPhi)*cos(tempTheta)*radius;
            float y = cos(tempPhi) * sin(tempTheta) * radius;
            float z = sin(tempPhi) * radius;
            glNormal3f(x,y,z);
            glVertex3f(x,y,z);

            x = cos(tempPhi)*cos(tempTheta + theta)*radius;
            y = cos(tempPhi) * sin(tempTheta + theta) * radius;
            z = sin(tempPhi) * radius;
            glNormal3f(x,y,z);
            glVertex3f(x,y,z);

            x = cos(tempPhi + phi)*cos(tempTheta + theta)*radius;
            y = cos(tempPhi + phi) * sin(tempTheta + theta) * radius;
            z = sin(tempPhi + phi) * radius;
            glNormal3f(x,y,z);
            glVertex3f(x,y,z);

            x = cos(tempPhi + phi)*cos(tempTheta)*radius;
            y = cos(tempPhi + phi) * sin(tempTheta) * radius;
            z = sin(tempPhi + phi) * radius;
            glNormal3f(x,y,z);
            glVertex3f(x,y,z);
            }
        }
    glEnd();

}


void drawAxes(){
    glMatrixMode(GL_MODELVIEW); // switch to modelview
    glPushMatrix();             // push a matrix on the stack

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grey_colour); // set colour
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black_colour);           // but they do emit

    glBegin(GL_LINES); // start drawing lines
	glVertex3f(0.0, 0.0, 0.0); glVertex3f(1.0, 0.0, 0.0); // x-axis
	glVertex3f(0.0, 0.0, 0.0); glVertex3f(0.0, 1.0, 0.0); // y-axis
	glVertex3f(0.0, 0.0, 0.0); glVertex3f(0.0, 0.0, 1.0); // z-axis
    glEnd();

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black_colour); 	//set reflective colour

    glPushMatrix(); // push a matrix on the stack
	glTranslatef(0.0, 0.0, 1.0);      // move to end of z axis
	glutSolidCone(0.02, 0.1, 10, 2);  // draw a solid cone for the z-axis
	glRotatef(90.0, 1.0, 0.0, 0.0);   // rotate to draw in z=0 plane
	glTranslatef(0.1, 0.0, 0.0);      // move away slightly
	glScalef(0.001,0.001,0.001);      // scale down
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Z'); // and draw the letter Z
    glPopMatrix();  // pop matrix off stack

    glPushMatrix(); // push a matrix on the stack
	glTranslatef(0.0, 1.0, 0.0);       // move to end of y axis
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.02, 0.1, 10, 2);  // draw a solid cone for the y-axis
	glRotatef(90.0, 1.0, 0.0, 0.0);   // rotate to draw in y=0 plane
	glTranslatef(0.1, 0.0, 0.0);      // move away slightly
	glScalef(0.001,0.001,0.001);      // scale down
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Y'); // and draw the letter Y
    glPopMatrix(); // pop matrix off stack

    glPushMatrix(); // push a matrix on the stack
	glTranslatef(1.0, 0.0, 0.0);      // move to end of x axis
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glutSolidCone(0.02,0.1, 10, 2);   // draw a solid cone for the x-axis
	glRotatef(90.0, 0.0, 1.0, 0.0);   // rotate to draw in x=0 plane
	glTranslatef(0.0, 0.1, 0.0);      // move away slightly
	glScalef(0.001,0.001,0.001);      // scale down
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'X'); // and draw the letter X
    glPopMatrix(); // pop matrix off stack

    glMatrixMode(GL_MODELVIEW); // switch to modelview
    glPopMatrix();  // pop matrix off stack
} // drawAxes()
