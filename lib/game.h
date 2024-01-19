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

class AssignmentGame : public BaseGame {
protected:
    int solve() override {
        int hits = 0;

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (this->board->guess(i, j) == ResponseType::HIT) {
                    hits += 1;
                }

                if (this->board->guess(i, j) == ResponseType::NEARMISS) {
                    // straight
                    hits += TestNearMiss(i + 1, j);
                    hits += TestNearMiss(i - 1, j);
                    hits += TestNearMiss(i, j + 1);
                    hits += TestNearMiss(i, j - 1);

                    // diagonal
                    hits += TestNearMiss(i + 1, j + 1);
                    hits += TestNearMiss(i - 1, j - 1);
                    hits += TestNearMiss(i - 1, j + 1);
                    hits += TestNearMiss(i + 1, j - 1);
                }
            }
        }

        return hits;
    }

    int TestNearMiss(int x, int y) {
        if (CheckValidGuess(x, y) && this->board->guess(x, y) == ResponseType::HIT) {
            return 1;
        }
        return 0;
    }

    bool CheckValidGuess(int x, int y) {
        return x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH;
    }
};

#endif /* GAME_H */
