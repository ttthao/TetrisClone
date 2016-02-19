
/*
 * Filename: Board.c
 * Author: Tommy Truong
 * Description: This file holds the methods to place the pieces onto the board.
 * Date: 06/17/2015
 */

#include "Board.h"

/*
* Constructor name: Board
* Constructor prototype: Board(sevenPieces *cPiece, int cScrnHt);
*
* Description: Board constructor.
*
* Parameters: sevenPieces *cPiece -- The desired piece.
*			  int cScrnHt -- The desired screen height.
*
* Side Effects: None.
* Error Conditions: None.
* Return Value: None.
*/

Board::Board(sevenPieces *cPiece, int cScrnHt) {

	/* Set piece to the desired type */
	bPiece = cPiece;

	/* Set screen height to passed height */
	bScrnHt = cScrnHt;

	/* Initialize the board */
	initBoard();
}

/*
 * Function name: startBoard
 * Function prototype: void startBoard();
 *
 * Description: Initialize the board blocks w/free positions.
 *
 * Parameters: None.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

void Board::initBoard() {
    for(int i = 0; i < WIDTH; i++)
    {
        /* Fill the board w/free positions from top to bottom, left to right */
        for(int j = 0; j < HEIGHT; j++)
            bBoard[i][j] = EMPTY;
    }
}

/*
 * Function name: placePiece
 * Function prototype: void placePiece(int x, int y, int block, int rotation);
 *
 * Description: Place 1 of the 7 pieces in the board by filling the bloaks.
 *
 * Parameters: int x -- Horizontal position in blocks.
 *             int y -- Vertical position in blocks.
 *             int block -- 1 of the 7 pieces to draw.
 *             int rotation -- 1 of the 4 possible rotations.
 *
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

void Board::setPiece(int x, int y, int block, int rotation) {
    for(int i1 = x, i2 = 0; i1 < x + PIECE_MATRIX; i1++, i2++)
    {
        for(int j1 = y, j2 = 0; j1 < y + PIECE_MATRIX; j1++, j2++)
        {
            /* Marks the positions filled for future rendering */
            if(bPiece -> getBlockType(block, rotation, j2, i2) != 0)
                bBoard[i1][j1] = FILLED;
        }
    }
}

/*
 * Function name: endGame
 * Function prototype: bool endGame();
 *
 * Description: End the game when the top line has a block.
 *
 * Parameters: None.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

bool Board::gameOver()
{
    /* If top line filled with a block, end game */
    for(int i = 0; i < WIDTH; i++)
    {
        /* Check from left to right for a single filled position */
        if(bBoard[i][0] == FILLED)
			return true;
    }
    return false;
}

/*
 * Function name: deleteLine
 * Function prototype: void deleteLine(int y);
 *
 * Description: Deletes a line by moving the lines above down a line.
 *
 * Parameters: int y -- Vertical position of the line to delete.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

void Board::deleteLine(int y) {
    /* Delete the line by moving lines above down */
    for(int j = y; j > 0; j--)
    {
        /* Move each block above the current one down */
        for(int i = 0; i < WIDTH; i++)
            bBoard[i][j] = bBoard[i][j-1];
    }
}

/*
 * Function name: deletePossLines
 * Function prototype: void deletePossLines();
 *
 * Description: Checks if any lines need to be deleted.
 *
 * Parameters: None.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

void Board::deletePossLines() {

    /* Check each horizontal line */
    for(int j = 0; j < HEIGHT; j++)
    {
        /* Check each block from left to right */
		int i = 0;
        for(; i < WIDTH; i++)
        {
            /* If an empty position is found, don't delete the line */
            if(bBoard[i][j] != FILLED)
                break;
        }

        /* If all blocks from left to right filled, delete it */
        if(i == WIDTH)
            deleteLine(j);
    }
}

/*
 * Function name: isBlockFree
 * Function prototype: bool isBlockFree(int x, int y)
 *
 * Description: Checks if position is filled or free.
 *
 * Parameters: int x -- Horizontal position in blocks.
               int y -- Vertical position in blocks.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: True if empty otherwise false.
 */

bool Board::isBlockEmpty(int x, int y) {
	if (bBoard[x][y] != FILLED)
		return true;
	else
		return false;
}

/*
 * Function name: getXPosPixels
 * Function prototype: int getXPosPixels(int pos);
 *
 * Description: Calculates the horizontal position in pixels.
 *
 * Parameters: int pos -- Horizontal position of the block.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: Position in pixels.
 */

int Board::getXPosPixels(int x) {

    return (BOARD_POS - (PIECE_AREA * (WIDTH/2)) + (x*PIECE_AREA));
}

/*
 * Function name: getYPosPixels
 * Function prototype: int getYPosPixels(int pos);
 *
 * Description: Calculates the vertical position in pixels.
 *
 * Parameters: int pos -- Vertical position of the block.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: Position in pixels.
 */

int Board::getYPosPixels(int y) {

    return ((bScrnHt - (PIECE_AREA * HEIGHT)) + (y*PIECE_AREA));
}

/*
 * Function name: isMvmntPoss
 * Function prototype: bool isMvmntPoss(int x, int y, int block, int rotation);
 *
 * Description: Checks if piece can be place w/out collision.
 *
 * Parameters: int x -- Horizontal position of the block.
 *             int y -- Vertical position of the block.
 *             int block -- Piece to move.
 *             int rotation -- 1 of the 4 rotated pieces.
 *
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: True if possible otherwise fale.
 */

bool Board::isMvmntPoss(int x, int y, int block, int rotation) {
    for(int i1 = x, i2 = 0; i1 < x + PIECE_MATRIX; i1++, i2++)
    {
        for(int j1 = y, j2 = 0; j1 < y + PIECE_MATRIX; j1++, j2++)
        {
            /* Check if x & y are past the borders */
            if(i1 < 0 || i1 > (WIDTH - 1) || j1 > (HEIGHT - 1))
            {
                if(bPiece -> getBlockType(block, rotation, j2, i2) != 0)
                    return 0;
            }

            /* Check if collision w/another placed piece */
            if(j1 >= 0)
            {
                if((bPiece -> getBlockType(block, rotation, j2, i2) != 0) 
					&& (!isBlockEmpty(i1, j1)))
                    return false;
            }
        }
    }
    
    /* No collision */
    return true;
}
