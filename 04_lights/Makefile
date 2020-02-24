GLUT_DIR="C:\Users\Sebastian\Documents\work\freeglut"
GXX=g++.exe
FLAGS=-Wall -g

main.exe: main.o
	$(GXX) $(FLAGS) -o main.exe  main.o -L$(GLUT_DIR)\lib\ -lfreeglut -lglu32  -lopengl32

main.o: main.cpp
	$(GXX) $(FLAGS) -I$(GLUT_DIR)\include -c -o main.o main.cpp 
    