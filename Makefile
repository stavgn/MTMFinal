CC=g++
OBJS= Edge.o Graph.o main.o Vertex.o
EXEC=gcalc
DEBUG=# now empty, assign -g for debug
CFLAGS=-std=c++11 -Wall -Werror

$(EXEC) : $(OBJS)
	${CC} ${DEBUG} ${OBJS} -o $@

Edge.o: Edge.cpp Edge.h Vertex.h Vertex.h
	${CC} -c ${DEBUG} ${CFLAGS} $*.cpp
Graph.o: Graph.cpp Graph.h Vertex.h Edge.h Vertex.h
	${CC} -c ${DEBUG} ${CFLAGS} $*.cpp
main.o: main.cpp Graph.h Vertex.h Edge.h Vertex.h
	${CC} -c ${DEBUG} ${CFLAGS} $*.cpp
Vertex.o: Vertex.cpp Vertex.h	
	${CC} -c ${DEBUG} ${CFLAGS} $*.cpp

clean:
	rm -f $(OBJS) ${EXEC}
