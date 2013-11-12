/*
 * TicTacToeStrategyBase.hh
 *
 *  Created on: Sep 1, 2013
 *      Author: notroot
 */

#ifndef TICTACTOESTRATEGYBASE_HH_
#define TICTACTOESTRATEGYBASE_HH_

#include "TicTacToeBoard.hh"

namespace TicTacToe {

  class PlayerStrategyBase
  {
  public:
    PlayerStrategyBase() {}
    virtual ~PlayerStrategyBase() {}

    // Returns the position
    virtual int move(Board &board) = 0;
  };

}; // namespace

#endif /* TICTACTOESTRATEGYBASE_HH_ */
