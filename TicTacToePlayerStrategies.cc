/*
 * TicTacToePlayerStrategies.cc
 *
 *  Created on: Sep 1, 2013
 *      Author: notroot
 */

#include <iostream>

#include "TicTacToePlayerStrategies.hh"

using namespace std;

namespace TicTacToe
{

  //
  // Human Strategy
  //

  int PlayerStrategyHuman::move(Board& board)
  {
    cout << "Choose a position: ";
    int position;
    cin >> position;

    return position;
  }


  //
  // Computer Strategy
  //

  int PlayerStrategyComputer::move(Board& board)
  {
    // Update the winners with the last move
    int lastMove(board.getLastMove());
    if(lastMove >= 0)
    {
      removeWinnersWithPosition(lastMove, myWinnerPositions_);
      updateWinnersWithPosition(lastMove, theirWinnerPositions_);
    }

    // First defense: see if the opponent is about to win and block it
    int position = defense();

    // Now Offense
    if(position < 0)
    {
      position = offense();
    }

    cout << "Computer chose position: " << position << endl;

    removeWinnersWithPosition(position, theirWinnerPositions_);
    updateWinnersWithPosition(position, myWinnerPositions_);

    return position;
  }

  void PlayerStrategyComputer::removeWinnersWithPosition(int position, vector<list<int> > &winnerPositions)
  {
    // Remove all the playerA lists that contains the position played by playerB
    // since playerA cant win with any of those lists now
    for(int i = 0; i < Board::NUM_WINNERS; ++i)
    {
        bool foundIt(false);
        list<int> &winner(winnerPositions[i]);

        for(list<int>::iterator iter = winner.begin();
            iter != winner.end() && !foundIt;
            ++iter)
        {
            if(*iter == position)
            {
                winner.clear();
                foundIt = true;
            }
        }
    }
  }

  void PlayerStrategyComputer::updateWinnersWithPosition(int position, vector<list<int> > &winnerPositions)
  {
    // Update playerA lists with the position played by playerA
    // Remove the played position from the lists
    // if a list is {0, 1, 2} and they play 1, then the list
    // will be {0, 2} meaning they can play either of those
    // later searching for lists of size 1 will be those where the opponent could win
    for(int i = 0; i < Board::NUM_WINNERS; ++i)
    {
        bool foundIt(false);
        list<int> &winner(winnerPositions[i]);

        for(list<int>::iterator iter = winner.begin();
            iter != winner.end() && !foundIt;
            ++iter)
        {
            if(*iter == position)
            {
                winner.erase(iter);
                foundIt = true;
            }
        }
    }
  }

  // Looks for the first possible opponent winning position
  int PlayerStrategyComputer::defense()
  {
    int firstSize2(-1);

    // A list of size 2 means that the opponent played one of the 3 positions in a winner list
    // A list of size 1 means that if the opponent plays that remaining position they win

    for(int i = 0; i < Board::NUM_WINNERS; ++i)
    {
        list<int> &winner(theirWinnerPositions_[i]);
        int size(winner.size());

        if(size == 1)
        {
            cout << "And the computer gets a block!!!" << endl;
            return winner.front();
        }
#if 0
        // TODO for now, lets not defend against size 2 lists
        //      we should only do this if offense() doesnt find anything
        else if(size == 2)
        {
            firstSize2 = winner.front();
        }
#endif
    }

    return firstSize2;
  }

  // Looks for the next possible winning position
  int PlayerStrategyComputer::offense()
  {
    int firstSize3(-1);
    int firstSize2(-1);

    // A list of size 1 means that that is a winning move
    // A list of size 2 means that one of the 3 positions in a winner list has been played
    // A list of size 3 means that none of the positions in the last have been played

    for(int i = 0; i < Board::NUM_WINNERS; ++i)
    {
        list<int> &winner(myWinnerPositions_[i]);
        int size(winner.size());

        if(size == 1)
        {
            return winner.front();
        }
        else if(size == 2)
        {
            firstSize2 = winner.front();
        }
        else
        {
            firstSize3 = winner.front();
        }
    }

    if(firstSize2 >= 0)
    {
        return firstSize2;
    }
    else
    {
        return firstSize3;
    }
  }

} /* namespace TicTacToe */
