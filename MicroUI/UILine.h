//
//  UILine.h
//  MicroUI
//
//  Created by Khaled AlTurkestani on 10/15/12.
//
//

#ifndef __MicroUI__UILine__
#define __MicroUI__UILine__

#include <iostream>
#include "st.h"
#include "stgl.h"

class UILine
{
public:
    UILine(STPoint2 beingPoint, const STColor4f& color);
    
    void Display();
    
    void HandleMouseDown(const STPoint2& position);
    void HandleMouseUp(const STPoint2& position);
    void HandleMouseMove(const STPoint2& position);
    
    bool OnEndLine(STPoint2& position);
    bool OnBeginLine(STPoint2& position);
    
private:
    STPoint2 beginPoint;
    STPoint2 endPoint;
    STColor4f color;
    bool moveEnd;
    bool moveBegin;
    bool doneDrawing;
    //void moveLine(STPoint2& position);

};
    
#endif /* defined(__MicroUI__UILine__) */
