# ai-assisted-project-11-2-26

## Terminal Sudoku

Build with a C++11 compiler:

```sh
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp -o sudoku
```

Run the game with `./sudoku`. Enter moves as `row column value`, using
1-based row and column numbers and values from 1 to 9. Enter `0` as the value
to clear an editable cell. The game prevents changing the puzzle's clues and
rejects moves that duplicate a value in the same row, column, or 3x3 box.
Enter `h` for help or `q` to quit.