#ifndef GUI_HANDLER_
#define GUI_HANDLER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <SDL.h>
#include <SDL_video.h>
#include "MiniMax.h"
#include "GuiFrameWork.h"


#define Widget struct Widget

#define NUMBER_OF_SKILL_LEVELS 9
#define NUMBER_OF_WORLD_FILES 5
#define CAT_ON_BOARD 'C'
#define MOUSE_ON_BOARD 'M'
#define CHEESE_ON_BOARD 'P'
#define WALL_ON_BOARD 'W'
#define EMPTY_ON_BOARD '#'
#define BOARD_SIZE 7
#define MOUSE 'm'
#define CAT 'c'
#define HUMAN 'h'
#define MACHINE 'a'  //a stands for automatic
#define DRAW 'd'    
#define NONE 'n'    //n means no winner just yet and the game is not finished


#define MAXCOMMANDLENGTH 10
#define SAVED_NUM_OF_TURNS 20
#define OPEN_FILE_ERROR "Error: opening file has failed"

typedef struct Player{
	char Human_or_Machine;  //h for HUMAN, a for MACHINE
	int skill_level;  //from 1 to 9
}Player;


typedef struct Game
{
	Player *cat_player;
	Player *mouse_player;
	char StartPlayer;   //small c stands for cat, small m stands for mouse
	char CurrPlayer;   //small c stands for cat, small m stands for mouse  
	char NextPlayer;   //small c stands for cat, small m stands for mouse 
	char GameBoard[BOARD_SIZE][BOARD_SIZE];
	unsigned int NumberOfTurns;
	char winner;  //NULL at begining.  CAT means cat won, MOUSE means mouse won, DRAW is when
	//NumberOfTurns ==0 and no one won.  if no one won and NumberOfTurns !=0, winner == NULL
	int mouse_currRow;
	int mouse_currCol;
	int cat_currRow;
	int cat_currCol;
	int cheese_currRow;
	int cheese_currCol;
	int is_game_paused;   //1 means paused, 0 means not paused
	int is_game_over;     //1 means over, 0 means not over
	
}Game;



//display the main menu 
void display_Main_Menu();
//displays the cat type selection menu
void display_cat_type_selection_menu (Widget *widgetNode, int x, int y);
//displays the mouse type selection menu
void display_mouse_type_selection_menu (Widget *widgetNode, int x, int y);
//scans the widgetChildren list of curr_window to discover which of it's buttons was 
//mouse clicked.
Widget* discover_button_selected (Widget *curr_window, int mouse_clickedX, 
	int mouse_clickedY);
//returns 1 if and only if button was mouse clicked on
int isButtonMouseClicked (Widget *widget, int mouse_clickedX, int mouse_clickedY);
//handles main event loop of the program
void handle_events();

int is_current_window_the_game_window (Widget *curr_window);
int is_current_window_the_paused_game_window (Widget *curr_window);

//handles the event of pressing the back button in cat_skill_level_menu, in mouse_type_selctio
void handle_back_button(Widget *widget, int x, int y);
//handle click on back button in cat selection type menu
void handle_back_on_cat_type_selection_menu(Widget *widget, int x, int y);
//handle mouse click on machine button in cat selection type menu
void handle_machine_on_cat_type_selection_menu(Widget *widgetNode, int x, int y);
//handle mouse click on machine button in mouse selection type menu
void handle_machine_on_mouse_type_selection_menu(Widget *widgetNode, int x, int y);


//handle mouse click on level button
void handle_level_button(Widget *widgetNode, int x, int y);


//handle done button in cat skill level selection menu
void handle_done_button_on_cat_select_machine_level_menu (Widget *widget, int x, int y);
//handle done button in mouse skill level selection menu
void handle_done_button_on_mouse_select_machine_level_menu (Widget *widget, int x, int y);
//handle click on up button in select machine level
void handle_up_button_on_select_machine_level (Widget *widget, int x, int y);
//handle click on down buttonin select machine level
void handle_down_button_on_select_machine_level (Widget *widget, int x, int y);
//discovers cat level in main game
char* discover_cat_level();
//discovers mouse level in main game
char* discover_mouse_level();


/////////////////////////////////   KEYBOARD HANDELING FUNCTIONS   ///////////////

//updates the marked button in a window with a number of buttons
void update_marked_button_in_window(Widget *widget);

//handle mouse click on up or down arrows in cat skill level menu
//void handle_up_

//called upon tab key pressed. unmarks button_marked  and marks it's 
//brother. if the marked button was current_window's last child, unmark it and mark the 
//first child which is a real button (not a logo for example).  may return NULL
Widget* update_marking_because_tab_pressed (Widget* button_marked);
Widget* handle_tab_in_skill_level_menu (Widget *button_marked);
void update_marking_because_mouse_click (Widget *button_marked);

//discovers which one of curr_window's buttons is currently marked
Widget* discover_button_marked (Widget *curr_window);
//used in handle_events function when space bar is pressed and current_window == game_window
// or current_window == paused game window
Widget* get_space_button_in_game_window (Widget *game_window);
//used in handle_events function when F1 is pressed and current_window == paused_game_window
Widget* get_reconfigure_mouse_button (Widget *paused_game_window);
//used in handle_events function when F2 is pressed and current_window == paused_game_window
Widget* get_reconfigure_cat_button (Widget *paused_game_window);
Widget* get_restart_button(Widget *paused_game_window);
Widget* get_go_to_main_menu_button(Widget *paused_game_window);
void handle_up_arrow_on_game_window (Widget *currentWindow);
void handle_down_arrow_on_game_window (Widget *currentWindow);
void handle_left_arrow_on_game_window (Widget *currentWindow);
void handle_right_arrow_on_game_window (Widget *currentWindow);

void handle_up_arrow_on_skill_level_menu (Widget *currentWindow);
void handle_down_arrow_on_skill_level_menu (Widget *currentWindow);



//GUI FOR GAME FUNCTIONS
void initialize_regular_board (Widget *widgetNode, int x, int y);
//tells what to do in case of a click on a board block
void handle_click_on_board_block (Widget *widgetNode, int x, int y);
//updates gui after making a legal move
void update_gui_after_move();
//paints the gui board according to the information in the global variable MainGame
void paint_board_from_Game_fields(Widget *widgetNode, int x, int y);
//handles click or hitting the space bar key while at the game window
void handle_click_on_space_button (Widget *space_button, int x, int y);
void handle_resume_game (Widget *resume_game_button, int x, int y);
//handles reconfigure animal on game window
void handle_reconfigure (Widget *reconfigure_button, int x, int y);
void handle_restart_game (Widget *restart_game_button, int x, int y);
void handle_go_to_main_menu (Widget *go_to_main_menu_button, int x, int y);
void handle_quit (Widget *quit_button_on_game_window, int x, int y);

void handle_machine_button_on_reconfigure (Widget *machine_button_on_reconfigure_mouse,
	int x, int y);
//handles done button in reconfigure 
void handle_done_button_on_reconfigure (Widget *done_recofigure_button, int x, int y);
//handles the back button on reconfigure machine
void handle_back_button_on_reconfigure_machine (Widget *back_reconfigure_machine_button, 
	int x, int y);
//discards mouse type selection menu and returns to paused game window
void handle_human_button_on_reconfigure (Widget *human_button_on_reconfigure, int x, int y);

//updates the first text row in the game window
void update_first_text_row_in_game_window (Widget *gameWindow);

//GUI FOR LOAD GAME
void display_load_game_selection_menu (Widget *widgetNode, int x, int y);
void handle_up_button_on_load_game (Widget *widget, int x, int y);
void handle_down_button_on_load_game (Widget *widget, int x, int y);
//choose if cat human or machine after click 'done' on the LoadGame menu
void display_cat_type_selection_menu_after_load_game (Widget *widgetNode, int x, int y);
void handle_back_on_load_game_menu (Widget *widget, int x, int y);
void handle_back_on_cat_type_selection_menu_after_load_game(Widget *widget, int x, int y);
void handle_mouse_press_on_world_button(Widget *widget, int x, int y);

//GUI FOR CREATE GAME
void display_world_builder_tool (Widget *widgetNode, int x, int y);
void goBackToMainMenuFromWorldBuilder (Widget *widgetNode, int x, int y);
void mark_block (Widget *widgetNode, int x, int y);
void place_Mouse_On_A_Block (Widget *widgetNode, int x, int y);
void place_Cat_On_A_Block (Widget *widgetNode, int x, int y);
void place_Cheese_On_A_Block (Widget *widgetNode, int x, int y);
void place_Wall_On_A_Block (Widget *widgetNode, int x, int y);
void place_EmptySpace_On_A_Block (Widget *widgetNode, int x, int y);

void handle_save_world_button (Widget *widgetNode, int x, int y);
void handle_invalid_world_for_save_button (Widget *widgetNode, int x, int y);
void handle_back_button_on_invalid_world_menu (Widget *widgetNode, int x, int y);
void handle_valid_world_for_save_button (Widget *widgetNode, int x, int y);
void handle_done_button_for_saving_valid_world (Widget *widgetNode, int x, int y);

void handle_up_arrow_on_world_builder (Widget *currentWindow);
void handle_down_arrow_on_world_builder (Widget *currentWindow);
void handle_left_arrow_on_world_builder (Widget *currentWindow);
void handle_right_arrow_on_world_builder (Widget *currentWindow);

//handle keyboard for world builder functions:
void handle_place_mouse_by_keyboard_on_world_builder(Widget*currentWindow);
void handle_place_cat_by_keyboard_on_world_builder (Widget *currentWindow);
void handle_place_cheese_by_keyboard_on_world_builder (Widget *currentWindow);
void handle_place_wall_by_keyboard_on_world_builder (Widget *currentWindow);
void handle_place_EmptySpace_by_keyboard_on_world_builder (Widget* currentWindow);



//GUI FOR EDIT GAME
void display_edit_game_selection_menu (Widget *widgetNode, int x, int y);
void handle_done_on_edit_game_menu (Widget *widgetNode, int x, int y);
void handle_back_on_edit_game_menu (Widget *widgetNode, int x, int y);
void handle_save_world_button_after_edit (Widget *widgetNode, int x, int y);
void handle_valid_world_for_save_button_after_edit (Widget *widgetNode, int x, int y);
void handle_done_button_for_saving_valid_world_after_edit (Widget *widgetNode, int x, int y);

//logic functions
unsigned getNumberFromUser(char *string);
void IsThereAWinner();
void MakeMouseIdioticMove();
void MakeCatIdioticMove();
void MakeComputerIdioticMove();
void Make_A_Move(int row, int col);  //negative coordinates mean computer needs to make a move
int IsMovePosible(int row, int col);
void CreateEmptyBoard(Game* game);
void printBoard(Game* game);
void LoadDetailsOfGame(char* world);
void SaveDetailsOfGame(char* world);
int IsThereMouseOnBoard();
int IsThereCatOnBoard();
int IsThereCheeseOnBoard();

void MakeMiniMaxMove();
int evaluate (void* game);
ListRef getChildren (void* state);
void freeData(void* data);
Game* stateAfterMakeMove(int row, int col, Game* currState);
int IsMovePosibleForGetChildren(Game* game, int row, int col);
double Distance (int row1, int col1, int row2, int col2);
int NumOfWallsInRectangle(Game* game, int row1, int col1, int row2, int col2);

#endif