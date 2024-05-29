#add all the files that you need to the files makefile variable below as a space seperated list
files = shader.cpp Objects/Floor.cpp Objects/Window.cpp Objects/Camera.cpp Helpers/FrustrumCulling.cpp scene.cpp include/stb_image.cpp

main: main.cpp glad.c
	g++ -g $(files) main.cpp glad.c -lglfw -pthread -lGLEW -ldl -lGL -o main

clean:
	rm -f *.o main

run:
	./main

all:
	make clean
	make
	make run