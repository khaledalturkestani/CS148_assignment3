// UIButton.cpp
#include "UIButton.h"

#include "st.h"
#include "stgl.h"
#include "stglut.h"

//
// Constructor: Initialize a UI button with
// a given font face and label text.
//
UIButton::UIButton(STFont* font,
                   const std::string& text,
                   FireCallback callback,
                   CaptureCallback capture,
                   ReleaseCallback release)
    : mFont(font)
    , mText(text)
    , mCallback(callback)
    , mCaptureCallback(capture)
    , mReleaseCallback(release)
{
    state = IDLE;
}

/** CS 148 TODO:
*
*   Implement your button here.
*/

void UIButton::HandleMouseDown(const STPoint2& position)
{
    this->mCaptureCallback(this);
    
    bool onButton = this->HitTest(position);
    if (onButton) {
        state = DOWN;
    } else {
        state = IDLE;
    }
    this->Display();
    glutPostRedisplay();
    glClear(GL_COLOR_BUFFER_BIT);
    printState();
}

void UIButton::HandleMouseUp(const STPoint2& position)
{
    this->mReleaseCallback();
    
    bool onButton = this->HitTest(position);
    if (!onButton) {
        state = IDLE;
    } else {
        this->mCallback(this);
        state = OVER;
    }
    this->Display();
    glutPostRedisplay();
    glClear(GL_COLOR_BUFFER_BIT);
    printState();
}

void UIButton::HandleMouseMove(const STPoint2& position)
{
    bool onButton = this->HitTest(position);
    if (!onButton && state == DOWN) {
        state = OVER;
    } else if (onButton && state == OVER) {
        state = DOWN;
    }
    this->Display();
    glutPostRedisplay();
    glClear(GL_COLOR_BUFFER_BIT);
}

void UIButton::HandleMouseEnter()
{
    if (state == IDLE) {
        state = OVER;
    }
    this->Display();
    glutPostRedisplay();
    glClear(GL_COLOR_BUFFER_BIT);
    printState();
}

void UIButton::HandleMouseLeave()
{
    if (state == DOWN) {
        state = OVER;
    } else if (state == OVER) {
        state = IDLE;
    }
    this->Display();
    glutPostRedisplay();
    glClear(GL_COLOR_BUFFER_BIT);
    printState();
}

void UIButton::printState()
{
    if (state == IDLE) {
        printf("IDLE\n");
    } else if (state == OVER) {
        printf("OVER\n");
    } else {
        printf("DOWN\n");
    }
}


STPoint2 UIButton::centerText()
{
    UIRectangle r = this->GetRectangle();
    float fontWidth = this->mFont->ComputeWidth(mText);
    float fontHeight = this->mFont->GetHeight();
    float rWidth = (r.pMax.x) - (r.pMin.x);
    float rHeight = (r.pMax.y) - (r.pMin.y);
    float newX = (rWidth - fontWidth)/2;
    float newY = (rHeight - fontHeight)/2;
    return STPoint2(newX, newY);
}

STColor4f UIButton::getColor()
{
    STColor4f color;
    if (state == IDLE) {
        color = STColor4f(1, 0, 0, 1);
    } else if (state == OVER) {
        color = STColor4f(0, 1, 0, 1);
    } else {
        color = STColor4f(0, 0, 1, 1);
    }
    return color;   
}



void UIButton::Display()
{
    glPushMatrix();
    UIRectangle r = this->GetRectangle();
    STColor4f color = getColor();
    glColor4f(color.r, color.g, color.b, color.a);
    glRectf(r.pMin.x, r.pMin.y, r.pMax.x, r.pMax.y);
	STPoint2 textPos = centerText();
    glTranslatef(r.pMin.x+textPos.x, r.pMin.y+textPos.y, 0);
    (this->mFont)->DrawString(this->mText, STColor4f(0.0, 0.0, 0.0, 1.0));
    glPopMatrix();
}


