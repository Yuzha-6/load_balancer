all: log.o fdwrapper.o conn.o mgr.o lbserver

log.o: log.cpp log.h
	g++ -c log.cpp -o log.o
fdwrapper.o: fdwrapper.cpp fdwrapper.h
	g++ -c fdwrapper.cpp -o fdwrapper.o
conn.o: conn.cpp conn.h
	g++ -c conn.cpp -o conn.o
mgr.o: mgr.cpp mgr.h
	g++ -c mgr.cpp -o mgr.o
lbserver: processpool.h main.cpp log.o fdwrapper.o conn.o mgr.o
	g++ processpool.h log.o fdwrapper.o conn.o mgr.o main.cpp -o lbserver

clean:
	rm *.o lbserver
