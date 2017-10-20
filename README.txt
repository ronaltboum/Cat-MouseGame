##########################################################################################

README file for the CatAndMouse project (2015)
Partners: Ron Altboum & Amit Yaakobovich


##########################################################################################

Our design choices:
We divided the implementation to these files:
- GuiFrameWork.c , GuiFrameWork.h : These are the GUI factories
- GuiHandler.c , GuiHandler.h :  Handle gui events like mouse click or keyboard press, and also is responsible for logic (contain the evaluation function). Contains a function named handle_events which is the major event handleing function of the project.
- CatAndMouse.c :  Starts the game by calling the GUI factory functions in GuiFrameWork.c. At the end, frees all resources.
- MiniMax.c :  It's the file from ex3, to which we added Alph Beta prunning. It's invoked by the logic functions in GuiHandler.c.

##########################################################################################

List of modules:
	main - contains CatAndMouse.c , and all the other files given.
	gui - contains GuiFrameWork.c , GuiFrameWork.h which are gui factories.  Contains GuiHandler.c , GuiHandler.h which handle the gui events and also provide logic services.
	

##########################################################################################

Utility evaluation function:
	high level description - 
The function computes the DIFFERENCE between the Unique Distance (an explanation about that will be brought later on) between the cat and the mouse, AND the Unique Distance between the mouse and the cheese.
The Unique Distance is computed in the following matter:
We'll mark d(a,b) as the normal ditance between objects a and b 	computed via the normal square rooted distance formula.
We'll mark :  #walls(a,b) as the number of walls in the rectange 	of which the two objects are its vertices. Notice that there must 	be such a rectange. 
The Unique Distance between objects a and b   = d(a,b) + 2*#walls(a,b)
#walls is computed via the function NumOfWallsInRectangle.
An object can be either cat, mouse or cheese.


	reasoning -
The reason to give each wall an additional weight of 2 in the Unique Distance is because the wall almost certainly causes the elongation of the trip between one object to the other. A detour to bypass a wall takes about 2 steps more.
The mouse is always the max player, therefore it wishes for the biggest possible value of the evaluation function. The mouse wants to get closer to the cheese and get further away from the cat. Our evaluation function checks these 2 conditions simulatenously. The closer the mouse gets to the cheese and the further away he gets from the cat, the difference computed in the evaluation function will grow and so will the evaluation function value. 
The cat is always the minimal player, therefore it wishes for the minimal possible evaluation value. As the cat gets closer to the mouse, the difference computed in the evaluation function decreases (becasue the mouse is usually close to the cheese), and therefore the evaluation value will decrease. 


	running time - 
We'll mark n as the number of blocks in the game. The evaluation function's running time is O(n). Explanation: There's a constant number of calculations (calculating #walls, calculating d(a,b) ). Each such calculation takes O(n). Therefore the overall running time is O(n).

##########################################################################################
