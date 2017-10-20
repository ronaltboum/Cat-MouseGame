#include "GuiHandler.h"  

int main(int argc, char **argv){
	 
	extern int failure;           //declared in GuiFrameWork.c
	extern Widget *main_window;   //declared in GuiHandler.c
	extern Widget *current_window;  //current window of the program. for example main menu
                                   //window, load game window...  declared in GuiFrameWork.c
	extern Game* MainGame;        //declared in GuiHandler.c
	
	//int igor = 1;

	if(argc >= 2){
		if(argc > 2){
			printf("ERROR:  Too many command line arguments\n");
			return 1;
		}
		else if(  (strcmp(argv[1], "console")) != 0  ){
			printf("ERROR:  Command line argument must be console\n");
			return 1;
		}
		printf("q\n");  //the case where there's one argument which is console.
		return 0;
	}
	
	failure =0;  

	MainGame=(Game*)malloc(sizeof(Game));
	MainGame->cat_player = (Player*)malloc(sizeof(Player));
	MainGame->mouse_player = (Player*)malloc(sizeof(Player));
	MainGame->winner = NONE;
	MainGame->is_game_over = 0;  //game initialzied in not over mode
	MainGame->is_game_paused = 0;
	
	if( SDL_Init( SDL_INIT_VIDEO ) == -1 ){
		perror("ERROR: SDL_Init failed"); 
		failure =1;
		return 1;  
	}

	atexit(SDL_Quit);

	main_window = Construct_Main_Window(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT);
	if(failure)
		return 1;
	current_window = main_window;  //current_window is now the screen. will be update in display_Main_Menu function
	display_Main_Menu();
	if(failure){
		free(main_window->offsetRect);
		free(main_window);
		return 1;
	}
	

	handle_events();
	free_All_Widgets(&main_window->WidgetChildren);
	free(main_window->offsetRect);
	free(main_window);
	free(MainGame->cat_player);
	free(MainGame->mouse_player);
	free(MainGame);

	//while(igor)
		//scanf("%d", &igor);

	return 0;
}



