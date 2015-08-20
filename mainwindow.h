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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QLabel>
#include "cgshape.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void selectCircleShape();
    void selectSquareShape();
    void selectTriangleShape();
    void selectPencilShape();
    void selectLineShape();
    void selectColor();
    void saveSlot();
    void undoSlot();
    void redoSlot();
    void toggleFilled(bool value);

private:
    Ui::MainWindow *ui;

    QMenu *fileMenu;
    QMenu *toolMenu;
    QMenu *editMenu;

    QAction *saveAction;
    QAction *undoAction;
    QAction *redoAction;

    QAction *colorAction;
    QAction *squareAction;
    QAction *triangleAction;
    QAction *pencilAction;
    QAction *circleAction;
    QAction *filledAction;
    QAction *lineAction;

    QLabel *colorLabel;

    void buildActions();
    void buildToolBar();
    void buildMenus();
    void disableAllAction();

};

#endif // MAINWINDOW_H
