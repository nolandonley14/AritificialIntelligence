** The Game of Life Terminal Simulation **

1)  You have two options for the initial n x n grid colony before evolution.

  i)  If no command line arguments are given, the initial grid colony
  will all be randomly generated using ​rand()​.

  ii) You may also specify a filename for the initial grid colony at the
  command line using a ​-f​ option.  For example,

  evolution -f simple1.txt​ uses the initial grid found in external file
  simple1.txt ​prior to evolution.

2)  You will be prompted for the number of generations that your
artificial life colony will continue to evolve.  Assume this is a positive integer
n​ less than 100.

3) The n x n grid colony will be printed before evolution begins and
after each generation.  An ​X​ on the screen and in the input file indicates a
living cell.  A ​0​ indicates a dead cell.  This allows the you to be able to see
interesting patterns of complexity and behavior of your simorgs.

**Tip**
Test a randomly generated colony on at least 20 generations to really some rich relationships.


** How it works **

The colony is represented by a single vector of a custom struct cells.
Each cell has a:
- char state: 'X' or '0'
- vector<char>: neighbors
- int age: 0-10

The vector is either randomly populated with X's at 30% or populated by reading the initial file.
Then after the user inputs the desired number of generations, the program is ready.
For each Generation the algorithm is:

1) Get each cells neighbors states

    In one if else statement, determine, the cells location in the grid, and therefore
    which cells are its neighbors. Then populate it's neighbors vector with each of its
    neighbors states.

2) Calculate the Next Generation

  a) create a copy of the Colony

  b) By iterating through each of the original colony cells neighbors and counting the number
   that are alive, we can determine the state of each cell for the next generation, and set that
   state in the copy colony.

  c) Set the colony equal to the copy colony

3) Print the Colony to the console

4) Repeat
