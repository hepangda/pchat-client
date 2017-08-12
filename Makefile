OBJECTS = pchat.o network/spkg.o network/rvpkg.o network/dpkg.o network/package.o
CXXFLAG = -std=c++14 -I ./include -Wall -Wno-deprecated -ljsoncpp -lpthread -lportal -lpcurses -lncursesw

pchat: $(OBJECTS)
	g++ $(CXXFLAG) -o pchat $(OBJECTS)

network/spkg.o : network/spkg.cpp
	g++ $(CXXFLAG) -c network/spkg.cpp -o network/spkg.o
network/dpkg.o : network/dpkg.cpp
	g++ $(CXXFLAG) -c network/dpkg.cpp  -o network/dpkg.o
network/rvpkg.o : network/rvpkg.cpp
	g++ $(CXXFLAG) -c network/rvpkg.cpp  -o network/rvpkg.o
network/package.o : network/package.cpp
	g++ $(CXXFLAG) -c network/package.cpp  -o network/package.o

extra/watchdog.o : extra/watchdog.cpp
	g++ $(CXXFLAG) -c extra/watchdog.cpp -o network/watchdog.o

pchat.o : pchat.cpp
	g++ $(CXXFLAG) -c pchat.cpp -o pchat.o

.PHONY: clean
clean :
	-rm $(OBJECTS)