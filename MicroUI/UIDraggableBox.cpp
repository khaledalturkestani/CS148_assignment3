//
//  DraggableBox.cpp
//  MicroUI
//
//  Created by Khaled AlTurkestani on 10/14/12.
//
//

#include "UIDraggableBox.h"

// UIBox.cpp

#include "stgl.h"
#include "stglut.h"

//
// Constructor: Initialize a UI box with a given color.
//
UIDraggableBox::UIDraggableBox(const STColor4f& color, BeginDrag box1, EndDrag box2)
                                : mColor(color)
                                , mBeginDrag(box1)
                                , mEndDrag(box2)
{
}

//
// Display the box to the current OpenGL context.
//
void UIDraggableBox::Display()
{
    glPushMatrix();
    UIRectangle r = this->GetRectangle();
    STColor4f c = mColor;
    glColor4f(c.r, c.g, c.b, c.a);
    glRectf(r.pMin.x, r.pMin.y, r.pMax.x, r.pMax.y);
    glTranslatef(r.pMin.x, r.pMin.y, 0);
    glPopMatrix();
}

void UIDraggableBox::HandleMouseMove(const STPoint2 &position)
{
    STPoint2 newMin = STPoint2(this->GetRectangle().pMin.x+position.x-currentPos.x,
                               this->GetRectangle().pMin.y+position.y-currentPos.y);
    STPoint2 newMax = STPoint2(this->GetRectangle().pMax.x+position.x-currentPos.x,
                               this->GetRectangle().pMax.y+position.y-currentPos.y);
    this->SetRectangle(UIRectangle(newMin, newMax));
    this->Display();
    glutPostRedisplay();
    currentPos = position;
}

void UIDraggableBox::HandleMouseDown(const STPoint2 &position)
{
    this->mBeginDrag(this);
    currentPos = position;
}

void UIDraggableBox::HandleMouseUp(const STPoint2 &position)
{
    this->mEndDrag();
}


