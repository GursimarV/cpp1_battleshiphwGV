#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "consts.h"

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
        
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (this->board->guess(i, j) == ResponseType::NEARMISS)
                {
                    for (i = i - 1; i + 1; i++)
                    {
                        for (j = j - 1; j + 1; j++)
                        {
                            if (this->board->guess(i, j) == ResponseType::HIT)
                            {
                                hits += 1;
                            }
                        }
                    }
                }

            }
            
        }
        return SHIP_COUNT;
    }
};


#endif /* GAME_H */
