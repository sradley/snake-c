CC = gcc

CFLAGS = -Wall -ansi
INCLUDES = -I./src/
LFLAGS = -L/usr/include/
LIBS = -lncurses
SRCS = src/*.c
MAIN = bin/snake

all: $(MAIN)
	@echo $(MAIN) has compiled successfully

$(MAIN): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(SRCS) $(LFLAGS) $(LIBS)

clean:
	$(RM) $(MAIN)
	@echo $(MAIN) removed