Implementation of AHO CORASIC algorithm for multipattern exact match.

Assumed to be in Linux (DEBIAN) OS:

Tools required: g++, make.

Commands: 
make clean

make
---------------------------------------------------------------------------------------------------
./mygrep [-f] <pattern>/<patternfile> <searchfile>

(OR)

./mygrep <pattern>

>>> Enter the string

>>> start giving your input, It'll match it simultaneously and produce the result

Ctrl+D to stop your input.
--------------------------------------------------------------------------------------------------
eg:

make clean
make
./mygrep -f /usr/share/dict/american-english /usr/share/dict/british-english

(OR)

make clean
make
./mygrep -f 'warning|error|critical|maximal|tutor' /usr/share/dict/american-english

(OR)

make clean
make
./mygrep 'warning|error|critical|maximal|tutor'

 Enter the String
>>> Enter the string

>>> start giving your input, It'll match it simultaneously and produce the result

Ctrl+D to stop your input.

--------------------------------------------------------------------------------------------------

One or Three arguments to be supplied.

0. Optional argument '-f' to specify if the pattern or input is given through a file.

1. The pattern to be matched. (Can be multi pattern). eg: 'warning|error|critical|maximal|tutor'
   Should have "|" as the seperator (delimiter) OR
   Can be a file with -f option.

2. The input via Keyboard without the -f option OR
   The file in which the pattern has to be searched. eg: /usr/share/dict/american-english with -f option

3. The time calcuation hasn't been implemented. You can check the time it takes for execution using the time command.
   eg: time ./mygrep 'warning|error|critical|maximal|tutor' /usr/share/dict/american-english

