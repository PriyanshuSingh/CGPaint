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

#ifndef CGSHAPE_H
#define CGSHAPE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <QColor>
#include <QPointF>
#include <QWidget>
#include <cmath>
class CGShape
{
public:
    CGShape();
    virtual ~CGShape();

    virtual void init();
    virtual void update();
    virtual void draw();
    enum SHAPE_TYPE{
        CIRCLE,
        SQUARE,
        LINE,
        TRIANGLE,
        PENCIL,
        NONE
    };

    bool isActive() const;
    void setActive(bool value);

    int getBrushSize() const;
    void setBrushSize(int value);

    QPointF getEndPoint() const;
    void setEndPoint(const QPointF &value);

    QPointF getStartPoint() const;
    void setStartPoint(const QPointF &value);

    bool isFilled() const;
    void setFilled(bool value);

    QColor getColor() const;
    void setColor(const QColor &value);


protected:
    bool active;
    bool filled;
    QColor color;
    QPointF startPoint;
    QPointF endPoint;
    int brushSize;

    //buffer IDs
    GLuint vaoID;
    GLuint vboID;


};

#endif // CGSHAPE_H
