#include "GuiHandler.h"    

int quit;  //when quit==1 we leave the program
Widget *main_window;  //the screen
int last_world =1;
Game* MainGame;


/////////////////////////   DISPLAY MENU AND BUTTON CLICK HANDELING FUNCTIONS   ///////////
void display_Main_Menu(){     

	extern int failure;  extern Widget *current_window;
	Widget* main_menu_window = NULL;     Widget* newGame; //Widget* loadGame; Widget* game_logo; 
	//Widget* createGame; Widget* editGame;  Widget* quitGame;
	//ConstructWidget(src, father, xCoordinate, yCoordinate, width, height, NULL);

	main_menu_window = Construct_Window("images/orangePaint.bmp",main_window, 0, 0, 200, 200,NULL);
	if(failure)
		return;
	//a label is contained in a window. 
	Construct_Label("images/Cat&MouseLogo.bmp", main_menu_window ,300,100, 300, 250,NULL);
	if(failure)
		return;
	newGame = Construct_Button("images/bNew Game.bmp", main_menu_window ,350,200, 158,44
		,display_cat_type_selection_menu);
	if(failure) {return;}

	Construct_Button("images/gLoadGame.bmp", main_menu_window ,350,300, 158,44
		,display_load_game_selection_menu);
	if(failure) {return;}

	Construct_Button("images/gCreateGame.bmp", main_menu_window ,350,400, 158,44
		,display_world_builder_tool);
	if(failure) {return;}

	Construct_Button("images/gEditGame.bmp", main_menu_window ,350,500, 158,44
		,display_edit_game_selection_menu);
	if(failure) {return;}

	Construct_Button("images/gQuit.bmp", main_menu_window ,350,600, 158,44
		,handle_quit);
	if(failure) {return;}
	
	//newGame is marked in the default state
	newGame->isMarked = 2;
	paint_Gui_Tree_on_Screen(main_window);
	if(failure)
		return;
	current_window = main_menu_window;  //update the current_window global field to be the 
	//main menu window
}


//event handle functions
void display_cat_type_selection_menu (Widget *widgetNode, int x, int y){

	extern int failure;  extern Widget *current_window;
	Widget *cat_type_selection_menu;    Widget *choose_your_cat_logo;      
	Widget *gback_button;     Widget *bHuman_button;   Widget *gMachine_button;

	//logic updates:
	LoadDetailsOfGame("worlds/world_1.txt");
	//discard main menu first:
	free_All_Widgets( &(main_window->WidgetChildren) );
	main_window->WidgetChildren = NULL;
	
	//cat_type_selection_menu's father is new game button in main menu window
	cat_type_selection_menu= Construct_Window("images/orangePaint.bmp",main_window, 0, 0, 200,
		200,NULL);
	if(failure)
		return;
	//update the current window field
	current_window = cat_type_selection_menu;

	choose_your_cat_logo = Construct_Label("images/Choose Your Cat.bmp", cat_type_selection_menu,
		200, 100, 300,250, NULL);
	if(failure)
		return;
	choose_your_cat_logo->isMarked = 3;  

	bHuman_button = Construct_Button("images/bHuman.bmp", cat_type_selection_menu,
		250, 300, 233,59, display_mouse_type_selection_menu); 
	if(failure)
		return;
	//bHuman_button is marked in the default state
	bHuman_button->isMarked = 2;

	gMachine_button = Construct_Button("images/gMachine.bmp", cat_type_selection_menu,
		250, 500, 234,59, handle_machine_on_cat_type_selection_menu);
	if(failure)
		return;
	//gMachine_button isn't marked in the default state
    gMachine_button->isMarked = 3;

	gback_button = Construct_Button("images/gBack.bmp", cat_type_selection_menu,
		250, 700, 234,59, handle_back_on_cat_type_selection_menu);
	if(failure)
		return;
	//gback_button isn't marked in the default state
	gback_button->isMarked = 3;

	paint_Gui_Tree_on_Screen(main_window);
	if(failure)
		return;
}

//displays the mouse type selection menu
void display_mouse_type_selection_menu (Widget *widgetNode, int x, int y){

	extern int failure;  extern Widget *current_window;

	Widget *grandFather_logo;
	Widget *mouse_type_selection_menu;    Widget *choose_your_mouse_logo;      
	Widget *gback_button;     Widget *bHuman_button;   Widget *gMachine_button;
	mouse_type_selection_menu = NULL;
	//cat is human
	//cat machine level is father of done button, which is father of mouse type selection menu
	//cat type selection menu is father of human button, which is father of mouse type seleciton men
	//so i can find out if the cat is human or machine, by checking mouse type selction menu's
	//grandfather's first child (the logo)
	if(widgetNode->root != NULL){
		if( ((widgetNode->root)->WidgetChildren) !=NULL)
			grandFather_logo =  ( ( (widgetNode->root) )->WidgetChildren);
	}
	
	if(!strcmp(grandFather_logo->src,"images/Choose Your Cat.bmp")){

		MainGame->cat_player->Human_or_Machine = HUMAN;
		

		//now need to update the marked buttons in choose cat type selection menu:
		widgetNode->isMarked = 99;  ///////UTILITY FUNCTION TO REMARK BROTHERS
		//unmark all the other buttons in cat_type_selection_menu except the machine button
		update_marked_button_in_window(widgetNode->root);
		//now need to physically mark in blue the machine button in the previous menu
		if(grandFather_logo->brotherWidget != NULL){
					grandFather_logo->brotherWidget->src = "images/bHuman.bmp";
					grandFather_logo->brotherWidget->brotherWidget->src
						= "images/gMachine.bmp";	
		}

		mouse_type_selection_menu= Construct_Window("images/orangePaint.bmp",widgetNode,
		-250, -300, 200,200,NULL);  //just changed to negative coordinates
		if(failure) {return;}
	}
	else if(!strcmp(grandFather_logo->src, "images/Choose Cat Skill Level Logo.bmp")){

		MainGame->cat_player->Human_or_Machine = MACHINE;

		mouse_type_selection_menu= Construct_Window("images/orangePaint.bmp",widgetNode,
		-250, -500, 200,200,NULL);  
		if(failure) {return;}
	}
	//mouse_type_selection_menu's father is human button in cat_type_selection_menu
	
	//update the current window field
	current_window = mouse_type_selection_menu;

	choose_your_mouse_logo = Construct_Label("images/Choose Your Mouse.bmp", mouse_type_selection_menu,
		200, 100, 300,200, NULL);
	if(failure)
		return;
	choose_your_mouse_logo->isMarked =3;

	bHuman_button = Construct_Button("images/bHuman.bmp", mouse_type_selection_menu,
		250, 300, 233,59, paint_board_from_Game_fields); 
	if(failure)
		return;
	bHuman_button->isMarked =2;

	gMachine_button = Construct_Button("images/gMachine.bmp", mouse_type_selection_menu,
		250, 500, 234,59, handle_machine_on_mouse_type_selection_menu);
	if(failure)
		return;
	gMachine_button->isMarked = 3;

	gback_button = Construct_Button("images/gBack.bmp", mouse_type_selection_menu,
		250, 700, 234,59, handle_back_button);
	if(failure)
		return;
	gback_button->isMarked = 3;

	paint_Gui_Tree_on_Screen(main_window);
}

//handles the event of pressing the back button in mouse type select menu, also in
//cat_skill_level_menu 
void handle_back_button(Widget *widget, int x, int y){

	extern int failure;  extern Widget *current_window;
	//mouse back button's father is mouse selcet type menu, his father is human button
	//on cat type select menu. we need to discard mouse select type menu and his subtree
	Widget *temp;
	
	//for tab, need to find out which button was marked in the previous window


	temp = (current_window->root);  //temp is human button on cat select type menu
	//update the current_window to be the cat_type_selection_menu
	current_window = (current_window->root)->root;
	
	free_All_Widgets( &(temp->WidgetChildren) );  //temp->WidgetChildren is mouse menu
	if(failure) {return;}

	temp->WidgetChildren = NULL; //human button's children are now null
	paint_Gui_Tree_on_Screen(main_window);
	if(failure)	{return;}

}

//handle click on back button in cat selection type menu
void handle_back_on_cat_type_selection_menu(Widget *widget, int x, int y){

	extern int failure;  extern Widget *current_window;
//cat_type's father is new game button in main menu window. 
	current_window = main_window;
	//discard cat type selection menu:
	free_All_Widgets(&main_window->WidgetChildren);
	if(failure) {return;}
	main_window->WidgetChildren = NULL;
	display_Main_Menu();  //current_window is updated to be the main menu window in this func
	if(failure) {return;}
	
}

//handle mouse click on machine button in cat selection type menu
void handle_machine_on_cat_type_selection_menu(Widget *widgetNode, int x, int y){

	extern int failure;  extern Widget *current_window;

	Widget *cat_skill_level_menu;    Widget *Choose_Cat_Skill_Level_Logo;      
	Widget *gback_button;    Widget *gdone_button;    Widget *up_button; 
	Widget *down_button;     Widget *level_5_blue_button;
	
	//cat_skill_level_menu's father is machine button in cat_type_selection_menu
    //widgetNode is actually machine buttone in cat_type_selection_menu. will be used
	//in handle events function

	//cat is computer
	MainGame->cat_player->Human_or_Machine = MACHINE;

	//first need to update that on the previous menu which is cat_type_selection_menu, 
	//the current button marked is machine button

	widgetNode->isMarked = 99;  ///////UTILITY FUNCTION TO REMARK BROTHERS
	//unmark all the other buttons in cat_type_selection_menu except the machine button
	update_marked_button_in_window(widgetNode->root);
	//now need to physically mark in blue the machine button in the previous menu
	if(widgetNode->root != NULL){
		if( widgetNode->root->WidgetChildren != NULL){
			if( strcmp(widgetNode->root->WidgetChildren->src,
				"images/Choose Your Cat.bmp") ==0 ){
					widgetNode->root->WidgetChildren->brotherWidget->src = 
						"images/gHuman.bmp";
					widgetNode->root->WidgetChildren->brotherWidget->brotherWidget->src
						= "images/bMachine.bmp";
			}
		}
	}


	cat_skill_level_menu = Construct_Window("images/orangePaint.bmp",widgetNode,
		-245, -495, 800,800,NULL);  //just changed to negative coordinates
	if(failure)		{return;}

	//update the current window field
	current_window = cat_skill_level_menu;

	Choose_Cat_Skill_Level_Logo = Construct_Label("images/Choose Cat Skill Level Logo.bmp",
		cat_skill_level_menu, 200, 100, 300,200, NULL);
    if(failure)		{return;}
	Choose_Cat_Skill_Level_Logo->isMarked = 3;

	level_5_blue_button = Construct_Button("images/blevel 5.bmp", cat_skill_level_menu,
		250, 300, 204,59, handle_level_button); 
	if(failure)		{return;}
	level_5_blue_button->isMarked = 2;

	up_button = Construct_Button("images/up button.bmp", cat_skill_level_menu,
		455, 300, 32,30, handle_up_button_on_select_machine_level);
    if(failure)		{return;}
	up_button->isMarked = 3;

	down_button = Construct_Button("images/down button.bmp", cat_skill_level_menu,
		455, 330, 32,29, handle_down_button_on_select_machine_level);
    if(failure)		{return;}
	down_button->isMarked = 3;

	gdone_button = Construct_Button("images/gdone.bmp", cat_skill_level_menu,
		250, 500, 234,59, handle_done_button_on_cat_select_machine_level_menu);
	if(failure)		{return;}
	gdone_button->isMarked = 3;

	gback_button = Construct_Button("images/gBack.bmp", cat_skill_level_menu,
		250, 700, 234,59, handle_back_button);
	if(failure)		{return;}
	gback_button->isMarked = 3;

    paint_Gui_Tree_on_Screen(main_window);
    if(failure)		{return;}

}

//handles machine on mouse type selection menu
void handle_machine_on_mouse_type_selection_menu(Widget *widgetNode, int x, int y){

	extern int failure;  extern Widget *current_window;

	Widget *mouse_skill_level_menu;    Widget *Choose_Mouse_Skill_Level_Logo;      
	Widget *gback_button;    Widget *gdone_button;    Widget *up_button; 
	Widget *down_button;     Widget *level_5_blue_button;
	
	//mouse_skill_level_menu's father is machine button in cat_type_selection_menu
    //widgetNode is actually machine buttone in cat_type_selection_menu. will be used
	//in handle events function

	//mouse is computer
	MainGame->mouse_player->Human_or_Machine = MACHINE;

	//first need to update that on the previous menu which is cat_type_selection_menu, 
	//the current button marked is machine button

	widgetNode->isMarked = 99;  ///////UTILITY FUNCTION TO REMARK BROTHERS
	//unmark all the other buttons in cat_type_selection_menu except the machine button
	update_marked_button_in_window(widgetNode->root);
	//now need to physically mark in blue the machine button in the previous menu
	if(widgetNode->root != NULL){
		if( widgetNode->root->WidgetChildren != NULL){
			if( strcmp(widgetNode->root->WidgetChildren->src,
				"images/Choose Your Mouse.bmp") ==0 ){
					widgetNode->root->WidgetChildren->brotherWidget->src = 
						"images/gHuman.bmp";
					widgetNode->root->WidgetChildren->brotherWidget->brotherWidget->src
						= "images/bMachine.bmp";
			}
		}
	}

	mouse_skill_level_menu = Construct_Window("images/orangePaint.bmp",widgetNode,
		-245, -495, 800,800,NULL);  
	if(failure)		{return;}

	//update the current window field
	current_window = mouse_skill_level_menu;

	Choose_Mouse_Skill_Level_Logo = Construct_Label("images/Choose Mouse Skill Level Logo.bmp",
		mouse_skill_level_menu, 200, 100, 300,200, NULL);
    if(failure)		{return;}
	Choose_Mouse_Skill_Level_Logo->isMarked = 3;

	level_5_blue_button = Construct_Button("images/blevel 5.bmp", mouse_skill_level_menu,
		250, 300, 204,59, handle_level_button); 
	if(failure)		{return;}
	level_5_blue_button->isMarked = 2;

	up_button = Construct_Button("images/up button.bmp", mouse_skill_level_menu,
		455, 300, 32,30, handle_up_button_on_select_machine_level);
    if(failure)		{return;}
	up_button->isMarked = 3;

	down_button = Construct_Button("images/down button.bmp", mouse_skill_level_menu,
		455, 330, 32,29, handle_down_button_on_select_machine_level);
    if(failure)		{return;}
	down_button->isMarked = 3;

	gdone_button = Construct_Button("images/gdone.bmp", mouse_skill_level_menu,
		250, 500, 234,59, handle_done_button_on_mouse_select_machine_level_menu);
	if(failure)		{return;}
	gdone_button->isMarked = 3;

	gback_button = Construct_Button("images/gBack.bmp", mouse_skill_level_menu,
		250, 700, 234,59, handle_back_button); 
	if(failure)		{return;}
	gback_button->isMarked = 3;

    paint_Gui_Tree_on_Screen(main_window);
    if(failure)		{return;}

}


//handle mouse click on level button
void handle_level_button(Widget *widgetNode, int x, int y){

	if(widgetNode == NULL)
		return;
	if (widgetNode->isMarked == 2)
		return;

	if ( strcmp(widgetNode->src, "images/glevel 1.bmp") == 0)
		widgetNode->src = "images/blevel 1.bmp";
	else if ( strcmp(widgetNode->src, "images/glevel 2.bmp") == 0)
		widgetNode->src="images/blevel 2.bmp";
	else if ( strcmp(widgetNode->src, "images/glevel 3.bmp") == 0)
		widgetNode->src="images/blevel 3.bmp";
	else if ( strcmp(widgetNode->src, "images/glevel 4.bmp") == 0)
		widgetNode->src="images/blevel 4.bmp";
	else if ( strcmp(widgetNode->src, "images/glevel 5.bmp") == 0)
		widgetNode->src="images/blevel 5.bmp";
	else if ( strcmp(widgetNode->src, "images/glevel 6.bmp") == 0)
		widgetNode->src="images/blevel 6.bmp";
	else if ( strcmp(widgetNode->src, "images/glevel 7.bmp") == 0)
		widgetNode->src="images/blevel 7.bmp";
	else if ( strcmp(widgetNode->src, "images/glevel 8.bmp") == 0)
		widgetNode->src="images/blevel 8.bmp";
	else if ( strcmp(widgetNode->src, "images/glevel 9.bmp") == 0)
		widgetNode->src="images/blevel 9.bmp";


	widgetNode->isMarked = 2 ; //mark the level button
	//now need to unmark all the other buttons:

	widgetNode->brotherWidget->brotherWidget->brotherWidget->isMarked = 3; //done button
	widgetNode->brotherWidget->brotherWidget->brotherWidget->src="images/gdone.bmp";
	widgetNode->brotherWidget->brotherWidget->brotherWidget->brotherWidget->isMarked=3;
	widgetNode->brotherWidget->brotherWidget->brotherWidget->brotherWidget->src="images/gBack.bmp";

	paint_Gui_Tree_on_Screen(main_window);
}

//handle done button in cat skill level selection menu
void handle_done_button_on_cat_select_machine_level_menu (Widget *widget, int x, int y){
	//widget is done button. widget's root is cat select machine level menu. widget's root's
	//second child is "images/blevel 5.bmp" or some other level
	Widget *cat_machine_level;  //Widget *cat_machine_menu; 
	char level;

	//first we update markings in previous window:
	widget->isMarked = 99;  ///////UTILITY FUNCTION TO REMARK BROTHERS
	update_marked_button_in_window(widget->root);
	//now we need to physically change the images in the previous window:
	update_marking_because_mouse_click(widget);


	//cat_machine_menu = widget->root;
	cat_machine_level = ( (widget->root)->WidgetChildren)->brotherWidget;
	
	level = cat_machine_level->src[14]; //14th index
	//update the cat's skill level
	MainGame->cat_player->skill_level = (int)(level)-48;  //level 5 is 53
	
	display_mouse_type_selection_menu(widget, -250,-1200);
}


//handle done button in mouse skill level selection menu
void handle_done_button_on_mouse_select_machine_level_menu (Widget *widget, int x, int y){
	//widget is done button. widget's root is mouse select machine level menu. widget's root's
	//second child is "images/blevel 5.bmp" or some other level
	Widget *mouse_machine_level;   //Widget *mouse_machine_menu;
	char level;

	//first we update markings in previous window:
	widget->isMarked = 99;  ///////UTILITY FUNCTION TO REMARK BROTHERS
	update_marked_button_in_window(widget->root);
	//now we need to physically change the images in the previous window:
	update_marking_because_mouse_click(widget);


	//mouse_machine_menu = widget->root;
	mouse_machine_level = ( (widget->root)->WidgetChildren)->brotherWidget;
	
	level = mouse_machine_level->src[14]; //14th index
	//update the cat's skill level
	MainGame->mouse_player->skill_level = (int)(level)-48;  //level 5 is 53
	
	//display_mouse_type_selection_menu(widget, -250,-1200);
	paint_board_from_Game_fields(widget, -250, -2000);
}

//handle click on up button in select machine level
void handle_up_button_on_select_machine_level (Widget *widget, int x, int y){

	//blevel 5 button's brother is up_button whose brother is down_button. 
	//cat_skill_level_menu is father to all of the above. it's first child is blevel 6 button
	//Widget *skill_level_menu;   either cat_skill_level_menu or mouse_skill_level_menu
	Widget *level_number;       //skill_level_menu's first child which contains the level
	char *level_src;

	//skill_level_menu = widget->root;
	level_number = (((widget->root)->WidgetChildren)->brotherWidget);
	level_src = level_number->src;
	if( strcmp(level_src,"images/blevel 1.bmp") ==0){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 2.bmp";
	}
	else if( strcmp(level_src,"images/blevel 2.bmp") ==0){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 3.bmp";
	}
	else if( strcmp(level_src,"images/blevel 3.bmp") ==0){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 4.bmp";
	}
	else if( strcmp(level_src,"images/blevel 4.bmp") ==0){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 5.bmp";
	}
	else if( strcmp(level_src,"images/blevel 5.bmp") ==0){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 6.bmp";
	}
	else if( strcmp(level_src,"images/blevel 6.bmp") ==0){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 7.bmp";
	}
	else if( strcmp(level_src,"images/blevel 7.bmp") ==0){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 8.bmp";
	}
	else if( strcmp(level_src,"images/blevel 8.bmp") ==0){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 9.bmp";
	}
	paint_Gui_Tree_on_Screen(main_window);
}

//handle click on  down in select machine level
void handle_down_button_on_select_machine_level (Widget *widget, int x, int y){

	//Widget *skill_level_menu;   either cat_skill_level_menu or mouse_skill_level_menu
	Widget *level_number;       //skill_level_menu's first child which contains the level
	char *level_src;

	//skill_level_menu = widget->root;
	level_number = (((widget->root)->WidgetChildren)->brotherWidget);
	level_src = level_number->src;
	if( strcmp(level_src, "images/blevel 9.bmp") ==0 ){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 8.bmp";
	}
	else if( strcmp(level_src, "images/blevel 8.bmp") ==0 ){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 7.bmp";
	}
	else if( strcmp(level_src, "images/blevel 7.bmp") ==0 ){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 6.bmp";
	}
	else if( strcmp(level_src, "images/blevel 6.bmp") ==0 ){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 5.bmp";
	}
	else if( strcmp(level_src, "images/blevel 5.bmp") ==0 ){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 4.bmp";
	}
	else if( strcmp(level_src, "images/blevel 4.bmp") ==0 ){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 3.bmp";
	}
	else if( strcmp(level_src, "images/blevel 3.bmp") ==0 ){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 2.bmp";
	}
	else if( strcmp(level_src, "images/blevel 2.bmp") ==0 ){
		(((widget->root)->WidgetChildren)->brotherWidget)->src = "images/blevel 1.bmp";
	}
	paint_Gui_Tree_on_Screen(main_window);
}

//discovers cat level in main game
char* discover_cat_level(){

	if(MainGame->cat_player->skill_level ==1)
		return "images/blevel 1.bmp";
	else if (MainGame->cat_player->skill_level ==2)
		return "images/blevel 2.bmp";
	else if (MainGame->cat_player->skill_level ==3)
		return "images/blevel 3.bmp";
	else if (MainGame->cat_player->skill_level ==4)
		return "images/blevel 4.bmp";
	else if (MainGame->cat_player->skill_level ==5)
		return "images/blevel 5.bmp";
	else if (MainGame->cat_player->skill_level ==6)
		return "images/blevel 6.bmp";
	else if (MainGame->cat_player->skill_level ==7)
		return "images/blevel 7.bmp";
	else if (MainGame->cat_player->skill_level ==8)
		return "images/blevel 8.bmp";
	//else if (MainGame->cat_player->skill_level ==9)
		//return "images/blevel 9.bmp";
	else
		return "images/blevel 9.bmp";
}

//discovers mouse level in main game
char* discover_mouse_level(){

	if(MainGame->mouse_player->skill_level ==1)
		return "images/blevel 1.bmp";
	else if (MainGame->mouse_player->skill_level ==2)
		return "images/blevel 2.bmp";
	else if (MainGame->mouse_player->skill_level ==3)
		return "images/blevel 3.bmp";
	else if (MainGame->mouse_player->skill_level ==4)
		return "images/blevel 4.bmp";
	else if (MainGame->mouse_player->skill_level ==5)
		return "images/blevel 5.bmp";
	else if (MainGame->mouse_player->skill_level ==6)
		return "images/blevel 6.bmp";
	else if (MainGame->mouse_player->skill_level ==7)
		return "images/blevel 7.bmp";
	else if (MainGame->mouse_player->skill_level ==8)
		return "images/blevel 8.bmp";
	//else if (MainGame->mouse_player->skill_level ==9)
		//return "images/blevel 9.bmp";
	else
		return "images/blevel 9.bmp";
}


//updates the marked button in a window with a number of buttons. widget is the window which
// has several buttons in it.  the assumption is there's always exactly one button marked
void update_marked_button_in_window(Widget *widget){

	Widget *candidate_button = widget->WidgetChildren;
	while(candidate_button != NULL){
		if(candidate_button->isMarked == 99)
			candidate_button->isMarked = 2;  //this will be the button which will be marked
		else
			candidate_button->isMarked = 3;  //unmark all the other buttons
		candidate_button = candidate_button->brotherWidget;
	}
}



Widget* update_marking_because_tab_pressed (Widget* button_marked){  //TRYOUT VERSION!!!

	extern Widget *current_window;

	Widget *bro;  Widget *first_child_of_window;  char *image_path;  //int booly = 0;       
	bro = NULL;
	
	if(button_marked->root == NULL)  
		return NULL;

	first_child_of_window = button_marked->root->WidgetChildren;

	if(button_marked->root->WidgetChildren == NULL)
		return NULL;

	//first we find out if we're in a window that doesn't support tab presses:
	if( strcmp(first_child_of_window->src, "images/newWorldLogo.bmp") ==0 ||
		strcmp(first_child_of_window->src, "images/World1Logo.bmp") ==0 ||
		strcmp(first_child_of_window->src, "images/World2Logo.bmp") ==0 ||
		strcmp(first_child_of_window->src, "images/World3Logo.bmp") ==0 ||
		strcmp(first_child_of_window->src, "images/World4Logo.bmp") ==0 ||
		strcmp(first_child_of_window->src, "images/World5Logo.bmp") ==0 ||
		strcmp(first_child_of_window->src, "images/CannotSaveInvalidWorldLogo.bmp") ==0 ||
		is_current_window_the_game_window(current_window) == 1 ||
		is_current_window_the_paused_game_window(current_window) == 1  )
		
		return NULL;

	button_marked->isMarked = 3;  //unmark the previously marked button
	image_path = button_marked->root->WidgetChildren->src;  //image_path now points to
	//the first child (usually it's a logo) of the current_window
	if(strcmp(image_path, "images/Cat&MouseLogo.bmp") ==0 ){  //main menu
		if(strcmp(button_marked->src, "images/bNew Game.bmp") ==0 ){
			button_marked->src = "images/gNew Game.bmp";
			bro = button_marked->brotherWidget;
			bro->src = "images/bLoadGame.bmp";
		}
		else if(strcmp(button_marked->src, "images/bLoadGame.bmp") ==0 ){
			button_marked->src = "images/gLoadGame.bmp";
			bro = button_marked->brotherWidget;
			bro->src = "images/bCreateGame.bmp";
		}
		else if(strcmp(button_marked->src, "images/bCreateGame.bmp") ==0 ){
			button_marked->src = "images/gCreateGame.bmp";
			bro = button_marked->brotherWidget;
			bro->src = "images/bEditGame.bmp";
		}

		else if(strcmp(button_marked->src, "images/bEditGame.bmp") ==0 ){
			button_marked->src = "images/gEditGame.bmp";
			bro = button_marked->brotherWidget;
			bro->src = "images/bQuit.bmp";
		}
		else{
			button_marked->src = "images/gQuit.bmp";
			bro = first_child_of_window->brotherWidget;
			bro->src = "images/bNew Game.bmp";
		}
	}  //end of main menu option

	else if(strcmp(image_path, "images/Choose Your Cat.bmp") ==0 ||
		strcmp(image_path, "images/Choose Your Mouse.bmp") ==0  ){  //type selection menus

		if(strcmp(button_marked->src, "images/bHuman.bmp") ==0 ){ 
			button_marked->src = "images/gHuman.bmp";
			bro = button_marked->brotherWidget;
			bro->src = "images/bMachine.bmp";
		}

		else if(strcmp(button_marked->src, "images/bMachine.bmp") ==0 ){
			button_marked->src = "images/gMachine.bmp";
			bro = button_marked->brotherWidget;
			bro->src = "images/bBack.bmp";
		}
		else{
			button_marked->src = "images/gBack.bmp";
			bro = first_child_of_window->brotherWidget;
			bro->src = "images/bHuman.bmp";
		}

	} //closes type selection menus option
	
	else if( strcmp(image_path,"images/Choose Cat Skill Level Logo.bmp") ==0 ||
		strcmp(image_path,"images/Choose Mouse Skill Level Logo.bmp")==0 ){ //skill level menus

			bro = handle_tab_in_skill_level_menu (button_marked);
			paint_Gui_Tree_on_Screen(main_window);
			return bro;
	}

	else if(  strcmp(image_path,"images/saveWorldLogo.bmp")==0 ||
		strcmp(image_path,"images/editGameLogo.bmp")==0   ||
		strcmp(image_path,"images/loadGameLogo.bmp")==0  ) {
	//if they're equal then strcmp == 0. 
	// !( strcmp(s1,s2) ==0 ) means:  if s1==s2, then 0.  if s1 !=s2 then 1
		if ((!(  strcmp(button_marked->src,"images/bdone.bmp") == 0 ))
			&&(!(  strcmp(button_marked->src,"images/bBack.bmp") ==0 ) )){
		if( strcmp(button_marked->src,"images/bWorld1.bmp") ==0  )
			button_marked->src = "images/gWorld1.bmp";
		else if( strcmp(button_marked->src,"images/bWorld2.bmp") ==0  )
			button_marked->src = "images/gWorld2.bmp";
		else if( strcmp(button_marked->src,"images/bWorld3.bmp") ==0  )
			button_marked->src = "images/gWorld3.bmp";
		else if( strcmp(button_marked->src,"images/bWorld4.bmp") ==0  )
			button_marked->src = "images/gWorld4.bmp";
		else if( strcmp(button_marked->src,"images/bWorld5.bmp") ==0  )
			button_marked->src = "images/gWorld5.bmp";
		bro = button_marked->brotherWidget->brotherWidget->brotherWidget;
		bro->src = "images/bdone.bmp";
		
		}
		else if( strcmp(button_marked->src,"images/bdone.bmp") ==0 ){
			button_marked->src = "images/gdone.bmp";
			bro = button_marked->brotherWidget;
			bro->src = "images/bBack.bmp";
		}
		else if( strcmp(button_marked->src, "images/bBack.bmp") == 0 ){
			button_marked->src = "images/gBack.bmp";
			bro = button_marked->root->WidgetChildren->brotherWidget;
			if(strcmp(bro->src,"images/gWorld1.bmp") == 0)
				bro->src = "images/bWorld1.bmp";
			else if(strcmp(bro->src,"images/gWorld2.bmp") == 0)
			    bro->src = "images/bWorld2.bmp";
			else if(strcmp(bro->src,"images/gWorld3.bmp") == 0)
			    bro->src = "images/bWorld3.bmp";
			else if(strcmp(bro->src,"images/gWorld4.bmp") == 0)
			    bro->src = "images/bWorld4.bmp";
			else if(strcmp(bro->src,"images/gWorld5.bmp") == 0)
			    bro->src = "images/bWorld5.bmp";
		}

	}

	if(bro!=NULL)
		bro->isMarked = 2;  //bro is now the newly marked button
	paint_Gui_Tree_on_Screen(main_window);
	return bro;
}


Widget* handle_tab_in_skill_level_menu (Widget *button_marked){
	//logo, blevel, up, down, done, back
	Widget *first_child_of_father;  Widget *bro; Widget *done_button; Widget *back_button;
	Widget *level;  int option;

	if(button_marked->root == NULL)
		return NULL;
	if(button_marked->root->WidgetChildren == NULL)
		return NULL;
	button_marked->isMarked = 3;  //unmark 
	first_child_of_father = button_marked->root->WidgetChildren;
	level = first_child_of_father->brotherWidget;

	//simplest option is when done was blue:
	done_button = level->brotherWidget->brotherWidget->brotherWidget;
	back_button = done_button->brotherWidget;
	if( strcmp(done_button->src, "images/bdone.bmp") == 0){
		done_button->src = "images/gdone.bmp";
		back_button->src = "images/bBack.bmp";
		back_button->isMarked = 2; //mark back button
		bro = back_button; //will be returned at end of function
		//paint_Gui_Tree_on_Screen(main_window);
		return bro;
	}

	if(level->src[14] == '1')    //"glevel 7
		option = 1;
	else if (level->src[14] == '2')    
		option = 2;
	else if (level->src[14] == '3')    
		option = 3;
	else if (level->src[14] == '4')    
		option = 4;
	else if (level->src[14] == '5')    
		option = 5;
	else if (level->src[14] == '6')    
		option = 6;
	else if (level->src[14] == '7')    
		option = 7;
	else if (level->src[14] == '8')    
		option = 8;
	else if (level->src[14] == '9')    
		option = 9;

	//case where back button was marked:  level was gray and should now be blue
	 if( strcmp(back_button->src, "images/bBack.bmp") == 0){
		back_button->src = "images/gBack.bmp";
		level->isMarked = 2;  //mark level
		switch(option){
		case 1:
			level->src = "images/blevel 1.bmp";
			break;
		case 2:
			level->src = "images/blevel 2.bmp";
			break;
		case 3:
			level->src = "images/blevel 3.bmp";
			break;
		case 4:
			level->src = "images/blevel 4.bmp";
			break;
		case 5:
			level->src = "images/blevel 5.bmp";
			break;
		case 6:
			level->src = "images/blevel 6.bmp";
			break;
		case 7:
			level->src = "images/blevel 7.bmp";
			break;
		case 8:
			level->src = "images/blevel 8.bmp";
			break;
		case 9:
			level->src = "images/blevel 9.bmp";
			break;
		}//closes switch
		//paint_Gui_Tree_on_Screen(main_window);
		return level;
	}
	else{ //level was blue and now it should be gray and done should be blue
		done_button->isMarked = 2; //mark done button
		done_button->src = "images/bdone.bmp";
		switch(option){
		case 1:
			level->src = "images/glevel 1.bmp";
			break;
		case 2:
			level->src = "images/glevel 2.bmp";
			break;
		case 3:
			level->src = "images/glevel 3.bmp";
			break;
		case 4:
			level->src = "images/glevel 4.bmp";
			break;
		case 5:
			level->src = "images/glevel 5.bmp";
			break;
		case 6:
			level->src = "images/glevel 6.bmp";
			break;
		case 7:
			level->src = "images/glevel 7.bmp";
			break;
		case 8:
			level->src = "images/glevel 8.bmp";
			break;
		case 9:
			level->src = "images/glevel 9.bmp";
			break;
		}
		//paint_Gui_Tree_on_Screen(main_window);
		return done_button;
	}
	
}

//we assume that all the isMarked fields were already updated. this function is only
//for physical updates - meaning changing the src field of the widgets
void update_marking_because_mouse_click (Widget *button_marked){

	Widget *first_child_of_father;  Widget *level; Widget *done_button; //Widget* back_button;
	  int option;  //int choice;
	if(button_marked->root == NULL)
		return;
	if(button_marked->root->WidgetChildren == NULL)
		return;
	first_child_of_father = button_marked->root->WidgetChildren;
	// if( ! (strcmp(s1,s2) == 0)) ):  if s1==s2, then 0.  if s1 != s2, then 1
	if( (!(strcmp(first_child_of_father->src, "images/Choose Cat Skill Level Logo.bmp") == 0) )
		&& ( !(strcmp(first_child_of_father->src, "images/Choose Mouse Skill Level Logo.bmp") == 0) ) )
		
		return;

	level = first_child_of_father->brotherWidget;
	//simplest option is when done was blue:
	done_button = level->brotherWidget->brotherWidget->brotherWidget;
	//back_button = done_button->brotherWidget;
	if(level->src[14] == '1')    
		option = 1;
	else if (level->src[14] == '2')    
		option = 2;
	else if (level->src[14] == '3')    
		option = 3;
	else if (level->src[14] == '4')    
		option = 4;
	else if (level->src[14] == '5')    
		option = 5;
	else if (level->src[14] == '6')    
		option = 6;
	else if (level->src[14] == '7')    
		option = 7;
	else if (level->src[14] == '8')    
		option = 8;
	else if (level->src[14] == '9')    
		option = 9;


	switch(option){
		case 1:
			level->src = "images/glevel 1.bmp";
			break;
		case 2:
			level->src = "images/glevel 2.bmp";
			break;
		case 3:
			level->src = "images/glevel 3.bmp";
			break;
		case 4:
			level->src = "images/glevel 4.bmp";
			break;
		case 5:
			level->src = "images/glevel 5.bmp";
			break;
		case 6:
			level->src = "images/glevel 6.bmp";
			break;
		case 7:
			level->src = "images/glevel 7.bmp";
			break;
		case 8:
			level->src = "images/glevel 8.bmp";
			break;
		case 9:
			level->src = "images/glevel 9.bmp";
			break;
		} //closes switch

	done_button->src = "images/bdone.bmp";
}


//discovers which one of curr_window's buttons is currently marked
Widget* discover_button_marked (Widget *curr_window){

	Widget *candidate_button = curr_window->WidgetChildren;
	while(candidate_button != NULL){
		if(candidate_button->isMarked == 2)
			return candidate_button;  
	
		candidate_button = candidate_button->brotherWidget;
	}
	return NULL;   //should never get here
}

//used in handle_events function when space bar is pressed and current_window == game_window
Widget* get_space_button_in_game_window (Widget *game_window){

	//space bar button is the 57th child of game window. (also last child)
	Widget *temp_child;    Widget *prev_child;
	temp_child = game_window->WidgetChildren;
	while( (temp_child = temp_child->brotherWidget) != NULL){
		prev_child = temp_child;
	}
	return prev_child;
}

//used in handle_events function when F1 is pressed and current_window == paused_game_window
Widget* get_reconfigure_mouse_button (Widget *paused_game_window){
	//mouse is 49+7, cat is 49+8
	Widget *temp_child;    
	int mouse_cnt = 0;
	temp_child = paused_game_window->WidgetChildren;
	while(mouse_cnt < 55){
		++mouse_cnt;
		temp_child = temp_child->brotherWidget;
	}
	return temp_child;
}

//used in handle_events function when F1 is pressed and current_window == paused_game_window
Widget* get_reconfigure_cat_button (Widget *paused_game_window){
	//mouse is 49+7, cat is 49+8
	Widget *temp_child;    
	int cat_cnt = 0;
	temp_child = paused_game_window->WidgetChildren;
	while(cat_cnt < 56){
		++cat_cnt;
		temp_child = temp_child->brotherWidget;
	}
	return temp_child;
}

Widget* get_restart_button(Widget *paused_game_window){

	Widget *temp_child;    
	int restart_cnt = 0;
	temp_child = paused_game_window->WidgetChildren;
	while(restart_cnt < 57){
		++restart_cnt;
		temp_child = temp_child->brotherWidget;
	}
	return temp_child;
}

Widget* get_go_to_main_menu_button(Widget *paused_game_window){

	Widget *temp_child;    
	int restart_cnt = 0;
	temp_child = paused_game_window->WidgetChildren;
	while(restart_cnt < 58){
		++restart_cnt;
		temp_child = temp_child->brotherWidget;
	}
	return temp_child;
}



void handle_up_arrow_on_game_window (Widget *currentWindow){

	int go_to_row;   
	//first, need to verify the current player is human
	if(MainGame->CurrPlayer == MOUSE){
		if(MainGame->mouse_player->Human_or_Machine == MACHINE)
			return;
	}
	else if(MainGame->CurrPlayer == CAT){
		if(MainGame->cat_player->Human_or_Machine == MACHINE)
			return;
	}

	//function will translate to row,col and call isMovePossible
	if(MainGame->CurrPlayer == MOUSE){
		//first find location of mouse
		go_to_row = MainGame->mouse_currRow - 1;
		IsMovePosible( go_to_row , MainGame->mouse_currCol);
	}
	else{  //current player is the cat
		go_to_row = MainGame->cat_currRow - 1;
		IsMovePosible(go_to_row , MainGame->cat_currCol);
	}
}


void handle_down_arrow_on_game_window (Widget *currentWindow){

	int go_to_row;  
	//first, need to verify the current player is human
	if(MainGame->CurrPlayer == MOUSE){
		if(MainGame->mouse_player->Human_or_Machine == MACHINE)
			return;
	}
	else if(MainGame->CurrPlayer == CAT){
		if(MainGame->cat_player->Human_or_Machine == MACHINE)
			return;
	}

	
	if(MainGame->CurrPlayer == MOUSE){
		go_to_row = MainGame->mouse_currRow + 1;
		IsMovePosible( go_to_row , MainGame->mouse_currCol);
		
	}
	else{  //current player is the cat
		go_to_row = MainGame->cat_currRow + 1;
		IsMovePosible(go_to_row , MainGame->cat_currCol);
	}
}


void handle_left_arrow_on_game_window (Widget *currentWindow){

	 int go_to_col;
	//first, need to verify the current player is human
	if(MainGame->CurrPlayer == MOUSE){
		if(MainGame->mouse_player->Human_or_Machine == MACHINE)
			return;
	}
	else if(MainGame->CurrPlayer == CAT){
		if(MainGame->cat_player->Human_or_Machine == MACHINE)
			return;
	}

	
	if(MainGame->CurrPlayer == MOUSE){
		go_to_col = MainGame->mouse_currCol - 1;
		IsMovePosible(MainGame->mouse_currRow , go_to_col);
		
	}
	else{  //current player is the cat
		go_to_col = MainGame->cat_currCol - 1;
		IsMovePosible(MainGame->cat_currRow , go_to_col);
	}
}


void handle_right_arrow_on_game_window (Widget *currentWindow){

	 int go_to_col;
	//first, need to verify the current player is human
	if(MainGame->CurrPlayer == MOUSE){
		if(MainGame->mouse_player->Human_or_Machine == MACHINE)
			return;
	}
	else if(MainGame->CurrPlayer == CAT){
		if(MainGame->cat_player->Human_or_Machine == MACHINE)
			return;
	}

	
	if(MainGame->CurrPlayer == MOUSE){
		go_to_col = MainGame->mouse_currCol + 1;
		IsMovePosible(MainGame->mouse_currRow , go_to_col);
		
	}
	else{  //current player is the cat
		go_to_col = MainGame->cat_currCol + 1;
		IsMovePosible(MainGame->cat_currRow , go_to_col);
	}
}



void handle_up_arrow_on_skill_level_menu (Widget *currentWindow){

	Widget *logo;
	if(currentWindow->WidgetChildren != NULL){
		logo = currentWindow->WidgetChildren;
		if( strcmp(logo->src, "images/Choose Cat Skill Level Logo.bmp") ==0 ){
			//logo, blevel, upbutton, downbutton, done,back
			//we only do something if the level button is marked:
			if(logo->brotherWidget->isMarked == 2){
				handle_up_button_on_select_machine_level(
					logo->brotherWidget->brotherWidget, 0,0);
			}
		}
		else if (strcmp(logo->src, "images/Choose Mouse Skill Level Logo.bmp") ==0 ){
			//logo, blevel, upbutton, downbutton, done,back
			//we only do something if the level button is marked:
			if(logo->brotherWidget->isMarked == 2){
				handle_up_button_on_select_machine_level(
					logo->brotherWidget->brotherWidget, 0,0);
			}
		}
	}
}

void handle_down_arrow_on_skill_level_menu (Widget *currentWindow){

	Widget *logo;
	if(currentWindow->WidgetChildren != NULL){
		logo = currentWindow->WidgetChildren;
		if( strcmp(logo->src, "images/Choose Cat Skill Level Logo.bmp") ==0 ){
			//logo, blevel, upbutton, downbutton, done,back
			//we only do something if the level button is marked:
			if(logo->brotherWidget->isMarked == 2){
				handle_down_button_on_select_machine_level(
					logo->brotherWidget->brotherWidget->brotherWidget, 0,0);
			}
		}
		else if (strcmp(logo->src, "images/Choose Mouse Skill Level Logo.bmp") ==0 ){
			//logo, blevel, upbutton, downbutton, done,back
			//we only do something if the level button is marked:
			if(logo->brotherWidget->isMarked == 2){
				handle_down_button_on_select_machine_level(
					logo->brotherWidget->brotherWidget->brotherWidget, 0,0);
			}
		}
	}
}


//scans the widgetChildren list of curr_window to discover which of it's buttons was 
//mouse clicked.
Widget* discover_button_selected (Widget *curr_window, int mouse_clickedX, 
	int mouse_clickedY){

	Widget *candidate_button = curr_window->WidgetChildren;
	while(candidate_button != NULL){
		//first check if candidate_button is really a button(and not a label for example)
		if(candidate_button->do_on_press != NULL){
			if(isButtonMouseClicked (candidate_button, mouse_clickedX,mouse_clickedY)==1){
                return candidate_button;
			}
		}
		candidate_button = candidate_button->brotherWidget;
	}

	return NULL;   //should never get here
}


//returns 1 if and only if button was mouse clicked on
int isButtonMouseClicked (Widget *widget, int mouse_clickedX, int mouse_clickedY){

	if( (widget->xCoordinate < mouse_clickedX) && 
		(mouse_clickedX < widget->xCoordinate + widget->width) 
		&& (widget->yCoordinate < mouse_clickedY) &&
		(mouse_clickedY < widget->yCoordinate + widget->height))
	   return 1; 
	
	return 0;
}

void handle_events(){

	extern int failure;  extern Widget *current_window;

	SDL_Event e;    Widget *button_marked;
	Widget *button_clicked;   char *imagePath;
	button_marked = NULL;    button_clicked = NULL;
	while (!quit  && (failure ==0) ) {
	    while (SDL_PollEvent(&e) != 0  && (failure ==0)) {
			switch (e.type) {
				case (SDL_QUIT):
					quit = 1;
					break;
				case (SDL_KEYUP):
					if (e.key.keysym.sym == SDLK_ESCAPE){

						imagePath = current_window->WidgetChildren->src;
						if( is_current_window_the_paused_game_window(current_window) == 1 ||
							(strcmp(imagePath , "images/newWorldLogo.bmp") == 0) ||
							(strcmp(imagePath, "images/World1Logo.bmp") == 0) ||  
							(strcmp(imagePath, "images/World2Logo.bmp") == 0) ||
							(strcmp(imagePath, "images/World3Logo.bmp") == 0) ||
							(strcmp(imagePath, "images/World4Logo.bmp") == 0) ||
							(strcmp(imagePath, "images/World5Logo.bmp") == 0) )
								quit = 1;
								     
					}
					
					else if(e.key.keysym.sym == SDLK_m){
							
							if ( (strcmp(current_window->WidgetChildren->src,"images/newWorldLogo.bmp") ==0)||
							(strcmp(current_window->WidgetChildren->src,"images/World1Logo.bmp") ==0 ) ||  
							(strcmp(current_window->WidgetChildren->src , "images/World2Logo.bmp") ==0 ) ||
							(strcmp(current_window->WidgetChildren->src, "images/World3Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src ,"images/World4Logo.bmp") == 0 ) ||
							(strcmp(current_window->WidgetChildren->src , "images/World5Logo.bmp") ==0)  ) //current_window == world builder
								handle_place_mouse_by_keyboard_on_world_builder(current_window);
							 
						}


					else if(e.key.keysym.sym == SDLK_c){
							
							if  ( (strcmp(current_window->WidgetChildren->src, "images/newWorldLogo.bmp") == 0)||
							(strcmp(current_window->WidgetChildren->src, "images/World1Logo.bmp") == 0) ||  
							(strcmp(current_window->WidgetChildren->src, "images/World2Logo.bmp") ==0) ||
							(strcmp(current_window->WidgetChildren->src , "images/World3Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src ,"images/World4Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src ,"images/World5Logo.bmp") == 0)  ) //current_window == world builder
								handle_place_cat_by_keyboard_on_world_builder(current_window);
						}

					else if(e.key.keysym.sym == SDLK_p){
							
							if  ( (strcmp(current_window->WidgetChildren->src, "images/newWorldLogo.bmp") == 0)||
							(strcmp(current_window->WidgetChildren->src, "images/World1Logo.bmp") == 0) ||  
							(strcmp(current_window->WidgetChildren->src ,"images/World2Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src ,"images/World3Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src ,"images/World4Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src,"images/World5Logo.bmp") == 0)  ) //current_window == world builder
								handle_place_cheese_by_keyboard_on_world_builder(current_window);
						}

					else if(e.key.keysym.sym == SDLK_w){
							
							if  ( (strcmp(current_window->WidgetChildren->src, "images/newWorldLogo.bmp") == 0)||
							(strcmp(current_window->WidgetChildren->src, "images/World1Logo.bmp") == 0) ||  
							(strcmp(current_window->WidgetChildren->src ,"images/World2Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src ,"images/World3Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src, "images/World4Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src ,"images/World5Logo.bmp") == 0)  ) //current_window == world builder
								handle_place_wall_by_keyboard_on_world_builder(current_window);
						}

					else if(e.key.keysym.sym == SDLK_s){
							
							if ( strcmp(current_window->WidgetChildren->src ,
								"images/newWorldLogo.bmp") == 0) //current_window == world builder
								handle_save_world_button(current_window->WidgetChildren->brotherWidget,0,0);

							else if ( (strcmp(current_window->WidgetChildren->src ,"images/World1Logo.bmp") == 0) ||  
							(strcmp(current_window->WidgetChildren->src ,"images/World2Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src ,"images/World3Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src ,"images/World4Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src ,"images/World5Logo.bmp") == 0) )
							handle_save_world_button_after_edit(current_window->WidgetChildren->
							brotherWidget,0,0);
						}


					else if (e.key.keysym.sym == SDLK_SPACE){

						imagePath = current_window->WidgetChildren->src;
					
						if (is_current_window_the_game_window(current_window) ==1)  {
							//we're in game window
							MainGame->is_game_paused = 1;
							handle_click_on_space_button
					(get_space_button_in_game_window(current_window) , 0,0);
				
						} 
						else if(is_current_window_the_paused_game_window(current_window) ==1 ){ //curr window is pause game window{

							if(MainGame->is_game_over == 0){  //game isn't over
							//should discard paused game window and return to game window
								MainGame->is_game_paused = 0;
								handle_resume_game
									(get_space_button_in_game_window(current_window) , 0,0);
							}//closes case where no winner and no draw
							else{ // there's a winner or a draw
								//MainGame->is_game_paused = 1;  //game is reinitialized in
								// unpaused state
								//handle_click_on_space_button
					//(get_space_button_in_game_window(current_window) , 0,0);
							}
						}

						else if  ( (strcmp(current_window->WidgetChildren->src ,"images/newWorldLogo.bmp") == 0)||
							(strcmp(current_window->WidgetChildren->src, "images/World1Logo.bmp") == 0) ||  
							(strcmp(current_window->WidgetChildren->src , "images/World2Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src ,"images/World3Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src , "images/World4Logo.bmp") == 0)||
							(strcmp(current_window->WidgetChildren->src, "images/World5Logo.bmp") == 0) ) //current_window == world builder
								handle_place_EmptySpace_by_keyboard_on_world_builder (current_window);
					}//closes space bar key

					else if(e.key.keysym.sym == SDLK_F1){
						if(is_current_window_the_paused_game_window(current_window) ==1 ){ 
							//curr window is pause game window			
							handle_reconfigure
							(get_reconfigure_mouse_button(current_window),0,0);
						}
								else if ( strcmp(current_window->WidgetChildren->src,
								"images/newWorldLogo.bmp") == 0) //current_window == world builder
								goBackToMainMenuFromWorldBuilder(current_window->WidgetChildren->
								brotherWidget->brotherWidget,0,0);
								
								else if ( (strcmp(current_window->WidgetChildren->src, "images/World1Logo.bmp") == 0) ||  
							(strcmp(current_window->WidgetChildren->src, "images/World2Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src, "images/World3Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src ,"images/World4Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src, "images/World5Logo.bmp") == 0) )
							handle_back_on_edit_game_menu(current_window->WidgetChildren->
							brotherWidget->brotherWidget,0,0);
	
					} //closes F1 key

					else if(e.key.keysym.sym == SDLK_F2){
			
						if(is_current_window_the_paused_game_window(current_window) ==1 ) //curr window is pause game window
										
							handle_reconfigure
							(get_reconfigure_cat_button(current_window),0,0);
						
					}// closes F2 key

					else if(e.key.keysym.sym == SDLK_F3){
						if(is_current_window_the_paused_game_window(current_window) ==1 ) //curr window is pause game window
										
							handle_restart_game
							(get_restart_button(current_window),0,0);	
					
					} //closes F3 key

					//handle_go_to_main_menu
					else if(e.key.keysym.sym == SDLK_F4){
						if(is_current_window_the_paused_game_window(current_window) ==1 ) //curr window is pause game window
									
							handle_go_to_main_menu
							(get_go_to_main_menu_button(current_window),0,0);
								
					} //closes F4 key

				//case (SDLK_UP):  //up arrow
				//	if(e.key.keysym.sym == SDLK_UP){
				//		
				//		if (is_current_window_the_game_window(current_window) ==1)  //we're in game window
				//			handle_up_arrow_on_game_window(current_window);

				//		
				//		else if  ( (strcmp(current_window->WidgetChildren->src, "images/newWorldLogo.bmp") == 0)||
				//			(strcmp(current_window->WidgetChildren->src, "images/World1Logo.bmp") == 0) ||  
				//			(strcmp(current_window->WidgetChildren->src, "images/World2Logo.bmp") == 0) ||
				//			(strcmp(current_window->WidgetChildren->src, "images/World3Logo.bmp") == 0) ||
				//			(strcmp(current_window->WidgetChildren->src, "images/World4Logo.bmp") == 0) ||
				//			(strcmp(current_window->WidgetChildren->src, "images/World5Logo.bmp") == 0)  ) //current_window == world builder
				//				handle_up_arrow_on_world_builder(current_window);

				//		else if ( strcmp(current_window->WidgetChildren->src,
				//			"images/Choose Cat Skill Level Logo.bmp") == 0 ||
				//			strcmp(current_window->WidgetChildren->src,
				//			"images/Choose Mouse Skill Level Logo.bmp") == 0)
				//			handle_up_arrow_on_skill_level_menu(current_window);

				//		else if  ( (strcmp(current_window->WidgetChildren->src, "images/saveWorldLogo.bmp") == 0)||
				//			(strcmp(current_window->WidgetChildren->src, "images/editGameLogo.bmp") == 0) ||  
				//			(strcmp(current_window->WidgetChildren->src,"images/loadGameLogo.bmp") == 0) )
				//			handle_up_button_on_load_game(current_window->WidgetChildren->brotherWidget->
				//			brotherWidget,0,0);

				//	}


				//	case (SDLK_DOWN):  //down arrow
				//		if(e.key.keysym.sym == SDLK_DOWN){

				//			if (is_current_window_the_game_window(current_window) ==1)  //we're in game window
				//				handle_down_arrow_on_game_window(current_window);

				//			else if  ( (strcmp(current_window->WidgetChildren->src, "images/newWorldLogo.bmp") == 0)||
				//			(strcmp(current_window->WidgetChildren->src, "images/World1Logo.bmp") == 0) ||  
				//			(strcmp(current_window->WidgetChildren->src, "images/World2Logo.bmp") == 0) ||
				//			(strcmp(current_window->WidgetChildren->src, "images/World3Logo.bmp") == 0) ||
				//			(strcmp(current_window->WidgetChildren->src, "images/World4Logo.bmp") == 0) ||
				//			(strcmp(current_window->WidgetChildren->src, "images/World5Logo.bmp") == 0)  ) //current_window == world builder
				//				handle_down_arrow_on_world_builder(current_window);

				//			else if ( strcmp(current_window->WidgetChildren->src,
				//				"images/Choose Cat Skill Level Logo.bmp") == 0 ||
				//				strcmp(current_window->WidgetChildren->src,
				//				"images/Choose Mouse Skill Level Logo.bmp") == 0)
				//				handle_down_arrow_on_skill_level_menu(current_window);

				//			else if  ( (strcmp(current_window->WidgetChildren->src,"images/saveWorldLogo.bmp") == 0)||
				//			(strcmp(current_window->WidgetChildren->src, "images/editGameLogo.bmp") == 0) ||  
				//			(strcmp(current_window->WidgetChildren->src, "images/loadGameLogo.bmp") == 0) )
				//			handle_down_button_on_load_game(current_window->WidgetChildren->brotherWidget->
				//			brotherWidget->brotherWidget,0,0);

				//		}


				//	case (SDLK_LEFT):  //left arrow
				//		if(e.key.keysym.sym == SDLK_LEFT){

				//			if (is_current_window_the_game_window(current_window) == 1)  //we're in game window
				//				handle_left_arrow_on_game_window(current_window);

				//			else if  ( (strcmp(current_window->WidgetChildren->src, "images/newWorldLogo.bmp") == 0)||
				//			(strcmp(current_window->WidgetChildren->src, "images/World1Logo.bmp") == 0) ||  
				//			(strcmp(current_window->WidgetChildren->src, "images/World2Logo.bmp") == 0) ||
				//			(strcmp(current_window->WidgetChildren->src, "images/World3Logo.bmp") == 0) ||
				//			(strcmp(current_window->WidgetChildren->src, "images/World4Logo.bmp") == 0) ||
				//			(strcmp(current_window->WidgetChildren->src, "images/World5Logo.bmp") == 0)  ) //current_window == world builder
				//				handle_left_arrow_on_world_builder(current_window);
				//		}

				//	case (SDLK_RIGHT):  //right arrow
				//		if(e.key.keysym.sym == SDLK_RIGHT){

				//			if (is_current_window_the_game_window(current_window) == 1)  //we're in game window
				//				handle_right_arrow_on_game_window(current_window);

				//			else if  ( (strcmp(current_window->WidgetChildren->src, "images/newWorldLogo.bmp") == 0)||
				//			(strcmp(current_window->WidgetChildren->src, "images/World1Logo.bmp") == 0) ||  
				//			(strcmp(current_window->WidgetChildren->src, "images/World2Logo.bmp") == 0) || 
				//			(strcmp(current_window->WidgetChildren->src, "images/World3Logo.bmp") == 0) || 
				//			(strcmp(current_window->WidgetChildren->src, "images/World4Logo.bmp") == 0) || 
				//			(strcmp(current_window->WidgetChildren->src, "images/World5Logo.bmp") == 0)  ) //current_window == world builder
				//				handle_right_arrow_on_world_builder(current_window);
				//		}


					
					else if(e.key.keysym.sym == SDLK_UP){
						
						if (is_current_window_the_game_window(current_window) ==1)  //we're in game window
							handle_up_arrow_on_game_window(current_window);

						
						else if  ( (strcmp(current_window->WidgetChildren->src, "images/newWorldLogo.bmp") == 0)||
							(strcmp(current_window->WidgetChildren->src, "images/World1Logo.bmp") == 0) ||  
							(strcmp(current_window->WidgetChildren->src, "images/World2Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src, "images/World3Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src, "images/World4Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src, "images/World5Logo.bmp") == 0)  ) //current_window == world builder
								handle_up_arrow_on_world_builder(current_window);

						else if ( strcmp(current_window->WidgetChildren->src,
							"images/Choose Cat Skill Level Logo.bmp") == 0 ||
							strcmp(current_window->WidgetChildren->src,
							"images/Choose Mouse Skill Level Logo.bmp") == 0)
							handle_up_arrow_on_skill_level_menu(current_window);

						else if  ( (strcmp(current_window->WidgetChildren->src, "images/saveWorldLogo.bmp") == 0)||
							(strcmp(current_window->WidgetChildren->src, "images/editGameLogo.bmp") == 0) ||  
							(strcmp(current_window->WidgetChildren->src,"images/loadGameLogo.bmp") == 0) )
							handle_up_button_on_load_game(current_window->WidgetChildren->brotherWidget->
							brotherWidget,0,0);

					}//end of up arrow option


						else if(e.key.keysym.sym == SDLK_DOWN){  //down arrow

							if (is_current_window_the_game_window(current_window) ==1)  //we're in game window
								handle_down_arrow_on_game_window(current_window);

							else if  ( (strcmp(current_window->WidgetChildren->src, "images/newWorldLogo.bmp") == 0)||
							(strcmp(current_window->WidgetChildren->src, "images/World1Logo.bmp") == 0) ||  
							(strcmp(current_window->WidgetChildren->src, "images/World2Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src, "images/World3Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src, "images/World4Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src, "images/World5Logo.bmp") == 0)  ) //current_window == world builder
								handle_down_arrow_on_world_builder(current_window);

							else if ( strcmp(current_window->WidgetChildren->src,
								"images/Choose Cat Skill Level Logo.bmp") == 0 ||
								strcmp(current_window->WidgetChildren->src,
								"images/Choose Mouse Skill Level Logo.bmp") == 0)
								handle_down_arrow_on_skill_level_menu(current_window);

							else if  ( (strcmp(current_window->WidgetChildren->src,"images/saveWorldLogo.bmp") == 0)||
							(strcmp(current_window->WidgetChildren->src, "images/editGameLogo.bmp") == 0) ||  
							(strcmp(current_window->WidgetChildren->src, "images/loadGameLogo.bmp") == 0) )
							handle_down_button_on_load_game(current_window->WidgetChildren->brotherWidget->
							brotherWidget->brotherWidget,0,0);

						}  //end of down arrow option


					 
						else if(e.key.keysym.sym == SDLK_LEFT){  //left arrow

							if (is_current_window_the_game_window(current_window) == 1)  //we're in game window
								handle_left_arrow_on_game_window(current_window);

							else if  ( (strcmp(current_window->WidgetChildren->src, "images/newWorldLogo.bmp") == 0)||
							(strcmp(current_window->WidgetChildren->src, "images/World1Logo.bmp") == 0) ||  
							(strcmp(current_window->WidgetChildren->src, "images/World2Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src, "images/World3Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src, "images/World4Logo.bmp") == 0) ||
							(strcmp(current_window->WidgetChildren->src, "images/World5Logo.bmp") == 0)  ) //current_window == world builder
								handle_left_arrow_on_world_builder(current_window);
						} //end of left arrow option

					 
						else if(e.key.keysym.sym == SDLK_RIGHT){   //right arrow

							if (is_current_window_the_game_window(current_window) == 1)  //we're in game window
								handle_right_arrow_on_game_window(current_window);

							else if  ( (strcmp(current_window->WidgetChildren->src, "images/newWorldLogo.bmp") == 0)||
							(strcmp(current_window->WidgetChildren->src, "images/World1Logo.bmp") == 0) ||  
							(strcmp(current_window->WidgetChildren->src, "images/World2Logo.bmp") == 0) || 
							(strcmp(current_window->WidgetChildren->src, "images/World3Logo.bmp") == 0) || 
							(strcmp(current_window->WidgetChildren->src, "images/World4Logo.bmp") == 0) || 
							(strcmp(current_window->WidgetChildren->src, "images/World5Logo.bmp") == 0)  ) //current_window == world builder
								handle_right_arrow_on_world_builder(current_window);
						} //end of right arrow option



						break;  



					
				case (SDL_KEYDOWN):
					if(e.key.keysym.sym==SDLK_RETURN){   //quit = 1;
						button_marked = discover_button_marked(current_window);
						if(button_marked != NULL){
							if(button_marked->isMarked == 2){
								if(button_marked->do_on_press != NULL)
									button_marked->do_on_press (button_marked, -8, -8); 
							}
								//-8 , -8 values are irrelevant.
						}
					}
						  //it's /r. not sure it works in Unix!!!
				
				
					
				 else if(e.key.keysym.sym==SDLK_TAB){
					button_marked = discover_button_marked(current_window);
						if(button_marked != NULL){
							button_marked= update_marking_because_tab_pressed (button_marked);
						
						}
						
				}


				break; 
				
				case (SDL_MOUSEBUTTONUP):
					
				    button_clicked = discover_button_selected(current_window, e.button.x,
						e.button.y);
					if(button_clicked != NULL){

					//call on the function that knows what to do in case this button was clicked
					button_clicked->do_on_press (button_clicked, e.button.x, e.button.y);
					}
					break;
				default:
					break;
			}
		}
	}
}

// 1 means game window.  0 means not game window
int is_current_window_the_game_window (Widget *curr_window){

	extern Widget *current_window;

	char *imagePath;
	if(current_window->WidgetChildren == NULL)
		return 0;
	imagePath = current_window->WidgetChildren->src;

	if( strcmp(imagePath,"images/whiteBlock75on74.bmp") ==0  ||
		strcmp(imagePath, "images/mouseBlock.bmp") == 0 ||
		strcmp(imagePath, "images/catBlock.bmp") == 0 ||
		strcmp(imagePath, "images/cheeseBlock.bmp") == 0 ||
		strcmp(imagePath, "images/wallBlock.bmp") == 0 )
		    return 1;
	else
		return 0;
}

// 1 means game window.  0 means not game window
int is_current_window_the_paused_game_window (Widget *curr_window){

	extern Widget *current_window;

	char *imagePath;
	if(current_window->WidgetChildren == NULL)
		return 0;
	imagePath = current_window->WidgetChildren->src;

	if( strcmp(imagePath,"images/grayBlock75on74.bmp") ==0  ||
		strcmp(imagePath, "images/grayMouse74on75.bmp") == 0 ||
		strcmp(imagePath, "images/grayCat74on75.bmp") == 0 ||
		strcmp(imagePath, "images/graycheeseBlock74on75.bmp") == 0 ||
		strcmp(imagePath, "images/graywallBlock74on75.bmp") == 0 )
		    return 1;
	else
		return 0;
}



//GUI FOR GAME FUNCTIONS
void initialize_regular_board (Widget *widgetNode, int x, int y){

	extern int failure;  extern Widget *current_window;

	int temp_width =250;   int temp_height = 250;   int width_cnt=0;   int height_cnt=0;
	Widget *game_window;  //Widget *board_window;    Widget *top_panel;   Widget *side_bar;   
	//Widget *whiteBlock_button;   whiteBlock75on74

	//mouse if human
	MainGame->mouse_player->Human_or_Machine = HUMAN;
	//game_windows father is 
	game_window = Construct_Window("images/orangePaint.bmp",widgetNode,
		-250, -300, 550,550,NULL);  
	if(failure) {return;}
	//update the current window field
	current_window = game_window;
    
//	choose_your_mouse_logo = Construct_Label("images/Choose Your Mouse.bmp", game_window,
//		250, 100, 300,200, NULL);
//	if(failure)
//		return;

	//cat on 1,1   mouse on 2,3   cheese on 6,5   wall on 4,4
	for(height_cnt=0; height_cnt< 7; height_cnt++){
		temp_width= 250;
		for(width_cnt=0; width_cnt < 7; width_cnt++){

			if(height_cnt ==1 && width_cnt == 1){
				Construct_Button("images/catBlock.bmp", game_window,
                                 temp_width, temp_height, 75,74, handle_click_on_board_block);
				if(failure) {return;}
			}
			
			else if(height_cnt ==2 && width_cnt == 3){
				Construct_Button("images/mouseBlock.bmp", game_window,
                                 temp_width, temp_height, 75,74, handle_click_on_board_block);
				if(failure) {return;}
			}

			else if(height_cnt ==6 && width_cnt == 5){
				Construct_Button("images/cheeseBlock.bmp", game_window,
                                 temp_width, temp_height, 75,74, handle_click_on_board_block);
				if(failure) {return;}
			}
			//WALL_ON_BOARD
			else if(height_cnt == 4 && width_cnt == 4){
				Construct_Button("images/wallBlock.bmp", game_window,
                                 temp_width, temp_height, 75,74, handle_click_on_board_block);
				if(failure) {return;}
			}
            else{
				Construct_Button("images/whiteBlock75on74.bmp", game_window,
                                 temp_width, temp_height, 75,74, handle_click_on_board_block); 
              if(failure) {return;}
			}
			//temp_width= temp_width +75;
			temp_width = temp_width + 75;
		}
		temp_height= temp_height +74;
	}

paint_Gui_Tree_on_Screen(main_window);

}
//tells what to do in case of a click on a board block
void handle_click_on_board_block (Widget *widgetNode, int x, int y){
	//calls upon a function which reads from char** and draws the gui
	//need to run of current_window->WidgetChildren from 1 to 49, and update the src's
	//Widget *temp_Block;
	int rowClicked=0;   int colClicked=0;   int booly; //int er; 
	//int rowIndex=0;   int colIndex=0;
	booly =1;
	//temp_Block = current_window->WidgetChildren;  current_window is father of all blocks
//discover row first:

	if(MainGame->is_game_paused ==1){
		return;
	}

	while(booly){
		if(y<= ( ((rowClicked + 1) *75)+ 250)  && y>= ( ((rowClicked ) *75)+ 250) ){
			booly = 0;  //found row
			break;
		}
		++rowClicked;

		//printf("in handle click on board block in 1st while loop\n");
	}

	booly = 1;
	//find column
	while(booly){
		if(x<= ( ((colClicked + 1) *74)+ 250)  && x>= ( ((colClicked ) *74)+ 250) ){
			booly = 0;  //found row
			break;
		}
		++colClicked;
	
	}
	
	IsMovePosible(rowClicked, colClicked);
}

//updates gui after making a legal move
void update_gui_after_move(){  //need to know global variable current window

	extern int failure;  extern Widget *current_window;

	SDL_Event e;
	Widget *temp_Block;  Widget *button_clicked;
	int rowIndex;  int colIndex;   
	int is_current_player_machine;   // 1 means machine, 2 means human
	//double diff_t;
	time_t start_t;   time_t end_t;
	
	
	temp_Block = current_window->WidgetChildren;

	if(MainGame->CurrPlayer == CAT){
		if(MainGame->cat_player->Human_or_Machine == MACHINE)
			is_current_player_machine = 1;  //curr player is machine
		else
			is_current_player_machine = 2;  //curr player is human
	}
	else if(MainGame->CurrPlayer == MOUSE){
		if(MainGame->mouse_player->Human_or_Machine == MACHINE)
			is_current_player_machine = 1;  //curr player is machine
		else
			is_current_player_machine = 2;  //curr player is human
	}

	for(rowIndex=0; rowIndex < 7; rowIndex++){

			for(colIndex=0; colIndex < 7; colIndex++){
				if( strcmp(temp_Block->src, "images/whiteBlock75on74.bmp") == 0){
					if(MainGame->GameBoard[rowIndex][colIndex] == MOUSE_ON_BOARD){
						temp_Block->src = "images/mouseBlock.bmp";
						
					}
					else if(MainGame->GameBoard[rowIndex][colIndex] == CAT_ON_BOARD){
						temp_Block->src = "images/catBlock.bmp";
						
					}
				}//closes empty block if
				else if( strcmp(temp_Block->src, "images/mouseBlock.bmp") == 0){
					if(MainGame->GameBoard[rowIndex][colIndex] == EMPTY_ON_BOARD){
						temp_Block->src = "images/whiteBlock75on74.bmp";
						
					}
					else if(MainGame->GameBoard[rowIndex][colIndex] == CAT_ON_BOARD){
						temp_Block->src = "images/catBlock.bmp";
						
					}
				}//closes mouse if
				
				else if( strcmp(temp_Block->src, "images/catBlock.bmp") == 0){

					if(MainGame->GameBoard[rowIndex][colIndex] == EMPTY_ON_BOARD){
						temp_Block->src = "images/whiteBlock75on74.bmp";
						
					}
					else if(MainGame->GameBoard[rowIndex][colIndex] == MOUSE_ON_BOARD){
						temp_Block->src = "images/mouseBlock.bmp";
						
					}
				}//close cat if

			temp_Block = temp_Block->brotherWidget;
			} //closes inner for loop
		}

//	49 blocks,
// then mouse's move, 50
//left parentheses51
//blank digit 52
//right digit  53
//rigt parenthesis  54
//2nd row - one widget - machine computing or human waiting
//3rd row - one button pause button
	//now temp_Block is the 50'th child of game window - animal's move
	if( strcmp(temp_Block->src , "images/Mouse's move.bmp") == 0)
		temp_Block->src ="images/Cat's move.bmp";
	else
		temp_Block->src = "images/Mouse's move.bmp";

	temp_Block = temp_Block->brotherWidget->brotherWidget;  //left digit or blank digit
	update_first_text_row_in_game_window(temp_Block);
	//update the second text row:
	temp_Block = temp_Block->brotherWidget->brotherWidget->brotherWidget;
	if(is_current_player_machine == 1)  //curr player is machine 
		temp_Block->src = "images/Machine - computing....bmp";
	else
		temp_Block->src = "images/Human - waiting for next move....bmp";
	////if we have a winner:        //IF WE HAVE WINNER OR DRAW AMIT NEEDS TO STOP RECURSION
	if(MainGame->winner == CAT || MainGame->winner == MOUSE || MainGame->winner == DRAW)
		MainGame->is_game_over =1;  //1 means over, 0 means not over
	//need to open paused state window, accepct the game can't be unpaused

	//if machine vs machine add a DELAY of 1 second:
	//also, if machine vs machine mode, we need to allow pause
	if( (MainGame->cat_player->Human_or_Machine == MACHINE) &&
		(MainGame->mouse_player->Human_or_Machine == MACHINE) ){
		
		SDL_Delay(1000);

		time(&start_t);
		while( ( SDL_PollEvent(&e) != 0)  && (failure ==0) ){ //we allow one second to press pause

			time(&end_t);
			if( difftime(end_t, start_t) > 1){
				//printf("stuck in if diff time\n");
				break;
			}
			switch (e.type) {
				case (SDL_KEYUP):
					if (e.key.keysym.sym == SDLK_SPACE){ 
						//first need to physically paint
				//the move that was made earlier on the screen. then need to paint the 
				//paused game window.
						//printf("im in machine vs machine and i presses escape\n");
						paint_Gui_Tree_on_Screen(main_window);
						if (is_current_window_the_game_window(current_window) ==1)  {
							//we're in game window
							MainGame->is_game_paused = 1;  //pause game
							handle_click_on_space_button
					(get_space_button_in_game_window(current_window) , 0,0);
					//printf("MainGame-> is_game_paused = %d\n", MainGame->is_game_paused);

							//if(MainGame->is_game_over == 1)  //case where there's a winner or a draw
								//handle_click_on_space_button( get_space_button_in_game_window(current_window),
									//0,0 );
							return;
						} 
						

					}

					break;

					case (SDL_MOUSEBUTTONUP):
					
				    button_clicked = discover_button_selected(current_window, e.button.x,
						e.button.y);
					if(button_clicked != NULL){

					//call on the function that knows what to do in case this button was clicked
					button_clicked->do_on_press (button_clicked, e.button.x, e.button.y);
					}
						
					break;
				default:
					break;
			}
			
			
		} //closes while event loop
		
	}  //closes case of MACHINE VS MACHINE

	paint_Gui_Tree_on_Screen(main_window);

	if(MainGame->is_game_over == 1){  //case where there's a winner or a draw
		handle_click_on_space_button( get_space_button_in_game_window(current_window),
			0,0 );
	}
} 


//paints board from the information in the global variable MainGame
void paint_board_from_Game_fields(Widget *widgetNode, int x, int y){
    
	extern int failure;  extern Widget *current_window;

	//static int paint_board_cnt= 0;   //should be zeroed again after the game is finished
	int left_digit;   int right_digit;   
	int is_start_player_machine;  //1 means start player is a machine, 2 means it's human
	int temp_width =250;   int temp_height = 250;   //int width_cnt=0;   int height_cnt=0;
	int row_index = 0;     int col_index=0;
	Widget *grandfather_logo;
	Widget *game_window;  //Widget *board_window;       Widget *side_bar;   
	Widget *whiteBlock_button;   //whiteBlock75on74
	
	//find out whether start player is human or machine:
	if(MainGame->StartPlayer == CAT){ 
		if(MainGame->cat_player->Human_or_Machine == MACHINE)
			is_start_player_machine= 1;  //start player is machine and it's a cat
		else
			is_start_player_machine= 2;  //start player is human and it's a cat
	}
	else if(MainGame->StartPlayer == MOUSE){  
		if(MainGame->mouse_player->Human_or_Machine == MACHINE)
			is_start_player_machine= 3;  //start player is machine and it's a mouse
		else
			is_start_player_machine= 4;  //start player is human and it's a mouse
	}

	//need to find out if mouse is human or machine
	grandfather_logo = (widgetNode->root)->WidgetChildren;
	if( strcmp(grandfather_logo->src , "images/Choose Your Mouse.bmp") == 0)
		MainGame->mouse_player->Human_or_Machine = HUMAN;
		
	
	else if( strcmp(widgetNode->src, "images/restartGame.bmp") == 0){
	}

	else
		MainGame->mouse_player->Human_or_Machine = MACHINE;

	free_All_Widgets( &(main_window->WidgetChildren) );
	if(failure) {return;}
	main_window->WidgetChildren = NULL;
	game_window = Construct_Window("images/orangePaint.bmp",main_window,
			0, 0, 800,800,NULL); 
	if(failure) {return;}

	current_window = game_window;
	
	for(row_index = 0; row_index < 7; row_index++){
		temp_width= 250;
		for(col_index =0; col_index < 7; col_index++){

			if( MainGame->GameBoard[row_index][col_index] == CAT_ON_BOARD){
			
					whiteBlock_button = Construct_Button("images/catBlock.bmp", game_window,
                                 temp_width, temp_height, 75,74, handle_click_on_board_block);
					if(failure) {return;}
					whiteBlock_button->isMarked = 3;
			}
			
			else if(MainGame->GameBoard[row_index][col_index] == MOUSE_ON_BOARD){
				
				//mouse is machine
				whiteBlock_button = Construct_Button("images/mouseBlock.bmp", game_window,
                           temp_width, temp_height, 75,74, handle_click_on_board_block);
				if(failure) {return;}
				whiteBlock_button->isMarked = 3;  //mouse is not marked
				
			}

			else if(MainGame->GameBoard[row_index][col_index] == CHEESE_ON_BOARD){
				whiteBlock_button = Construct_Button("images/cheeseBlock.bmp", game_window,
                                 temp_width, temp_height, 75,74, handle_click_on_board_block);
				if(failure) {return;}
				whiteBlock_button->isMarked = 3;
			}
			//WALL_ON_BOARD
			else if(MainGame->GameBoard[row_index][col_index] == WALL_ON_BOARD){
				whiteBlock_button = Construct_Button("images/wallBlock.bmp", game_window,
                                 temp_width, temp_height, 75,74, handle_click_on_board_block);
				if(failure) {return;}
				whiteBlock_button->isMarked = 3;
			}
            else{
				whiteBlock_button = Construct_Button("images/whiteBlock75on74.bmp", game_window,
                                 temp_width, temp_height, 75,74, handle_click_on_board_block); 
              if(failure) {return;}
			  whiteBlock_button->isMarked = 3;
			}
			
			temp_width = temp_width + 75;
		}
		temp_height= temp_height +74;
	} //closes for loop

//paint the upper panel: 6 images for first line, 1 images for second line. 1 button for 3rd
	if(MainGame->StartPlayer == MOUSE){
		Construct_Label ("images/Mouse's move.bmp", game_window,
			300,50,165,35, NULL);
		if(failure) {return;}
	}
	else{
		Construct_Label ("images/Cat's move.bmp", game_window,
			300,50,165,35, NULL);
		if(failure) {return;}
	}

	Construct_Label ("images/left parenthesis.bmp", game_window,
		460,50,10,35, NULL);
	if(failure) {return;}
	//now need to find out what's the number of turns. if number of turns >=10:  
	//for right digit i need number of turns%10
	//for left digit i need number of turn/10
	//if number of turns <=9:  i need '9'  ch = (char)(((int)'0')+sveta);
	if(MainGame->NumberOfTurns < 10) {

		//paint a blank image with orange color instead of the left digit. put the single
		//digit in place of the right digit:
		Construct_Label ("images/blank digit.bmp", game_window,475,50,10,35, NULL);
			if(failure) {return;}

		if(MainGame->NumberOfTurns == 0){
		   //                                  DO SOMETHING
		}
		else if(MainGame->NumberOfTurns == 1){
		   Construct_Label ("images/1.bmp", game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(MainGame->NumberOfTurns == 2){
		   Construct_Label ("images/2.bmp", game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(MainGame->NumberOfTurns == 3){
		   Construct_Label ("images/3.bmp", game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(MainGame->NumberOfTurns == 4){
		   Construct_Label ("images/4.bmp", game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(MainGame->NumberOfTurns == 5){
		   Construct_Label ("images/5.bmp", game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(MainGame->NumberOfTurns == 6){
		   Construct_Label ("images/6.bmp", game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(MainGame->NumberOfTurns == 7){
		   Construct_Label ("images/7.bmp", game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(MainGame->NumberOfTurns == 8){
		   Construct_Label ("images/8.bmp", game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(MainGame->NumberOfTurns == 9){
		   Construct_Label ("images/9.bmp", game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}

	}
	

	else{     //number of turns > 9  and therefor we have 2 digits for number of turns
		//left digit first:
		
		left_digit = MainGame->NumberOfTurns/10;
		 if(left_digit == 1){
			Construct_Label ("images/1.bmp" , game_window,475,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(left_digit == 2){
			Construct_Label ("images/2.bmp" , game_window,475,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(left_digit == 3){
			Construct_Label ("images/3.bmp" , game_window,475,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(left_digit == 4){
			Construct_Label ("images/4.bmp" , game_window,475,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(left_digit == 5){
			Construct_Label ("images/5.bmp" , game_window,475,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(left_digit == 6){
			Construct_Label ("images/6.bmp" , game_window,475,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(left_digit == 7){
			Construct_Label ("images/7.bmp" , game_window,475,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(left_digit == 8){
			Construct_Label ("images/8.bmp" , game_window,475,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(left_digit == 9){
			Construct_Label ("images/9.bmp" , game_window,475,50,10,35, NULL);
			if(failure) {return;}
		}

		//now the right digit:
		right_digit = MainGame->NumberOfTurns%10;
		if(right_digit == 0){
			Construct_Label ("images/0.bmp" , game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(right_digit == 1){
			Construct_Label ("images/1.bmp" , game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(right_digit == 2){
			Construct_Label ("images/2.bmp" , game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(right_digit == 3){
			Construct_Label ("images/3.bmp" , game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(right_digit == 4){
			Construct_Label ("images/4.bmp" , game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(right_digit == 5){
			Construct_Label ("images/5.bmp" , game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(right_digit == 6){
			Construct_Label ("images/6.bmp" , game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(right_digit == 7){
			Construct_Label ("images/7.bmp" , game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(right_digit == 8){
			Construct_Label ("images/8.bmp" , game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
		else if(right_digit == 9){
			Construct_Label ("images/9.bmp" , game_window,490,50,10,35, NULL);
			if(failure) {return;}
		}
	} //closes else option of number of turns>=10

	//consturct the right parenthesis:
		Construct_Label ("images/right parenthesis.bmp", game_window, 505,50,10,35, NULL);
		if(failure) {return;}
   //2nd text row:
	//if start player is machine
		if(is_start_player_machine == 1 || is_start_player_machine == 3 ){   //start player is machine
			Construct_Label ("images/Machine - computing....bmp", game_window,
				300,120,230,30, NULL);
			if(failure) {return;}
		}
		else { //start player is human
			Construct_Label ("images/Human - waiting for next move....bmp", game_window,
			300,120,290,30, NULL);
			if(failure) {return;}
		}

//paint the side bar:
Construct_Label("images/Gray side bar.bmp", game_window, 0,250, 250, 670, NULL);
if(failure) {return;}

//paint the 3rd text row:  space bar button is the last child of game window
//49+8 = 57th child
Construct_Button("images/gray Pause Before Next Move.bmp", game_window,
                          300, 175, 342,40, handle_click_on_space_button);
if(failure) {return;}

paint_Gui_Tree_on_Screen(main_window);


//if start player is machine
if(is_start_player_machine == 1 || is_start_player_machine == 3)   // start player is machine
	Make_A_Move(-8,-8);  //negative coordinates means computer needs to make a move
	
}//closes function


//handles click or hitting the space bar key while at the game window
void handle_click_on_space_button (Widget *space_button, int x, int y){

	extern int failure;  extern Widget *current_window;

	 Widget *pause_game_window;  //Widget *temp_Block;  
	//SDL_Event e;
	int row_index;   int col_index;  int temp_width;  int temp_height;  int right_digit;
	int left_digit;
	temp_height = 250;
	 
	pause_game_window = Construct_Window("images/orangePaint.bmp", space_button,
		-300,-175,800,800, NULL);
	//update the current window:
	current_window = pause_game_window;
	//temp_Block = current_window->WidgetChildren;

	MainGame->is_game_paused =1;   //game is paused


	for(row_index = 0; row_index < 7; row_index++){
		temp_width= 250;
		for(col_index =0; col_index < 7; col_index++){

			if( MainGame->GameBoard[row_index][col_index] == CAT_ON_BOARD){
				Construct_Button("images/grayCat74on75.bmp", pause_game_window,
                                 temp_width, temp_height, 75,74, NULL);
				if(failure) {return;}
			}
			else if(MainGame->GameBoard[row_index][col_index] == MOUSE_ON_BOARD){
				Construct_Button("images/grayMouse74on75.bmp", pause_game_window,
                                 temp_width, temp_height, 75,74, NULL);
				if(failure) {return;}
			}

			else if(MainGame->GameBoard[row_index][col_index] == CHEESE_ON_BOARD){
				Construct_Button("images/graycheeseBlock74on75.bmp", pause_game_window,
                                 temp_width, temp_height, 75,74, NULL);
				if(failure) {return;}
			}
			//WALL_ON_BOARD
			else if(MainGame->GameBoard[row_index][col_index] == WALL_ON_BOARD){
				Construct_Button("images/graywallBlock74on75.bmp", pause_game_window,
                                 temp_width, temp_height, 75,74, NULL);
				if(failure) {return;}
			}
            else{
				Construct_Button("images/grayBlock75on74.bmp", pause_game_window,
                                 temp_width, temp_height, 75,74, NULL); 
              if(failure) {return;}
			}
			temp_width = temp_width + 75;
		}
		temp_height= temp_height +74;
	} //closes for loop


	// UPPER PANEL
	if(MainGame->is_game_over == 0){    // no winner, not a draw. game is still on

		//paint the upper panel: 5 images for first line, 1 images for second line. 1 button for 3rd
		if(MainGame->StartPlayer == MOUSE){
			Construct_Label ("images/Mouse's move.bmp", pause_game_window,
				300,50,165,35, NULL);
			if(failure) {return;}
		}
		else{
			Construct_Label ("images/Cat's move.bmp", pause_game_window,
				300,50,165,35, NULL);
			if(failure) {return;}
		}

		Construct_Label ("images/left parenthesis.bmp", pause_game_window,
			460,50,10,35, NULL);
		if(failure) {return;}
		//now need to find out what's the number of turns. if number of turns >=10:  
		//for right digit i need number of turns%10
		//for left digit i need number of turn/10
		//if number of turns <=9:  i need '9'  ch = (char)(((int)'0')+sveta);
			if(MainGame->NumberOfTurns < 10) {

		//paint a blank image with orange color instead of the left digit. put the single
		//digit in place of the right digit:
			Construct_Label ("images/blank digit.bmp", pause_game_window,475,50,10,35, NULL);
			if(failure) {return;}

			if(MainGame->NumberOfTurns == 0){
			 //                                  DO SOMETHING
			}
			else if(MainGame->NumberOfTurns == 1){
				Construct_Label ("images/1.bmp", pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(MainGame->NumberOfTurns == 2){
				 Construct_Label ("images/2.bmp", pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(MainGame->NumberOfTurns == 3){
				 Construct_Label ("images/3.bmp", pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(MainGame->NumberOfTurns == 4){
				Construct_Label ("images/4.bmp", pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(MainGame->NumberOfTurns == 5){
				Construct_Label ("images/5.bmp", pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(MainGame->NumberOfTurns == 6){
				Construct_Label ("images/6.bmp", pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(MainGame->NumberOfTurns == 7){
				Construct_Label ("images/7.bmp", pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(MainGame->NumberOfTurns == 8){
				Construct_Label ("images/8.bmp", pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(MainGame->NumberOfTurns == 9){
				Construct_Label ("images/9.bmp", pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}

		}
	

		else{     //number of turns > 9  and therefor we have 2 digits for number of turns
		//left digit first:
		
			left_digit = MainGame->NumberOfTurns/10;
			 if(left_digit == 1){
				Construct_Label ("images/1.bmp" , pause_game_window,475,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(left_digit == 2){
				Construct_Label ("images/2.bmp" , pause_game_window,475,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(left_digit == 3){
				Construct_Label ("images/3.bmp" , pause_game_window,475,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(left_digit == 4){
				Construct_Label ("images/4.bmp" , pause_game_window,475,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(left_digit == 5){
				Construct_Label ("images/5.bmp" , pause_game_window,475,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(left_digit == 6){
				Construct_Label ("images/6.bmp" , pause_game_window,475,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(left_digit == 7){
				Construct_Label ("images/7.bmp" , pause_game_window,475,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(left_digit == 8){
				Construct_Label ("images/8.bmp" , pause_game_window,475,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(left_digit == 9){
				Construct_Label ("images/9.bmp" , pause_game_window,475,50,10,35, NULL);
				if(failure) {return;}
			}

			//now the right digit:
			right_digit = MainGame->NumberOfTurns%10;
			if(right_digit == 0){
				Construct_Label ("images/0.bmp" , pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(right_digit == 1){
			Construct_Label ("images/1.bmp" , pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(right_digit == 2){
				Construct_Label ("images/2.bmp" , pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(right_digit == 3){
				Construct_Label ("images/3.bmp" , pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(right_digit == 4){
				Construct_Label ("images/4.bmp" , pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(right_digit == 5){
				Construct_Label ("images/5.bmp" , pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(right_digit == 6){
				Construct_Label ("images/6.bmp" , pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(right_digit == 7){
				Construct_Label ("images/7.bmp" , pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(right_digit == 8){
				Construct_Label ("images/8.bmp" , pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
			else if(right_digit == 9){
				Construct_Label ("images/9.bmp" , pause_game_window,490,50,10,35, NULL);
				if(failure) {return;}
			}
		} //closes else option of number of turns>=10

		//consturct the right parenthesis:
			Construct_Label ("images/right parenthesis.bmp", pause_game_window, 505,50,10,35, NULL);
			if(failure) {return;}

		//2nd text row:
			if(MainGame->CurrPlayer == CAT){
				if(MainGame->cat_player->Human_or_Machine == HUMAN)
					Construct_Label ("images/humanPaused.bmp", pause_game_window,300,120,230,30, NULL);
				else
					Construct_Label ("images/machinePaused.bmp", pause_game_window,300,120,230,30, NULL);
			
			}
			else if(MainGame->CurrPlayer == MOUSE){
				if(MainGame->mouse_player->Human_or_Machine == HUMAN)
					Construct_Label ("images/humanPaused.bmp", pause_game_window,300,120,230,30, NULL);
				else
					Construct_Label ("images/machinePaused.bmp", pause_game_window,300,120,230,30, NULL);
			
			}


	}       // closes if no winner, no draw. 

	else if(MainGame->is_game_over == 1){  //there's a winner or a draw. 1 image and 4 blank images
	//for the 1st text row. 1 real image for 2nd text row 
		if(MainGame->winner == CAT){
			//blank message for 2nd text row:
			Construct_Label ("images/BlockorangePaint.bmp", pause_game_window,
				300,50,1,1, NULL);
			if(failure) {return;}
			//message instead of 1st text row
			Construct_Label ("images/GameOverCatWins.bmp", pause_game_window,
				300,50,232,150, NULL);
			if(failure) {return;}
				
		}
		else if(MainGame->winner == MOUSE){
			
			//blank message for 2nd text row:
			Construct_Label ("images/BlockorangePaint.bmp", pause_game_window,
				300,50,1,1, NULL);
			if(failure) {return;}
			//message instead of 1st text row
			Construct_Label ("images/GameOverMouseWins.bmp", pause_game_window,
				300,50,232,150, NULL);
			if(failure) {return;}
			
		}
		else if(MainGame->winner == DRAW){ //draw
			//blank message for 2nd text row:
			Construct_Label ("images/BlockorangePaint.bmp", pause_game_window,
				300,50,1,1, NULL);
			if(failure) {return;}
			//message instead of 1st text row
			Construct_Label ("images/GameOverTimeout.bmp", pause_game_window,
				300,50,232,150, NULL);
			if(failure) {return;}
	
		} //closes draw case

		//now paint 4 blank images to complete first row
		Construct_Label ("images/BlockorangePaint.bmp", pause_game_window,
				532,50,1,1, NULL);
		if(failure) {return;}
		Construct_Label ("images/BlockorangePaint.bmp", pause_game_window,
				572,50,1,1, NULL);
		if(failure) {return;}
		Construct_Label ("images/BlockorangePaint.bmp", pause_game_window,
				612,50,1,1, NULL);
		if(failure) {return;}
		Construct_Label ("images/BlockorangePaint.bmp", pause_game_window,
				642,50,1,1, NULL);
		if(failure) {return;}

	} //closes case where there's a winner or draw

	
	//side panel:
	Construct_Button("images/reconfigureMouse.bmp", pause_game_window,
                          10, 250, 186,53, handle_reconfigure);
	if(failure) {return;}
	Construct_Button("images/reconfigureCat.bmp", pause_game_window,
                          10, 330, 187,51, handle_reconfigure);
	if(failure) {return;}
	Construct_Button("images/restartGame.bmp", pause_game_window,
                          10, 410, 187,53, handle_restart_game);
	if(failure) {return;}
	Construct_Button("images/goToMainMenuPauseWindowBoard.bmp", pause_game_window,
                          10, 490, 187,53, handle_go_to_main_menu);
	if(failure) {return;}
	Construct_Button("images/quitProgramPauseWindowBoard.bmp", pause_game_window,
                          10, 570, 188,57, handle_quit);
	if(failure) {return;}

	//3rd text row in upper panel:
	if(MainGame->is_game_over == 0){  //no winner, no draw
		Construct_Button("images/ResumeGame.bmp", pause_game_window,
                          300, 175, 342,40, handle_resume_game);
		if(failure) {return;}
	}
	else if(MainGame->is_game_over == 1){  //game over
		Construct_Label("images/BlockorangePaint.bmp", pause_game_window,
                          300, 125, 1,1, NULL);
		if(failure) {return;}
	}
	
	paint_Gui_Tree_on_Screen(main_window);

}

void handle_resume_game (Widget *resume_game_button, int x, int y){

	//function needs to free the pause game window and return to the game window
	//resume_game_button's father is pause game window. it's father is the space bar button
	//in game window
	extern int failure;  extern Widget *current_window;

	Widget *space_button;
	current_window = resume_game_button->root->root->root;
	//printf("current window's child is %s\n", current_window->WidgetChildren->src);
	space_button = resume_game_button->root->root;
	free_All_Widgets( &(space_button->WidgetChildren) );
	if(failure) {return;}
	space_button->WidgetChildren = NULL;
	MainGame->is_game_paused = 0;
	paint_Gui_Tree_on_Screen(main_window);

	if(MainGame->CurrPlayer == MOUSE){
		if(MainGame->mouse_player->Human_or_Machine == MACHINE)
			Make_A_Move(-8,-8);
	}
	else if(MainGame->CurrPlayer == CAT){
		if(MainGame->cat_player->Human_or_Machine == MACHINE)
			Make_A_Move(-8,-8);
	}
}

//handles reconfigure animal on game window
void handle_reconfigure (Widget *reconfigure_button, int x, int y){

	extern int failure;  extern Widget *current_window;

	char *mouse_level;
	Widget *window;    Widget *logo;      
	Widget *gback_button;    Widget *gdone_button;    Widget *up_button;  Widget *down_button;
	Widget *level_button;   Widget *human_button;  Widget *machine_button;

	if( strcmp(reconfigure_button->src , "images/reconfigureMouse.bmp") == 0){  //reconfigure mouse
		
		window = Construct_Window( "images/orangePaint.bmp",reconfigure_button,-10,-250,800,800,NULL);
		if (failure) {return;}

	if (MainGame->mouse_player->Human_or_Machine == MACHINE){
		logo = Construct_Label("images/Choose Mouse Skill Level Logo.bmp",
		window, 200, 100, 300,200, NULL);
    if(failure)		{return;}

	mouse_level = discover_mouse_level();

	level_button = Construct_Button(mouse_level, window,
		250, 300, 204,59, handle_level_button); 
	if(failure)		{return;}
	level_button->isMarked = 2;

	up_button = Construct_Button("images/up button.bmp", window,
		455, 300, 32,30, handle_up_button_on_select_machine_level);
    if(failure)		{return;}
	up_button->isMarked =3;

	down_button = Construct_Button("images/down button.bmp", window,
		455, 330, 32,29, handle_down_button_on_select_machine_level);  
    if(failure)		{return;}
	down_button->isMarked = 3;

	gdone_button = Construct_Button("images/gdone.bmp", window,
		250, 500, 234,59, handle_done_button_on_reconfigure);
	if(failure)		{return;}
	gdone_button->isMarked = 3;

	gback_button = Construct_Button("images/gBack.bmp", window,
		250, 700, 234,59, handle_back_button_on_reconfigure_machine);
	if(failure)		{return;}
	gback_button->isMarked = 3;

	paint_Gui_Tree_on_Screen(main_window);
    if(failure)		{return;}
	}

	else if (MainGame->mouse_player->Human_or_Machine == HUMAN){  //mouse is human

		 logo = Construct_Label("images/Choose Your Mouse.bmp", window,
			200, 100, 300,200, NULL);
		if(failure) {return;}
		logo->isMarked = 3;

		human_button = Construct_Button("images/bHuman.bmp", window,
			250, 300, 234,59, handle_human_button_on_reconfigure); 
		if(failure) {return;}
		human_button->isMarked = 2;

		machine_button = Construct_Button("images/gMachine.bmp", window,
			250, 500, 234,59, handle_machine_button_on_reconfigure);
		if(failure) {return;}
		machine_button->isMarked = 3;

		gback_button = Construct_Button("images/gBack.bmp", window,
		250, 700, 234,59, handle_human_button_on_reconfigure);
		if(failure) {return;}
		gback_button->isMarked = 3;

    paint_Gui_Tree_on_Screen(main_window);

	}  //closes else if mouse is human

	}  //closes reconfigure mouse
	
	else{  //reconfigure cat

		window = Construct_Window( "images/orangePaint.bmp",reconfigure_button,-10,-330,800,800,NULL);
		if (failure) {return;}

		if(MainGame->cat_player->Human_or_Machine == MACHINE){  //cat is machine
			logo = Construct_Label("images/Choose Cat Skill Level Logo.bmp",
			window, 200, 100, 300,200, NULL);
		if(failure)		{return;}
		logo->isMarked = 3;

		mouse_level = discover_cat_level();

		level_button = Construct_Button(mouse_level, window,
			250, 300, 204,59, handle_level_button); 
		if(failure)		{return;}
		level_button->isMarked = 2;

		up_button = Construct_Button("images/up button.bmp", window,
			455, 300, 32,30, handle_up_button_on_select_machine_level);
		if(failure)		{return;}
		up_button->isMarked = 3;
	
		down_button = Construct_Button("images/down button.bmp", window,
			455, 330, 32,29, handle_down_button_on_select_machine_level);  
		if(failure)		{return;}
		down_button->isMarked = 3;

		gdone_button = Construct_Button("images/gdone.bmp", window,
			250, 500, 234,59, handle_done_button_on_reconfigure);
		if(failure)		{return;}
		gdone_button->isMarked = 3;

		gback_button = Construct_Button("images/gBack.bmp", window,
			250, 700, 234,59, handle_back_button_on_reconfigure_machine);
		if(failure)		{return;}
		gback_button->isMarked = 3;
		paint_Gui_Tree_on_Screen(main_window);
		if(failure)		{return;}
	}

	else if (MainGame->cat_player->Human_or_Machine == HUMAN){  //cat is human

		logo = Construct_Label("images/Choose Your Cat.bmp", window,
			200, 100, 300,200, NULL);
		if(failure) {return;}
		logo->isMarked = 3;

		human_button = Construct_Button("images/bHuman.bmp", window,
			250, 300, 234,59, handle_human_button_on_reconfigure); 
		if(failure) {return;}
		human_button->isMarked = 2;

		machine_button = Construct_Button("images/gMachine.bmp", window,
			250, 500, 234,59, handle_machine_button_on_reconfigure);
		if(failure) {return;}
		machine_button->isMarked = 3;
		
	gback_button = Construct_Button("images/gBack.bmp", window,
		250, 700, 234,59, handle_human_button_on_reconfigure);
	if(failure) {return;}
	gback_button->isMarked = 3;

    paint_Gui_Tree_on_Screen(main_window);

	}  //closes else if cat is human

	} //closes reconfigure cat

	current_window = window;
}

//handles restart game
void handle_restart_game (Widget *restart_game_button, int x, int y){

	if(last_world == 1)
		LoadDetailsOfGame("worlds/world_1.txt");
	else if(last_world == 2)
		LoadDetailsOfGame("worlds/world_2.txt");
	else if(last_world == 3)
		LoadDetailsOfGame("worlds/world_3.txt");
	else if(last_world == 4)
		LoadDetailsOfGame("worlds/world_4.txt");
	else if(last_world == 5)
		LoadDetailsOfGame("worlds/world_5.txt");

	MainGame->is_game_paused = 0;  //unpause the game
	MainGame->is_game_over = 0;    //reinitialized the game as not over
	MainGame->winner = NONE;
	paint_board_from_Game_fields(restart_game_button, x,y);
}

void handle_go_to_main_menu (Widget *go_to_main_menu_button, int x, int y){

	MainGame->is_game_paused = 0;  //game is reinitialized to be unpaused
	MainGame->is_game_over = 0;    //reinitialized the game as not over
	MainGame->winner = NONE;       
	free_All_Widgets( &(main_window->WidgetChildren) );
	display_Main_Menu();
}

void handle_quit(Widget *quit_button_on_game_window, int x, int y){

	quit = 1;
}


//called upon when the animal was human and we press reconfigure animal. 
void handle_machine_button_on_reconfigure (Widget *machine_button_on_reconfigure_mouse,
	int x, int y){

	extern int failure;  extern Widget *current_window;

	Widget *reconfigure_mouse_button;    Widget *mouse_skill_level_menu;
	Widget *logo;  Widget *level_button;  Widget *up_button;   Widget *down_button; 
	Widget *done_button;  Widget *back_button;

	reconfigure_mouse_button = machine_button_on_reconfigure_mouse->root->root;
	if( strcmp(reconfigure_mouse_button->src, "images/reconfigureMouse.bmp") == 0){
		MainGame->mouse_player->Human_or_Machine = MACHINE;
		//need to discard the mouse type selection menu and to open the machine skill level menu:
		//machine_button_on_reconfigure_mouse's father is mouse type select menu. it's father is
		//reconfigure mouse button
	
		free_All_Widgets( &(reconfigure_mouse_button->WidgetChildren) );
		reconfigure_mouse_button->WidgetChildren = NULL;

		mouse_skill_level_menu = Construct_Window ("images/orangePaint.bmp",
		reconfigure_mouse_button, -10, -250, 800,800, NULL);

		current_window = mouse_skill_level_menu;

		logo = Construct_Label("images/Choose Mouse Skill Level Logo.bmp",
			mouse_skill_level_menu, 200, 100, 300,200, NULL);
		if(failure)		{return;}
		logo->isMarked = 3;

		level_button = Construct_Button("images/blevel 5.bmp", mouse_skill_level_menu,
			250, 300, 204,59, handle_level_button); 
		if(failure)		{return;}
		level_button->isMarked = 2;

		up_button = Construct_Button("images/up button.bmp", mouse_skill_level_menu,
			455, 300, 32,30, handle_up_button_on_select_machine_level);
		if(failure)		{return;}
		up_button->isMarked = 3;

		down_button = Construct_Button("images/down button.bmp", mouse_skill_level_menu,
			455, 330, 32,29, handle_down_button_on_select_machine_level);
		if(failure)		{return;}
		down_button->isMarked = 3;

		done_button = Construct_Button("images/gdone.bmp", mouse_skill_level_menu,
			250, 500, 234,59, handle_done_button_on_reconfigure);
		if(failure)		{return;}
		done_button->isMarked = 3;

		//click on back button should discard this window and display mouse type selection window
		//with machine button marked
		back_button = Construct_Button("images/gBack.bmp", mouse_skill_level_menu,
			250, 700, 234,59, handle_back_button_on_reconfigure_machine);
		if(failure)		{return;}
		back_button->isMarked = 3;

	} // closes reconfigure mouse

	else{ //reconfigure cat

		MainGame->cat_player->Human_or_Machine = MACHINE;
		free_All_Widgets( &(reconfigure_mouse_button->WidgetChildren) );
		reconfigure_mouse_button->WidgetChildren = NULL;

		mouse_skill_level_menu = Construct_Window ("images/orangePaint.bmp",
		reconfigure_mouse_button, -10, -330, 800,800, NULL);

		current_window = mouse_skill_level_menu;

		logo = Construct_Label("images/Choose Cat Skill Level Logo.bmp",
			mouse_skill_level_menu, 200, 100, 300,200, NULL);
		if(failure)		{return;}
		logo->isMarked = 3;

		level_button = Construct_Button("images/blevel 5.bmp", mouse_skill_level_menu,
			250, 300, 204,59, handle_level_button); 
		if(failure)		{return;}
		level_button->isMarked = 2;

		up_button = Construct_Button("images/up button.bmp", mouse_skill_level_menu,
			455, 300, 32,30, handle_up_button_on_select_machine_level);
		if(failure)		{return;}
		up_button->isMarked = 3;

		down_button = Construct_Button("images/down button.bmp", mouse_skill_level_menu,
			455, 330, 32,29, handle_down_button_on_select_machine_level);
		if(failure)		{return;}
		down_button->isMarked = 3;

		done_button = Construct_Button("images/gdone.bmp", mouse_skill_level_menu,
			250, 500, 234,59, handle_done_button_on_reconfigure);
		if(failure)		{return;}
		done_button->isMarked = 3;

		//click on back button should discard this window and display mouse type selection window
		//with machine button marked
		back_button = Construct_Button("images/gBack.bmp", mouse_skill_level_menu,
			250, 700, 234,59, handle_back_button_on_reconfigure_machine);
		if(failure)		{return;}
		back_button->isMarked = 3;

	} //closes reconfigure cat
	paint_Gui_Tree_on_Screen(main_window);
}

//handles done button in reconfigure 
void handle_done_button_on_reconfigure (Widget *done_recofigure_button, int x, int y){

	extern Widget *current_window;

	Widget *mouse_machine_menu;      Widget *mouse_machine_level;   Widget *grandFather;
	Widget *animal_logo;
	char level;

	if(done_recofigure_button->root == NULL)
		return;
	if(done_recofigure_button->root->WidgetChildren == NULL)
		return;
	mouse_machine_menu = done_recofigure_button->root;
	animal_logo = mouse_machine_menu->WidgetChildren;
	if(animal_logo->brotherWidget == NULL)
		return;
	mouse_machine_level = ( (done_recofigure_button->root)->WidgetChildren)->brotherWidget;
	level = mouse_machine_level->src[14]; //14th index

	//first need to update markings in previous menu:
	done_recofigure_button->isMarked = 99;  ///////UTILITY FUNCTION TO REMARK BROTHERS
	update_marked_button_in_window(done_recofigure_button->root);
	//now we need to physically change the images in the previous window:
	update_marking_because_mouse_click(done_recofigure_button);

	if( strcmp(animal_logo->src , "images/Choose Mouse Skill Level Logo.bmp") == 0) //reconfigure mouse
		MainGame->mouse_player->skill_level = (int)(level)-48;  //level 5 is 53

	else //reconfigure cat
		MainGame->cat_player->skill_level = (int)(level)-48;  //level 5 is 53

	grandFather = done_recofigure_button->root->root;
	free_All_Widgets(&(grandFather->WidgetChildren) );
	grandFather->WidgetChildren = NULL;

	current_window = grandFather->root;
	paint_Gui_Tree_on_Screen(main_window);
}

//handles the back button on reconfigure machine mouse
void handle_back_button_on_reconfigure_machine (Widget *back_reconfigure_machine_button, 
	int x, int y){

	extern int failure;  extern Widget *current_window;

	Widget *type_select_window;   Widget *reconfigure_mouse_button;  Widget *logo;
	Widget *human_button;    Widget *machine_button;   Widget *back_button;
	//should discard the skill level window and display the type window with machine button marked
	//back_reconfigure_machine_button
	 
	reconfigure_mouse_button = back_reconfigure_machine_button->root->root;

	//printf("reconfigure mouse button's src is %s\n", reconfigure_mouse_button->src);


	free_All_Widgets( &(reconfigure_mouse_button->WidgetChildren) );  //temp->WidgetChildren is mouse menu
	if(failure) {return;}

	reconfigure_mouse_button->WidgetChildren = NULL; 

	//display type selection window 
	//back_reconfigure_machine_button's father is skill level window. it's father is 
	//reconfigure mouse button.  
	if(strcmp(reconfigure_mouse_button->src ,"images/reconfigureMouse.bmp") == 0){

		type_select_window = Construct_Window("images/orangePaint.bmp", reconfigure_mouse_button, 
			-10,-250,800,800,NULL);
		if(failure) {return;}

		logo = Construct_Label( "images/Choose Your Mouse.bmp", type_select_window,
			200, 100, 300,200, NULL);
		if(failure) {return;}
		logo->isMarked = 3;

	} //closes reconfigure mouse

	else{  //reconfigure cat

		type_select_window = Construct_Window("images/orangePaint.bmp", reconfigure_mouse_button, 
		-10,-330,800,800,NULL);
		if(failure) {return;}

		logo = Construct_Label( "images/Choose Your Cat.bmp", type_select_window,
			200, 100, 300,200, NULL);
		if(failure) {return;}
		logo->isMarked = 3;
	} //closes reconfigure cat

	human_button = Construct_Button("images/gHuman.bmp", type_select_window,
		250, 300, 234,59, handle_human_button_on_reconfigure); 
	if(failure) {return;}
	human_button->isMarked = 3;

	machine_button = Construct_Button("images/bMachine.bmp", type_select_window,
		250, 500, 234,59, handle_machine_button_on_reconfigure);
	if(failure) {return;}
	machine_button->isMarked = 2;

	back_button = Construct_Button("images/gBack.bmp", type_select_window,
		250, 700, 234,59, handle_human_button_on_reconfigure);
	back_button->isMarked = 3;

	current_window = type_select_window;
	paint_Gui_Tree_on_Screen(main_window);
}

//discards mouse type selection menu and returns to paused game window
void handle_human_button_on_reconfigure (Widget *human_button_on_reconfigure, int x, int y){

	extern Widget *current_window;

	Widget *reconfigure_button = human_button_on_reconfigure->root->root;
	//grandfather of human button is reconfigure button in paused game window
	if( strcmp(human_button_on_reconfigure->root->root->src ,"images/reconfigureMouse.bmp") == 0)
		MainGame->mouse_player->Human_or_Machine = HUMAN;
	else if( strcmp(human_button_on_reconfigure->root->root->src, "images/reconfigureCat.bmp") == 0)
		MainGame->cat_player->Human_or_Machine = HUMAN;

	free_All_Widgets( &(reconfigure_button->WidgetChildren) );
	reconfigure_button->WidgetChildren = NULL;

	current_window = reconfigure_button->root;

	paint_Gui_Tree_on_Screen(main_window);
}


//updates the first text row in the game window
void update_first_text_row_in_game_window (Widget *tempBlock){

	int left_digit;   int right_digit;

	if(MainGame->NumberOfTurns < 10){
		
		//special case where number of turns was 10 and now it's 9
		if(MainGame->NumberOfTurns == 9){
			tempBlock->src = "images/blank digit.bmp";
			tempBlock = tempBlock->brotherWidget;
			tempBlock->src = "images/9.bmp";
		}
		tempBlock = tempBlock->brotherWidget;   //right digit

		if(MainGame->NumberOfTurns == 0){
		   //                                  DO SOMETHING
		}
		else if(MainGame->NumberOfTurns == 1){
			tempBlock->src = "images/1.bmp";
		}
		else if(MainGame->NumberOfTurns == 2){
		   tempBlock->src = "images/2.bmp";
		}
		else if(MainGame->NumberOfTurns == 3){
		   tempBlock->src = "images/3.bmp";
		}
		else if(MainGame->NumberOfTurns == 4){
		   tempBlock->src = "images/4.bmp";
		}
		else if(MainGame->NumberOfTurns == 5){
		   tempBlock->src = "images/5.bmp";
		}
		else if(MainGame->NumberOfTurns == 6){
		   tempBlock->src = "images/6.bmp";
		}
		else if(MainGame->NumberOfTurns == 7){
		   tempBlock->src = "images/7.bmp";
		}
		else if(MainGame->NumberOfTurns == 8){
		   tempBlock->src = "images/8.bmp";
		}
}//closes if
	else{  //number of turns >=10
		left_digit = MainGame->NumberOfTurns/10;
		if(left_digit == 1)
			tempBlock->src = "images/1.bmp";
		else if (left_digit == 2)
			tempBlock->src = "images/2.bmp";
		else if (left_digit == 3)
			tempBlock->src = "images/3.bmp";
		else if (left_digit == 4)
			tempBlock->src = "images/4.bmp";
		else if (left_digit == 5)
			tempBlock->src = "images/5.bmp";
		else if (left_digit == 6)
			tempBlock->src = "images/6.bmp";
		else if (left_digit == 7)
			tempBlock->src = "images/7.bmp";
		else if (left_digit == 8)
			tempBlock->src = "images/8.bmp";
		else if (left_digit == 9)
			tempBlock->src = "images/9.bmp";

		tempBlock = tempBlock->brotherWidget; 
		//now right digit:
		right_digit = MainGame->NumberOfTurns%10;
		if(right_digit == 0)
			tempBlock->src = "images/0.bmp";
		else if(right_digit == 1)
			tempBlock->src = "images/1.bmp";
		else if(right_digit == 2)
			tempBlock->src = "images/2.bmp";
		else if(right_digit == 3)
			tempBlock->src = "images/3.bmp";
		else if(right_digit == 4)
			tempBlock->src = "images/4.bmp";
		else if(right_digit == 5)
			tempBlock->src = "images/5.bmp";
		else if(right_digit == 6)
			tempBlock->src = "images/6.bmp";
		else if(right_digit == 7)
			tempBlock->src = "images/7.bmp";
		else if(right_digit == 8)
			tempBlock->src = "images/8.bmp";
		else if(right_digit == 9)
			tempBlock->src = "images/9.bmp";
	}
}//closes function

///////////////////////////////// GUI FOR LOAD GAME ////////////////////////////////////


void display_load_game_selection_menu (Widget *widgetNode, int x, int y){

	extern int failure;  extern Widget *current_window;

	Widget *load_type_selection_menu;  Widget *load_game_logo; Widget* world_1_blue_button;
	Widget *up_button; Widget *down_button; Widget *gdone_button; Widget *gback_button;


	last_world=1;
	load_type_selection_menu= Construct_Window("images/orangePaint.bmp",widgetNode, -350,-300, 200,
		200,NULL);
	if(failure)
		return;

	//update the current window field
	current_window = load_type_selection_menu;

	load_game_logo = Construct_Label("images/loadGameLogo.bmp", load_type_selection_menu,
		275, 100, 113,25, NULL);
	if(failure)
		return;
	load_game_logo->isMarked = 3;

	world_1_blue_button = Construct_Button("images/bWorld1.bmp", load_type_selection_menu,
		250, 300, 204,59, handle_mouse_press_on_world_button); 
	if(failure)		{return;}
	world_1_blue_button->isMarked = 2;

	up_button = Construct_Button("images/up button.bmp", load_type_selection_menu,
		455, 300, 32,30, handle_up_button_on_load_game);
    if(failure)		{return;}
	up_button->isMarked = 3;

	down_button = Construct_Button("images/down button.bmp", load_type_selection_menu,
		455, 330, 32,29, handle_down_button_on_load_game);
    if(failure)		{return;}
	down_button->isMarked = 3;

	gdone_button = Construct_Button("images/gdone.bmp", load_type_selection_menu,
		250, 500, 234,59, display_cat_type_selection_menu_after_load_game);
	if(failure)		{return;}
	gdone_button->isMarked=3;

	gback_button = Construct_Button("images/gBack.bmp", load_type_selection_menu,
		250, 700, 234,59, handle_back_on_load_game_menu);
	if(failure)		{return;}
	gback_button->isMarked=3;

	paint_Gui_Tree_on_Screen(main_window);
    if(failure)		{return;}

}

void handle_up_button_on_load_game (Widget *widget, int x, int y){

	
	//Widget *choose_world_menu;   
	Widget *world_number;       
	
	int i;
	char new_world_src[19]={0};
	//choose_world_menu = widget->root;
	if (widget->root->WidgetChildren->brotherWidget->isMarked==3)
		return;
	world_number = (((widget->root)->WidgetChildren)->brotherWidget);

	widget->brotherWidget->brotherWidget->src="images/gdone.bmp";
	
	for (i=0;i<19;i++)
		new_world_src[i]=world_number->src[i];

	if (new_world_src[13]-48==NUMBER_OF_WORLD_FILES){
		//means the chosen world is world 5, so up button does nothing
		return;
	}
	
	else{
		if (new_world_src[13]=='1'){
			((widget->root)->WidgetChildren)->brotherWidget->src="images/bWorld2.bmp";
			
		}
		else if (new_world_src[13]=='2'){
			((widget->root)->WidgetChildren)->brotherWidget->src="images/bWorld3.bmp";
			
		}
		else if (new_world_src[13]=='3'){
			((widget->root)->WidgetChildren)->brotherWidget->src="images/bWorld4.bmp";
		
		}
		else if (new_world_src[13]=='4'){
			((widget->root)->WidgetChildren)->brotherWidget->src="images/bWorld5.bmp";
		}
		last_world++;
		((widget->root)->WidgetChildren)->brotherWidget->isMarked=2;
		widget->brotherWidget->brotherWidget->src="images/gdone.bmp";
		widget->brotherWidget->brotherWidget->isMarked=3;
		widget->brotherWidget->brotherWidget->brotherWidget->src="images/gBack.bmp";
		widget->brotherWidget->brotherWidget->brotherWidget->isMarked=3;
	}
	
	paint_Gui_Tree_on_Screen(main_window);

}

void handle_down_button_on_load_game (Widget *widget, int x, int y){

	//Widget *choose_world_menu;   
	Widget *world_number;       
	
	int i;
	char new_world_src[19]={0};
	if (widget->root->WidgetChildren->brotherWidget->isMarked==3)
		return;
	//choose_world_menu = widget->root;
	world_number = (((widget->root)->WidgetChildren)->brotherWidget);

	widget->brotherWidget->src="images/gdone.bmp";
	
	for (i=0;i<19;i++)
		new_world_src[i]=world_number->src[i];

	if (new_world_src[13]-48==1){
		//means the chosen world is world 1, so down button does nothing
		return;
	}
	
	else{
		if (new_world_src[13]=='2'){
			((widget->root)->WidgetChildren)->brotherWidget->src="images/bWorld1.bmp";
			
		}
		else if (new_world_src[13]=='3'){
			((widget->root)->WidgetChildren)->brotherWidget->src="images/bWorld2.bmp";
			
		}
		else if (new_world_src[13]=='4'){
			((widget->root)->WidgetChildren)->brotherWidget->src="images/bWorld3.bmp";
			
		}
		else if (new_world_src[13]=='5'){
			((widget->root)->WidgetChildren)->brotherWidget->src="images/bWorld4.bmp";
			
		}
		last_world--;
		((widget->root)->WidgetChildren)->brotherWidget->isMarked=2;
		widget->brotherWidget->src="images/gdone.bmp";
		widget->brotherWidget->isMarked=3;
		widget->brotherWidget->brotherWidget->src="images/gBack.bmp";
		widget->brotherWidget->brotherWidget->isMarked=3;
	}
	
	paint_Gui_Tree_on_Screen(main_window);
}

//choose if cat human or machine after click 'done' on the LoadGame menu
void display_cat_type_selection_menu_after_load_game (Widget *widgetNode, int x, int y){

	extern int failure;  extern Widget *current_window;

	Widget *cat_type_selection_menu;    Widget *choose_your_cat_logo;      
	Widget *gback_button;     Widget *bHuman_button;   Widget *gMachine_button;
    Widget *CurrWorld;
	char WorldNumber;
	char WorldPath[19];

	CurrWorld = ( (widgetNode->root)->WidgetChildren)->brotherWidget;
	WorldNumber=CurrWorld->src[13];
	WorldPath[0]='w'; WorldPath[1]='o'; WorldPath[2]='r'; WorldPath[3]='l'; WorldPath[4]='d';
	WorldPath[5]='s'; WorldPath[6]='/'; WorldPath[7]='w'; WorldPath[8]='o'; WorldPath[9]='r';
	WorldPath[10]='l'; WorldPath[11]='d'; WorldPath[12]='_'; WorldPath[13]=WorldNumber;
	WorldPath[14]='.'; WorldPath[15]='t'; WorldPath[16]='x'; WorldPath[17]='t'; WorldPath[18]='\0';
	

	//printf("%s",WorldPath);
	
	LoadDetailsOfGame(WorldPath);
	
	//cat_type_selection_menu's father is new game button in main menu window
	cat_type_selection_menu= Construct_Window("images/orangePaint.bmp",widgetNode, -250, -500, 200,
		200,NULL);
	if(failure)
		return;
	//update the current window field
	current_window = cat_type_selection_menu;

	choose_your_cat_logo = Construct_Label("images/Choose Your Cat.bmp", cat_type_selection_menu,
		200, 100, 300,250, NULL);
	if(failure)
		return;
	choose_your_cat_logo->isMarked = 3;

	bHuman_button = Construct_Button("images/bHuman.bmp", cat_type_selection_menu,
		250, 300, 234,59, display_mouse_type_selection_menu); 
	if(failure)
		return;
	bHuman_button->isMarked = 2;
	
	gMachine_button = Construct_Button("images/gMachine.bmp", cat_type_selection_menu,
		250, 500, 234,59, handle_machine_on_cat_type_selection_menu);
	if(failure)
		return;
	//gMachine_button isn't marked in the default state
    gMachine_button->isMarked = 3;

	gback_button = Construct_Button("images/gBack.bmp", cat_type_selection_menu,
		250, 700, 234,59, handle_back_on_cat_type_selection_menu_after_load_game);
	if(failure)
		return;
	//gback_button isn't marked in the default state
	gback_button->isMarked = 3;

	paint_Gui_Tree_on_Screen(main_window);
	if(failure)
		return;
}

void handle_back_on_load_game_menu (Widget *widget, int x, int y){

	extern int failure;  extern Widget *current_window;

	Widget* main_menu_window;  Widget* newGame; Widget* loadGame; //Widget* game_logo;
	Widget* createGame; Widget* editGame; Widget* quitGame; 
	
	current_window = main_window;
	
	free_All_Widgets(&main_window->WidgetChildren);
	if(failure) {return;}
	
	main_window->WidgetChildren = NULL;

	main_menu_window = Construct_Window("images/orangePaint.bmp",main_window, 0, 0, 200, 200,NULL);
	if(failure)
		return;
	//a label is contained in a window. 
	Construct_Label("images/Cat&MouseLogo.bmp", main_menu_window ,300,100, 300, 250,NULL);
	if(failure)
		return;
	newGame = Construct_Button("images/gNew Game.bmp", main_menu_window ,350,200, 158,44
		,display_cat_type_selection_menu);
	if(failure) {return;}
	newGame->isMarked=3;

	loadGame = Construct_Button("images/bLoadGame.bmp", main_menu_window ,350,300, 158,44
		,display_load_game_selection_menu);
	if(failure) {return;}
	loadGame->isMarked = 2;

	createGame = Construct_Button("images/gCreateGame.bmp", main_menu_window ,350,400, 158,44
		,display_world_builder_tool);
	if(failure) {return;}
	createGame->isMarked = 3;

	editGame = Construct_Button("images/gEditGame.bmp", main_menu_window ,350,500, 158,44
		,display_edit_game_selection_menu);
	if(failure) {return;}
	editGame->isMarked=3;

	quitGame = Construct_Button("images/gQuit.bmp", main_menu_window ,350,600, 158,44
		,handle_quit);
	if(failure) {return;}
	quitGame->isMarked = 3;
	
	paint_Gui_Tree_on_Screen(main_window);
	if(failure)
		return;
	current_window = main_menu_window;  //update the current_window global field to be the 
	//main menu window
	
}

void handle_back_on_cat_type_selection_menu_after_load_game(Widget *widget, int x, int y){
	// widget is back button on cat_type_selection
	// after pressing back button on cat_type_selection, done button should be marked

	extern int failure;  extern Widget *current_window;

	Widget* load_type_selection_menu; Widget* load_game_logo; Widget* world_grey_button;
	Widget* up_button; Widget* down_button; Widget* bdone_button; Widget* gback_button;
	char* WorldImage;
	
	load_type_selection_menu= Construct_Window("images/orangePaint.bmp",widget, -250, -700, 200,
		200,NULL);
	if(failure)
		return;

	//update the current window field
	current_window = load_type_selection_menu;

	load_game_logo = Construct_Label("images/loadGameLogo.bmp", load_type_selection_menu,
		275, 100, 113,25, NULL);
	if(failure)
		return;
	load_game_logo->isMarked = 3;

	if (last_world==1)
		WorldImage="images/gWorld1.bmp";
	else if (last_world==2)
		WorldImage="images/gWorld2.bmp";
	else if (last_world==3)
		WorldImage="images/gWorld3.bmp";
	else if (last_world==4)
		WorldImage="images/gWorld4.bmp";
	else if (last_world==5)
		WorldImage="images/gWorld5.bmp";

	world_grey_button = Construct_Button(WorldImage, load_type_selection_menu,
		250, 300, 153,49, NULL); 
	if(failure)		{return;}
	world_grey_button->isMarked=3;

	up_button = Construct_Button("images/up button.bmp", load_type_selection_menu,
		455, 300, 32,30, handle_up_button_on_load_game);
    if(failure)		{return;}
	up_button->isMarked = 3;

	down_button = Construct_Button("images/down button.bmp", load_type_selection_menu,
		455, 330, 32,29, handle_down_button_on_load_game);
    if(failure)		{return;}
	down_button->isMarked = 3;

	bdone_button = Construct_Button("images/bdone.bmp", load_type_selection_menu,
		250, 500, 234,59, display_cat_type_selection_menu_after_load_game);
	if(failure)		{return;}
	bdone_button->isMarked=2;

	gback_button = Construct_Button("images/gBack.bmp", load_type_selection_menu,
		250, 700, 234,59, handle_back_on_load_game_menu);
	if(failure)		{return;}
	gback_button->isMarked=3;

	paint_Gui_Tree_on_Screen(main_window);
}

void handle_mouse_press_on_world_button(Widget *widget, int x, int y){
	//widget is world button

	if (widget->isMarked==2)
		return;

	if ( strcmp(widget->src, "images/gWorld1.bmp") == 0)
		widget->src="images/bWorld1.bmp";
	else if ( strcmp(widget->src, "images/gWorld2.bmp") == 0)
		widget->src="images/bWorld2.bmp";
	else if ( strcmp(widget->src, "images/gWorld3.bmp") == 0)
		widget->src="images/bWorld3.bmp";
	else if ( strcmp(widget->src, "images/gWorld4.bmp") == 0)
		widget->src="images/bWorld4.bmp";
	else if ( strcmp(widget->src, "images/gWorld5.bmp") == 0)
		widget->src="images/bWorld5.bmp";

	widget->isMarked=2;
	widget->brotherWidget->brotherWidget->brotherWidget->isMarked=3;
	widget->brotherWidget->brotherWidget->brotherWidget->src="images/gdone.bmp";
	widget->brotherWidget->brotherWidget->brotherWidget->brotherWidget->isMarked=3;
	widget->brotherWidget->brotherWidget->brotherWidget->brotherWidget->src="images/gBack.bmp";

	paint_Gui_Tree_on_Screen(main_window);


}


////////////////////////////////////////// GUI FOR CREATE GAME ///////////////////////////

void display_world_builder_tool (Widget *widgetNode, int x, int y){

	extern int failure;  extern Widget *current_window;

	Widget* world_builder__tool; //Widget* new_world_logo; Widget* saveWorld_button;
	//Widget* goToMainMenu_button; Widget* quitProgram_button; Widget* placeMouse_button;
	//Widget* placeCat_button; Widget* placeCheese_button; Widget* placeWall_button;
	 Widget* block; //Widget* placeEmptySpace_button;
	int temp_width =250;   int temp_height = 250;
	int row_index=0; int col_index=0;


	world_builder__tool = Construct_Window("images/orangePaint.bmp",widgetNode, -350,-400, 200,
		200,NULL);
	if(failure)
		return;

	//update the current window field
	current_window = world_builder__tool;

	Construct_Label("images/newWorldLogo.bmp", world_builder__tool,
		350, 25, 150,75, NULL);
	if(failure)
		return;

	Construct_Button("images/GreenSaveWorld.bmp", world_builder__tool,
		50, 100, 138,40, handle_save_world_button);
    if(failure)		{return;}

	Construct_Button("images/GoToMainMenu.bmp", world_builder__tool,
		330, 100, 138,40, goBackToMainMenuFromWorldBuilder);
    if(failure)		{return;}

	Construct_Button("images/GreenQuitProgram.bmp", world_builder__tool,
		600, 100, 138,40, handle_quit);
    if(failure)		{return;}

	Construct_Button("images/GreenPlaceMouse.bmp", world_builder__tool,
		50, 250, 138,40, place_Mouse_On_A_Block);
    if(failure)		{return;}

	Construct_Button("images/GreenPlaceCat.bmp", world_builder__tool,
		50, 350, 138,40, place_Cat_On_A_Block);
    if(failure)		{return;}

	Construct_Button("images/GreenPlaceCheese.bmp", world_builder__tool,
		50, 450, 138,40, place_Cheese_On_A_Block);
    if(failure)		{return;}

	Construct_Button("images/GreenPlaceWall.bmp", world_builder__tool,
		50, 550, 138,40, place_Wall_On_A_Block);
    if(failure)		{return;}

	Construct_Button("images/GreenPlaceEmptySpace.bmp", world_builder__tool,
		50, 650, 138,40, place_EmptySpace_On_A_Block);
    if(failure)		{return;}

	for(row_index = 0; row_index < BOARD_SIZE; row_index++){
		temp_width= 250;
		for(col_index =0; col_index < BOARD_SIZE; col_index++){

			if ((row_index==0)&&(col_index==0)){
				block=Construct_Button("images/marked white 73 on 66.bmp", world_builder__tool,
                                 temp_width, temp_height, 73,66, mark_block);
				if(failure) {return;}
				block->isMarked=2;
			}
			else{
				block=Construct_Button("images/white 73 on 66.bmp", world_builder__tool,
                                 temp_width, temp_height, 73,66, mark_block);
				if(failure) {return;}
				block->isMarked=3;
			}

	
			temp_width = temp_width + 73;
		}
		temp_height= temp_height +66;
	} //closes for loop
	
	//current_window = world_builder__tool;

	paint_Gui_Tree_on_Screen(main_window);
    if(failure)		{return;}

}

void goBackToMainMenuFromWorldBuilder (Widget *widgetNode, int x, int y){
	//widgetNode is 'Go to Main Menu' button 
	
	extern int failure;  extern Widget *current_window;

	Widget* main_menu_window;  Widget* newGame; Widget* loadGame;
	Widget* createGame; Widget* editGame;  //Widget* quitGame; Widget* game_logo;
	
	current_window = main_window;
	
	free_All_Widgets(&main_window->WidgetChildren);
	if(failure) {return;}
	
	main_window->WidgetChildren = NULL;

	main_menu_window = Construct_Window("images/orangePaint.bmp",main_window, 0, 0, 200, 200,NULL);
	if(failure)
		return;
	//a label is contained in a window. 
	Construct_Label("images/Cat&MouseLogo.bmp", main_menu_window ,300,100, 300, 250,NULL);
	if(failure)
		return;
	newGame = Construct_Button("images/gNew Game.bmp", main_menu_window ,350,200, 158,44
		,display_cat_type_selection_menu);
	if(failure) {return;}

	newGame->isMarked=3;

	loadGame = Construct_Button("images/gLoadGame.bmp", main_menu_window ,350,300, 158,44
		,display_load_game_selection_menu);
	if(failure) {return;}

	loadGame->isMarked = 3;

	createGame = Construct_Button("images/bCreateGame.bmp", main_menu_window ,350,400, 158,44
		,display_world_builder_tool);
	if(failure) {return;}

	createGame->isMarked = 2;
	editGame = Construct_Button("images/gEditGame.bmp", main_menu_window ,350,500, 158,44
		,display_edit_game_selection_menu);
	if(failure) {return;}

	editGame->isMarked=3;

	Construct_Button("images/gQuit.bmp", main_menu_window ,350,600, 158,44
		,handle_quit);
	if(failure) {return;}

	
	paint_Gui_Tree_on_Screen(main_window);
	if(failure)
		return;
	current_window = main_menu_window;  //update the current_window global field to be the 
	//main menu window
	if(failure) {return;}
}

void mark_block (Widget *widgetNode, int x, int y){
	//widgetNode is the block

	extern Widget *current_window;

	Widget* block;
	int i;

	if ( (strcmp(widgetNode->src, "images/marked white 73 on 66.bmp") == 0)
		|| (strcmp(widgetNode->src, "images/markedMouse.bmp") == 0)
	|| (strcmp(widgetNode->src, "images/markedCat.bmp") == 0) 
	|| (strcmp(widgetNode->src, "images/markedCheese.bmp") == 0) ||
	(strcmp(widgetNode->src, "images/markedWall.bmp") == 0) ){
		//block is already marked
		widgetNode->isMarked=2;
		return;
	}
	
	else if ( strcmp(widgetNode->src, "images/white 73 on 66.bmp") == 0){ 
		
		widgetNode->src="images/marked white 73 on 66.bmp";                                                    
	} 
	else if ( strcmp(widgetNode->src, "images/catBlock 73 on 66.bmp") == 0){ 
		widgetNode->src="images/markedCat.bmp";                                                    
	} 
	else if ( strcmp(widgetNode->src, "images/cheeseBlock 73 on 66.bmp") == 0){ 
		widgetNode->src="images/markedCheese.bmp";                                                    
	} 
	else if ( strcmp(widgetNode->src, "images/mouseBlock 73 on 66.bmp") == 0){ 
		widgetNode->src="images/markedMouse.bmp";                                                    
	} 
	else if ( strcmp(widgetNode->src, "images/wallBlock 73 on 66.bmp") == 0){ 
		widgetNode->src="images/markedWall.bmp";                                                    
	} 
	widgetNode->isMarked=2;
	block=current_window->WidgetChildren;
	for (i=0;i<9;i++)
		block=block->brotherWidget; //getting to first block (top left)
	while (block!=NULL){
		if (block!=widgetNode){
			if ( strcmp(block->src, "images/marked white 73 on 66.bmp") == 0){
				block->src="images/white 73 on 66.bmp";
			}
			else if ( strcmp(block->src, "images/markedCat.bmp") == 0)
				block->src="images/catBlock 73 on 66.bmp";
			else if ( strcmp(block->src, "images/markedCheese.bmp") == 0)
				block->src="images/cheeseBlock 73 on 66.bmp";
			else if ( strcmp(block->src, "images/markedMouse.bmp")== 0)
				block->src="images/mouseBlock 73 on 66.bmp";
			else if ( strcmp(block->src, "images/markedWall.bmp") == 0)
				block->src="images/wallBlock 73 on 66.bmp";
			block->isMarked=3;
		}
		
		block=block->brotherWidget;
	}
	
	
	paint_Gui_Tree_on_Screen(main_window);
	

}

void place_Mouse_On_A_Block (Widget *widgetNode, int x, int y){
	//widgetNode is 'Place Mouse' button

	extern Widget *current_window;

	Widget* block;
	int i;
	
	block=current_window->WidgetChildren;

	for (i=0;i<9;i++)
		block=block->brotherWidget; //getting to first block (top left)

	while (block!=NULL){
		if (block->isMarked==2)
			block->src="images/markedMouse.bmp";
		else{
			if ( (strcmp(block->src, "images/mouseBlock 73 on 66.bmp") == 0)
				|| (strcmp(block->src, "images/markedMouse.bmp") == 0) )
				block->src="images/white 73 on 66.bmp";
			block->isMarked=3;
		}
		block=block->brotherWidget;
	}
	MainGame->StartPlayer=MOUSE;
	paint_Gui_Tree_on_Screen(main_window);
}

void place_Cat_On_A_Block (Widget *widgetNode, int x, int y){
	//widgetNode is 'Place Cat' button

	extern Widget *current_window;

	Widget* block;
	int i;
	
	block=current_window->WidgetChildren;

	for (i=0;i<9;i++)
		block=block->brotherWidget; //getting to first block (top left)

	while (block!=NULL){
		if (block->isMarked==2)
			block->src="images/markedCat.bmp";
		else{
			if ( (strcmp(block->src, "images/catBlock 73 on 66.bmp") == 0)
				|| (strcmp(block->src, "images/markedCat.bmp") == 0) )
				block->src="images/white 73 on 66.bmp";
			block->isMarked=3;
		}
		block=block->brotherWidget;
	}
	MainGame->StartPlayer=CAT;
	paint_Gui_Tree_on_Screen(main_window);
}

void place_Cheese_On_A_Block (Widget *widgetNode, int x, int y){
	//widgetNode is 'Place Cheese' button

	extern Widget *current_window;

	Widget* block;
	int i;
	
	block=current_window->WidgetChildren;

	for (i=0;i<9;i++)
		block=block->brotherWidget; //getting to first block (top left)

	while (block!=NULL){
		if (block->isMarked==2)
			block->src="images/markedCheese.bmp";
		else{
			if ( (strcmp(block->src, "images/cheeseBlock 73 on 66.bmp") == 0) ||
				(strcmp(block->src, "images/markedCheese.bmp") == 0) )
				block->src="images/white 73 on 66.bmp";
			block->isMarked=3;
		}
		block=block->brotherWidget;
	}

	paint_Gui_Tree_on_Screen(main_window);
}

void place_Wall_On_A_Block (Widget *widgetNode, int x, int y){
	//widgetNode is 'Place Wall' button

	extern Widget *current_window;

	Widget* block;
	int i;
	
	block=current_window->WidgetChildren;

	for (i=0;i<9;i++)
		block=block->brotherWidget; //getting to first block (top left)

	while (block!=NULL){
		if (block->isMarked==2)
			block->src="images/markedWall.bmp";
		else
			block->isMarked=3;
		block=block->brotherWidget;
	}

	paint_Gui_Tree_on_Screen(main_window);
}

void place_EmptySpace_On_A_Block (Widget *widgetNode, int x, int y){
	//widgetNode is 'Place Empty Space' button

	extern Widget *current_window;

	Widget* block;
	int i;
	
	block=current_window->WidgetChildren;

	for (i=0;i<9;i++)
		block=block->brotherWidget; //getting to first block (top left)

	while (block!=NULL){
		if (block->isMarked==2)
			block->src="images/marked white 73 on 66.bmp";
		else
			block->isMarked=3;
		block=block->brotherWidget;
	}

	paint_Gui_Tree_on_Screen(main_window);

}

void handle_save_world_button (Widget *widgetNode, int x, int y){
	//widgetNode is 'Save World' button

	Widget* block; 
	int i,j;
	//int row=0; int col=0; 

	block=widgetNode; //now block is 'Save World' button

	for (i=0;i<8;i++)
		block=block->brotherWidget; //getting to first block (top left)

	//update MainGame Board
	
	for (i=0;i<BOARD_SIZE;i++){
		for (j=0;j<BOARD_SIZE;j++){
			if ( (strcmp(block->src, "images/catBlock 73 on 66.bmp") == 0) ||
				(strcmp(block->src, "images/markedCat.bmp") == 0) )
				MainGame->GameBoard[i][j]=CAT_ON_BOARD;
			else if ( (strcmp(block->src, "images/cheeseBlock 73 on 66.bmp") == 0) ||
				(strcmp(block->src, "images/markedCheese.bmp") == 0) )
				MainGame->GameBoard[i][j]=CHEESE_ON_BOARD;
			else if ( (strcmp(block->src, "images/wallBlock 73 on 66.bmp") == 0) ||
				(strcmp(block->src, "images/markedWall.bmp") == 0) )
				MainGame->GameBoard[i][j]=WALL_ON_BOARD;
			else if ( (strcmp(block->src, "images/mouseBlock 73 on 66.bmp") == 0) ||
				(strcmp(block->src, "images/markedMouse.bmp") == 0) )
				MainGame->GameBoard[i][j]=MOUSE_ON_BOARD;
			else if ( (strcmp(block->src, "images/white 73 on 66.bmp") == 0) ||
				(strcmp(block->src, "images/marked white 73 on 66.bmp") == 0) )
				MainGame->GameBoard[i][j]=EMPTY_ON_BOARD;
			block=block->brotherWidget;
		}
	}
	
	//checking if cat, mouse or cheese is missing from board
	if ((!(IsThereCatOnBoard()))||(!(IsThereMouseOnBoard()))||(!(IsThereCheeseOnBoard()))) {
		
		handle_invalid_world_for_save_button( widgetNode, -50, -100 );
	}
	else{
		last_world=1;
		handle_valid_world_for_save_button( widgetNode, -50, -100 );
	}

}

void handle_invalid_world_for_save_button (Widget *widgetNode, int x, int y){
	//widgetNode is 'Save World' button
	extern int failure;  extern Widget *current_window;

	Widget* invalid_world_menu; Widget* cannot_save_invalid__world_logo; //Widget* missing_item_logo;
	Widget* b_back_button;
	
	invalid_world_menu= Construct_Window("images/orangePaint.bmp",widgetNode,-50, -100, 200,
		200,NULL);
	if(failure)
		return;
	//update the current window field
	current_window = invalid_world_menu;

	cannot_save_invalid__world_logo = Construct_Label("images/CannotSaveInvalidWorldLogo.bmp", invalid_world_menu,
		150, 100, 400,54, NULL);
	if(failure)
		return;
	cannot_save_invalid__world_logo->isMarked = 3;

	//if cat is missing, prints a message. otherwise, if mouse is missing, prints a message.otherwise,
	//of cheese is missing, prints a message. always prints only one message.

	if (!(IsThereCatOnBoard())){
		Construct_Label("images/CatIsMissingLogo.bmp", invalid_world_menu,
		260, 200, 300,63, NULL);
	if(failure)
		return;
	}
	else if (!(IsThereMouseOnBoard())){
		Construct_Label("images/MouseIsMissingLogo.bmp", invalid_world_menu,
		250, 200, 300,63, NULL);
	if(failure)
		return;
	}
	else if (!(IsThereCheeseOnBoard())){
		Construct_Label("images/CheeseIsMissingLogo.bmp", invalid_world_menu,
		250, 200, 300,63, NULL);
	if(failure)
		return;
	}
	
	b_back_button = Construct_Button("images/bBack.bmp", invalid_world_menu,
		300, 500, 234,59, handle_back_button_on_invalid_world_menu);
	if(failure)
		return;
	b_back_button->isMarked = 2;

	paint_Gui_Tree_on_Screen(main_window);
}

void handle_back_button_on_invalid_world_menu (Widget *widgetNode, int x, int y){
	//widgetNode is 'Back' button on invalid world menu
	extern int failure;  extern Widget *current_window;

	Widget* Save_World_Button;


	Save_World_Button=widgetNode->root->root;
	free_All_Widgets(&(Save_World_Button->WidgetChildren)); //free all childs of 'Save World' button
	Save_World_Button->WidgetChildren=NULL;
	current_window=Save_World_Button->root;

	paint_Gui_Tree_on_Screen(main_window);
	if(failure)
		return;
}

void handle_valid_world_for_save_button (Widget *widgetNode, int x, int y){
	//widgetNode is 'Save World' button
	extern int failure;  extern Widget *current_window;

	Widget* save_world_selection_menu; Widget* save_world_logo; Widget* world_1_blue_button;
	Widget* up_button; Widget* down_button; Widget* gdone_button; Widget* gback_button;

	
	save_world_selection_menu= Construct_Window("images/orangePaint.bmp",widgetNode, -50,-100, 200,
		200,NULL);
	if(failure)
		return;

	//update the current window field
	current_window = save_world_selection_menu;

	save_world_logo = Construct_Label("images/saveWorldLogo.bmp", save_world_selection_menu,
		300, 100, 116,25, NULL);
	if(failure)
		return;
	save_world_logo->isMarked = 3;

	world_1_blue_button = Construct_Button("images/bWorld1.bmp", save_world_selection_menu,
		250, 300, 204,59, handle_mouse_press_on_world_button); 
	if(failure)		{return;}
	world_1_blue_button->isMarked=2;

	up_button = Construct_Button("images/up button.bmp", save_world_selection_menu,
		455, 300, 32,30, handle_up_button_on_load_game);
    if(failure)		{return;}
	up_button->isMarked = 3;

	down_button = Construct_Button("images/down button.bmp", save_world_selection_menu,
		455, 330, 32,29, handle_down_button_on_load_game);
    if(failure)		{return;}
	down_button->isMarked = 3;

	gdone_button = Construct_Button("images/gdone.bmp", save_world_selection_menu,
		250, 500, 234,59, handle_done_button_for_saving_valid_world);
	if(failure)		{return;}
	gdone_button->isMarked=3;

	gback_button = Construct_Button("images/gBack.bmp", save_world_selection_menu,
		250, 700, 234,59, handle_back_button_on_invalid_world_menu);
	if(failure)		{return;}
	gback_button->isMarked=3;

	paint_Gui_Tree_on_Screen(main_window);
}

void handle_done_button_for_saving_valid_world (Widget *widgetNode, int x, int y){
	//widgetNode is 'Done' button on the save_valid_world menu

	Widget* chosen_world;
	char world_number; char WorldPath[19];

	chosen_world=widgetNode->root->WidgetChildren->brotherWidget;
	world_number=chosen_world->src[13];

	WorldPath[0]='w'; WorldPath[1]='o'; WorldPath[2]='r'; WorldPath[3]='l'; WorldPath[4]='d';
	WorldPath[5]='s'; WorldPath[6]='/'; WorldPath[7]='w'; WorldPath[8]='o'; WorldPath[9]='r';
	WorldPath[10]='l'; WorldPath[11]='d'; WorldPath[12]='_'; WorldPath[13]=world_number;
	WorldPath[14]='.'; WorldPath[15]='t'; WorldPath[16]='x'; WorldPath[17]='t'; WorldPath[18]='\0';

	SaveDetailsOfGame(WorldPath); //details of game were already updated from gui to MainGame in 
	                              //'handle_save_world_button' function

	handle_back_button_on_invalid_world_menu (widgetNode,-250, -500);
	


}

void handle_up_arrow_on_world_builder (Widget *currentWindow){

	extern int failure;  extern Widget *current_window;

	Widget* block; 
	int i; 
	int count=0;

	block=current_window->WidgetChildren;
	for (i=0;i<9;i++)
		block=block->brotherWidget; //getting to first block (top left)

	while (block!=NULL){
		if (block->isMarked==2)  //for sure there will be a marked block
			break;
		
		block=block->brotherWidget;
		count++;
	}
	if (count<7){ //means we are in first line and up arrow does nothing
		paint_Gui_Tree_on_Screen(main_window);
			if(failure)		{return;}
			return;
	}
	block=current_window->WidgetChildren;
	for (i=0;i<9;i++)
		block=block->brotherWidget; //getting to first block (top left)

	for (i=0;i<(count-7);i++) //getting to wanted block (according to up arrow)
		block=block->brotherWidget;

	mark_block(block,0,0);
}

void handle_down_arrow_on_world_builder (Widget *currentWindow){

	extern int failure;  extern Widget *current_window;

	Widget* block; 
	int i;

	block=current_window->WidgetChildren;
	for (i=0;i<9;i++)
		block=block->brotherWidget; //getting to first block (top left)
	while (block!=NULL){
		if (block->isMarked==2)  //for sure there will be a marked block
			break;
		
		block=block->brotherWidget;
	}
	for (i=0;i<7;i++){
		block=block->brotherWidget; //getting to wanted block (according to down arrow)
		if (block==NULL){ //means we are in last line and down arrow does nothing
			paint_Gui_Tree_on_Screen(main_window);
			if(failure)		{return;}
			return;
		}
	}
	mark_block(block,0,0);
}

void handle_left_arrow_on_world_builder (Widget *currentWindow){

	extern int failure;  extern Widget *current_window;

	Widget* block; Widget* PrevBlock;
	int i;

	block=current_window->WidgetChildren;
	for (i=0;i<9;i++)
		block=block->brotherWidget; //getting to first block (top left)

	i=1;
	while (block!=NULL){
		
		if (block->isMarked==2)  //for sure there will be a marked block
			break;
		
		PrevBlock=block;
		block=block->brotherWidget;
		i++;
	}
	if (i%7==1){ // means we are in leftest column and left arrow does nothing
		paint_Gui_Tree_on_Screen(main_window);
			if(failure)		{return;}
			return;
	}
	mark_block(PrevBlock,0,0);

}

void handle_right_arrow_on_world_builder (Widget *currentWindow){

	extern int failure;  extern Widget *current_window;

	Widget* block; 
	int i;

	block=current_window->WidgetChildren;
	for (i=0;i<9;i++)
		block=block->brotherWidget; //getting to first block (top left)

	i=1;
	while (block!=NULL){
		if (block->isMarked==2)  //for sure there will be a marked block
			break;
		
		block=block->brotherWidget;
		i++;
	}
	if (i%7==0){ // means we are in rightest column and right arrow does nothing
		paint_Gui_Tree_on_Screen(main_window);
			if(failure)		{return;}
			return;
	}
	mark_block(block->brotherWidget,0,0);
}

void handle_place_mouse_by_keyboard_on_world_builder (Widget *currentWindow){

	extern Widget *current_window;

	Widget* block; 
	int i;

	block=current_window->WidgetChildren;
	for (i=0;i<4;i++)
		block=block->brotherWidget; //getting to place mouse button
	place_Mouse_On_A_Block(block,0,0);
}

void handle_place_cat_by_keyboard_on_world_builder (Widget *currentWindow){

	extern Widget *current_window;

	Widget* block; 
	int i;

	block=current_window->WidgetChildren;
	for (i=0;i<5;i++)
		block=block->brotherWidget; //getting to place cat button
	place_Cat_On_A_Block(block,0,0);

}

void handle_place_cheese_by_keyboard_on_world_builder (Widget *currentWindow){

	extern Widget *current_window;

	Widget* block; 
	int i;

	block=current_window->WidgetChildren;
	for (i=0;i<6;i++)
		block=block->brotherWidget; //getting to place cheese button
	place_Cheese_On_A_Block(block,0,0);

}

void handle_place_wall_by_keyboard_on_world_builder (Widget *currentWindow){

	extern Widget *current_window;

	Widget* block; 
	int i;

	block=current_window->WidgetChildren;
	for (i=0;i<7;i++)
		block=block->brotherWidget; //getting to place wall button
	place_Wall_On_A_Block(block,0,0);
}

void handle_place_EmptySpace_by_keyboard_on_world_builder (Widget *currentWindow){

	extern Widget *current_window;

	Widget* block; 
	int i;

	block=current_window->WidgetChildren;
	for (i=0;i<8;i++)
		block=block->brotherWidget; //getting to place wall button
	place_EmptySpace_On_A_Block(block,0,0);

}





////////////////////////////////////////// GUI FOR EDIT GAME  ////////////////////////////
void display_edit_game_selection_menu (Widget *widgetNode, int x, int y){

	extern int failure;  extern Widget *current_window;

	Widget *edit_type_selection_menu; Widget* edit_game_logo; Widget* world_1_blue_button;
	Widget* up_button; Widget* down_button; Widget* gdone_button; Widget* gback_button;

	last_world=1;
	edit_type_selection_menu= Construct_Window("images/orangePaint.bmp",widgetNode, -350,-500, 200,
		200,NULL);
	if(failure)
		return;

	//update the current window field
	current_window = edit_type_selection_menu;

	edit_game_logo = Construct_Label("images/editGameLogo.bmp", edit_type_selection_menu,
		275, 100, 105,21, NULL);
	if(failure)
		return;
	edit_game_logo->isMarked = 3;

	world_1_blue_button = Construct_Button("images/bWorld1.bmp", edit_type_selection_menu,
		250, 300, 204,59, handle_mouse_press_on_world_button); 
	if(failure)		{return;}
	world_1_blue_button->isMarked=2;

	up_button = Construct_Button("images/up button.bmp", edit_type_selection_menu,
		455, 300, 32,30, handle_up_button_on_load_game);
    if(failure)		{return;}
	up_button->isMarked = 3;

	down_button = Construct_Button("images/down button.bmp", edit_type_selection_menu,
		455, 330, 32,29, handle_down_button_on_load_game);
    if(failure)		{return;}
	down_button->isMarked = 3;

	gdone_button = Construct_Button("images/gdone.bmp", edit_type_selection_menu,
		250, 500, 234,59, handle_done_on_edit_game_menu);
	if(failure)		{return;}
	gdone_button->isMarked = 3;

	gback_button = Construct_Button("images/gBack.bmp", edit_type_selection_menu,
		250, 700, 234,59, handle_back_on_edit_game_menu);
	if(failure)		{return;}
	gback_button->isMarked = 3;

	paint_Gui_Tree_on_Screen(main_window); 
}


void handle_done_on_edit_game_menu (Widget *widgetNode, int x, int y){
	//widgetNode is 'Done' button on Edit Game menu
	extern int failure;  extern Widget *current_window;

	Widget* DoneFather; Widget* world_builder_tool; //Widget* WorldLogo; Widget* saveWorld_button;
	//Widget* goToMainMenu_button; Widget* quitProgram_button; Widget* placeMouse_button; 
	//Widget* placeCat_button; Widget* placeCheese_button; Widget* placeWall_button; Widget* placeEmptySpace_button;
	Widget* block;
	
	char WorldToEdit;
	
	char WorldTextFile[19];
	int temp_width =250;   int temp_height = 250;
	int row_index=0; int col_index=0;
	//char WorldLogoPath[22]={0};

	DoneFather=widgetNode->root;
	WorldToEdit=DoneFather->WidgetChildren->brotherWidget->src[13];

	free_All_Widgets( &(main_window->WidgetChildren) );
	main_window->WidgetChildren = NULL;

	world_builder_tool = Construct_Window("images/orangePaint.bmp",main_window, 0,0, 200,
		200,NULL);
	if(failure)
		return;

	current_window=world_builder_tool;

	/*WorldLogoPath[0]='i'; WorldLogoPath[1]='m'; WorldLogoPath[2]='a'; WorldLogoPath[3]='g'; 
	WorldLogoPath[4]='e'; WorldLogoPath[5]='s'; WorldLogoPath[6]='/'; WorldLogoPath[7]='W';
	WorldLogoPath[8]='o'; WorldLogoPath[9]='r'; WorldLogoPath[10]='l'; WorldLogoPath[11]='d'; 
	WorldLogoPath[12]=WorldToEdit; WorldLogoPath[13]='L'; WorldLogoPath[14]='o'; WorldLogoPath[15]='g'; 
	WorldLogoPath[16]='o'; WorldLogoPath[17]='.'; WorldLogoPath[18]='b'; WorldLogoPath[19]='m';
	WorldLogoPath[20]='p'; WorldLogoPath[21]='\0';*/


	if (WorldToEdit=='1'){
	Construct_Label("images/World1Logo.bmp", world_builder_tool, 350,20, 200,
		200,NULL);
	if(failure)
		return;
	}
	else if (WorldToEdit=='2'){
	Construct_Label("images/World2Logo.bmp", world_builder_tool, 350,20, 200,
		200,NULL);
	if(failure)
		return;
	}
	else if (WorldToEdit=='3'){
	Construct_Label("images/World3Logo.bmp", world_builder_tool, 350,20, 200,
		200,NULL);
	if(failure)
		return;
	}
	else if (WorldToEdit=='4'){
	Construct_Label("images/World4Logo.bmp", world_builder_tool, 350,20, 200,
		200,NULL);
	if(failure)
		return;
	}
	else if (WorldToEdit=='5'){
	Construct_Label("images/World5Logo.bmp", world_builder_tool, 350,20, 200,
		200,NULL);
	if(failure)
		return;
	
	}

	Construct_Button("images/GreenSaveWorld.bmp", world_builder_tool,
		50, 100, 138,40, handle_save_world_button_after_edit);
    if(failure)		{return;}

	Construct_Button("images/GoToMainMenu.bmp", world_builder_tool,
		330, 100, 138,40, handle_back_on_edit_game_menu);
    if(failure)		{return;}

	Construct_Button("images/GreenQuitProgram.bmp", world_builder_tool,
		600, 100, 138,40, handle_quit);
    if(failure)		{return;}

	Construct_Button("images/GreenPlaceMouse.bmp", world_builder_tool,
		50, 250, 138,40, place_Mouse_On_A_Block);
    if(failure)		{return;}

	Construct_Button("images/GreenPlaceCat.bmp", world_builder_tool,
		50, 350, 138,40, place_Cat_On_A_Block);
    if(failure)		{return;}

	Construct_Button("images/GreenPlaceCheese.bmp", world_builder_tool,
		50, 450, 138,40, place_Cheese_On_A_Block);
    if(failure)		{return;}

	Construct_Button("images/GreenPlaceWall.bmp", world_builder_tool,
		50, 550, 138,40, place_Wall_On_A_Block);
    if(failure)		{return;}

	Construct_Button("images/GreenPlaceEmptySpace.bmp", world_builder_tool,
		50, 650, 138,40, place_EmptySpace_On_A_Block);
    if(failure)		{return;}

	//loading details from world file to Gui

	WorldTextFile[0]='w'; WorldTextFile[1]='o'; WorldTextFile[2]='r'; WorldTextFile[3]='l';
	WorldTextFile[4]='d'; WorldTextFile[5]='s'; WorldTextFile[6]='/'; WorldTextFile[7]='w';
	WorldTextFile[8]='o'; WorldTextFile[9]='r'; WorldTextFile[10]='l'; WorldTextFile[11]='d';
	WorldTextFile[12]='_'; WorldTextFile[13]=WorldToEdit; WorldTextFile[14]='.'; WorldTextFile[15]='t';
	WorldTextFile[16]='x'; WorldTextFile[17]='t'; WorldTextFile[18]='\0';

	LoadDetailsOfGame(WorldTextFile);

	for(row_index = 0; row_index < BOARD_SIZE; row_index++){
		temp_width= 250;
		for(col_index =0; col_index < BOARD_SIZE; col_index++){

			if ((row_index==0)&&(col_index==0)){
				if (MainGame->GameBoard[row_index][col_index]==EMPTY_ON_BOARD){
				block=Construct_Button("images/marked white 73 on 66.bmp", world_builder_tool,
                                 temp_width, temp_height, 73,66, mark_block);
				if(failure) {return;}
				}
				else if (MainGame->GameBoard[row_index][col_index]==MOUSE_ON_BOARD){
				block=Construct_Button("images/markedMouse.bmp", world_builder_tool,
                                 temp_width, temp_height, 73,66, mark_block);
				if(failure) {return;}
				}
				else if (MainGame->GameBoard[row_index][col_index]==CAT_ON_BOARD){
				block=Construct_Button("images/markedCat.bmp", world_builder_tool,
                                 temp_width, temp_height, 73,66, mark_block);
				if(failure) {return;}
				}
				else if (MainGame->GameBoard[row_index][col_index]==CHEESE_ON_BOARD){
				block=Construct_Button("images/markedCheese.bmp", world_builder_tool,
                                 temp_width, temp_height, 73,66, mark_block);
				if(failure) {return;}
				}
				else if (MainGame->GameBoard[row_index][col_index]==WALL_ON_BOARD){
				block=Construct_Button("images/markedWall.bmp", world_builder_tool,
                                 temp_width, temp_height, 73,66, mark_block);
				if(failure) {return;}
				}
				block->isMarked=2;
			}
			else{
				if (MainGame->GameBoard[row_index][col_index]==EMPTY_ON_BOARD){
				block=Construct_Button("images/white 73 on 66.bmp", world_builder_tool,
                                 temp_width, temp_height, 73,66, mark_block);
				if(failure) {return;}
				}
				else if (MainGame->GameBoard[row_index][col_index]==MOUSE_ON_BOARD){
				block=Construct_Button("images/mouseBlock 73 on 66.bmp", world_builder_tool,
                                 temp_width, temp_height, 73,66, mark_block);
				if(failure) {return;}
				}
				else if (MainGame->GameBoard[row_index][col_index]==CAT_ON_BOARD){
				block=Construct_Button("images/catBlock 73 on 66.bmp", world_builder_tool,
                                 temp_width, temp_height, 73,66, mark_block);
				if(failure) {return;}
				}
				else if (MainGame->GameBoard[row_index][col_index]==CHEESE_ON_BOARD){
				block=Construct_Button("images/cheeseBlock 73 on 66.bmp", world_builder_tool,
                                 temp_width, temp_height, 73,66, mark_block);
				if(failure) {return;}
				}
				else if (MainGame->GameBoard[row_index][col_index]==WALL_ON_BOARD){
				block=Construct_Button("images/wallBlock 73 on 66.bmp", world_builder_tool,
                                 temp_width, temp_height, 73,66, mark_block);
				if(failure) {return;}
				}
				block->isMarked=3;
			}

	
			temp_width = temp_width + 75;
		}
		temp_height= temp_height +74;
	} //closes for loop

	paint_Gui_Tree_on_Screen(main_window);
    if(failure)		{return;}


}

void handle_back_on_edit_game_menu (Widget *widgetNode, int x, int y){
	//widgetNode is 'Back' button on edit_game_menu
	extern int failure;  extern Widget *current_window;
	
	Widget* main_menu_window; Widget* game_logo; Widget* newGame; Widget* loadGame;
	Widget* createGame; Widget* editGame; Widget* quitGame; 
	
	current_window = main_window;
	
	free_All_Widgets(&main_window->WidgetChildren);
	if(failure) {return;}
	
	main_window->WidgetChildren = NULL;

	main_menu_window = Construct_Window("images/orangePaint.bmp",main_window, 0, 0, 200, 200,NULL);
	if(failure)
		return;
	//a label is contained in a window. 
	game_logo = Construct_Label("images/Cat&MouseLogo.bmp", main_menu_window ,300,100, 300, 250,NULL);
	if(failure)
		return;
	game_logo->isMarked = 3;

	newGame = Construct_Button("images/gNew Game.bmp", main_menu_window ,350,200, 158,44
		,display_cat_type_selection_menu);
	if(failure) {return;}
	newGame->isMarked=3;

	loadGame = Construct_Button("images/gLoadGame.bmp", main_menu_window ,350,300, 158,44
		,display_load_game_selection_menu);
	if(failure) {return;}
	loadGame->isMarked = 3;

	createGame = Construct_Button("images/gCreateGame.bmp", main_menu_window ,350,400, 158,44
		,display_world_builder_tool);
	if(failure) {return;}
	createGame->isMarked = 3;

	editGame = Construct_Button("images/bEditGame.bmp", main_menu_window ,350,500, 158,44
		,display_edit_game_selection_menu);
	if(failure) {return;}
	editGame->isMarked=2;

	quitGame = Construct_Button("images/gQuit.bmp", main_menu_window ,350,600, 158,44
		,handle_quit);
	if(failure) {return;}
	quitGame->isMarked=3;

	
	paint_Gui_Tree_on_Screen(main_window);
	if(failure)
		return;
	current_window = main_menu_window;  //update the current_window global field to be the 
	//main menu window
	if(failure) {return;}

}

void handle_save_world_button_after_edit (Widget *widgetNode, int x, int y){
	//widgetNode is 'Save World' button

	Widget* block; 
	int i,j;
	//int row=0; int col=0; 

	block=widgetNode; //now block is 'Save World' button

	for (i=0;i<8;i++)
		block=block->brotherWidget; //getting to first block (top left)

	//update MainGame Board
	
	for (i=0;i<BOARD_SIZE;i++){
		for (j=0;j<BOARD_SIZE;j++){
			if ( (strcmp(block->src, "images/catBlock 73 on 66.bmp") == 0) ||
				(strcmp(block->src, "images/markedCat.bmp") == 0) )
				MainGame->GameBoard[i][j]=CAT_ON_BOARD;
			else if ( (strcmp(block->src, "images/cheeseBlock 73 on 66.bmp") == 0) ||
				(strcmp(block->src, "images/markedCheese.bmp") == 0) )
				MainGame->GameBoard[i][j]=CHEESE_ON_BOARD;
			else if ( (strcmp(block->src, "images/wallBlock 73 on 66.bmp") == 0) ||
				(strcmp(block->src, "images/markedWall.bmp") == 0) )
				MainGame->GameBoard[i][j]=WALL_ON_BOARD;
			else if ( (strcmp(block->src, "images/mouseBlock 73 on 66.bmp") == 0) ||
				(strcmp(block->src, "images/markedMouse.bmp") == 0) )
				MainGame->GameBoard[i][j]=MOUSE_ON_BOARD;
			else if ( (strcmp(block->src, "images/white 73 on 66.bmp") == 0) ||
				(strcmp(block->src, "images/marked white 73 on 66.bmp") == 0) )
				MainGame->GameBoard[i][j]=EMPTY_ON_BOARD;
			block=block->brotherWidget;
		}
	}
	
	//checking if cat, mouse or cheese is missing from board
	if ((!(IsThereCatOnBoard()))||(!(IsThereMouseOnBoard()))||(!(IsThereCheeseOnBoard()))) {
		
		handle_invalid_world_for_save_button( widgetNode, -50, -100 );
	}
	else{
		handle_valid_world_for_save_button_after_edit( widgetNode, -50, -100 );
	}


}

void handle_valid_world_for_save_button_after_edit (Widget *widgetNode, int x, int y){
	//widgetNode is 'Save World' button
	extern int failure;  extern Widget *current_window;

	Widget* save_world_selection_menu; Widget* save_world_logo; Widget* world_blue_button;
	Widget* up_button; Widget* down_button; Widget* gdone_button; Widget* gback_button;

	
	save_world_selection_menu= Construct_Window("images/orangePaint.bmp",widgetNode, -50,-100, 200,
		200,NULL);
	if(failure)
		return;

	//update the current window field
	current_window = save_world_selection_menu;

	save_world_logo = Construct_Label("images/saveWorldLogo.bmp", save_world_selection_menu,
		300, 100, 116,25, NULL);
	if(failure)
		return;
	save_world_logo->isMarked = 3;

	if (last_world==1){
	world_blue_button = Construct_Button("images/bWorld1.bmp", save_world_selection_menu,
		250, 300, 158,44, handle_mouse_press_on_world_button); 
	if(failure)		{return;}
	}
	else if (last_world==2){
	world_blue_button = Construct_Button("images/bWorld2.bmp", save_world_selection_menu,
		250, 300, 158,44, handle_mouse_press_on_world_button); 
	if(failure)		{return;}
	}
	else if (last_world==3){
	world_blue_button = Construct_Button("images/bWorld3.bmp", save_world_selection_menu,
		250, 300, 158,44, handle_mouse_press_on_world_button); 
	if(failure)		{return;}
	}
	else if (last_world==4){
	world_blue_button = Construct_Button("images/bWorld4.bmp", save_world_selection_menu,
		250, 300, 158,44, handle_mouse_press_on_world_button); 
	if(failure)		{return;}
	}
	else if (last_world==5){
	world_blue_button = Construct_Button("images/bWorld5.bmp", save_world_selection_menu,
		250, 300, 158,44, handle_mouse_press_on_world_button); 
	if(failure)		{return;}
	}

	world_blue_button->isMarked=2;

	up_button = Construct_Button("images/up button.bmp", save_world_selection_menu,
		408, 300, 32,30, handle_up_button_on_load_game);
    if(failure)		{return;}
	up_button->isMarked = 3;

	down_button = Construct_Button("images/down button.bmp", save_world_selection_menu,
		408, 330, 32,29, handle_down_button_on_load_game);
    if(failure)		{return;}
	down_button->isMarked = 3;

	gdone_button = Construct_Button("images/gdone.bmp", save_world_selection_menu,
		250, 500, 234,59, handle_done_button_for_saving_valid_world_after_edit);
	if(failure)		{return;}
	gdone_button->isMarked=3;

	gback_button = Construct_Button("images/gBack.bmp", save_world_selection_menu,
		250, 700, 234,59, handle_back_button_on_invalid_world_menu);
	if(failure)		{return;}
	gback_button->isMarked=3;

	paint_Gui_Tree_on_Screen(main_window);
}

void handle_done_button_for_saving_valid_world_after_edit (Widget *widgetNode, int x, int y){
	//widgetNode is 'Done' button on the save_valid_world menu

	extern int failure;  extern Widget *current_window;

	Widget* chosen_world; Widget* Save_World_Button;
	char world_number; char WorldPath[19];

	chosen_world=widgetNode->root->WidgetChildren->brotherWidget;
	world_number=chosen_world->src[13];

	WorldPath[0]='w'; WorldPath[1]='o'; WorldPath[2]='r'; WorldPath[3]='l'; WorldPath[4]='d';
	WorldPath[5]='s'; WorldPath[6]='/'; WorldPath[7]='w'; WorldPath[8]='o'; WorldPath[9]='r';
	WorldPath[10]='l'; WorldPath[11]='d'; WorldPath[12]='_'; WorldPath[13]=world_number;
	WorldPath[14]='.'; WorldPath[15]='t'; WorldPath[16]='x'; WorldPath[17]='t'; WorldPath[18]='\0';

	SaveDetailsOfGame(WorldPath); //details of game were already updated from gui to MainGame in 
	                              //'handle_save_world_button' function

	//handle_back_button_on_invalid_world_menu (widgetNode,-250, -500
	Save_World_Button=widgetNode->root->root;
	free_All_Widgets(&(Save_World_Button->WidgetChildren)); //free all childs of 'Save World' button
	Save_World_Button->WidgetChildren=NULL;
	current_window=Save_World_Button->root;
	if (last_world==1)
		current_window->WidgetChildren->src="images/World1Logo.bmp";
	else if (last_world==2)
		current_window->WidgetChildren->src="images/World2Logo.bmp";
	else if (last_world==3)
		current_window->WidgetChildren->src="images/World3Logo.bmp";
	else if (last_world==4)
		current_window->WidgetChildren->src="images/World4Logo.bmp";
	else if (last_world==5)
		current_window->WidgetChildren->src="images/World5Logo.bmp";
		

	paint_Gui_Tree_on_Screen(main_window);
	if(failure)
		return;

}



//////////////////////////////////////////////    logic functions
unsigned getNumberFromUser(char *string){
	return (unsigned) strtol(string, NULL, MAXCOMMANDLENGTH);
}

void IsThereAWinner(){

	int mouseAndcatRowDistance, mouseAndcatColDistance;
	int mouseAndcheeseRowDistance, mouseAndcheeseColDistance;

	mouseAndcatRowDistance = abs (MainGame->cat_currRow - MainGame->mouse_currRow);
	mouseAndcatColDistance = abs (MainGame->cat_currCol - MainGame->mouse_currCol);
	mouseAndcheeseRowDistance = abs (MainGame->cheese_currRow - MainGame->mouse_currRow);
	mouseAndcheeseColDistance = abs (MainGame->cheese_currCol - MainGame->mouse_currCol);
	if ((MainGame->cat_currCol == MainGame->mouse_currCol)&&(mouseAndcatRowDistance == 1))
		MainGame->winner=CAT;
	else if ((MainGame->cat_currRow==MainGame->mouse_currRow)&&(mouseAndcatColDistance==1))
		MainGame->winner=CAT;
	
	else if ((MainGame->cheese_currCol==MainGame->mouse_currCol)&&(mouseAndcheeseRowDistance == 1)){
		MainGame->winner=MOUSE;
		
	}
	else if ((MainGame->cheese_currRow==MainGame->mouse_currRow)&&(mouseAndcheeseColDistance == 1)){
		MainGame->winner=MOUSE;
		
	}
	else if (MainGame->NumberOfTurns == 0)
		MainGame->winner=DRAW;

	else
		MainGame->winner=NONE;
}

void MakeMouseIdioticMove(){

	MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol]=EMPTY_ON_BOARD;
		if (MainGame->mouse_currCol==0){
			if (MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol+1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol+1]=MOUSE_ON_BOARD;
				MainGame->mouse_currCol=MainGame->mouse_currCol+1;
			}
			else{
				 if (MainGame->mouse_currRow==0){
					 MainGame->GameBoard[MainGame->mouse_currRow+1][MainGame->mouse_currCol]=MOUSE_ON_BOARD;
					 MainGame->mouse_currRow=MainGame->mouse_currRow+1;
				 }
				 else if (MainGame->mouse_currRow==6){
					 MainGame->GameBoard[MainGame->mouse_currRow-1][MainGame->mouse_currCol]=MOUSE_ON_BOARD;
					 MainGame->mouse_currRow=MainGame->mouse_currRow-1;
				 }
				 else{
					 if (MainGame->GameBoard[MainGame->mouse_currRow-1][MainGame->mouse_currCol]==EMPTY_ON_BOARD){
						 MainGame->GameBoard[MainGame->mouse_currRow-1][MainGame->mouse_currCol]=MOUSE_ON_BOARD;
						 MainGame->mouse_currRow=MainGame->mouse_currRow-1;
					 }
					 else{
						 MainGame->GameBoard[MainGame->mouse_currRow+1][MainGame->mouse_currCol]=MOUSE_ON_BOARD;
						 MainGame->mouse_currRow=MainGame->mouse_currRow+1;
					 }

				 }
			}
		}
		else if (MainGame->mouse_currCol==6){
			if (MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol-1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol-1]=MOUSE_ON_BOARD;
				MainGame->mouse_currCol=MainGame->mouse_currCol-1;
			}
			else{
				if (MainGame->mouse_currRow==0){
					MainGame->GameBoard[MainGame->mouse_currRow+1][MainGame->mouse_currCol]=MOUSE_ON_BOARD;
					MainGame->mouse_currRow=MainGame->mouse_currRow+1;
				}
				else if (MainGame->mouse_currRow==6){
					MainGame->GameBoard[MainGame->mouse_currRow-1][MainGame->mouse_currCol]=MOUSE_ON_BOARD;
					MainGame->mouse_currRow=MainGame->mouse_currRow-1;
				}
				else{
					if (MainGame->GameBoard[MainGame->mouse_currRow-1][MainGame->mouse_currCol]==EMPTY_ON_BOARD){
						MainGame->GameBoard[MainGame->mouse_currRow-1][MainGame->mouse_currCol]=MOUSE_ON_BOARD;
						MainGame->mouse_currRow=MainGame->mouse_currRow-1;
					}
					 else{
						 MainGame->GameBoard[MainGame->mouse_currRow+1][MainGame->mouse_currCol]=MOUSE_ON_BOARD;
						 MainGame->mouse_currRow=MainGame->mouse_currRow+1;
					 }

				 }
			}
		}
		else if (MainGame->mouse_currRow==0){
			if (MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol-1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol-1]=MOUSE_ON_BOARD;
				MainGame->mouse_currCol=MainGame->mouse_currCol-1;
			}
			else if (MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol+1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol+1]=MOUSE_ON_BOARD;
				MainGame->mouse_currCol=MainGame->mouse_currCol+1;
			}
			else{
				MainGame->GameBoard[MainGame->mouse_currRow+1][MainGame->mouse_currCol]=MOUSE_ON_BOARD;
				MainGame->mouse_currRow=MainGame->mouse_currRow+1;
			}

		}
		else if (MainGame->mouse_currRow==6){
			if (MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol-1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol-1]=MOUSE_ON_BOARD;
				MainGame->mouse_currCol=MainGame->mouse_currCol-1;
			}
			else if (MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol+1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol+1]=MOUSE_ON_BOARD;
				MainGame->mouse_currCol=MainGame->mouse_currCol+1;
			}
			else{
				MainGame->GameBoard[MainGame->mouse_currRow-1][MainGame->mouse_currCol]=MOUSE_ON_BOARD;
				MainGame->mouse_currRow=MainGame->mouse_currRow-1;
			}
		}
		else{
			if (MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol-1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol-1]=MOUSE_ON_BOARD;
				MainGame->mouse_currCol=MainGame->mouse_currCol-1;
			}
			else if (MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol+1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol+1]=MOUSE_ON_BOARD;
				MainGame->mouse_currCol=MainGame->mouse_currCol+1;
			}
			else if (MainGame->GameBoard[MainGame->mouse_currRow-1][MainGame->mouse_currCol]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->mouse_currRow-1][MainGame->mouse_currCol]=MOUSE_ON_BOARD;
				MainGame->mouse_currRow=MainGame->mouse_currRow-1;
			}
			else{
				MainGame->GameBoard[MainGame->mouse_currRow+1][MainGame->mouse_currCol]=MOUSE_ON_BOARD;
				MainGame->mouse_currRow=MainGame->mouse_currRow+1;
			}
		}
}

void MakeCatIdioticMove(){

	MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol]=EMPTY_ON_BOARD;
		if (MainGame->cat_currCol==0){
			if (MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol+1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol+1]=CAT_ON_BOARD;
				MainGame->cat_currCol=MainGame->cat_currCol+1;
			}
			else{
				 if (MainGame->cat_currRow==0){
					 MainGame->GameBoard[MainGame->cat_currRow+1][MainGame->cat_currCol]=CAT_ON_BOARD;
					 MainGame->cat_currRow=MainGame->cat_currRow+1;
				 }
				 else if (MainGame->cat_currRow==6){
					 MainGame->GameBoard[MainGame->cat_currRow-1][MainGame->cat_currCol]=CAT_ON_BOARD;
					 MainGame->cat_currRow=MainGame->cat_currRow-1;
				 }
				 else{
					 if (MainGame->GameBoard[MainGame->cat_currRow-1][MainGame->cat_currCol]==EMPTY_ON_BOARD){
						 MainGame->GameBoard[MainGame->cat_currRow-1][MainGame->cat_currCol]=CAT_ON_BOARD;
						 MainGame->cat_currRow=MainGame->cat_currRow-1;
					 }
					 else{
						 MainGame->GameBoard[MainGame->cat_currRow+1][MainGame->cat_currCol]=CAT_ON_BOARD;
						 MainGame->cat_currRow=MainGame->cat_currRow+1;
					 }
				 }
			}
		}
		else if (MainGame->cat_currCol==6){
			if (MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol-1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol-1]=CAT_ON_BOARD;
				MainGame->cat_currCol=MainGame->cat_currCol-1;
			}
			else{
				if (MainGame->cat_currRow==0){
					MainGame->GameBoard[MainGame->cat_currRow+1][MainGame->cat_currCol]=CAT_ON_BOARD;
					MainGame->cat_currRow=MainGame->cat_currRow+1;
				}
				else if (MainGame->cat_currRow==6){
					MainGame->GameBoard[MainGame->cat_currRow-1][MainGame->cat_currCol]=CAT_ON_BOARD;
					MainGame->cat_currRow=MainGame->cat_currRow-1;
				}
				else{
					if (MainGame->GameBoard[MainGame->cat_currRow-1][MainGame->cat_currCol]==EMPTY_ON_BOARD){
						MainGame->GameBoard[MainGame->cat_currRow-1][MainGame->cat_currCol]=CAT_ON_BOARD;
						MainGame->cat_currRow=MainGame->cat_currRow-1;
					}
					 else{
						 MainGame->GameBoard[MainGame->cat_currRow+1][MainGame->cat_currCol]=CAT_ON_BOARD;
						 MainGame->cat_currRow=MainGame->cat_currRow+1;
					 }

				 }
			}
		}
		else if (MainGame->cat_currRow==0){
			if (MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol-1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol-1]=CAT_ON_BOARD;
				MainGame->cat_currCol=MainGame->cat_currCol-1;
			}
			else if (MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol+1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol+1]=CAT_ON_BOARD;
				MainGame->cat_currCol=MainGame->cat_currCol+1;
			}
			else{
				MainGame->GameBoard[MainGame->cat_currRow+1][MainGame->cat_currCol]=CAT_ON_BOARD;
				MainGame->cat_currRow=MainGame->cat_currRow+1;
			}

		}
		else if (MainGame->mouse_currRow==6){
			if (MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol-1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol-1]=CAT_ON_BOARD;
				MainGame->cat_currCol=MainGame->cat_currCol-1;
			}
			else if (MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol+1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol+1]=CAT_ON_BOARD;
				MainGame->cat_currCol=MainGame->cat_currCol+1;
			}
			else{
				MainGame->GameBoard[MainGame->cat_currRow-1][MainGame->cat_currCol]=CAT_ON_BOARD;
				MainGame->cat_currRow=MainGame->cat_currRow-1;
			}
		}
		else{
			if (MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol-1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol-1]=CAT_ON_BOARD;
				MainGame->cat_currCol=MainGame->cat_currCol-1;
			}
			else if (MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol+1]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol+1]=CAT_ON_BOARD;
				MainGame->cat_currCol=MainGame->cat_currCol+1;
			}
			else if (MainGame->GameBoard[MainGame->cat_currRow-1][MainGame->cat_currCol]==EMPTY_ON_BOARD){
				MainGame->GameBoard[MainGame->cat_currRow-1][MainGame->cat_currCol]=CAT_ON_BOARD;
				MainGame->cat_currRow=MainGame->cat_currRow-1;
			}
			else{
				MainGame->GameBoard[MainGame->cat_currRow+1][MainGame->cat_currCol]=CAT_ON_BOARD;
				MainGame->cat_currRow=MainGame->cat_currRow+1;
			}
		}
}

void MakeComputerIdioticMove(){

	if ((MainGame->mouse_player->Human_or_Machine==MACHINE) && 
		(MainGame->cat_player->Human_or_Machine==MACHINE) ){    //both players are machines
			while ((MainGame->winner==NONE)&&(MainGame->NumberOfTurns>0)){
				if ((MainGame->CurrPlayer==MOUSE)&&(MainGame->mouse_player->Human_or_Machine==MACHINE)){
		//mouse turn and mouse is machine
					MakeMouseIdioticMove();
					MainGame->CurrPlayer=CAT;
		            MainGame->NextPlayer=MOUSE;
				}
				else if((MainGame->CurrPlayer==CAT)&&(MainGame->cat_player->Human_or_Machine==MACHINE)){
		//cat turn and cat is machine
					MakeCatIdioticMove();
		            MainGame->CurrPlayer=MOUSE;
		            MainGame->NextPlayer=CAT;
				}
				MainGame->NumberOfTurns--;
				IsThereAWinner();
				update_gui_after_move();
			}

	}
	else if ((((MainGame->mouse_player->Human_or_Machine==HUMAN) &&
		(MainGame->cat_player->Human_or_Machine==MACHINE) ))||(((MainGame->mouse_player->Human_or_Machine==MACHINE) &&
		(MainGame->cat_player->Human_or_Machine==HUMAN) ))){
			if ((MainGame->CurrPlayer==MOUSE)&&(MainGame->mouse_player->Human_or_Machine==MACHINE)){
				//mouse turn and mouse is machine
				MakeMouseIdioticMove();
				MainGame->CurrPlayer=CAT;
				MainGame->NextPlayer=MOUSE;
		
			}
			else if((MainGame->CurrPlayer==CAT)&&(MainGame->cat_player->Human_or_Machine==MACHINE)){
				//cat turn and cat is machine
				MakeCatIdioticMove();
				MainGame->CurrPlayer=MOUSE;
				MainGame->NextPlayer=CAT;
			}
			MainGame->NumberOfTurns--;
			IsThereAWinner();
			update_gui_after_move();

	}  //closes general case where one of the players is a machine and one is human
}

void Make_A_Move(int row, int col){ //make a move to board[row][col]

	if(MainGame->is_game_paused == 1){  //for MACHINE VS MACHINE. 
		return;
	}

	if ((row<0)&&(col<0))
		MakeMiniMaxMove();
	else{
		if (MainGame->CurrPlayer==MOUSE){ //it's mouse turn
			MainGame->GameBoard[MainGame->mouse_currRow][MainGame->mouse_currCol]=EMPTY_ON_BOARD;
		    MainGame->GameBoard[row][col]=MOUSE_ON_BOARD;
		    MainGame->mouse_currRow=row;
		    MainGame->mouse_currCol=col;
		    MainGame->CurrPlayer=CAT;
		    MainGame->NextPlayer=MOUSE;
		}
		else{ // it's cat's turn
			
			MainGame->GameBoard[MainGame->cat_currRow][MainGame->cat_currCol]=EMPTY_ON_BOARD;
		    MainGame->GameBoard[row][col]=CAT_ON_BOARD;
		    MainGame->cat_currRow=row;
		    MainGame->cat_currCol=col;
		    MainGame->CurrPlayer=MOUSE;
		    MainGame->NextPlayer=CAT;

	}

	MainGame->NumberOfTurns--;
	IsThereAWinner();
	/*if ((MainGame->NumberOfTurns==0) &&(MainGame->winner==NONE))
		MainGame->winner=DRAW;*/
	update_gui_after_move();
	//now need to handle the case where the current player is a machine:
	if(MainGame->is_game_over == 0){  //game not over

		if(MainGame->is_game_paused == 1){  //for MACHINE VS MACHINE. 
		return;
		}

		if( (MainGame->CurrPlayer == MOUSE) &&
			(MainGame->mouse_player->Human_or_Machine == MACHINE) ){
				Make_A_Move(-8,-8);
				//MainGame->NumberOfTurns--;
				//IsThereAWinner();
		}
		else if ( (MainGame->CurrPlayer == CAT) &&
			(MainGame->cat_player->Human_or_Machine == MACHINE) ){
				Make_A_Move(-8,-8);
				//MainGame->NumberOfTurns--;
				//IsThereAWinner();
		}

	} //closes case where game isn't over

}

} 

int IsMovePosible(int row, int col){ //returns 1 if possible, 0 if not possible
	                                                // function receives wanted block dimensions

        

	if ((row<0)||(row>(BOARD_SIZE-1))||(col<0)||(col>(BOARD_SIZE-1))){ //illegal dimensions of row/col
			//printf("i'm in is move posible in case of illegall dimension\n");		
			return 0;
	}
		
	if (!((MainGame->GameBoard[row][col])==EMPTY_ON_BOARD)){ //wanted block has a wall in it
			//printf("i'm in is move possible in case wanted block has a wall in it\n");		
		return 0;
	}
	if ((MainGame->CurrPlayer)==MOUSE){ //it's mouse turn

			
		if ((MainGame->mouse_currCol)==col){
			if ((abs(row-MainGame->mouse_currRow))==1){
                                //printf("mouse turn, legal move, mouse should move\n");
				Make_A_Move(row,col);
				return 1;
			}
		}
		else if ((MainGame->mouse_currRow)==row){
			if ((abs(col-MainGame->mouse_currCol))==1){
                                //printf("mouse turn, legal move, mouse should move\n");
				Make_A_Move(row,col);
				return 1;
			}
		}
	}
	else{ //it's cat's turn
		if ((MainGame->cat_currCol)==col){
			if ((abs(row-MainGame->cat_currRow))==1){
				Make_A_Move(row,col);
				return 1;
			}
		}
		else if ((MainGame->cat_currRow)==row){
			if ((abs(col-MainGame->cat_currCol))==1){
				Make_A_Move(row,col);
				return 1;
			}
		}
	}
	//printf("i'm in is move possible but didn't get into cases like i should have\n");

	
	return 0;
}

void CreateEmptyBoard(Game* game){

	int i,j;
	for (i = 0; i < BOARD_SIZE ; ++i) 
		for ( j = 0; j < BOARD_SIZE ; ++j)  
			(game->GameBoard)[i][j]=EMPTY_ON_BOARD;
}

void printBoard(Game* game){

	int i,j;
		for (i = 0; i < BOARD_SIZE; i++){
			for (j = 0; j < BOARD_SIZE; j++){
				printf("%c  ", (game->GameBoard)[i][j]);
			}
			printf("\n");
			printf("\n");
		}
}

void LoadDetailsOfGame(char* world){  //if we start a new game we should read from world1.txt
	                                  //if we load a game 'world' can be world1.txt,world2.txt,...,world5.txt

	int i,j,c;
	int count;
	char NumOfTurns[3]={0};
	FILE *f;
	f=fopen(world,"r");
	if (f==NULL)
		perror(OPEN_FILE_ERROR);
	count=0;
	for (i=0;i<2;i++){
		if ((c = fgetc(f))!=32){
			NumOfTurns[count]=(char)c;
			count++;
		}
	}
	MainGame->NumberOfTurns=(int)getNumberFromUser(NumOfTurns);
	
	while (((c = fgetc(f)) == ' ') || (c == '\n') || (c == '\r') ){//keep reading until the end of line
	
	}
	
	if (c==MOUSE){
		MainGame->StartPlayer=MainGame->CurrPlayer=MOUSE;
		MainGame->NextPlayer=CAT;
	}
	else{
		MainGame->StartPlayer=MainGame->CurrPlayer=CAT;
		MainGame->NextPlayer=MOUSE;
	}
	
	while (((c = fgetc(f)) != ' ') && (c != '\n') && (c != '\r') ){
	}
	while (((c = fgetc(f)) == ' ') || (c == '\n') || (c == '\r') ){//keep reading until the end of line
	
	}
	MainGame->GameBoard[0][0]=c;
	for (i=0;i<BOARD_SIZE;i++){
		for (j=0;j<BOARD_SIZE;j++){
			if (!(j==0))
				MainGame->GameBoard[i][j]=(char)(fgetc(f));
			else
				MainGame->GameBoard[i][j]=c;
			if (MainGame->GameBoard[i][j]==MOUSE_ON_BOARD){
				MainGame->mouse_currRow=i;
				MainGame->mouse_currCol=j;
			}
			else if (MainGame->GameBoard[i][j]==CAT_ON_BOARD){
				MainGame->cat_currRow=i;
				MainGame->cat_currCol=j;
			}
			else if (MainGame->GameBoard[i][j]==CHEESE_ON_BOARD){
				MainGame->cheese_currRow=i;
				MainGame->cheese_currCol=j;
			}
		}
		
			while (((c = fgetc(f)) == ' ') || (c == '\n') || (c == '\r') ){//keep reading until the end of line
				if (c==EOF)
					break;
			}
		
	}

	assert(!(fclose(f)));

}

void SaveDetailsOfGame(char* world){

	int i,j;
	FILE *f;
	f=fopen(world,"w+");
	if (f==NULL)
		perror(OPEN_FILE_ERROR);
	MainGame->NumberOfTurns=SAVED_NUM_OF_TURNS;
	fputs("20",f);
	fputc('\n',f);
	if (MainGame->StartPlayer==MOUSE)
		fputs("mouse",f);
	else
		fputs("cat",f);
	fputc('\n',f);
	for (i=0;i<BOARD_SIZE;i++){
		for (j=0;j<BOARD_SIZE;j++){
			fputc(MainGame->GameBoard[i][j],f);
			
		}
		fputc('\n',f);
	}
	
	assert (fclose(f)==0);

}

int IsThereMouseOnBoard(){ //return 1 if there is already a mouse on board, 0 otherwise
	int i,j;
	for (i = 0; i < BOARD_SIZE; i++){
			for (j = 0; j < BOARD_SIZE; j++){
				if (MainGame->GameBoard[i][j]==MOUSE_ON_BOARD)
					return 1;
			} 
	}
	return 0;
}

int IsThereCatOnBoard(){ //return 1 if there is already a cat on board, 0 otherwise
	int i,j;
	for (i = 0; i < BOARD_SIZE; i++){
			for (j = 0; j < BOARD_SIZE; j++){
				if (MainGame->GameBoard[i][j]==CAT_ON_BOARD)
					return 1;
			} 
	}
	return 0;
}

int IsThereCheeseOnBoard(){ //return 1 if there is already a cheese on board, 0 otherwise
	int i,j;
	for (i = 0; i < BOARD_SIZE; i++){
			for (j = 0; j < BOARD_SIZE; j++){
				if (MainGame->GameBoard[i][j]==CHEESE_ON_BOARD)
					return 1;
			} 
	}
	return 0;
}

void MakeMiniMaxMove(){

	struct MiniMaxResult miniMaxResult;    //for getBestChild 
	int i,j;
	int rows_for_minimax[4];
	int cols_for_minimax[4];
	int count=0;



	if(MainGame->is_game_paused== 1){  //for MACHINE VS MACHINE. 
		return;
	}


	for (i=0;i<4;i++){
		rows_for_minimax[i]=-1;
		cols_for_minimax[i]=-1;
	}
	for (i=0;i<BOARD_SIZE;i++){
		for (j=0;j<BOARD_SIZE;j++){
			if ((IsMovePosibleForGetChildren(MainGame,i,j))==1){
				rows_for_minimax[count]=i; cols_for_minimax[count]=j; count++;
			}
		}
	}
	
	if(evaluate(MainGame) == MAX_EVALUATION){
		MainGame->winner=MOUSE;
		return;
	}
	else if (evaluate(MainGame) == MIN_EVALUATION){
		MainGame->winner=CAT;
		return;
	}
	else if (MainGame->NumberOfTurns==0){
		MainGame->winner=DRAW;
		return;
	}
	
	if ((MainGame->CurrPlayer==MOUSE)&&(MainGame->mouse_player->Human_or_Machine==MACHINE)){
		if (MainGame->NumberOfTurns>=((unsigned)(MainGame->mouse_player->skill_level)))
			miniMaxResult = getBestChild(MainGame, MainGame->mouse_player->skill_level, getChildren,freeData, 
			evaluate, 1);
		else
			miniMaxResult = getBestChild(MainGame, MainGame->NumberOfTurns, getChildren,freeData, 
			evaluate, 1);
		Make_A_Move(rows_for_minimax[miniMaxResult.index],cols_for_minimax[miniMaxResult.index]);
		//printf("evaluation: %d\n",evaluate(MainGame));
		if ((MainGame->NumberOfTurns==0)||(!(MainGame->winner==NONE)))
			return;
		if (MainGame->cat_player->Human_or_Machine==MACHINE)
			MakeMiniMaxMove();

	}

	else if  ((MainGame->CurrPlayer==CAT)&&(MainGame->cat_player->Human_or_Machine==MACHINE)){
		if (MainGame->NumberOfTurns>=((unsigned)(MainGame->cat_player->skill_level)))
			miniMaxResult = getBestChild(MainGame, MainGame->cat_player->skill_level, getChildren,freeData, 
			evaluate, 0);
		else
			miniMaxResult = getBestChild(MainGame, MainGame->NumberOfTurns, getChildren,freeData, 
			evaluate, 0);
		Make_A_Move(rows_for_minimax[miniMaxResult.index],cols_for_minimax[miniMaxResult.index]);
		//printf("evaluation: %d\n",evaluate(MainGame));
		if ((MainGame->NumberOfTurns==0)||(!(MainGame->winner==NONE)))
			return;
		if (MainGame->mouse_player->Human_or_Machine==MACHINE)
			MakeMiniMaxMove();
		
	}
}


int evaluate (void* game){ // cat is minPlayer, mouse is maxPlayer

	double mouse_and_cat_distance= Distance(( (Game*)game)->mouse_currRow,( (Game*)game)->mouse_currCol,
		              ( (Game*)game)->cat_currRow,( (Game*)game)->cat_currCol);
	
	double mouse_and_cheese_distance= Distance(( (Game*)game)->mouse_currRow,( (Game*)game)->mouse_currCol,
		                   ( (Game*)game)->cheese_currRow,( (Game*)game)->cheese_currCol);

	if (mouse_and_cat_distance==1)
		return MIN_EVALUATION; //cat wins - cat is adjacent to mouse
	else if (mouse_and_cheese_distance==1)
		return MAX_EVALUATION; //mouse wins - mouse is adjacent to cheese

	mouse_and_cat_distance=mouse_and_cat_distance+
		2*NumOfWallsInRectangle(( (Game*)game), ( (Game*)game)->mouse_currRow,
		( (Game*)game)->mouse_currCol,
		( (Game*)game)->cat_currRow,( (Game*)game)->cat_currCol);

	mouse_and_cheese_distance=mouse_and_cheese_distance+
		2*NumOfWallsInRectangle(( (Game*)game), ( (Game*)game)->mouse_currRow,
		( (Game*)game)->mouse_currCol,
		( (Game*)game)->cheese_currRow,( (Game*)game)->cheese_currCol);

	return (int)(mouse_and_cat_distance-mouse_and_cheese_distance);
}


ListRef getChildren (void* state){  
	
	int i,j;   
	int childrenCnt=0;
	ListRef childList = NULL;       
	Game* childState;
	Game* fatherState= (Game*)(state);
	
	for (i=0;i<BOARD_SIZE;i++){
		for (j=0;j<BOARD_SIZE;j++){
			if ((IsMovePosibleForGetChildren(fatherState,i,j))==1){
				childState= stateAfterMakeMove(i,j,fatherState);   
				if(childrenCnt == 0){    
					childList= newList(childState);
				    childrenCnt++;
				}
				else
					append(childList, childState); 
				
			}
		}
		
	}
	

	return childList;      //getChildren.len == 0  iff childList =NULL. 
}

void freeData(void* data){  //will be used in getBestChild as FreeFunc. resleases strcut
	//State
	
	free(((Game*)(data))->mouse_player);
	free(((Game*)(data))->cat_player);
	free((Game*)(data));
}

Game* stateAfterMakeMove(int row, int col, Game* currState){

	int i,j;
	Game* newState= (Game*)malloc(sizeof(Game));
	newState->cat_player=(Player*)malloc(sizeof(Player)); 
	newState->cat_player->Human_or_Machine=currState->cat_player->Human_or_Machine;
	newState->cat_player->skill_level=currState->cat_player->skill_level;
	newState->mouse_player=(Player*)malloc(sizeof(Player)); 
	newState->mouse_player->Human_or_Machine=currState->mouse_player->Human_or_Machine;
	newState->mouse_player->skill_level=currState->mouse_player->skill_level;
	newState->StartPlayer=currState->StartPlayer;
	newState->CurrPlayer=currState->CurrPlayer; //will be changed later
	newState->NextPlayer=currState->NextPlayer; //will be changed later
	newState->NumberOfTurns=currState->NumberOfTurns; //will be changed later
	//newState->winner=currState->winner;
	newState->mouse_currCol=currState->mouse_currCol;
	newState->mouse_currRow=currState->mouse_currRow;
	newState->cat_currCol=currState->cat_currCol;
	newState->cat_currRow=currState->cat_currRow;
	newState->cheese_currCol=currState->cheese_currCol;
	newState->cheese_currRow=currState->cheese_currRow;

	
	for (i=0;i<BOARD_SIZE;i++){
		for (j=0;j<BOARD_SIZE;j++){
			newState->GameBoard[i][j]=currState->GameBoard[i][j];
		}
	}
	  
	if (currState->CurrPlayer==CAT){ // cat's turn
		newState->CurrPlayer=MOUSE;
		newState->NextPlayer=CAT;
		newState->GameBoard[row][col]=CAT_ON_BOARD;
		newState->GameBoard[newState->cat_currRow][newState->cat_currCol]=EMPTY_ON_BOARD;
		newState->cat_currRow=row;
		newState->cat_currCol=col;

	}
	else{ //mouse's turn

		newState->CurrPlayer=CAT;
		newState->NextPlayer=MOUSE;
		newState->GameBoard[row][col]=MOUSE_ON_BOARD;
		newState->GameBoard[newState->mouse_currRow][newState->mouse_currCol]=EMPTY_ON_BOARD;
		newState->mouse_currRow=row;
		newState->mouse_currCol=col;
	}
	newState->NumberOfTurns--;


	return newState;
}

int IsMovePosibleForGetChildren(Game* game, int row, int col ){ //only checks if move possible, 
	                                                           //does NOT make a move

	if ((row<0)||(row>BOARD_SIZE-1)||(col<0)||(col>BOARD_SIZE-1)) //illegal dimensions of row/col
		return 0;
	if (!(game->GameBoard[row][col]==EMPTY_ON_BOARD)) //wanted block has a wall in it
		return 0;
	if (game->CurrPlayer==MOUSE){ //it's mouse turn
		if (game->mouse_currCol==col){
			if ((abs(row-game->mouse_currRow))==1){
				return 1;
			}
		}
		else if (game->mouse_currRow==row){
			if ((abs(col-game->mouse_currCol))==1){
				return 1;
			}
		}
	}
	else{ //it's cat's turn
		if (game->cat_currCol==col){
			if ((abs(row-game->cat_currRow))==1){
				return 1;
			}
		}
		else if (game->cat_currRow==row){
			if ((abs(col-game->cat_currCol))==1){
				return 1;
			}
		}
	}
	return 0;
}

double Distance (int row1, int col1, int row2, int col2){

	double squars_sum=((row1-row2)*(row1-row2))+((col1-col2)*(col1-col2))+0.0;
	return sqrt(squars_sum);
}

int NumOfWallsInRectangle(Game* game, int row1, int col1, int row2, int col2){

	int i,j;
	int minRow, minCol;
	int NumOfWalls=0;
	int Rec_length=(abs(row1-row2))+1;
	int Rec_width=(abs(col1-col2))+1;
	if (row1<=row2) minRow=row1;
	else if (row2<row1) minRow=row2;
	if (col1<=col2) minCol=col1;
	else if (col2<col1) minCol=col2;
	

	for (i=minRow;i<Rec_length+minRow;i++){
		for (j=minCol;j<Rec_width+minCol;j++){
			if (game->GameBoard[i][j]==WALL_ON_BOARD)
				NumOfWalls++;
		}
	}

	return NumOfWalls;
	
}


