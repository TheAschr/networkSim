
clean:
	rm -r *.gch

all :
	g++ *.cpp -lfreetype -lglfw -lglew -framework OpenGL