# freecity
An open source city simulator, inspired by Simcity.

## Requirements
gcc

## Compile & run
$ make

$ ./freecity

## Main goal

I'd like to create a good city simulator, not only as a game. The program should simulate the dynamics of a city as an enviroinment: people, jobs, companies and the economy in general.

## Development status

For now the simulator is in a beginning stage. I'm working on the basic structures, data types and other basic stuff.

## Citymaker

Citymaker (you can find it in the citymaker subdirectory) is my tool for generating "debug" cities. It will also display the city map (for debugging purposes only) on the linux framebuffer.

### Using citymaker

Usage: citymaker mycity.fc

The fc file is a debugging file format. The syntax is

\#This is a comment
\#The following two lines create two residential buildings
resid(X,Y,S,C)
resid(X,Y,S,C)
....

where X,Y are coordinates, S is the bulding size, C is the capacity.

Citymaker uses a very trivial parser, without error avoidance or coorrection, so you have to double check the syntax. Each line can be at most 80 chars long. I'm working on a routine that displays the map on the linux framebuffer. I'll show a preview ASAP.

Citymaker compiles the file and creates a binary file that can be loaded from freecity.

## Graphics

For now no graphics is provided: I'm just working on the simulator only. Any help or collaboration on the simulator and/or the graphics is encouraged.