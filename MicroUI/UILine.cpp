//
//  UILine.cpp
//  MicroUI
//
//  Created by Khaled AlTurkestani on 10/15/12.
//
//

#include "UILine.h"
#include "stglut.h"

UILine::UILine(STPoint2 beginPoint, const STColor4f& color)
{
    //HandleMouseDown(beginPoint);
    this->color = color;
    doneDrawing = false;
}

void UILine::Display()
{
    glBegin(GL_LINES);
    glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
    glVertex2f(beginPoint.x, beginPoint.y); // origin of the line
    glVertex2f(endPoint.x, endPoint.y); // ending point of the line
    glEnd();
    //if (doneDrawing) {
        glBegin(GL_POINTS);
        glColor4f(1, 1, 1, 1);
        glVertex2f(endPoint.x-1, endPoint.y-1);
        glVertex2f(endPoint.x-1, endPoint.y);
        glVertex2f(endPoint.x-1, endPoint.y+1);
        glVertex2f(endPoint.x, endPoint.y-1);
        glVertex2f(endPoint.x, endPoint.y);
        glVertex2f(endPoint.x, endPoint.y+1);
        glVertex2f(endPoint.x+1, endPoint.y-1);
        glVertex2f(endPoint.x+1, endPoint.y);
        glVertex2f(endPoint.x+1, endPoint.y+1);
        glEnd();
    //}
    glutPostRedisplay();
}

void UILine::HandleMouseDown(const STPoint2& position)
{
    if (doneDrawing == false) {
        this->beginPoint = position;
        this->endPoint = position;
    } else if (moveEnd) {
        this->endPoint = position;
    } else if (moveBegin) {
        this->beginPoint = position;
    }
    this->Display();
}

void UILine::HandleMouseUp(const STPoint2& position)
{
    if (doneDrawing == false) this->endPoint = position;
    else if (moveEnd) this->endPoint = position;
    else if (moveBegin) this->beginPoint = position;
    this->doneDrawing = true;
    this->Display();
}

void UILine::HandleMouseMove(const STPoint2& position)
{
    if (doneDrawing == false) this->endPoint = position;
    else if (moveEnd) this->endPoint = position;
    else if (moveBegin) this->beginPoint = position;
    this->Display();
}

bool UILine::OnEndLine(STPoint2& position)
{
    for (int i = 0; i < 10; i++) {
        if ((position.x == this->endPoint.x && position.y == this->endPoint.y)
            || (position.x == this->endPoint.x && position.y == this->endPoint.y+i)
            || (position.x == this->endPoint.x && position.y == this->endPoint.y-i)
            || (position.x+1 == this->endPoint.x+i && position.y == this->endPoint.y)
            || (position.x+1 == this->endPoint.x+i && position.y == this->endPoint.y+i)
            || (position.x+1 == this->endPoint.x+i && position.y == this->endPoint.y-i)
            || (position.x-1 == this->endPoint.x-i && position.y == this->endPoint.y)
            || (position.x-1 == this->endPoint.x-i && position.y == this->endPoint.y+i)
            || (position.x-1 == this->endPoint.x-i && position.y == this->endPoint.y-i)){
            
            this->moveEnd = true;
            this->moveBegin = false;
            return true;
        }
    }
    return false;
}

bool UILine::OnBeginLine(STPoint2& position)
{
    for (int i = 0; i < 10; i++) {
        if ((position.x == this->beginPoint.x && position.y == this->beginPoint.y)
            || (position.x == this->beginPoint.x && position.y == this->beginPoint.y+i)
            || (position.x == this->beginPoint.x && position.y == this->beginPoint.y-i)
            || (position.x+1 == this->beginPoint.x+i && position.y == this->beginPoint.y)
            || (position.x+1 == this->beginPoint.x+i && position.y == this->beginPoint.y+i)
            || (position.x+1 == this->beginPoint.x+i && position.y == this->beginPoint.y-i)
            || (position.x-1 == this->beginPoint.x-i && position.y == this->beginPoint.y)
            || (position.x-1 == this->beginPoint.x-i && position.y == this->beginPoint.y+i)
            || (position.x-1 == this->beginPoint.x-i && position.y == this->beginPoint.y-i)){
            
            this->moveBegin = true;
            this->moveEnd = false;
            return true;
        }
    }
    return false;
}