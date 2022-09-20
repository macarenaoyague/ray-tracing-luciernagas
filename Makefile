CPP = g++
CPPFLAGS = -std=c++20 -Wall -Wpedantic -Wextra -Wshadow -I /opt/X11/include -L /opt/X11/lib -lX11 -ljpeg -lpng -lz -Xpreprocessor -fopenmp -lomp
# TODO: poner paths si lo organizo en carpetas
# VPATH = ./src:./src/avl:./src/utils:./tests

all: main.o camara.o cimg.o luz.o mundo.o objeto.o rayo.o vector.o
	$(CPP) $(CPPFLAGS) ./o/main.o ./o/camara.o ./o/cimg.o ./o/luz.o ./o/mundo.o ./o/objeto.o ./o/rayo.o ./o/vector.o
	./a.out

main.o: main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp -o ./o/main.o

camara.o: Camara.h Camara.cpp
	$(CPP) $(CPPFLAGS) -c Camara.cpp -o ./o/camara.o

cimg.o: CImg.h
	$(CPP) $(CPPFLAGS) -c CImg.h -o ./o/cimg.o

luz.o: Luz.h
	$(CPP) $(CPPFLAGS) -c Luz.h -o ./o/luz.o

mundo.o: Mundo.h
	$(CPP) $(CPPFLAGS) -c Mundo.h -o ./o/mundo.o

objeto.o: Objeto.h Objeto.cpp
	$(CPP) $(CPPFLAGS) -c Objeto.cpp -o ./o/objeto.o

rayo.o: Rayo.h
	$(CPP) $(CPPFLAGS) -c Rayo.h -o ./o/rayo.o

vector.o: vector.h vector.cpp
	$(CPP) $(CPPFLAGS) -c vector.cpp -o ./o/vector.o

clean:
	rm ./o/*.o a.out