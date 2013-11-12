
#include <iostream>

#include "TicTacToeBoard.hh"
#include "TicTacToePlayer.hh"
#include "TicTacToePlayerStrategies.hh"

using namespace std;

void displayHelp()
{
  TicTacToe::Board helpBoard;
  TicTacToe::Board::PositionIdType id = '0';
  for(int i = 0; i < TicTacToe::Board::BOARD_SIZE; ++i)
  {
      helpBoard.move(id++, i);
  }

  cout << "When playing, choose the position as follows:" << endl;
  helpBoard.print();
}

int main(int argc, char **argv)
{
  // Get info about the Human player
  cout << "Choose your player [x or o] (x plays first): ";
  TicTacToe::Board::PositionIdType humanPlayerId;
  cin >> humanPlayerId;

  while(humanPlayerId != 'x' && humanPlayerId != 'o')
  {
	  cout << "Invalid entry, try again [x or o]: ";
	  cin >> humanPlayerId;
  }

  TicTacToe::Player *player;

  // Setup the Human Player
  TicTacToe::Player humanPlayer;
  humanPlayer.setId(humanPlayerId);
  humanPlayer.setPlayerStrategy(new TicTacToe::PlayerStrategyHuman());

  // Setup the Computer Player
  TicTacToe::Player computerPlayer;
  TicTacToe::PlayerStrategyComputer strategy;
  // Once the board is created, we'll inject the winner positions
  computerPlayer.setPlayerStrategy(&strategy);
  if(humanPlayerId == 'x')
  {
      computerPlayer.setId('o');
      player = &humanPlayer;
  }
  else
  {
      computerPlayer.setId('x');
      player = &computerPlayer;
  }

  displayHelp();

  //
  // Lets play
  //
  TicTacToe::Board board;
  strategy.setWinnerPositions(board.getWinnerPositions());
  TicTacToe::Board::MoveResult moveResult(TicTacToe::Board::MOVE_RESULT_ERROR);
  while(moveResult != TicTacToe::Board::MOVE_RESULT_WIN &&
        moveResult != TicTacToe::Board::MOVE_RESULT_FINISH)
  {
      // Loop until a valid move was chosen
      do
      {
          moveResult = board.move(player->getId(), player->move(board));

      } while(moveResult == TicTacToe::Board::MOVE_RESULT_ERROR ||
              moveResult == TicTacToe::Board::MOVE_RESULT_INVALID);

      // show the board
      board.print();

      // Switch the player pointer, if WIN or FINISH dont switch
      if(moveResult == TicTacToe::Board::MOVE_RESULT_SUCCESS)
      {
          if(player == &humanPlayer)
          {
              player = &computerPlayer;
          }
          else
          {
              player = &humanPlayer;
          }
      }
  }

  // Display the results
  if(moveResult == TicTacToe::Board::MOVE_RESULT_FINISH)
  {
      cout << "The game was a DRAW." << endl;
  }
  else
  {
      cout << "Player " << player->getId() << " wins!!" << endl;
  }

  return 0;
}

