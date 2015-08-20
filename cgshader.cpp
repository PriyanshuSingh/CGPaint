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

#include "cgshader.h"
#include <assert.h>
CGShader::CGShader()
{
    _totalShaders=0;
    _shaders[VERTEX_SHADER]=0;
    _shaders[FRAGMENT_SHADER]=0;
    _shaders[GEOMETRY_SHADER]=0;
    _attributeList.clear();
    _uniformAttributeList.clear();
}

CGShader::~CGShader()
{
    _attributeList.clear();
    _uniformAttributeList.clear();
}

void CGShader::loadFromString(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);

    const char * ptmp = source.c_str();
    glShaderSource (shader, 1, &ptmp, NULL);

    //check whether the shader loads fine
    GLint status;
    glCompileShader (shader);
    glGetShaderiv (shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog= new GLchar[infoLogLength];
        glGetShaderInfoLog (shader, infoLogLength, NULL, infoLog);
        qDebug()<<"Compile log: "<<infoLog<<endl;
        delete [] infoLog;
    }
    assert(_totalShaders < 3); // _shaders[] length is 3
    _shaders[_totalShaders++]=shader;
}

#include <fstream>
void CGShader::loadFromFile(GLenum type, const std::string &fileName)
{
    std::ifstream fp;
    fp.open(fileName.c_str(), std::ios_base::in);
    if(fp) {
        std::string line, buffer;
        while(std::getline(fp, line)) {
            buffer.append(line);
            buffer.append("\r\n");
        }
        //copy to source
        loadFromString(type, buffer);
    } else {
        qDebug()<<"Error loading shader: "<<fileName.c_str()<<endl;
    }
}

void CGShader::createAndLinkShaderProgram()
{
    _program = glCreateProgram ();
	if (_shaders[VERTEX_SHADER] != 0) {
		glAttachShader (_program, _shaders[VERTEX_SHADER]);
	}
	if (_shaders[FRAGMENT_SHADER] != 0) {
		glAttachShader (_program, _shaders[FRAGMENT_SHADER]);
	}
	if (_shaders[GEOMETRY_SHADER] != 0) {
		glAttachShader (_program, _shaders[GEOMETRY_SHADER]);
	}
	
	//link and check whether the program links fine
	GLint status;
	glLinkProgram (_program);
	glGetProgramiv (_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		
		glGetProgramiv (_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog= new GLchar[infoLogLength];
		glGetProgramInfoLog (_program, infoLogLength, NULL, infoLog);
        qDebug()<<"Link log: "<<infoLog<<endl;
		delete [] infoLog;
	}

	glDeleteShader(_shaders[VERTEX_SHADER]);
	glDeleteShader(_shaders[FRAGMENT_SHADER]);
	glDeleteShader(_shaders[GEOMETRY_SHADER]);
}

void CGShader::useProgram()
{
    glUseProgram(_program);
    assert(_program != 0); // using 0 for unUsing Program
}

void CGShader::unUseProgram()
{
    glUseProgram(0);
}

void CGShader::addAttribute(const std::string &attribute)
{
    _attributeList[attribute] = glGetAttribLocation(_program, attribute.c_str());
}

void CGShader::addUniform(const std::string &uniform)
{
    _uniformAttributeList[uniform] = glGetUniformLocation(_program, uniform.c_str());
}

GLuint CGShader::operator[](const std::string &attribute)
{
    return _attributeList[attribute];
}

GLuint CGShader::operator()(const std::string &uniform)
{
    return _uniformAttributeList[uniform];
}

void CGShader::deleteShaderProgram()
{
    glDeleteProgram(_program);
}
