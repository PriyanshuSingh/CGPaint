/**************************************************************************
**   Author: Priyanshu Singh
**   handle: tgamerz
**   Date:   13/08/2015
**
**   Copyright (c) 2015 Priyanshu Singh
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
** OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
** OR OTHER DEALINGS IN THE SOFTWARE.
**************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QColorDialog>
#include <QFormLayout>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setCurShapeType(CGShape::NONE);
    ui->centralWidget->setFilledShape(false);
    buildActions();
    buildToolBar();
    buildMenus();
    disableAllAction();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectCircleShape()
{
    ui->centralWidget->setCurShapeType(CGShape::CIRCLE);
    squareAction->setChecked(false);
    triangleAction->setChecked(false);
    pencilAction->setChecked(false);
    lineAction->setCheckable(false);
}

void MainWindow::selectSquareShape()
{
    ui->centralWidget->setCurShapeType(CGShape::SQUARE);
    circleAction->setChecked(false);
    triangleAction->setChecked(false);
    pencilAction->setChecked(false);
    lineAction->setChecked(false);
}

void MainWindow::selectTriangleShape()
{
    ui->centralWidget->setCurShapeType(CGShape::TRIANGLE);
    circleAction->setChecked(false);
    squareAction->setChecked(false);
    pencilAction->setChecked(false);
    lineAction->setChecked(false);
}

void MainWindow::selectPencilShape()
{
    ui->centralWidget->setCurShapeType(CGShape::PENCIL);
    circleAction->setChecked(false);
    squareAction->setChecked(false);
    triangleAction->setChecked(false);
    lineAction->setChecked(false);
}

void MainWindow::selectLineShape()
{
    ui->centralWidget->setCurShapeType(CGShape::LINE);
    circleAction->setChecked(false);
    squareAction->setChecked(false);
    triangleAction->setChecked(false);
    pencilAction->setChecked(false);
}

void MainWindow::selectColor()
{

    QColor color = QColorDialog::getColor(Qt::black);

    if(color.isValid()){
        colorLabel->setPalette(QPalette(color));
        colorLabel->setAutoFillBackground(true);
    }
    ui->centralWidget->setCurColor(color);
    colorAction->setChecked(false);
}

void MainWindow::saveSlot()
{
    QImage img = ui->centralWidget->getQImage();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save layout"));
    fileName = fileName + QString(".jpg");
    if(!img.save(fileName,"JPG")){
        QString msg = tr("Error writing to %1\n")
            .arg(fileName);
        QMessageBox::warning(this, tr("Error"), msg);
    }else{
        QMessageBox::information(this,tr("Save"),tr("Save Successful"));
    }

}

void MainWindow::undoSlot()
{
    ui->centralWidget->undo();
}

void MainWindow::redoSlot()
{
    ui->centralWidget->redo();
}

void MainWindow::toggleFilled(bool value)
{
    ui->centralWidget->setFilledShape(value);
}

void MainWindow::buildActions()
{

    circleAction = new QAction(QString("Circle"),this);
    circleAction->setIcon(QIcon(":/res/images/circle32.png"));
    circleAction->setStatusTip(QString("Draws Circle on canvas"));
    circleAction->setWhatsThis(QString("Circle"));
    circleAction->setCheckable(true);
    connect(circleAction, SIGNAL(triggered(bool)), this, SLOT(selectCircleShape()));

    triangleAction = new QAction(QString("Triangle"),this);
    triangleAction->setIcon(QIcon(":/res/images/triangle32.png"));
    triangleAction->setStatusTip(QString("Draws a triangle on canvas"));
    triangleAction->setWhatsThis(QString("Triangle"));
    triangleAction->setCheckable(true);
    connect(triangleAction, SIGNAL(triggered(bool)), this, SLOT(selectTriangleShape()));

    squareAction = new QAction(QString("Square"), this);
    squareAction->setIcon(QIcon(":/res/images/square32.png"));
    squareAction->setStatusTip(QString("Draws a rectangle on canvas"));
    squareAction->setCheckable(true);
    connect(squareAction, SIGNAL(triggered(bool)), this, SLOT(selectSquareShape()));

    pencilAction = new QAction(QString("Pencil"), this);
    pencilAction->setIcon(QIcon(":/res/images/pencil32.png"));
    pencilAction->setStatusTip(QString("Free hand drawing"));
    pencilAction->setWhatsThis(QString("Pencil Tool"));
    pencilAction->setCheckable(true);
    connect(pencilAction, SIGNAL(triggered(bool)), this, SLOT(selectPencilShape()));

    lineAction = new QAction(QString("Line"), this);
    lineAction->setIcon(QIcon(":/res/images/line32.png"));
    lineAction->setStatusTip(QString("Draws line on canvas"));
    lineAction->setCheckable(true);
    connect(lineAction, SIGNAL(triggered(bool)), this, SLOT(selectLineShape()));

    colorLabel = new QLabel();
    colorLabel->setFixedSize(25,25);
    colorLabel->setFrameStyle(QFrame::Sunken | QFrame::Panel);
    colorLabel->setPalette(QPalette(Qt::black));
    colorLabel->setAutoFillBackground(true);

    colorAction = new QAction(QString("Color"), this);
    colorAction->setIcon(QIcon(":/res/images/color32.png"));
    colorAction->setStatusTip(QString("Color picker"));
    colorAction->setWhatsThis(QString("Color picker"));
    colorAction->setCheckable(true);
    colorAction->setAutoRepeat(true);
    connect(colorAction, SIGNAL(triggered(bool)), this, SLOT(selectColor()));

    saveAction = new QAction(QString("&Save"),this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(saveSlot()));

    undoAction = new QAction(QString("undo"),this);
    undoAction->setShortcut(QKeySequence::Undo);
    connect(undoAction,SIGNAL(triggered(bool)), this, SLOT(undoSlot()));

    redoAction = new QAction(QString("redo"),this);
    redoAction->setShortcut(QKeySequence::Redo);
    connect(redoAction,SIGNAL(triggered(bool)), this, SLOT(redoSlot()));

    filledAction = new QAction(QString("Filled"), this);
    filledAction->setCheckable(true);
    connect(filledAction, SIGNAL(toggled(bool)), this, SLOT(toggleFilled(bool)));
}

void MainWindow::buildToolBar()
{
    ui->mainToolBar->addAction(circleAction);
    ui->mainToolBar->addAction(triangleAction);
    ui->mainToolBar->addAction(squareAction);
    ui->mainToolBar->addAction(pencilAction);
    ui->mainToolBar->addAction(lineAction);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(colorAction);

}

void MainWindow::buildMenus()
{
    //intializing menus
    fileMenu = new QMenu(QString("&File"));
    toolMenu = new QMenu(QString("&Tools"));
    editMenu = new QMenu(QString("&Edit"));

    //tool Menu
    toolMenu->addAction(circleAction);
    toolMenu->addAction(triangleAction);
    toolMenu->addAction(squareAction);
    toolMenu->addAction(pencilAction);
    toolMenu->addAction(lineAction);
    toolMenu->addSeparator();
    toolMenu->addAction(colorAction);
    toolMenu->addAction(filledAction);

    //file Menu
    fileMenu->addAction(saveAction);

    //EditMenu
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);

    //adding menu to menubar
    ui->menuBar->addMenu(fileMenu);
    ui->menuBar->addMenu(toolMenu);
    ui->menuBar->addMenu(editMenu);

}

void MainWindow::disableAllAction()
{
    circleAction->setChecked(false);
    squareAction->setChecked(false);
    triangleAction->setChecked(false);
    pencilAction->setChecked(false);
}
