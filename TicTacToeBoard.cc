/*
 * TicTacToeBoard.cc
 *
 *  Created on: Sep 1, 2013
 *      Author: notroot
 */

#include <iostream>
#include <list>

#include "TicTacToeBoard.hh"

using namespace std;

namespace TicTacToe {

const int Board::BOARD_SIZE = 9;
const int Board::NUM_WINNERS = 8;
const Board::PositionIdType Board::BOARD_POSITION_EMPTY = ' ';

Board::Board() :
	board_(BOARD_SIZE, BOARD_POSITION_EMPTY),
	winnerPositions_(NUM_WINNERS),
	lastMove_(-1)
{
  int index(0);
  list<int> winner;

  // First the rows
  winner.push_back(0);
  winner.push_back(1);
  winner.push_back(2);
  winnerPositions_[index++] = winner;

  winner.clear();
  winner.push_back(3);
  winner.push_back(4);
  winner.push_back(5);
  winnerPositions_[index++] = winner;

  winner.clear();
  winner.push_back(6);
  winner.push_back(7);
  winner.push_back(8);
  winnerPositions_[index++] = winner;

  // Then the columns
  winner.clear();
  winner.push_back(0);
  winner.push_back(3);
  winner.push_back(6);
  winnerPositions_[index++] = winner;

  winner.clear();
  winner.push_back(1);
  winner.push_back(4);
  winner.push_back(7);
  winnerPositions_[index++] = winner;

  winner.clear();
  winner.push_back(2);
  winner.push_back(5);
  winner.push_back(8);
  winnerPositions_[index++] = winner;

  // And finally the diagonals
  winner.clear();
  winner.push_back(0);
  winner.push_back(4);
  winner.push_back(8);
  winnerPositions_[index++] = winner;

  winner.clear();
  winner.push_back(2);
  winner.push_back(4);
  winner.push_back(6);
  winnerPositions_[index++] = winner;

}

Board::~Board()
{
}

Board::MoveResult Board::move(PositionIdType playerId, int position)
{
  // Check position is in range
  if(position >= BOARD_SIZE)
  {
      cerr << "ERROR: position: " << position << " is out of range" << endl;
      return MOVE_RESULT_ERROR;
  }

  // Check if the position has already been played
  if(board_[position] != BOARD_POSITION_EMPTY)
  {
      cerr << "Invalid position, its already been played" << endl;
      return MOVE_RESULT_INVALID;
  }

  board_[position] = playerId;
  lastMove_ = position;

  // Check if it was a winning move
  if(isWinner(playerId))
  {
      return MOVE_RESULT_WIN;
  }

  // Check if the game is finished, since there are no more empty positions left
  // TODO we could probably do this easier by checking the total number of moves so far
  bool positionsLeft(false);
  for(int i = 0; i < BOARD_SIZE; ++i)
  {
      if(board_[i] == BOARD_POSITION_EMPTY)
      {
          positionsLeft = true;
          break;
      }
  }
  if(!positionsLeft)
  {
      return MOVE_RESULT_FINISH;
  }

  return MOVE_RESULT_SUCCESS;
}

Board::PositionIdType Board::getPosition(int position) const
{
  if(position >= BOARD_SIZE)
  {
      return '?';
  }

  return board_[position];
}

void Board::print()
{
  int index(0);
  for(int i = 0; i < 3; ++i)
  {
      for(int j = 0; j < 3; ++j)
      {
          cout << " " << (PositionIdType) board_[index++] << " ";
          if(j != 2)
          {
              cout << "|";
          }
      }

      if(i != 2)
      {
          cout << endl << "---+---+---";
      }
      cout << endl;
  }

  cout << endl;
}

int Board::getNextAvailablePosition() const
{
  for(int i = 0; i < Board::BOARD_SIZE; ++i)
  {
      if(board_[i] == Board::BOARD_POSITION_EMPTY)
      {
          return i;
      }
  }

  // Invalid return
  return Board::BOARD_SIZE;
}

bool Board::isWinner(PositionIdType playerId)
{
  for(int i = 0; i < NUM_WINNERS; ++i)
  {
      bool foundIt(true);
      list<int> &playerMoves(winnerPositions_[i]);

      for(list<int>::iterator iter = playerMoves.begin();
          iter != playerMoves.end() && foundIt;
          ++iter)
      {
          if(board_[*iter] != playerId)
          {
              foundIt = false;
          }
      }

      // if its still true after checking the list, then its a winner
      if(foundIt)
      {
          return true;
      }
  }

  return false;
}

};
