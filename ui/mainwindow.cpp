#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view.h"
#include <QGLFormat>
#include "SupportCanvas3D.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // CURRENTLY CAUSING AN ERROR (COMMENTED OUT PORTION)
    // TODO: 1. Copy over the orbit camera and settings files, and
    //       2. incorporate 3D canvas, camera, and settings object to the ui

    QGLFormat qglFormat;
    qglFormat.setVersion(4, 3);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    qglFormat.setSampleBuffers(true);
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(ui->canvas3D);
    m_canvas3D = new SupportCanvas3D(qglFormat, this);
    gridLayout->addWidget(m_canvas3D, 0, 1);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
