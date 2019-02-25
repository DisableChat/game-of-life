//******************************************************************************
// File:          GameOfLife.h
// Author:        Wesley Ryder
// Description:
//******************************************************************************

#include <iostream>
#include <vector>
using namespace std;

class GameOfLife
{
  public:
    vector<vector<int> > SimulateLife(vector<vector<int> > &board, int life_cycles);
  private:
};


vector<vector<int> > GameOfLife::SimulateLife(vector<vector<int> > &board, int life_cycles)
{
  cout << "hi" << endl;
}

/*
// possible neighbors
1. (i + 1( mod )n, j)
2. (i − 1) mod n, j)
3. (i − 1) mod n, j + 1 mod n)
4. (i − 1) mod n, j − 1 mod n)
5. (i + 1) mod n, j + 1 mod n)
6. (i + 1) mod n, j − 1 mod n)
7. (i, j + 1 mod n)
8. (i, j − 1 mod n)
*/
