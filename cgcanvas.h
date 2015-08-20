/**************************************************************************
**   Author: Priyanshu Singh
**   handle: tgamerz
**   Date:   16/08/2015
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

#ifndef CGCANVAS_H
#define CGCANVAS_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QMouseEvent>
#include <QDebug>
#include "cgshader.h"
#include "cgshape.h"
#include "cgcircle.h"
#include "cgpencil.h"
#include "cgtriangle.h"
#include "cgsquare.h"
#include "cgundostack.h"
#include "cgline.h"
class CGCanvas : public QOpenGLWidget
{
    Q_OBJECT

public:
    CGCanvas(QWidget *parent=0);
    ~CGCanvas();


    QColor getCurColor() const;
    void setCurColor(const QColor &value);

    int getCurBrushSize() const;
    void setCurBrushSize(int value);

    CGShape::SHAPE_TYPE getCurShapeType() const;
    void setCurShapeType(const CGShape::SHAPE_TYPE &value);

    bool isFilledShape() const;
    void setFilledShape(bool value);

    QImage getQImage();
    void redo();
    void undo();

protected:

    // QOpenGLWidget interface
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    // QWidget interface
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    //void keyPressEvent(QKeyEvent *);

    void initCurShape();

private:

    CGShader canvasShader;

    //transformation Matrix
    glm::mat4 MVP;
    glm::mat4 projectionMatrix;
    glm::mat4 modelViewMatrix;

    //shapes vector
    std::vector< CGShape* > shapes;

    //current shape
    CGShape *curShape;
    CGShape::SHAPE_TYPE curShapeType;
    bool filledShape;

    //brush info
    QColor curColor;
    int curBrushSize;

    //UndoStack
    cg::CGUndoStack< CGShape* > undoStack;

    //helpers
    QPointF mousePressPoint;
    void printContextInformation();

};

#endif // CGCANVAS_H
