/*
 * Player.hh
 *
 *  Created on: Sep 1, 2013
 *      Author: notroot
 */

#ifndef PLAYER_HH_
#define PLAYER_HH_

#include "TicTacToeBoard.hh"
#include "TicTacToeStrategyBase.hh"

namespace TicTacToe
{

  class Player
  {
  public:
    Player(Board::PositionIdType id) : playerStrategy_(0), id_(id) {}
    Player() : playerStrategy_(0), id_('z') {}

    inline Board::PositionIdType getId() const  { return id_; }
    inline void setId(Board::PositionIdType id) { id_ = id;   }

    inline const PlayerStrategyBase* getPlayerStrategy() const { return playerStrategy_; }
    inline void setPlayerStrategy(PlayerStrategyBase* gameStrategy) { playerStrategy_ = gameStrategy;	}

    // Returns the position
    int move(Board &board);

  private:
    PlayerStrategyBase *playerStrategy_;
    Board::PositionIdType id_;
  };

} /* namespace TicTacToe */
#endif /* PLAYER_HH_ */
