#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "consts.h"
#include <iostream>
#include <list>
#include <cstdlib>

class BaseGame {
protected:
  Board * board;
  virtual int solve() = 0;
public:
  BaseGame();
  ~BaseGame();
  int run();
};


class ControlGame : public BaseGame {
protected:
    int solve() override {
        int hits = 0;
        for(int i = 0; i < HEIGHT; i++)
        {
            for(int j = 0; j < WIDTH; j++)
            {
                if(this->board->guess(i, j) == ResponseType::HIT)
                {
                    hits += 1;
                }
            }
        }
        return hits;
    }
};

class AssignmentGame : public BaseGame{
protected:
    int solve() override
    {
        int hits = 0;

        // Goes over each part of the board by position
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                // Check if the guess at this position is a HIT
                if (this->board->guess(i, j) == ResponseType::HIT)
                {
                    //Increase the hit counter
                    hits += 1;
                }

                // Check if the guess at this position is a NEARMISS
                if (this->board->guess(i, j) == ResponseType::NEARMISS)
                {
                    // Check for nearby hits in straight directions
                    hits += TestNearMiss(i + 1, j);
                    hits += TestNearMiss(i - 1, j);
                    hits += TestNearMiss(i, j + 1);
                    hits += TestNearMiss(i, j - 1);

                    // Check for nearby hits in diagonal directions
                    hits += TestNearMiss(i + 1, j + 1);
                    hits += TestNearMiss(i - 1, j - 1);
                    hits += TestNearMiss(i - 1, j + 1);
                    hits += TestNearMiss(i + 1, j - 1);
                }
            }
        }
        // Return the total hits count on the board
        return hits;
    }

    // Function to test for a near miss at a given position
    int TestNearMiss(int x, int y)
    {
        // Check if the guess at the specified position is a HIT and the position is valid
        if (CheckValidGuess(x, y) && this->board->guess(x, y) == ResponseType::HIT)
        {
            // Return 1 if it's a near miss
            return 1;
        }
        // Return 0 if not a near miss
        return 0;
    }

    // Function to check if a guess at the specified position is valid
    bool CheckValidGuess(int x, int y)
    {
        return x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH;
    }
};

#endif /* GAME_H */
