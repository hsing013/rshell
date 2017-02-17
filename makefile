all:
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic ${PWD}/src/main.cpp ${PWD}/src/base.cpp ${PWD}/src/connectors.cpp -o ${PWD}/bin/rshell

rshell:
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic ${PWD}/src/base.cpp -o ${PWD}/bin/rshell

clean:
		rm -rf ${PWD}/bin
