CC = g++
CFLAGS = -I.
DEPS = chip8.h
OBJ = chip8.o main.o

EXEC = Project

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

${EXEC} : $(OBJ)
	$(CC) -o $@ ${OBJ} $(CFLAGS)

clean :
	rm -rf ${OBJ} ${EXEC} ${EXEC}.exe