//******************************************************************************
// File:          GameOfLife.h
// Author:        Wesley Ryder
// Description:
//******************************************************************************

#include <iostream>
#include <vector>
using namespace std;

const int OVER_POPULATION = 4;
const int LONELINESS_0    = 0;
const int LONELINESS_1    = 1;
const int ALIVE_TWO       = 2;
const int RESPAWN         = 3;

class GameOfLife
{
  public:
    vector<vector<int> > SimulateLife(vector<vector<int> > &board, int life_cycles);
    int neighbor_val(int i, int j, vector<vector<int> > &old_board);
  };


vector<vector<int> > GameOfLife::SimulateLife(vector<vector<int> > &board, int life_cycles)
{

  int n = board.size();
  vector<vector<int> > old_board;
  old_board = board;

  for(int times = 0; times < life_cycles; times++)
  {
    vector<vector<int> > new_board;
    new_board = old_board;
    for(int i = 0; i < n; i++)
    {
      for(int j = 0; j < n; j++)
      {
        // if not eternal check neighbors
        int Ncount = 0;
        // checking the surrounding 8 neighbors
        if (old_board[i][j] != 2)
        {
          Ncount += neighbor_val( (n + i + 1) % n, j, old_board);
          Ncount += neighbor_val( (n + i - 1) % n, j, old_board);
          Ncount += neighbor_val( (n + i - 1) % n, (n + j + 1) % n, old_board);
          Ncount += neighbor_val( (n + i - 1) % n, (n + j - 1) % n, old_board);
          Ncount += neighbor_val( (n + i + 1) % n, (n + j + 1) % n, old_board);
          Ncount += neighbor_val( (n + i + 1) % n, (n + j - 1) % n, old_board);
          Ncount += neighbor_val( i, (n + j + 1) % n, old_board);
          Ncount += neighbor_val( i, (n + j - 1) % n, old_board);

          if(Ncount >= 4){new_board[i][j] = 0;}
          else if(Ncount == 0 || Ncount == 1){new_board[i][j] = 0;}
          else if(Ncount == 2)
          {
            if(old_board[i][j] == 0){new_board[i][j] = 0;}
            if(old_board[i][j] == 1){new_board[i][j] = 1;}
          }
          else if(Ncount == 3)
          {
            if(old_board[i][j] == 0){new_board[i][j] = 1;}
            else if (old_board[i][j] == 1){new_board[i][j] == 1;}
          }
        }
      }
    }
    for (int i=0;i<n;i++) {
      for (int j=0;j<n;j++) {
        cout << new_board[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
    old_board = new_board;
  }
  return old_board;
}


int GameOfLife::neighbor_val(int i, int j, vector<vector<int> > &old_board)
{
  int tmp = 0;
  if(old_board[i][j] == 1 || old_board[i][j] == 2)
  {
    tmp++;
  }
  return tmp;
}
