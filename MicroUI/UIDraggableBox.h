//
//  UIDraggableBox.h
//  MicroUI
//
//  Created by Khaled AlTurkestani on 10/14/12.
//
//

#ifndef __MicroUI__UIDraggableBox__
#define __MicroUI__UIDraggableBox__

#include <iostream>

#include "UIBox.h"
#include "STColor4f.h"

class UIDraggableBox :
public UIBox
{
public:
    typedef void (*BeginDrag)(UIWidget* box1);
    typedef void (*EndDrag)();
    //
    // Constructor: Initialize a UI box with a given color.
    //
    UIDraggableBox(const STColor4f& color, BeginDrag box1, EndDrag box2);
    
    //
    // Display the box to the current OpenGL context.
    //
    // Overrides UIWidget::Display
    //
    virtual void Display();
    
    virtual void HandleMouseDown(const STPoint2& position);
    virtual void HandleMouseUp(const STPoint2& position);
    virtual void HandleMouseMove(const STPoint2& position);
    
private:
    
    // Color
    STColor4f mColor;
    BeginDrag mBeginDrag;
    EndDrag mEndDrag;
    STPoint2 currentPos;
};

#endif // __UIBOX_H__
