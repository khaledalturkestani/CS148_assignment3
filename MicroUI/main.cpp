// main.cpp
// Starter code for CS 148 Assignment 3.

// Include libst headers for using OpenGL and GLUT.
#include "st.h"
#include "stgl.h"
#include "stglut.h"

// Include headers for UI clases.
#include "UIBox.h"
#include "UIDraggableBox.h"
#include "UIButton.h"
#include "UILabel.h"
#include "UIWidget.h"
#include "UILine.h"

// Include header for parsing config and line editor files
#include "parseConfig.h"

#define WIN_WIDTH 512
#define WIN_HEIGHT 512

// Globals used by this application.
// As a rule, globals are Evil, but this is a small application
// and the design of GLUT makes it hard to avoid them.

// Font to use for text in the UI.
static STFont* gFont = NULL;

// List of widgets being displayed.
static std::vector<UIWidget*> gWidgets;
static std::vector<UILine*> lines;

// Window size so we can properly update the UI.
static int gWindowSizeX = 0;
static int gWindowSizeY = 0;

// Background images
static STImage* gBgIm1;
static STImage* gBgIm2;

#ifndef BUFSIZ
#define BUFSIZ  512
#endif
// Background image filenames parsed from config file
static char gImage1Fname[BUFSIZ];
static char gImage2Fname[BUFSIZ];

// Line editor load/save filenames parsed from config file
static char gSaveFname[BUFSIZ];
static char gLoadFname[BUFSIZ];

// My global variables
static UIWidget* currentWidget = NULL;
static UIWidget* currentCaptured = NULL;
static UIWidget* currentDragged = NULL;
UILine *currentLine;
static int colorTracker = 0;

// Add a widget to the list of widgets in the window.
// Also sets the rectangle of the widget to the one specified.
void AddWidget(UIWidget* widget, const UIRectangle& rectangle)
{
    widget->SetRectangle(rectangle);
    gWidgets.push_back(widget);
}

// Creates any widgets or other objects used for displaying lines.
// lineEndpt1 and lineEndpt2 should both be coordindates RELATIVE TO THE IMAGE
// THEY ARE DRAWN TO. This means that if the lower left of one image is at
// (15,15), if lineEndpt1 is (10,10), it would actually be drawn at window
// coordinates (25,25).
//
// The imageChoice parameter tells you whether a line is being drawn to both images,
// or to a single images. When the user is manually adding lines, this parameter
// should be BOTH_IMAGES. When this function is called by loadLineEditorFile
// (already implemented), imageChoice will take on the value of either IMAGE_1
// or IMAGE_2.
void AddNewLine(STPoint2 lineEndpt1, STPoint2 lineEndpt2, ImageChoice imageChoice)
{
    /** CS148 TODO : ONLY REQUIRED FOR EXTRA CREDIT
     *
     * Use this to create any widgets and objects you use to display and edit lines.
     */
}

// Setup routnine.
// As you progress with implementing the assignment,
// you will want to modify this routine to create and
// test your new widget types.

// Capture mouse callback function.
void CaptureMouse(UIWidget *widget)
{
    currentCaptured = widget;
}

// Release mouse callback function.
void ReleaseMouse()
{
    currentCaptured = NULL;
}

// Pushbutton testing Fire callback function
void Firecallback(UIButton * button)
{
    printf("\n!!!!!!!! FIRE !!!!!!!!\n\n");
}

// Draws all lines in the "lines" vector.
void drawLines()
{
    int numLines = (int) lines.size();
    for (int j = 0; j < numLines; ++j) {
        UILine* line = lines[j];
        line->Display();
    }
}

// Delete lines callback function.
void DeleteCallback(UIButton * button)
{
    if (lines.size() > 0) {
        lines.pop_back();
        drawLines();
    }
}

// Begin dragging callback function
void BeginDrag(UIWidget *widget)
{
    currentDragged = widget;
}

// End dragging callback function
void EndDrag()
{
    currentDragged = NULL;
}

// Check if mouse is on the end point of an of the lines drawn
bool onEndOfLine(STPoint2& mousePos)
{
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i]->OnEndLine(mousePos)){
            currentLine = lines[i];
            return true;
        }
    }
    return false;
}

// Check if mouse is on the beginning point of an of the lines drawn
bool onBeginOfLine(STPoint2& mousePos)
{
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i]->OnBeginLine(mousePos)){
            currentLine = lines[i];
            return true;
        }
    }
    return false;
}

// Iterates through a collection of colors every time it's called when
// drawing a new line and returns a color
STColor4f setLineColor()
{
    if (colorTracker == 0){
        colorTracker++;
        return STColor4f(1, 0, 0, 1);
    } else if (colorTracker == 1) {
        colorTracker++;
        return STColor4f(0, 1, 0, 1);
    } else if (colorTracker == 2) {
        colorTracker++;
        return STColor4f(0, 0, 1, 1);
    } else if (colorTracker == 3) {
        colorTracker++;
        return STColor4f(1, 1, 0, 1);
    } else if (colorTracker == 4) {
        colorTracker++;
        return STColor4f(0, 1, 1, 1);
    } else {
        colorTracker = 0;
        return STColor4f(1, 0, 1, 1);
    }
}


void CreateWidgets()
{
    // Dgraggable Box
    //AddWidget(new UIDraggableBox(STColor4f(1,0,0,1), BeginDrag, EndDrag), UIRectangle(STPoint2(10,20), STPoint2(60, 50)));
    //AddWidget(new UILabel(gFont, "Hello World!"), UIRectangle(STPoint2(200, 200), STPoint2(110, 110)));
    //AddWidget(new UIBox(STColor4f(1,0,0,1)), UIRectangle(STPoint2(30, 30), STPoint2(80, 60)));
    
    // Push Button Test!
    //AddWidget(new UIButton(gFont, "Khaled ROCKS", Firecallback, CaptureMouse, ReleaseMouse), UIRectangle(STPoint2(156, 156), STPoint2(356, 356)));
    
    // Line Editor Initializations
    AddWidget(new UILabel(gFont, "Edit Lines Here!"), UIRectangle(STPoint2(170, 450), STPoint2(356, 512)));
    AddWidget(new UIButton(gFont, "Quit", Firecallback, CaptureMouse, ReleaseMouse),
              UIRectangle(STPoint2(156, 10), STPoint2(356, 60)));
    AddWidget(new UIButton(gFont, "Delete Last", DeleteCallback, CaptureMouse, ReleaseMouse),
              UIRectangle(STPoint2(10, 10), STPoint2(140, 60)));
    AddWidget(new UIDraggableBox(STColor4f(1,0,0,1), BeginDrag, EndDrag), UIRectangle(STPoint2(10,200), STPoint2(110, 300)));
    AddWidget(new UIDraggableBox(STColor4f(0,0,1,1), BeginDrag, EndDrag), UIRectangle(STPoint2(110,300), STPoint2(210, 400)));
}

// Display the UI, including all widgets.
void DisplayCallback()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Clear the window.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw background
    glEnable(GL_TEXTURE_2D);
    
    //gBgIm1->Draw();

    // Loop through all the widgets in the user
    // interface and tell each to display itself.
    int numWidgets = (int) gWidgets.size();
    for (int ii = 0; ii < numWidgets; ++ii) {
        UIWidget* widget = gWidgets[ii];
        widget->Display();
    }
    
    // Draw lines
    drawLines();
    
    glutSwapBuffers();
}

//
// Reshape the window and record the size so
// that we can use it in the mouse callbacks.
//
void ReshapeCallback(int w, int h)
{
    gWindowSizeX = w;
    gWindowSizeY = h;

    glViewport(0, 0, gWindowSizeX, gWindowSizeY);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0, gWindowSizeX, 0, gWindowSizeY, -1., 1.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MouseClickCallback(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        UIWidget* widget = NULL;
        STPoint2 mousePos = STPoint2(x, gWindowSizeY-y);
        if (currentDragged != NULL) { // Handle Draggable box
            if (state == GLUT_DOWN) {
                currentDragged->HandleMouseDown(mousePos);
            }
            if (state == GLUT_UP) {
                currentDragged->HandleMouseUp(mousePos);
            }
        } else if (currentCaptured != NULL) { // Handle captured button
            if (state == GLUT_DOWN) {
                currentCaptured->HandleMouseDown(mousePos); //Captured button
            }
            if (state == GLUT_UP) {
                currentCaptured->HandleMouseUp(mousePos); //Captured button
            }
        } else {
            int numWidgets = (int) gWidgets.size();
            for (int i = 0; i < numWidgets; ++i) {
                if (gWidgets[i]->HitTest(mousePos)) widget = gWidgets[i];
            }
            if (widget != NULL && state == GLUT_DOWN) { // Handle widget on mouse down
                widget->HandleMouseDown(mousePos);
            }
            if (widget != NULL && state == GLUT_UP) { // Handle widget on mouse up
                widget->HandleMouseUp(mousePos);
            }
            if (widget == NULL && state == GLUT_DOWN && onEndOfLine(mousePos)) { // When mouse clicks on end of line
                currentLine->HandleMouseDown(mousePos);
                printf("one END!\n");
            } else if (widget == NULL && state == GLUT_DOWN && onBeginOfLine(mousePos)) { // When mouse clicks on beginning of a line
                currentLine->HandleMouseDown(mousePos);
                printf("one BEGIN!\n");
            } else if (widget == NULL && state == GLUT_DOWN) { // When to draw a line (When mouse hits the baackground)
                STColor4f color = setLineColor();
                UILine * line = new UILine(mousePos, color);
                lines.push_back(line);
                currentLine = line;
                currentLine->HandleMouseDown(mousePos);
                printf("DRAWING!\n");
            } else if (widget == NULL && state == GLUT_UP) { // When done drawing or editing a line
                currentLine->HandleMouseUp(mousePos);
            }
        }
    }
}

void MousePassiveCallback(int x, int y) {
    UIWidget* widget = NULL;
    STPoint2 mousePos = STPoint2(x, gWindowSizeY-y);
    int numWidgets = (int) gWidgets.size();
    for (int i = 0; i < numWidgets; ++i) {
        if (gWidgets[i]->HitTest(mousePos)) widget = gWidgets[i];
    }
    if (widget != NULL) {
        if (currentWidget == NULL) {
            currentWidget = widget;
            currentWidget->HandleMouseEnter();
        } else if (widget != currentWidget) {
            currentWidget->HandleMouseLeave();
            currentWidget = widget;
            currentWidget->HandleMouseEnter();
        }
    } else if (widget == NULL && currentWidget != NULL) {
        currentWidget->HandleMouseLeave();
        currentWidget = NULL;
    }
}

void MouseDragCallback(int x, int y) {
    STPoint2 mousePos = STPoint2(x, gWindowSizeY-y);
    if (currentLine != NULL) { // Drag line
        currentLine->HandleMouseMove(mousePos);
    } else if (currentDragged != NULL) {
        currentDragged->HandleMouseMove(mousePos);
    } else if (currentCaptured != NULL) {
        currentCaptured->HandleMouseMove(mousePos);
    } else {
        UIWidget* widget = NULL;
        int numWidgets = (int) gWidgets.size();
        for (int i = 0; i < numWidgets; ++i) {
            if (gWidgets[i]->HitTest(mousePos)) widget = gWidgets[i];
        }
        if (widget != NULL) widget->HandleMouseMove(mousePos);
    }
}

// Initialize the application, loading resources,
// setting state, and creating widgets.
void Initialize()
{
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    gFont = new STFont("resources/arial.ttf", 24);

    CreateWidgets();
}

int main(int argc, char** argv)
{
    // Initialize GLUT.
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(20, 20);
    glutInitWindowSize(
        WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("CS148 Assignment 3");

    // Initialize the UI.
    Initialize();

    // Parse config file
    parseConfigFile(
        "config.txt",
        gImage1Fname,
        gImage2Fname,
        gSaveFname,
        gLoadFname,
        &gBgIm1,
        &gBgIm2);

    // Register GLUT callbacks and enter main loop.
    glutDisplayFunc(DisplayCallback);
    glutReshapeFunc(ReshapeCallback);
   
    // My event callbacks
    glutMouseFunc(MouseClickCallback);
    glutPassiveMotionFunc(MousePassiveCallback);
    glutMotionFunc(MouseDragCallback);

    
    glutMainLoop();

    // Cleanup code should be called here.
    delete gBgIm1;
    delete gBgIm2;

    return 0;
}
