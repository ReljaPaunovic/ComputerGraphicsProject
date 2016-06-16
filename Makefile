CC = g++ 
CFLAGS = -I./third-party/stb -I./third-party/glm -g -std=c++11 -L/usr/include/SFML
LDFLAGS = -lGL -lGLU -lglut -lGLEW -L$(LIBREP)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

sourcefiles := $(wildcard src/*.cpp)

CGFinalProject: out $(sourcefiles)
	$(CC) $(CFLAGS) -o out/CGFinalProject $(sourcefiles) $(LDFLAGS)

out:
	mkdir -p out

.PHONY: clean
clean:
	rm -rf out
