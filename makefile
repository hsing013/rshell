
all: main.cpp base.cpp base.h connectors.cpp connectors.h
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic main.cpp base.cpp connectors.cpp -o ${PWD}/bin/rshell

rshell: main.cpp base.cpp base.h connectors.cpp connectors.h
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic main.cpp base.cpp connectors.cpp -o ${PWD}/bin/rshell
