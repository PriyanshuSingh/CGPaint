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

#include "cgcircle.h"

CGCircle::CGCircle()
{

}

CGCircle::~CGCircle()
{

}



void CGCircle::init()
{
    angle = 2 * 3.14159265f / PRECISION_COUNT;

    glGenBuffers(1, &vboID);
    glGenVertexArrays(1, &vaoID);
}

void CGCircle::update()
{
    float radius = sqrtf((endPoint.x() - startPoint.x())*(endPoint.x() - startPoint.x())
                         +(endPoint.y() - startPoint.y())*(endPoint.y() - startPoint.y()));
    for(int i=0; i<PRECISION_COUNT; ++i){
        vertices[i] = glm::vec3(startPoint.x() + (cosf(i * angle) * radius), startPoint.y() + (sinf(i * angle) * radius),0.0f);
    }
    //bind vbo
    glBindBuffer(GL_ARRAY_BUFFER,vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    //unbind vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //bind vao
    glBindVertexArray(vaoID);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    //unbind vao
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);

}

void CGCircle::draw()
{

    if(isActive()){
        update();
    }
    //bind vao
    glBindVertexArray(vaoID);
    if(!isActive() && isFilled()){
        glDrawArrays(GL_TRIANGLE_FAN,0,PRECISION_COUNT);
    }else{
        glDrawArrays(GL_LINE_LOOP,0,PRECISION_COUNT);
    }
    //unbind vao
    glBindVertexArray(0);
}
