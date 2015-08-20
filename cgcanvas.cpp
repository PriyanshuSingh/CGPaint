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

#include "cgcanvas.h"
#include <QSurfaceFormat>
#include <QCoreApplication>
#include <vector>
CGCanvas::CGCanvas(QWidget *parent):QOpenGLWidget(parent)
{

    //Setting OpenGl version 4.1
    QSurfaceFormat glFormat;
    glFormat.setMajorVersion(4);
    glFormat.setMinorVersion(1);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    glFormat.setDefaultFormat(glFormat);
    glFormat.setSwapInterval(1);
    setFormat(glFormat);

    //initializing transformation matrix
    modelViewMatrix = glm::mat4(1);
    projectionMatrix = glm::ortho(0.0f, (float)width(), (float)height(), 0.0f);
    MVP = projectionMatrix*modelViewMatrix;

    //initializing canvas properties
    setFocusPolicy(Qt::StrongFocus);
    shapes.clear();
    curShapeType = CGShape::NONE;
    curShape = NULL;

}

CGCanvas::~CGCanvas()
{
    for(int i=0; i<shapes.size(); ++i){
        delete shapes[i];
    }
    shapes.clear();
}

void CGCanvas::initializeGL()
{
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        qDebug()<<"Failed to initialize GLEW";
    }
    printContextInformation();

    // Canvas color = white
    glClearColor(1.0f,1.0f,1.0f,1.0f);

    //load the shader
    qDebug()<< QCoreApplication::applicationDirPath().toLatin1().data();

    canvasShader.loadFromFile(GL_VERTEX_SHADER, "/Users/tgz/Projects/QtProjects/CGPaint/vertex_shader.vert");
    canvasShader.loadFromFile(GL_FRAGMENT_SHADER, "/Users/tgz/Projects/QtProjects/CGPaint/fragment_shader.frag");

    //compile and link shaders
    canvasShader.createAndLinkShaderProgram();

    canvasShader.useProgram();
        //add attributes and uniform
        canvasShader.addUniform("MVP");
        canvasShader.addUniform("fColor");
    canvasShader.unUseProgram();

    qDebug()<<"GL initialization complete";
}

void CGCanvas::resizeGL(int w, int h)
{
    projectionMatrix = glm::ortho(0.0f, (float)w, (float)h, 0.0f);
    //IMP NOTE: all the parameters of ortho should be of same type
    //Took almost 2 days to track this bug :P
    MVP = projectionMatrix * modelViewMatrix;
}

void CGCanvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPointSize(1.0f);
    glLineWidth(1.0f);
    glEnable(GL_BLEND);
    int size = shapes.size();
    GLuint a;
    glGenVertexArrays(1, &a);
    glBindVertexArray(a);
    canvasShader.useProgram();
        glUniformMatrix4fv(canvasShader("MVP"), 1, GL_FALSE, &MVP[0][0]);
        for(int i=0; i<size; ++i){
            glUniform3f(canvasShader("fColor"), shapes[i]->getColor().redF(), shapes[i]->getColor().greenF(), shapes[i]->getColor().blueF());
            shapes[i]->draw();
        }
        if(curShape){
            curShape->draw();
        }
    canvasShader.unUseProgram();
    glDisable(GL_BLEND);

}

void CGCanvas::printContextInformation()
{
    QOpenGLContext *cont = context();
    qDebug() << "Context valid: " << cont->isValid();
    qDebug() << "Really used OpenGl: " << cont->format().majorVersion() << "." << cont->format().minorVersion();
    qDebug() << "OpenGl information: VENDOR:       " << (const char*)glGetString(GL_VENDOR);
    qDebug() << "                    RENDERDER:    " << (const char*)glGetString(GL_RENDERER);
    qDebug() << "                    VERSION:      " << (const char*)glGetString(GL_VERSION);
    qDebug() << "                    GLSL VERSION: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    qDebug() << "endstuff\n";
}


void CGCanvas::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){
        if(curShapeType != CGShape::NONE){
            mousePressPoint = ev->localPos();
            //repaint();
        }
    }
}

void CGCanvas::mouseReleaseEvent(QMouseEvent *ev)
{
    if(curShape){
        curShape->setEndPoint(ev->localPos());
        shapes.push_back(curShape);
        repaint();
        curShape->setActive(false);
        repaint();
        curShape = NULL;
    }
}

void CGCanvas::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() & Qt::LeftButton){
        if(curShapeType != CGShape::NONE){
            if(curShape == NULL){
                initCurShape();
            }
            curShape->setEndPoint(ev->localPos());
            repaint();
        }
    }
}

void CGCanvas::initCurShape()
{
    switch(curShapeType){
    case CGShape::CIRCLE:
        curShape = new CGCircle();
        break;
    case CGShape::TRIANGLE:
        curShape = new CGTriangle();
        break;
    case CGShape::PENCIL:
        curShape = new CGPencil();
        break;
    case CGShape::SQUARE:
        curShape = new CGSquare();
        break;
    case CGShape::LINE:
        curShape = new CGLine();
        break;
    default:
        break;
    }
    curShape->setColor(curColor);
    curShape->setBrushSize(curBrushSize);
    curShape->setStartPoint(mousePressPoint);
    curShape->init();
    curShape->setActive(true);
    curShape->setFilled(isFilledShape());
}
bool CGCanvas::isFilledShape() const
{
    return filledShape;
}

void CGCanvas::setFilledShape(bool value)
{
    filledShape = value;
}

QImage CGCanvas::getQImage()
{
    return grabFramebuffer();
}

void CGCanvas::redo()
{
    CGShape* shape;
    if(undoStack.pop(shape)){
        shapes.push_back(shape);
        repaint();
    }
}

void CGCanvas::undo()
{
    if(shapes.empty()) return;

    if(undoStack.push(shapes.back())){
        shapes.pop_back();
        repaint();
    }
}


CGShape::SHAPE_TYPE CGCanvas::getCurShapeType() const
{
    return curShapeType;
}

void CGCanvas::setCurShapeType(const CGShape::SHAPE_TYPE &value)
{
    curShapeType = value;
}

int CGCanvas::getCurBrushSize() const
{
    return curBrushSize;
}

void CGCanvas::setCurBrushSize(int value)
{
    curBrushSize = value;
}

QColor CGCanvas::getCurColor() const
{
    return curColor;
}

void CGCanvas::setCurColor(const QColor &value)
{
    curColor = value;
}

