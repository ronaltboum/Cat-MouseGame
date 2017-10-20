CFLAGS=-Wall -g -std=c99 -pedantic-errors -lm

all: ListUtilsDemo MiniMaxDemo CatAndMouse

clean:  
	-rm ListUtils.o ListUtilsDemo.o MiniMax.o MiniMaxDemo.o  CatAndMouse.o GuiHandler.o GuiFrameWork.o ListUtilsDemo MiniMaxDemo CatAndMouse

CatAndMouse: CatAndMouse.o GuiHandler.o GuiFrameWork.o
	gcc -o CatAndMouse CatAndMouse.o GuiHandler.o GuiFrameWork.o MiniMax.o  ListUtils.o $(CFLAGS) `sdl-config --libs`

CatAndMouse.o: src/gui/GuiHandler.h src/gui/GuiFrameWork.h src/main/CatAndMouse.c  src/main/MiniMax.h src/main/ListUtils.h
	gcc -c -Isrc/main -Isrc/gui $(CFLAGS) src/gui/GuiHandler.c src/main/CatAndMouse.c  `sdl-config --cflags`

GuiHandler.o: src/gui/GuiHandler.h src/gui/GuiFrameWork.h src/main/MiniMax.h src/main/ListUtils.h
	gcc -c -Isrc/main -Isrc/gui $(CFLAGS) src/gui/GuiHandler.c `sdl-config --cflags`

GuiFrameWork.o: src/gui/GuiFrameWork.h src/gui/GuiFrameWork.c
	gcc -c $(CFLAGS) src/gui/GuiFrameWork.c `sdl-config --cflags` 

MiniMaxDemo: MiniMaxDemo.o MiniMax.o ListUtils.o
	gcc  -o MiniMaxDemo MiniMaxDemo.o MiniMax.o ListUtils.o $(CFLAGS)

MiniMaxDemo.o: src/main/MiniMaxDemo.c  src/main/MiniMax.h
	gcc -c $(CFLAGS) src/main/MiniMaxDemo.c

MiniMax.o: src/main/MiniMax.c src/main/MiniMax.h src/main/ListUtils.h
	gcc -c $(CFLAGS) src/main/MiniMax.c

ListUtilsDemo:  ListUtilsDemo.o ListUtils.o 
	gcc  -o ListUtilsDemo ListUtilsDemo.o ListUtils.o $(CFLAGS)

ListUtilsDemo.o: src/main/ListUtilsDemo.c src/main/ListUtils.h
	gcc -c $(CFLAGS) src/main/ListUtilsDemo.c

ListUtils.o: src/main/ListUtils.c src/main/ListUtils.h
	gcc -c $(CFLAGS) src/main/ListUtils.c






