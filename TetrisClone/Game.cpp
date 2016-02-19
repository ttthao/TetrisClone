/*
 * Filename: Game.cpp
 * Author: Tommy Truong
 * Description: Sets up the board & pieces.
 * Date: 06/17/2015
 */

#include "Game.h"
#include <stdlib.h>


Game::Game(Board *cBoard, sevenPieces *cPiece, drawTetris *cDrawTetris, int cScrnHt) {

	/* Set height as passed height */
	gScrnHt = cScrnHt;

	/* Point board to preset board */
	gBoard = cBoard;

	/* Point piece to preset piece */
	gPiece = cPiece;

	/* Set IO to preset IO */
	gDrawTetris = cDrawTetris;

	/* Start the game */
	startGame();
}

/*
 * Function name: getRand
 * Function prototype: int getRand(int a, int b);
 *
 * Description: Generates a random number between b & a.
 *
 * Parameters: int a -- The 1st number.
 *             int b -- The 2nd number.
 *
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: A random number between b & a.
 */

int Game::getRand(int a, int b) {
    return rand() % (b - a + 1) + a;
}

/*
 * Function name: startGame
 * Function prototype: void startGame();
 *
 * Description: Selects the 1st & subsequent piece.
 *
 * Parameters: None.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

void Game::startGame()
{
    /* Initialize random numbers, this randomizes the algorithm of rand() */
    srand((unsigned int) time(NULL));

    /* Randomly select the 1st piece */
    pieceType = getRand(0, MAX_PIECES);
    rotationType = getRand(0, MAX_ROTATIONS);
    xCurrent = (WIDTH/2) + gPiece -> getStartX(pieceType, rotationType);
    yCurrent = gPiece -> getStartY(pieceType, rotationType);

    /* Subsequent piece is generated */
    nextPiece = getRand(0, MAX_PIECES);
    nextRotation = getRand(0, MAX_ROTATIONS);
	nextX = NEXT_PIECE_X;
    nextY = NEXT_PIECE_Y;
}

/*
 * Function name: createNewPiece
 * Function prototype: void createNewPiece();
 *
 * Description: Sets the current piece as the next piece & generates the next.
 *
 * Parameters: None.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

void Game::createNewPiece() {
    
    /* Set the falling piece to be the next one */
    pieceType = nextPiece;
    rotationType = nextRotation;
    xCurrent = (WIDTH/2) + gPiece -> getStartX(pieceType, rotationType);
    yCurrent = gPiece -> getStartY(pieceType, rotationType);

    /* Generate the next piece */
    nextPiece = getRand(0, MAX_PIECES);
    nextRotation = getRand(0, MAX_ROTATIONS);
}

/*
 * Function name: drawPiece
 * Function prototype: void drawPiece(int x, int y, int piece, int rotation);
 *
 * Description: Draws the piece.
 *
 * Parameters: int x -- Horizontal position in blocks.
 *             int y -- Vertical position in blocks.
 *             int piece -- Piece to be drawn.
 *             int rotation -- The rotation of the piece.
 *
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

void Game::drawPiece(int x, int y, int pieceType, int rotationType) {

    /* Color of the block */
    color bColor;

    /* Find the position in pixels of where the piece should be drawn */
    int xPixels = gBoard -> getXPosPixels(x);
    int yPixels = gBoard -> getYPosPixels(y);

    /* Iterate through the 5x5 matrix of the piece to draw it */
    for(int i = 0; i < PIECE_MATRIX; i++)
    {
		/* Cycle throug the rows, then move up a line*/
        for(int j = 0; j < PIECE_MATRIX; j++)
        {
            /* Get block type & correct color */
            switch(gPiece -> getBlockType(pieceType, rotationType, j, i))
            {
                case 1:
                    bColor = BLUE;
                    break;

                case 2:
                    bColor = GREY;
                    break;
            }
            
            /* Check if piece is null */
            if(gPiece -> getBlockType(pieceType, rotationType, j, i) != 0)
                gDrawTetris -> drawFilledRect(xPixels + i*PIECE_AREA, 
				yPixels + j*PIECE_AREA, BLOCK_WH, BLOCK_WH, bColor);
        }
    }
}

/*
 * Function name: drawBoard
 * Function prototype: void drawBoard()
 *
 * Description: Draws the 2 borders & settled pieces.
 *
 * Parameters: None.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

void Game::drawBoard() {
    
    /* Find the position in pixels to draw the 2 borders */
	int leftX = BOARD_POS - (PIECE_AREA * (WIDTH / 2)) - 1,
		rightX = BOARD_POS + (PIECE_AREA * (WIDTH / 2)) + 1,
		top = gScrnHt - (PIECE_AREA * HEIGHT),
		borderHt = (gScrnHt - 1) - top;

    /* Draw the borders */
    gDrawTetris -> drawFilledRect(leftX - BORDER_WIDTH, top, BORDER_WIDTH, borderHt, RED);
    gDrawTetris -> drawFilledRect(rightX, top, BORDER_WIDTH, borderHt, RED);

    /* Draw settled pieces */
    leftX += 1;
	for (int i = 0; i < WIDTH; i++)
    {
        for(int j = 0; j < HEIGHT; j++)
        {
            if(!gBoard -> isBlockEmpty(i, j))
                gDrawTetris -> drawFilledRect(leftX + i*PIECE_AREA, 
				top + j*PIECE_AREA, BLOCK_WH, BLOCK_WH, GREY);
        }
    }
}

/*
 * Function name: drawScene
 * Function prototype: void drawScene()
 *
 * Description: Draws the entire game.
 *
 * Parameters: None.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

void Game::drawScene() {

	/* Draw the border lines & settled pieces */
    drawBoard();

	/* Draw the current falling piece */
    drawPiece(xCurrent, yCurrent, pieceType, rotationType);
	
	/* Draw the next piece on the side */
    drawPiece(nextX, nextY, nextPiece, nextRotation);
}
