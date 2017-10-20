#include "GuiFrameWork.h"


int failure;
Widget *current_window;   //current window of the program. for example main menu
//window, load game window...

//create a new widget.  src is file with bmp image we'll load
Widget* ConstructWidget(char *src, Widget *father , int xCoordinate, int yCoordinate,
	int width, int height, void   (*do_on_press)(Widget *widgetNode,int x, int y)){
		
	extern int failure;
	Widget *widget = (Widget*)malloc(sizeof(Widget));
	if(widget == NULL){  //in case of malloc error:
		failure = 1;
		perror("ERROR:  malloc failed in function");
		return NULL;
	}

	widget->brotherWidget = NULL;
	widget->WidgetChildren = NULL; 
	widget->offsetRect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	if(widget->offsetRect == NULL){
		failure = 1;
		free(widget);
		perror("ERROR:  malloc failed in function");
		return NULL;
	}

	//from src we load a BMP image onto the surface
	widget->src =  src;
	if(father != NULL){  //adjusting coordinates in case father!= null
		widget->yCoordinate = yCoordinate + father->yCoordinate;
		widget->xCoordinate = xCoordinate + father->xCoordinate;
	}
	else{ //adjust coordinates in case fater==null
		widget->yCoordinate = yCoordinate;
		widget->xCoordinate = xCoordinate;
	}

	widget->width = width;
	widget->height = height;
	//adjust offsetRect parameters:
	(widget->offsetRect)->h = widget->height;
	(widget->offsetRect)->w = widget->width;
	(widget->offsetRect)->y = widget->yCoordinate;
	(widget->offsetRect)->x = widget->xCoordinate;

	widget->surface=NULL;
	//function do_on_press defines what we do in case of a mouse or keyboard click event
	widget ->do_on_press = do_on_press;
	
	widget->root = father;
	//case where this widget is the root 
	if(father == NULL)
	   return widget;

	//add this widget to it's father's list of children
	father->WidgetChildren = addChild(father, widget);
	//give default value of 3 to isMarked field. 3 means unmarked
	widget->isMarked = 3;
	return widget;
}

//we don't use this for creating buttons.
Widget* Construct_Window(char *src, Widget *father , int xCoordinate, int yCoordinate,
	int width, int height, void   (*do_on_press)(Widget *widgetNode,int x, int y)){
 
		Widget *curr = ConstructWidget(src,father , xCoordinate, yCoordinate,
	                       width,height, NULL);
		
		current_window = curr;
		return curr;
}

//construct a button:
Widget* Construct_Button(char *src, Widget *father , int xCoordinate, int yCoordinate,
	int width, int height, void   (*do_on_press)(Widget *widgetNode,int x, int y)){

		return ConstructWidget(src,father , xCoordinate, yCoordinate,width,height
			, do_on_press);
}


Widget* addChild(Widget *father, Widget *child)
{
	Widget *tempHead = NULL, *lastChild = NULL;
	Widget *fathersChildren = father->WidgetChildren;
    
	//case where father has no children:
	if(fathersChildren == NULL){
		fathersChildren = child;
		fathersChildren->brotherWidget = NULL;
	}
	else{  //put child as father's last child:
		for(tempHead = fathersChildren; tempHead != NULL; tempHead = tempHead->brotherWidget)
		{   
			lastChild = tempHead;
		} 	
		lastChild->brotherWidget = child;
	}
	return fathersChildren;
}

//construct the main window of the program.  checks if sdl functions failed
Widget* Construct_Main_Window(int WIDTH, int HEIGHT)
{
    Widget* main_window;
    main_window = ConstructWidget(NULL, NULL, 0, 0, MAIN_WINDOW_WIDTH,
   MAIN_WINDOW_HEIGHT, NULL);
  
   if(failure)  //in case allocation in ConstructWidget function failed
   {
	   free(main_window);
	   return NULL;
   }

   main_window->surface = SDL_SetVideoMode(main_window->width,main_window->height, 0,
	   SDL_HWSURFACE | SDL_DOUBLEBUF);
   if(main_window->surface == NULL)
   {
	   failure = 1;
	   perror("ERROR:  SDL_SetVideoMode failed");
	   return NULL;
   }

   if(SDL_FillRect(main_window->surface, NULL, SDL_MapRGB(main_window->surface->format,
       255, 255, 255)) == -1)
   {
	   failure = 1;
	   perror("ERROR:  SDL_FillRect failed");
	   return NULL;
   }
   
   return main_window;
}

//construct a label. a label is contained in a window.
Widget* Construct_Label(char *src, Widget *father , int xCoordinate, int yCoordinate,
	int width, int height, void   (*do_on_press)(Widget *widgetNode,int x, int y)){

		return ConstructWidget(src, father, xCoordinate, yCoordinate, width, height, NULL);
}


//loads optimized image in 32 bit 
SDL_Surface *Load_Optimized_Image( char *sourceFile ) 
{
	//int i =0;
	SDL_Surface* tempImage = NULL;
	SDL_Surface* final_Image = NULL;
	Uint32 color;

	//printf("src is %s\n", sourceFile);


	tempImage = SDL_LoadBMP( sourceFile );
  
	if( tempImage == NULL ){

		failure = 1;
		perror("ERROR:  SDL_LoadBMP  failed");
		return NULL;
	}

	final_Image = SDL_DisplayFormat( tempImage );
	SDL_FreeSurface( tempImage );

	if( final_Image == NULL ){
		failure = 1;
		perror("ERROR:  SDL_DisplayFormat failed  ");
		return NULL;
	}

  //use magnata color
	color = SDL_MapRGB( final_Image->format, 255, 0, 255 );
	if(SDL_SetColorKey( final_Image, SDL_SRCCOLORKEY, color) !=0)
	{
		failure = 1;
		perror("ERROR:  SDL_Setcolor failed  ");
		return NULL;
	}
	
	return final_Image;
}

//loads the image from src to the widget and paints it in the buffer(double buffer)
void Paint_Widget(Widget *widget_Node, Widget *screen)
{
	    if(widget_Node ==NULL)
			return;
		if(widget_Node->root != NULL &&  widget_Node->src != NULL){


			if(widget_Node->surface != NULL){       
				
				if (SDL_FillRect(widget_Node->surface,0,0) != 0) {  
					printf("ERROR: failed to draw rect: %s\n", SDL_GetError());
					failure = 1;
					return;
				}
			}


			widget_Node->surface = Load_Optimized_Image(widget_Node->src);
			if(failure)
				return;

			if(SDL_BlitSurface( widget_Node->surface, NULL, screen->surface ,
				widget_Node->offsetRect) == -1){
				failure = 1;
				perror("ERROR:  SDL_BlitSurface failed  ");
				return;
			}
		} 
}


//paints all widget in tree using DFS:  first children, then brother
void Paint_Gui_Tree(Widget *widget_Node, Widget *screen)
{
    Widget* widget_Node_Root;
	if(widget_Node == NULL)
     return;

	Paint_Widget(widget_Node, screen);
	if(failure)
       return;

	if(widget_Node->brotherWidget == NULL && widget_Node->WidgetChildren == NULL ){ 
		widget_Node_Root = widget_Node->root;	
		if( widget_Node_Root->brotherWidget != NULL  && widget_Node_Root != NULL )
		{  //we move on to the brotherWidget's subtree
			Paint_Gui_Tree(widget_Node_Root->brotherWidget, screen); 
			if(failure)    //check if SDL functions failed
              return;
		}
      return;
	}

	if(widget_Node->WidgetChildren == NULL){
		if(widget_Node->brotherWidget != NULL){
			Paint_Gui_Tree(widget_Node->brotherWidget, screen);
			if(failure)
               return;
		}
	}

	else{  //case where widget_node has children:
		Paint_Gui_Tree(widget_Node->WidgetChildren, screen);
		if(failure)
         return;
	}
}

//paints gui tree physically on the screen
void paint_Gui_Tree_on_Screen(Widget *screen){

	Paint_Gui_Tree(screen, screen);
	if(failure)  //in case one of the SDL functions failed
	   return;
	if(SDL_Flip(screen->surface) !=0){
		failure = 1;
		return;
	}
}

//FREE FUNCTIONS:
void free_Widget(Widget **widget_Node){
	
	if(widget_Node == NULL)
		return;
	if((*widget_Node)->WidgetChildren != NULL )
			free((*widget_Node)->WidgetChildren);
	if((*widget_Node)->brotherWidget != NULL )
			free((*widget_Node)->WidgetChildren);
	if((*widget_Node)->surface != NULL)
			SDL_FreeSurface( (*widget_Node)->surface);
	if((*widget_Node)->offsetRect != NULL)
			free((*widget_Node)->offsetRect);
	free(*widget_Node);
	if(*widget_Node!= NULL)
		*widget_Node= NULL;
	widget_Node = NULL;
}

void free_All_Widgets(Widget **widget_Node)
{
	
	if(widget_Node == NULL)
		return;
	if(*widget_Node == NULL)  
		return;
	if((*widget_Node)->brotherWidget != NULL){
		
		free_All_Widgets(&((*widget_Node)->brotherWidget));
		(*widget_Node)->brotherWidget = NULL;  
	}
	if((*widget_Node)->WidgetChildren != NULL){
		
		free_All_Widgets(&((*widget_Node)->WidgetChildren));
		(*widget_Node)->WidgetChildren = NULL;  
	}

	if( (*widget_Node)->brotherWidget == NULL && (*widget_Node)->WidgetChildren == NULL)
	{
		free_Widget(widget_Node);  //free widget function frees all the struct's fields
		return;
	}

}