CC = g++
CFLAGS = -I.
# DEPS = chip8.h ../inc/sdl/*.h
OBJ = chip8.o main.o sdl.o display.o

EXEC = project

# %.o: %.cpp $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

# ${EXEC} : $(OBJ)
# 	$(CC) -o $@ ${OBJ} $(CFLAGS)

all:
	g++ -I../inc/SDL2 -L../lib -o ${EXEC} *.cpp -lmingw32 -lSDL2main -lSDL2

clean :
	rm -rf ${OBJ} ${EXEC} ${EXEC}.exe