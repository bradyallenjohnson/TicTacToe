/*
 * TicTacToeBoard.hh
 *
 *  Created on: Sep 1, 2013
 *      Author: Brady Johnson
 */

#ifndef TICTACTOEBOARD_HH_
#define TICTACTOEBOARD_HH_

#include <list>
#include <vector>

using namespace std;

namespace TicTacToe {

class Board
{
public:
  Board();
  ~Board();

  typedef char PositionIdType;

  const static int BOARD_SIZE;
  const static int NUM_WINNERS;
  const static PositionIdType BOARD_POSITION_EMPTY;

  enum MoveResult {
    MOVE_RESULT_ERROR = 0,    // Some sort of error: out of range
    MOVE_RESULT_INVALID,      // An invalid position was chosen: already played
    MOVE_RESULT_SUCCESS,      // The move was successful, keep going
    MOVE_RESULT_FINISH,       // The move was successful, but no more moves are possible
    MOVE_RESULT_WIN
  };

  Board::MoveResult move(PositionIdType playerId, int position);
  void print();

  PositionIdType getPosition(int position) const;
  int getNextAvailablePosition() const;
  inline int getLastMove() const { return lastMove_; }
  inline vector<list<int> > getWinnerPositions() const { return winnerPositions_; }


private:
  vector<PositionIdType> board_;
  vector<list<int> > winnerPositions_;
  int lastMove_;

  bool isWinner(PositionIdType playerId);
};

};

#endif /* TICTACTOEBOARD_HH_ */
