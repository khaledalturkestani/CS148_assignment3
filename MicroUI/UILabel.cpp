// UILabel.cpp
#include "UILabel.h"

#include "st.h"
#include "stgl.h"

//
// Constructor: Initialize a UI label with
// a given font face and text string.
//
UILabel::UILabel(STFont* font, const std::string& text)
    : mFont(font)
    , mText(text)
{
}

//
// Display the label to the current OpenGL context.
//
void UILabel::Display()
{
    /** CS 148 TODO:
    *
    *   You must implement the display logic for your label widget.
    *   Look at the STFont class for ideas of how to do this.
    *
    *   You should render your label based on the rectangle
    *   of the widget, but you do not need to "cut off" any
    *   text that extends outside this rectangle.
    */
    glPushMatrix();
	glTranslatef(this->GetRectangle().pMin.x, this->GetRectangle().pMin.y, 0);
	(this->mFont)->DrawString(this->mText, STColor4f(1.0, 1.0, 0.0, 1.0));
    glPopMatrix();
}
