CGFinalProject: out main.cpp
	g++ -o out/CGFinalProject main.cpp -lGL -lGLU -lglut

out:
	mkdir -p out

.PHONY: clean
clean:
	rm -rf out