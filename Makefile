
clean:
	rm -r *.gch

mac :
	g++ *.cpp -lfreetype -lglfw -lglew -framework OpenGL -std=c++14
linux :
	g++ -lGLEW -lglfw -lGL -lX11 -I/usr/include/freetype2 -lfreetype *.cpp -std=c++14
