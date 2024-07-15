#include "game.h"

namespace Board
{
	const uint8_t numberOfRows = 3;
	const uint8_t numberOfCols = 5;
};														

typedef enum
{
	PLAYER_1 = 0,
	PLAYER_2
}Player;											// Create 2 player list..

Player player = PLAYER_1;			// Create players and first player PLAYER_1..

typedef struct
{
	bool winDetected;
	char winner;
}gameResult_t;

static void UpdateGameBoard(LCD& lcd, char& pressedKey, char gameBoard[Board::numberOfRows][Board::numberOfCols])
{
	bool playerMadeAnInput = false;
	
	for(uint8_t rowIndex=0; rowIndex<Board::numberOfRows; rowIndex++)
	{
		for(uint8_t colIndex=0; colIndex<Board::numberOfCols; colIndex++)
		{
			if(pressedKey == gameBoard[rowIndex][colIndex])													// If the character on the board and the character pressed from the keypad are the same..
			{
				switch(player)
				{
					case PLAYER_1:																											// If player order is PLAYER_1..
						gameBoard[rowIndex][colIndex] = 'X';															// Replaces the character on Board at the same index with 'X'..
						player = PLAYER_2;																								// Playing order passes to PLAYER_2..
					  break;
					case PLAYER_2:																											// If player order is PLAYER_2..
						gameBoard[rowIndex][colIndex] = 'O';															// Replaces the character on Board at the same index with 'O'.
						player = PLAYER_1;																								// Playing order passes to PLAYER_1..
					  break;
				}
				playerMadeAnInput = true;																							// Input made by player..
				break;
			}
		}
		if(playerMadeAnInput)																											// If input made by player..
		{
			return;
		}
	}
}

static void DisplayGameBoard(LCD& lcd, char gameBoard[Board::numberOfRows][Board::numberOfCols])
{
	uint8_t rowPos = 1;
	const uint8_t startingColumnPos = 5;
	
	for(uint8_t rowIndex = 0; rowIndex < Board::numberOfRows; rowIndex++)
	{
		lcd.SetCursor(rowPos, startingColumnPos);
		rowPos++;
		for(uint8_t colIndex = 0; colIndex < Board::numberOfCols; colIndex++)
		{
			lcd.Print(gameBoard[rowIndex][colIndex]);
		}
	}
}

static gameResult_t CheckForHorizontalWin(char gameBoard[Board::numberOfRows][Board::numberOfCols])
{
	gameResult_t result = {0};
	char startOfRow;
	uint8_t numberOfMatchingPlayerInputs = 0;
	
	for(uint8_t rowIndex=2; rowIndex < Board::numberOfRows; rowIndex++)
	{
		startOfRow = gameBoard[rowIndex][0];
		for(uint8_t colIndex = 2; colIndex < Board::numberOfCols; colIndex+=2)
		{
			if(startOfRow == gameBoard[rowIndex][colIndex])
			{
				numberOfMatchingPlayerInputs++;
			}
		}
		
		if(numberOfMatchingPlayerInputs == 2)
		{
			result.winDetected = true;
			result.winner = startOfRow;
			return result;
		}
		else 
		{
			numberOfMatchingPlayerInputs = 0;
		}
	}
	return result;
}

static gameResult_t CheckForVerticalWin(char gameBoard[Board::numberOfRows][Board::numberOfCols])
{
	gameResult_t result = {0};
	char startOfColumn;
	uint8_t numberOfMatchingPlayerInputs = 0;
	
	for(uint8_t colIndex=0; colIndex<Board::numberOfCols; colIndex+=2)
	{
		startOfColumn = gameBoard[0][colIndex];
		for(uint8_t rowIndex = 1; rowIndex < Board::numberOfRows; rowIndex++)
		{
			if(startOfColumn == gameBoard[rowIndex][colIndex])
			{
				numberOfMatchingPlayerInputs++;
			}
		}
		if(numberOfMatchingPlayerInputs == 2)
		{
			result.winDetected = true;
			result.winner = startOfColumn;
			return result;
		}
		else
		{
			numberOfMatchingPlayerInputs = 0;
		}
	}
	return result;
}

static gameResult_t CheckForDialogWin(char gameBoard[Board::numberOfRows][Board::numberOfCols])
{
	gameResult_t result = {0};
	if((gameBoard[0][0] == gameBoard[1][2]) && (gameBoard[0][0] == gameBoard[2][4]))
	{
		result.winDetected = true;
		result.winner = gameBoard[0][0];
		return result;
	}
	
	if((gameBoard[0][4] == gameBoard[1][2]) && (gameBoard[0][4] == gameBoard[2][0]))
	{
		result.winDetected = true;
		result.winner = gameBoard[0][4];
		return result;
	}
	return result;
}

// Extern Functions:
void Game_DisplayIntro(LCD& lcd)
{
	lcd.Clear();
	lcd.SetCursor(0,1);
	lcd.Print("|   WELCOME      |");
	lcd.SetCursor(1,1);
	lcd.Print("|   TO THE       |");
	lcd.SetCursor(2,1);
	lcd.Print("|   TIC TAC TOE  |");
	lcd.SetCursor(3,1);
	lcd.Print("|   TOURNAMENT   |");
}

void Game_DisplayMenu(LCD& lcd)
{
	lcd.Clear();
	lcd.SetCursor(0,4);
	lcd.Print("Game Menu");
	lcd.SetCursor(1,0);
	lcd.Print("1|2|3   A:Start");
	lcd.SetCursor(2,0);
	lcd.Print("4|5|6   B:Back/Exit");
	lcd.SetCursor(3,0);
	lcd.Print("7|8|9   #:Rules");	
}

void Game_DisplayRules(LCD& lcd)
{
	lcd.Clear();
	lcd.SetCursor(0,4);
	lcd.Print("Rule(1/2)");
	lcd.SetCursor(1,0);
	lcd.Print("Press the numbers");
	lcd.SetCursor(2,0);
	lcd.Print("to place X or O to");
	lcd.SetCursor(3,0);
	lcd.Print("the game board");
	HAL_Delay(1500);
	lcd.Clear();
	lcd.SetCursor(0,4);
	lcd.Print("Rule(2/2)");
	lcd.SetCursor(1,0);
	lcd.Print("X is to player 1");
	lcd.SetCursor(2,0);
	lcd.Print("O is to player 2");
	lcd.SetCursor(3,0);
	lcd.Print("Players take turns");
}

void Game_Start(LCD& lcd, Keypad& keypad)
{
	lcd.Clear();
	lcd.SetCursor(0,3);
	lcd.Print("TIC TAC TOE");
	
	char gameBoard[Board::numberOfRows][Board::numberOfCols] = 
	{
		{'1','|','2','|','3'},
		{'4','|','5','|','6'},
		{'7','|','8','|','9'}
	};
	
	// Array of function pointers
	static gameResult_t(*CheckWin[3])(char gameBoard[Board::numberOfRows][Board::numberOfCols]) =
	{
		CheckForHorizontalWin,
		CheckForVerticalWin,
		CheckForDialogWin
	};
	
	while(1)
	{
		// Game Loop
		DisplayGameBoard(lcd, gameBoard);
		char pressedKey = keypad.GetCharShortPress();
		
		if(pressedKey == 'B')
		{
			// Exit Game
			Game_DisplayMenu(lcd);
			player = PLAYER_1;  // Return first player status to player 1
			break;
		}
		UpdateGameBoard(lcd, pressedKey, gameBoard);
		for(uint8_t i=0; i<3; i++)
		{
			gameResult_t result = CheckWin[i](gameBoard);
			if(result.winDetected)
			{
				lcd.SetCursor(1,13);
				if(result.winner == 'X')
				{
					lcd.Print("P1 Wins");
					break;
				}
				else if(result.winner == 'O')
				{
					lcd.Print("P2 Wins");
					break;
				}
			}
		}
	}
}
