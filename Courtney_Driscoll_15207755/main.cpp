#include <QApplication>
#include "mainwindow.h"
#if defined(__APPLE__) || defined(MACOSX)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    glutInit(&argc, argv);
    MainWindow w;
    w.setWindowTitle("COMP30020 Lab 8");
    w.show();

    return a.exec();
}
