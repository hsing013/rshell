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

3. git checkout hw2

4. make

5. bin/rshell
```

Features
---
-The program supports all bash commands located in /usr/bin

-It also has support for connectors such as "&&", "||", and ";"

-It also supports the comment symbol, "#", which will comment out anything after it.

-Lastly, to exit the program, one simply types "exit"

Bugs
---
-If incomplete statements such as "echo hello ||" are inputted, then it throws an error.

-If one symbol is used, for example "ls -a | echo hello", it will make everything past ls its arguements.

-The command cd doesn't work, it throws an error.

-Having more than two symbols, for example "ls -a &&& echo hello", will through an error
