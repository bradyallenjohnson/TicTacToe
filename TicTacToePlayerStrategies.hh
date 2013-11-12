/*
 * TicTacToePlayerStrategies.hh
 *
 *  Created on: Sep 1, 2013
 *      Author: notroot
 */

#ifndef TICTACTOEPLAYERSTRATEGIES_HH_
#define TICTACTOEPLAYERSTRATEGIES_HH_

#include "TicTacToeStrategyBase.hh"

namespace TicTacToe {

  class PlayerStrategyHuman : public TicTacToe::PlayerStrategyBase
  {
  public:
    PlayerStrategyHuman() {}
    virtual ~PlayerStrategyHuman() {}

    // Returns the position
    virtual int move(Board &board);
  };



  class PlayerStrategyComputer : public TicTacToe::PlayerStrategyBase
  {
  public:
    PlayerStrategyComputer() {}
    virtual ~PlayerStrategyComputer() {}

    inline void setWinnerPositions(vector<list<int> > winnerPositions)
    { myWinnerPositions_ = winnerPositions;  theirWinnerPositions_ = winnerPositions; }

    // Returns the position
    virtual int move(Board &board);

  private:
    vector<list<int> > myWinnerPositions_;
    vector<list<int> > theirWinnerPositions_;

    void removeWinnersWithPosition(int position, vector<list<int> > &winnerPositions);
    void updateWinnersWithPosition(int position, vector<list<int> > &winnerPositions);

    int defense();
    int offense();

  };

} /* namespace TicTacToe */

#endif /* TICTACTOEPLAYERSTRATEGIES_HH_ */
