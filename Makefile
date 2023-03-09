EXECUTABLE_NAME := vectorfield

CPP_SOURCE_FILES := \
	main.cpp \
	Application/Application.cpp \
	Plot/Plot.cpp \
	ParticleEngine/ParticleEngine.cpp \
	lib/misc_functions/functions.cpp

C_SOURCE_FILES := \
	Constants/Constants.c \
	Vector/Vector.c \
	lib/mapping/mapping.c \
	lib/SDL_FontCache/SDL_FontCache.c

CPP_FLAGS := \
	-I . \
	--std=c++20

C_FLAGS := \
	-I .

COMPILER_FLAGS := \
	`sdl2-config --cflags --libs` \
	-lSDL2_ttf

cpp:
	g++ -c $(CPP_SOURCE_FILES) $(CPP_FLAGS)

c:
	gcc -c $(C_SOURCE_FILES) $(C_FLAGS)

build:
	make cpp
	make c
	g++ *.o -o $(EXECUTABLE_NAME) $(COMPILER_FLAGS)
	make clean


debug:
	g++ -g -c $(CPP_SOURCE_FILES) $(CPP_FLAGS)
	gcc -g -c $(C_SOURCE_FILES) $(C_FLAGS)
	g++ *.o -o $(EXECUTABLE_NAME) $(COMPILER_FLAGS)
	gdb ./$(EXECUTABLE_NAME)

clean:
	rm *.o