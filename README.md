# ASCII Art compositor
C program that takes from stdin a sequence of instructions for pasting ASCII art pictures together, reads those pictures from files, and writes the combined picture to stdout.

## Usage
Clone the repository
```
$ git clone git@github.com:connormcl/art-compositor.git
```
Switch to the project directory
```
$ cd art-compositor
```
Run the Makefile
```
$ make
```
Feed the program instructions
```
$ echo "1 1 ship 3 5 ship 3 19 tree 7 2 ship 13 4 ship 4 22 tree 5 6 cake" | ./compositor
```
Each instruction should be of the form *row, column, fileName*

## Example
For example, suppose that the current directory contains these files:
```
    # # #
\==========/
 \......../
```
art-compositor/ship
```
  /\
 /vv\
/vvvv\
  ||
```
art-compositor/tree
```
     * * *
 ____|_|_|_____ 
|_____________|
|___HAPPY_____|
|__BIRTHDAY___|
|_____________|
```
art-compositor/cake


Then this is what we should get from executing the command:
```
$ echo "1 1 ship 3 5 ship 3 19 tree 7 2 ship 13 4 ship 4 22 tree 5 6 cake" | ./compositor

     # # #
 \==========/
  \......#.# #       /\
     \==========/   /vv\/\
      \....*.*.*   /vvv/vv\
       ____|_|_|_____|/vvvv\
      |_____________|   ||
  \===|___HAPPY_____|
   \..|__BIRTHDAY___|
      |_____________|


        # # #
    \==========/
     \......../
```

## Other information
Completed as part of an assignment during **CPSC 223: Data Structures and Programming Techniques** taught by James Aspnes during Spring 2015
