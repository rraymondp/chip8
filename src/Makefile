CC = g++
CFLAGS = -I.
# DEPS = chip8.h ../inc/sdl/*.h
OBJ = chip8.o main.o

EXEC = main

# %.o: %.cpp $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

# ${EXEC} : $(OBJ)
# 	$(CC) -o $@ ${OBJ} $(CFLAGS)

clean :
	rm -rf ${OBJ} ${EXEC} ${EXEC}.exe

all:
	g++ -I../inc/SDL2 -L../lib -o main *.cpp -lmingw32 -lSDL2main -lSDL2