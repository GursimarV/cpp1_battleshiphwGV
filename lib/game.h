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
      //Structuring Guessing
      struct Guess {
          int x;
          int y;
      };

      //Making lists of the guesses
      std::list<Guess> correctGuess;
      std::list<Guess> incorrectGuess;

      int solve() override {
          int hits = 0;

          //Initializing the random guess on both axis
          while (hits <= SHIP_COUNT) {
              int randomGuessX = 1 + rand() % 100;
              int randomGuessY = 1 + rand() % 100;

              ///Making a random response to the guess
              Guess guessRandomCurrent = { randomGuessX, randomGuessY };

              ResponseType response = this->board->guess(randomGuessX, randomGuessY);

              //Checking the random guess whether they hit, near miss, or miss
              if (response == ResponseType::HIT && AnotherGuess(randomGuessX, randomGuessY)) {
                  correctGuess.push_back(guessRandomCurrent);
                  hits += 1;
              }
              else if (response == ResponseType::NEARMISS) {
                  hits += TestNearMiss(randomGuessX, randomGuessY, 1, 0);
                  hits += TestNearMiss(randomGuessX, randomGuessY, -1, 0);
                  hits += TestNearMiss(randomGuessX, randomGuessY, 0, 1);
                  hits += TestNearMiss(randomGuessX, randomGuessY, 0, -1);
              }
              else if (response == ResponseType::MISS) {
                  incorrectGuess.push_back(guessRandomCurrent);
              }
          }
          return hits;
      }

      int TestNearMiss(int x, int y, int dx, int dy) {
          if (CheckValidGuess(x + dx, y + dy) && AnotherGuess(x + dx, y + dy)) {
              correctGuess.push_back({ x + dx, y + dy });
              return 1;
          }
          return 0;
      }

      bool CheckingLastGuess(int x, int y) {
          for (const auto& g : correctGuess) {
              if (g.x == x && g.y == y) {
                  return false;
              }
          }

          for (const auto& g : incorrectGuess) {
              if (g.x == x && g.y == y) {
                  return false;
              }
          }

          return true;
      }

      bool AnotherGuess(int x, int y) {
          return this->board->guess(x, y) == ResponseType::HIT;
      }

      bool CheckValidGuess(int x, int y) {
          return x <= WIDTH && y <= HEIGHT;
      }
};

#endif /* GAME_H */
