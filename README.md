# Sudoku Generator

This code attempts to generate puzzles through several different algorithms, where some fail to meet the requirements of a valid sudoku puzzle or simply cannot complete the generated sudoku given its current state. Note, this is a puzzle generator rather than a solver. This generator can make puzzles based on the one square within the puzzle, thus from n=2,3,4,.. 

## Build: 

Clone this repo, create a build directory and run `cmake ..` within the build directory. Then run `make` and run `./sudoku`.

## Current Algorithms:


 - Random: places random numbers within the grid randomly
 - Correct Random: same as the random one listed above but terminates when the last placed number violates sudoku rules
 - Diagonal Outward: Places numbers on the first diagonal initially, then places the next number upwards and leftwards until it reaches the end of the puzzle at the left and top. Then it continues onto the next diagonal and repeats
 - Diagonal Inwards: Starts with the top and left most points with respect to the diagonal point and moves to the right and down until it hits the current diagonal point, then repeats starting at the next top or bottom point
 - Numerical Fill: Fills the puzzle by filling out each i=1,..,n^2 values within the puzzle until any violations occur.