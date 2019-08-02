# Filler

Algorithmic game. Two bots place random pieces on a map, trying to occupy the most territory.

![](filler_demo.gif)

## Description

Two players take turns placing randomly generated pieces on a rectangle map of the known size. They earn a point for each covered square of a map. The game stops as soon as a given piece can no longer be placed. Wins the one who covered the larger area of a map.

The goal of this project is to write a bot which can win at least 3 of 5 games with every provided bot.

*This is the project of the Algorithms branch of the School 42 curriculum.*

**Detailed description of the task: [lem-in.en.pdf](https://github.com/dstepanets/Lem_in/blob/master/lem-in.en.pdf)**

## Usage

Compile with `make`. To run the game we use the virtual machine `filler_vm`, providing it with 2 players and a map.

```
./filler_vm -f <map> -p1 <player1.filler> -p2 <player2.filler>

   -f  --file		use a map file (required)
   -p1 --player1	use filler binary as a first player
   -p2 --player2	use filler binary as a second player

```

After compilation, my player `dstepane.filler` is placed in the root. The six enemy bots are in `players` directory. Three maps of different size in `maps` folder.

#### Visuals

There is a little bonus - a visual mode. Pipe the game output to the binary `visuals/visualizer` - and a battle will convert to emojis. For example:

```
./filler_vm -p1 ./dstepane.filler -p2 players/carli.filler -f maps/map01 | visuals/visualizer
```

**The program was tested only on Mac OS X.**

## Algorithm

