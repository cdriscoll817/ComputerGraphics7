#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    openGL = new GLWidget();
    openGL->setParent(ui->glScrollArea);
    ui->glScrollArea->setWidgetResizable( true );
    ui->glScrollArea->setWidget( openGL );

    this->setWindowTitle("OpenGL Lab");


    QObject::connect(ui->arcButton, SIGNAL(clicked()), this, SLOT(resetArcBall()));
    QObject::connect(ui->zoomButton, SIGNAL(clicked()), this, SLOT(resetZoom()));
    QObject::connect(ui->dragButton, SIGNAL(clicked()), this, SLOT(resetPosition()));
    QObject::connect(ui->actionSave_Image, SIGNAL(triggered()), this, SLOT(saveImage()));
    QObject::connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

}


void MainWindow::resetArcBall(){
    openGL->resetArc();
}

void MainWindow::resetPosition(){
    openGL->resetPos();
}

void MainWindow::resetZoom(){
    openGL->resetZoom();
}

void MainWindow::saveImage(){
    openGL->saveImage();
}

void MainWindow::closeEvent(QCloseEvent *event){
    qApp->quit();
}

MainWindow::~MainWindow()
{
    delete openGL;
    delete ui;
}
