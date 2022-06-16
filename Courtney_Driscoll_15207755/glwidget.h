#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QKeyEvent>
#if defined(__APPLE__) || defined(MACOSX)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <vector>

#include "Point.h"
#include "Vector.h"
#include "arcBall.h"

#define MAX_N_CONTROL_POINTS 100

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    // load & save routines
    void saveImage();

    virtual ~GLWidget();

public slots:
    void resetArc();
    void resetPos();
    void resetZoom();

protected:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    void setOrtho();

    Vector translation; // translation in window plane
    float zoom;         // zoom factor
    float xRot, yRot, zRot; // Euler rotations around axes
    int width, height;
    bool axes;
    arcBall *arc;
    bool resetArcBall;
};

#endif // GLWIDGET_H
