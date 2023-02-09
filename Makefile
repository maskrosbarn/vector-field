EXECUTABLE_NAME := main

CPP_SOURCE_FILES := \
	main.cpp \
	lib/mapping/mapping.cpp \
	Application/Application.cpp \
	Vector2D/Vector2D.cpp 

COMPILER_FLAGS := -o $(EXECUTABLE_NAME) -I . `sdl2-config --cflags --libs` -lSDL2_ttf

C_SOURCE_FILES := lib/SDL_FontCache/SDL_FontCache.c

cpp:
	g++ -c $(CPP_SOURCE_FILES) --std=c++20 -I .

c:
	gcc -c $(C_SOURCE_FILES)

all:
	make cpp
	make c
	g++ *.o -o main `sdl2-config --cflags --libs` -lSDL2_ttf
	rm *.o