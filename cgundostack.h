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

#ifndef CGUNDOSTACK_H
#define CGUNDOSTACK_H

namespace cg{

const int CG_STACK_MAX_LEN = 15;

template<typename T>
class CGUndoStack
{
public:
    CGUndoStack();

    bool push(T data);
    bool pop(T& out);
    bool isEmpty();

private:
    T array[CG_STACK_MAX_LEN];
    unsigned int top;
};

template<typename T>
inline CGUndoStack<T>::CGUndoStack()
{
    top = 0;
}

template<typename T>
inline bool CGUndoStack<T>::push(T data)
{
    if(top == CG_STACK_MAX_LEN) return false;
    array[top] = data;
    top++;

    return true;
}

template<typename T>
inline bool CGUndoStack<T>::pop(T &out)
{
    if(isEmpty()){
        return false;
    }

    out = array[top-1];
    top--;
    return true;
}

template<typename T>
inline bool CGUndoStack<T>::isEmpty()
{
    return (top == 0);
}

}
#endif // CGUNDOSTACK_H
