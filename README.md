# game-of-life
Sequential and Parallel verisions
## Sequential
  game-of-life/sequential-ver/Test_Harness.cc is the non ncurses final output method  
  game-of-life/sequential-ver/GOL_display.cc is the ncurses method  
  For a party Enter:
  ```
  g++ GOL_display.cc -lncurses 
  ./a.out < Test-Data/<"___".dat>
  ```
## Parallel
  For a party Enter:
  ```
  g++ -std=c++11 Test_Harness.cc -pthread
  ./a.out Test-Data/<___.dat>
  ```
  *note* parallel is more efficient in cases for larger matrix's ie.  
   100x100, 1000x1000 etc.
