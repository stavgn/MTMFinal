CC=/usr/local/bin/g++
OBJS= Calculator.o Command.o Exception.o Graph.o main.o Parser.o Vertex.o Helpers.o
EXEC=gcalc
DEBUG=-g# now empty, assign -g for debug
CFLAGS=-std=c++11 -Wall -Werror

$(EXEC) : $(OBJS)
	${CC} ${DEBUG} ${OBJS} -o $@

Command.o: Command.cpp Exception.h Graph.h Vertex.h Vertex.h Command.h Graph.h
	${CC} -c ${DEBUG} ${CFLAGS} $*.cpp
Graph.o: Graph.cpp Graph.h Vertex.h Vertex.h Helpers.h
	${CC} -c ${DEBUG} ${CFLAGS} $*.cpp
Exception.o: Exception.cpp Exception.h
	${CC} -c ${DEBUG} ${CFLAGS} $*.cpp
main.o: main.cpp Calculator.h Graph.h Vertex.h Exception.h	
	${CC} -c ${DEBUG} ${CFLAGS} $*.cpp
Vertex.o: Vertex.cpp Vertex.h Exception.h Helpers.h	
	${CC} -c ${DEBUG} ${CFLAGS} $*.cpp
Calculator.o: Calculator.cpp Calculator.h Graph.h Vertex.h Parser.h Command.h Graph.h Exception.h Command.h
	${CC} -c ${DEBUG} ${CFLAGS} $*.cpp
Parser.o: Parser.cpp Parser.h Command.h Graph.h Vertex.h Command.h Exception.h Helpers.o
	${CC} -c ${DEBUG} ${CFLAGS} $*.cpp
Helpers.o: Helpers.cpp Helpers.h	
	${CC} -c ${DEBUG} ${CFLAGS} $*.cpp
clean:
	rm -f $(OBJS) ${EXEC}


