# Mobitangga

CLI (command line interface) based game written in c with features like : Map, teleports, skills, buffs, turn based with undo turn, load configuration from file.

For further information, please check this [specification](https://docs.google.com/document/d/1XWxnjQnzXTIRdKlBelEWgc1iY9Jr1rDI1yqxjHCr6B8/edit)

## Installation (windows)

1. Download or clone this repository to your computer
2. Open main.exe

or you can build yourself with these steps

1. Download or clone this repository to your computer
2. Open the root directory using terminal
3. Use this command

```
gcc ./src/adt/mesinkata/mesinkata.c ./src/adt/mesinkata/mesinkar.c ./src/functions.c ./src/main.c ./src/adt/map/map.c ./src/adt/list/listlinier.c ./src/adt/stack/stack.c -o main
```

4. Open main.exe

## How to Play

At the beginning of the game, the game asked for a configuration file, there are already 4 map configurations ready to use :

1. small.txt
2. medium.txt
3. large.txt
4. extralarge.txt

After you input your desired player names, the game will began, here are the commands available

1. ROLL
2. MAP
3. INSPECT
4. SKILL
5. BUFF
6. UNDO
7. ENDTURN

Each command details are in this (bahasa indonesia) [specification](https://docs.google.com/document/d/1XWxnjQnzXTIRdKlBelEWgc1iY9Jr1rDI1yqxjHCr6B8/edit)

## Previews
