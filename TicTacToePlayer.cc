/*
 * TicTacToePlayer.cc
 *
 *  Created on: Sep 1, 2013
 *      Author: notroot
 */

#include <iostream>

#include "TicTacToePlayer.hh"

namespace TicTacToe
{

  // returns the position
  int Player::move(Board &board)
  {
    // Check that a game strategy has been set
    if(!playerStrategy_)
    {
        std::cerr << "ERROR no game strategy has been loaded" << std::endl;
        return Board::MOVE_RESULT_INVALID;
    }

    // Delegate to the Player Strategy
    return playerStrategy_->move(board);
  }

};
