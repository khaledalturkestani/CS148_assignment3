// UIButton.h
#ifndef __UIBUTTON_H__
#define __UIBUTTON_H__

/**
* A UIButton is a widget with a simple
* label that responds to mouse events.
*/

#include "UIWidget.h"
#define IDLE 1
#define OVER 2
#define DOWN 3

class UIButton :
    public UIWidget
{
public:
    // Type of callbacks to handle button-press "fire" events.
    typedef void (*FireCallback)(UIButton* button);
    typedef void (*CaptureCallback)(UIWidget* capture);
    typedef void (*ReleaseCallback)();

    //
    // Constructor: Initialize a UI button with
    // a given font face and label text.
    //
    UIButton(STFont* font,
             const std::string& text,
             FireCallback callback,
             CaptureCallback capture,
             ReleaseCallback release);

    /** CS 148 TODO:
    *
    *   Your button will need to override some or
    *   all of the virtual functions in UIWidget
    *   in order to display itself and respond
    *   to mouse events.
    */
    
    virtual void Display();
    
    virtual void HandleMouseDown(const STPoint2& position);
    virtual void HandleMouseUp(const STPoint2& position);
    virtual void HandleMouseEnter();
    virtual void HandleMouseLeave();
    virtual void HandleMouseMove(const STPoint2& position);
    
private:
    // Font to use for text
    STFont* mFont;

    // Text
    std::string mText;

    // "Fire" event callback
    FireCallback mCallback;
    CaptureCallback mCaptureCallback;
    ReleaseCallback mReleaseCallback;

    /** CS 148 TODO:
    *
    *   Your button will need some member variables
    *   to hold its state.
    */
    STPoint2 centerText();
    STColor4f getColor();
    void printState();
    bool mouseDownInside;
    bool mouseDown;
    bool insideButton;
    int state;
};

#endif // __UIBUTTON_H__
