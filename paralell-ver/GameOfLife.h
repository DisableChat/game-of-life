//******************************************************************************
// File:          GameOfLife.h
// Author:        Wesley Ryder
// Description:   Class implmentation for the GameOfLife, where this class
//                simply updates the matrix based on the logic of GameOfLife
//                with the twist eternal cells can exists Paralell version
//******************************************************************************

#include <iostream>
#include <vector>
#include <pthread.h>
#include <future>
#include <thread>
using namespace std;

// Declaration of neighbor_val -> refer to definition for more info
int neighbor_val(int i, int j, vector<vector<int> > &old_board);


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
    static void SimulateLife_parallel(vector<vector<int> > &board,
                                            vector<vector<int> > &new_board,
                                            int life_cycles,
                                            int tid,
                                            int Nthreads,
                                            vector<pthread_barrier_t> &layer_one,
                                            vector<pthread_barrier_t> &layer_two);
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
  int Nthreads  = 4;
  int tid       = 0;

  // Declaring pthread_barrier_t layer_one and layer_two
  vector<pthread_barrier_t> layer_one;
  vector<pthread_barrier_t> layer_two;

  // Resizing the barriers
  layer_one.resize(life_cycles);
  layer_two.resize(life_cycles);

  // Creating the vector of barriers
  for(int i = 0; i < life_cycles; i++)
  {
    pthread_barrier_init(&layer_one[i], NULL, Nthreads);
    pthread_barrier_init(&layer_two[i], NULL, Nthreads);
  }

  vector<vector<int> > new_board;
  new_board = board;

  future<void> X1 = async(launch::async,
                          SimulateLife_parallel,
                          ref(board),
                          ref(new_board),
                          life_cycles,
                          tid,
                          Nthreads,
                          ref(layer_one),
                          ref(layer_two));

  future<void> X2 = async(launch::async,
                          SimulateLife_parallel,
                          ref(board),
                          ref(new_board),
                          life_cycles,
                          tid + 1,
                          Nthreads,
                          ref(layer_one),
                          ref(layer_two));

  future<void> X3 = async(launch::async,
                          SimulateLife_parallel,
                          ref(board),
                          ref(new_board),
                          life_cycles,
                          tid + 2,
                          Nthreads,
                          ref(layer_one),
                          ref(layer_two));

  future<void> X4 = async(launch::async,
                          SimulateLife_parallel,
                          ref(board),
                          ref(new_board),
                          life_cycles,
                          tid + 3,
                          Nthreads,
                          ref(layer_one),
                          ref(layer_two));
  return new_board;
}

//******************************************************************************
// Function:      StimulateLife_parallel()
// Arguments:     vector<vector<int> > &board
//                int life_cycles
//                int tid
//                int Nthreads
// Description:   Update the matrix surviving population based on rules of
//                game of life. Then update the orginal board based on # of
//                life cycles
//******************************************************************************
void GameOfLife::SimulateLife_parallel(vector<vector<int> > &board,
                                        vector<vector<int> > &new_board,
                                        int life_cycles,
                                        int tid,
                                        int Nthreads,
                                        vector<pthread_barrier_t> &layer_one,
                                        vector<pthread_barrier_t> &layer_two)
{
  int n = board.size();

  // Life cycle loop
  for(int times = 0; times < life_cycles; times++)
  {
    // Double forloop for checking each grid locations neighbors
    for(int i = tid; i < n; i+= Nthreads)
    {
      for(int j = 0; j < n; j++)
      {
        int Ncount = 0;

        // If not eternal check neighbors -> where eternal neighbors never
        // die so there is no reason to update their values
        if (board[i][j] != 2)
        {
          // checking the surrounding 8 neighbors and updating population
          // count each time we find a living person
          Ncount += neighbor_val( (n + i + 1) % n, j, board);
          Ncount += neighbor_val( (n + i - 1) % n, j, board);
          Ncount += neighbor_val( (n + i - 1) % n, (n + j + 1) % n, board);
          Ncount += neighbor_val( (n + i - 1) % n, (n + j - 1) % n, board);
          Ncount += neighbor_val( (n + i + 1) % n, (n + j + 1) % n, board);
          Ncount += neighbor_val( (n + i + 1) % n, (n + j - 1) % n, board);
          Ncount += neighbor_val( i, (n + j + 1) % n, board);
          Ncount += neighbor_val( i, (n + j - 1) % n, board);

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
          else if(Ncount == 2 && board[i][j] == 1)
          {
            new_board[i][j] = 1;
          }
          else if(Ncount == 3 && board[i][j] == 0)
          {
            new_board[i][j] = 1;
          }
        }
      }
    }
    pthread_barrier_wait(&layer_one[times]);
    // Updating old board to new board for next "life cycle"
    board = new_board;
    pthread_barrier_wait(&layer_two[times]);
  }
}


//******************************************************************************
// Function:      neighbor_val()
// Arguments:     int i
//                int j
//                vector<vector<int> > &old_board
// Description:   Calculates the number of neighbors relative to current cell
//******************************************************************************
int neighbor_val(int i, int j, vector<vector<int> > &old_board)
{
  int tmp = 0;
  if(old_board[i][j] == 1 || old_board[i][j] == 2)
  {
    tmp++;
  }
  return tmp;
}
