CC = g++ 
CFLAGS = -I./third-party/stb -I./third-party/glm -g -std=c++11
LDFLAGS = -lGL -lGLU -lglut -lGLEW

sourcefiles := $(wildcard src/*.cpp)

CGFinalProject: out $(sourcefiles)
	$(CC) $(CFLAGS) -o out/CGFinalProject $(sourcefiles) $(LDFLAGS)

out:
	mkdir -p out

.PHONY: clean
clean:
	rm -rf out
