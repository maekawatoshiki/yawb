CFLAGS = -O1 -std=c++11
LIBFLAGS = -lm 
GTKMMFLAGS = `pkg-config gtkmm-2.4 --cflags --libs`
GTKMMCFLAGS= `pkg-config gtkmm-2.4 --cflags`
CC = clang++ $(CFLAGS)

yawb: main.o html.o window.o style.o
	$(CC) -o yawb -rdynamic main.o html.o window.o style.o $(LIBFLAGS) $(GTKMMFLAGS)

main.o: main.cpp
	$(CC) -c main.cpp $(GTKMMCFLAGS)

html.o: html.cpp html.hpp
	$(CC) -c html.cpp $(GTKMMCFLAGS)

window.o: window.cpp window.hpp
	$(CC) -c window.cpp $(GTKMMCFLAGS)

style.o: style.cpp style.hpp
	$(CC) -c style.cpp $(GTKMMCFLAGS)

clean:
	$(RM) *.o yawb
