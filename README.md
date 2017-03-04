RSHELL
===

Licensing Info: Read the License
---
Project Source can be downloaded from https://github.com/hsing013/rshell.git
----

Author & Contributor List
-------------
Harnoor Singh

Ben Treves

RSHELL Overview
----
This program is a bash terminal that runs bash commands located in /usr/bin.

Installation
------------
```
1. git clone https://github.com/hsing013/rshell.git

2. cd rshell

3. git checkout hw3

4. make

5. bin/rshell
```

Features
---
-The program supports all bash commands located in /usr/bin

-It also has support for connectors such as "&&", "||", and ";"

-It also supports the comment symbol, "#", which will comment out anything after it.

-Added support for precedence and the test feature

-Lastly, to exit the program, one simply types "exit"

Bugs
---
-If incomplete statements such as "echo hello ||" are inputted, then it throws an error.

-If one symbol is used, for example "ls -a | echo hello", it will make everything past ls its arguements.

-The command cd doesn't work, it throws an error.

-Having more than two symbols, for example "ls -a &&& echo hello", will return an error

-The syntax for the test feature has to have a space in between the flags, test, and brackets.
 CORRECT(examples): "test -e /home/path/file", "test -e main.cpp", "test main.cpp", "[ -e file ]", "[ /path/file ]
 INCORRECT(examples): "test-e file", "test -e/home/path", "[-e file]", "[ -e file]"

-Parantheses that are 3 level deep may or may not work correctly. For example, 
 "(((ls -a)) || ((echo Bill)) && (echo Gates))" will be wrong as it will trigger
 ls -a and echo Bill. But for example, "(((ls -a))) || (((echo Steve)))" will work correctly.

-There must be space after a semicolon or else there will be an error.