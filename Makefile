CFLAGS = -Wall
INCLUDES = -Iinclude/
SOURCES = main.c core.c
LIBRARIES = -ltalloc

all:
	gcc -o lucky $(CFLAGS) $(SOURCES) $(INCLUDES) $(LIBRARIES)

clean:
	rm lucky
