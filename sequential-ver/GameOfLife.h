//******************************************************************************
// File:          GameOfLife.h
// Author:        Wesley Ryder
// Description:
//******************************************************************************

#include <iostream>
#include <vector>
using namespace std;

//******************************************************************************
//  Class:        GameOfLife
//    Public:     func SimulateLife()
//                fun neighbor_val()
//    Private:    None
// Description:   Class that is used to represent the game of life
//******************************************************************************
class GameOfLife
{
  public:
    vector<vector<int> > SimulateLife(vector<vector<int> > &board, int life_cycles);
    int neighbor_val(int i, int j, vector<vector<int> > &old_board);
  };

//******************************************************************************
// Function:      StimulateLife()
// Arguments:     vector<vector<int> > &board
//                int life_cycles
// Description:   Update the matrix surviving population based on rules of
//                game of life. Then update the orginal board based on # of
//                life cycles
//******************************************************************************
vector<vector<int> > GameOfLife::SimulateLife(vector<vector<int> > &board, int life_cycles)
{

  int n = board.size();
  // Declaring old board and setting that equal to the passed in board
  vector<vector<int> > old_board;
  old_board = board;

  // Life cycle loop
  for(int times = 0; times < life_cycles; times++)
  {
    // Every life cycle we declare a fresh board and set that equal to
    // the old board
    vector<vector<int> > new_board;
    new_board = old_board;

    // Double forloop for checking each grid locations neighbors
    for(int i = 0; i < n; i++)
    {
      for(int j = 0; j < n; j++)
      {
        int Ncount = 0;

        // If not eternal check neighbors -> where eternal neighbors never
        // die so there is no reason to update their values
        if (old_board[i][j] != 2)
        {
          // checking the surrounding 8 neighbors and updating population
          // count each time we find a living person
          Ncount += neighbor_val( (n + i + 1) % n, j, old_board);
          Ncount += neighbor_val( (n + i - 1) % n, j, old_board);
          Ncount += neighbor_val( (n + i - 1) % n, (n + j + 1) % n, old_board);
          Ncount += neighbor_val( (n + i - 1) % n, (n + j - 1) % n, old_board);
          Ncount += neighbor_val( (n + i + 1) % n, (n + j + 1) % n, old_board);
          Ncount += neighbor_val( (n + i + 1) % n, (n + j - 1) % n, old_board);
          Ncount += neighbor_val( i, (n + j + 1) % n, old_board);
          Ncount += neighbor_val( i, (n + j - 1) % n, old_board);

          // Based on the neighbor count the person either dies or lives, or
          // is born
          // 4 or greater                       = death
          // 0 or 1                             = death
          // 2 and the cells current value = 0  = remain dead
          // 2 and the cells current value = 1  = remain alive
          // 3 and the cells current value = 1  = remain alive
          // 3 and current cell value = 0       = reborn aka alive
          if(Ncount >= 4)
          {
            new_board[i][j] = 0;
          }
          else if(Ncount == 0 || Ncount == 1)
          {
            new_board[i][j] = 0;
          }
          else if(Ncount == 2 && old_board[i][j] == 1)
          {
            new_board[i][j] = 1;
          }
          else if(Ncount == 3 && old_board[i][j] == 0)
          {
            new_board[i][j] = 1;
          }
        }
      }
    }
    // Updating old board to new board for next "life cycle"
    old_board = new_board;
  }
  return old_board;
}


//******************************************************************************
// Function:      neighbor_val()
// Arguments:     int i
//                int j
//                vector<vector<int> > &old_board
// Description:   Calculates the number of neighbors relative to current cell
//******************************************************************************
int GameOfLife::neighbor_val(int i, int j, vector<vector<int> > &old_board)
{
  int tmp = 0;
  if(old_board[i][j] == 1 || old_board[i][j] == 2)
  {
    tmp++;
  }
  return tmp;
}
