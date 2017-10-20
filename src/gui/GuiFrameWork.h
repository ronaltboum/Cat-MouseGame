#ifndef GUI_FRAMEWORK_
#define GUI_FRAMEWORK_

#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>


#define MAIN_WINDOW_WIDTH  800
#define MAIN_WINDOW_HEIGHT 800
#define Widget struct Widget

Widget{
	Widget* root;             
	Widget* brotherWidget;    //the next widget
	Widget* WidgetChildren;  //the children of this widget
	SDL_Surface* surface;/* current component shown on screen */
	char *src;   //we load the image in this file onto the surface
	SDL_Rect *offsetRect; 
	int xCoordinate;   //x coordinate
	int yCoordinate;  //y coordinate
	int width;   //width of the rectangle
	int height;  //height of the rectange
	void   (*do_on_press)(Widget *widgetNode,int x, int y); //tells what to do if someone
	//clicked on the widget
	int isMarked;  //only relevant for buttons. isMarked==2 means that the button is marked
	//isMarked==3 means that the button is not marked
};

//construct a new widget.  we use this to create any kind of widgets: labels,button
//panels, windows etc
Widget* ConstructWidget(char *src, Widget *father , int xCoordinate, int yCoordinate,
	int width, int height, void   (*do_on_press)(Widget *widgetNode,int x, int y));
//constructs a window. for example main menu window, load game menu, type selection menu...
Widget* Construct_Window(char *src, Widget *father , int xCoordinate, int yCoordinate,
	int width, int height, void   (*do_on_press)(Widget *widgetNode,int x, int y));
//consturct a label
Widget* Construct_Label(char *src, Widget *father , int xCoordinate, int yCoordinate,
	int width, int height, void   (*do_on_press)(Widget *widgetNode,int x, int y));
//adds Child to father's list of children
Widget* addChild(Widget *father, Widget *Child);
//construct the main window of the program
Widget* Construct_Main_Window(int WIDTH, int HEIGHT);
//construct a button
Widget* Construct_Button(char *src, Widget *father , int xCoordinate, int yCoordinate,
	int width, int height, void   (*do_on_press)(Widget *widgetNode,int x, int y));
//loads optimized image in 32 bit 
SDL_Surface *Load_Optimized_Image( char *sourceFile );
//paints all widget in tree using DFS
void Paint_Gui_Tree(Widget *widget_Node, Widget *screen);
//paint widget to buffer
void Paint_Widget(Widget *widget_Node, Widget *screen);
//paints gui tree physically on the screen
void paint_Gui_Tree_on_Screen(Widget *screen);


//FREE FUNCTIONS:
void free_Widget(Widget **widget_Node);
//frees all the widgets in the gui tree. starts from the bottom of the subtree of the
//rightmost brother
void free_All_Widgets(Widget **widget_Node);

#endif