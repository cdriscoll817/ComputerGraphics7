#include "glwidget.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <QDebug>

#include "Vector.h"

#include "objects.h"   // routines for drawing platonic solids

// the zoom factor
double zoomFactor = 1.0;

float ortho = 1.0;
float orthoNear = -100.0;
float orthoFar = 100.0;

GLfloat light_position[4] = {0.0, 100.0, 100.0, 0.0};

/* Some colours defined in rgb alpha space */
GLfloat red[]   = {1.0f, 0.0f, 0.0f, 1.0f};
GLfloat green[] = {0.0f, 1.0f, 0.0f, 1.0f};
GLfloat blue[]  = {0.0f, 0.0f, 1.0f, 1.0f};
GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};

bool drag;
bool pull;
float pullX = 0.0;
float pullY = 0.0;
float moveX = 0.0;
float moveY = 0.0;


int input;


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent){
    setFocusPolicy(Qt::StrongFocus);

    // and initialize our transformation parameters
    translation = Vector(0.0, 0.0, 0.0);
    zoom = 1.0;
    xRot = 0.0;
    yRot = 0.0;
    zRot = 0.0;

    axes = false;

    width = 800; height = 800;

    arc = new arcBall();
}

void GLWidget::setOrtho(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    if(aspectRatio > 1.0){
        glOrtho(-ortho, ortho, -ortho / aspectRatio, ortho / aspectRatio, -100, 100);
    }else{
        glOrtho(-ortho * aspectRatio, ortho * aspectRatio, -ortho, ortho, -100, 100);
    }
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::initializeGL(){
    //Clear the screen
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //Set up the view
    setOrtho();

    /*       Turn on the lights                           */
    /******************************************************/
    // start with a unit light vector from upper right front
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    /******************************************************/

}

void GLWidget::paintGL(){

    /*  Set up the visualization pipeline equivalent to lab7     */
    /*************************************************************/
    /* set the colour of the window to white*/
    glClearColor(1.0, 1.0, 1.0, 1.0);
    /* and clear the window */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Apply the arcball state to the gl matrix
    GLfloat mNow[16];

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    glTranslatef(pullX, pullY, 0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, mNow);
    arc->getMatrix(mNow);
    glLoadMatrixf(mNow);

    // now define the view matrix transformations in reverse order
    //    glTranslatef(translation[0], translation[1], translation[2]);
    // now apply our individual transformations in reverse order: model matrix first
    //    glRotatef(zRot, 0.0, 0.0, 1.0);
    //    glRotatef(yRot, 0.0, 1.0, 0.0);
    //    glRotatef(xRot, 1.0, 0.0, 0.0);
    //    glScalef(zoom, zoom, zoom);

    if(axes)  drawAxes();

    /**
     Test your shape here
     **/

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green); // give the object a colour

    switch(input)
    {
        case 2: drawTetrahedron(); break;
        case 3: drawOctahedron(); break;
        case 4: drawDodecahedron(); break;
        case 5: drawIcosahedron(); break;
        case 6: drawCylinder(2,3,20); break;
        case 7: drawCube(); break;
        case 8: drawSphere(2, 20, 20); break;
    }

    glPopMatrix();

    glFlush();
}

void GLWidget::resizeGL(int w, int h){
    width = w; height = h;
    glViewport(0, 0, width, height); // set the viewport
    setOrtho();
    this->updateGL();
}

void GLWidget::resetArc(){
    resetArcBall = !resetArcBall;
    arc->reset();
    this->updateGL();
}

void GLWidget::resetPos(){
    pullX = 0.0;
    pullY = 0.0;
    this->updateGL();
}

void GLWidget::resetZoom(){
    ortho = zoomFactor;
    setOrtho();
    this->updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent *event){
    switch(event->key()) {
    case Qt::Key_1: axes=!axes; this->updateGL();break;
    case Qt::Key_S: saveImage(); break;
    case Qt::Key_Q: qApp->exit(); break;
    case Qt::Key_2: input=event->key()-'0'; this->updateGL(); break;
    case Qt::Key_3: input=event->key()-'0'; this->updateGL(); break;
    case Qt::Key_4: input=event->key()-'0'; this->updateGL(); break;
    case Qt::Key_5: input=event->key()-'0'; this->updateGL(); break;
    case Qt::Key_6: input=event->key()-'0'; this->updateGL(); break;
    case Qt::Key_7: input=event->key()-'0'; this->updateGL(); break;
    case Qt::Key_8: input=event->key()-'0'; this->updateGL(); break;
    default:
        event->ignore();
        break;
    }
}

void GLWidget::wheelEvent(QWheelEvent *event){
    float numDegrees = (static_cast<float>(event->delta()) / 8.0);
    float numSteps = numDegrees / (180.0 * (1.0 / ortho));
    ortho -= numSteps;
    if(ortho <= 0.0){
        ortho = 0.0001;
    }
    setOrtho();
    this->updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        arc->startBall(event->x(),event->y(),width,height);
        drag = true;
    }
    if(event->button() == Qt::RightButton){
        moveX = static_cast<float>(event->x());
        moveY = static_cast<float>(event->y());
        pull = true;
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        if(drag == true){
            arc->updateBall(event->x(),event->y(),width,height);
            this->updateGL();
        }
    }
    if(pull == true){
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        if(aspectRatio < 1.0){
            pullX += (static_cast<float>(event->x()) - moveX) / (static_cast<float>(width) / ((ortho * 2.0) * aspectRatio));						//	set the vector
            pullY -= (static_cast<float>(event->y()) - moveY) / (static_cast<float>(height) / (ortho * 2.0));
        }else{
            pullX += (static_cast<float>(event->x()) - moveX) / (static_cast<float>(width) / (ortho * 2.0));						//	set the vector
            pullY -= (static_cast<float>(event->y()) - moveY) / (static_cast<float>(height) / ((ortho * 2.0) / aspectRatio));
        }
        moveX = static_cast<float>(event->x());
        moveY = static_cast<float>(event->y());
        this->updateGL();
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        drag = false;
        this->updateGL();
    }
    if(event->button() == Qt::RightButton){
        pull = false;
        this->updateGL();
    }
}

void GLWidget::saveImage(){
    QImage image = this->grabFrameBuffer();
    image.save("comp30020lab08.jpg","jpeg");
    if(!image.isNull()){
        qDebug()<<"Image saved successfully";
    }
}

GLWidget::~GLWidget() {
    // TODO Auto-generated destructor stub
}
