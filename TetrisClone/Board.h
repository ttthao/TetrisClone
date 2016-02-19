#ifndef BOARD_H
#define BOARD_H

#include "sevenPieces.h"

#define HEIGHT 20 /* Board height in blocks */
#define WIDTH 10 /* Board width in blocks */
#define BORDER_WIDTH 6 /* Width of 2 lines that contain the board */
#define	BLOCK_WH 15 /* A single block's width & height */
#define SCREEN_WIDTH 640 /* The window's width */
#define SCREEN_HEIGHT 480 /* The window's height */
#define PIECE_AREA 16 /* Width*height (Area) of each block in a piece */
#define PIECE_MATRIX 5 /* # of horizontal & vertical blocks of the matrix */
#define MIN_VERT_MARGIN 20 /* Min vertical margin for the board limit */
#define MIN_HORI_MARGIN 20 /* Min horizontal margin for the board limit */
#define BOARD_POS 320 /* Center of board between the 2 borders */

class Board
{
    public:
        /* Board Ctor */
        Board(sevenPieces *cPiece, int cScrnHt);
        
        /* Translates the block (x,y) positions into pixels */
        int getXPosPixels(int x);
        int getYPosPixels(int y);

        /* Determines if piece can be moved/rotated */
        bool isMvmntPoss(int x, int y, int block, int rotation);

        /* Determines if block is free or filled by a block from a piece */
        bool isBlockEmpty(int x, int y);

        /* Sets a piece on the board */
        void setPiece(int x, int y, int block, int rotation);

        /* Checks every line if any deletions are required */
        void deletePossLines();

        /* Ends game if top line has a filled block */
        bool gameOver();

    private:
        enum {EMPTY, FILLED};			/* Constants for empty/filled blocks */
        
		int bBoard[WIDTH][HEIGHT];		/* The actual board */

		sevenPieces *bPiece;			/* The actual piece selected by the ctor */

		int bScrnHt;					/* The actual screen height specified by the ctor */
        
        void initBoard();				/* Initialize the board */

        void deleteLine(int y);			/* Deletes a line */
};

#endif /* BOARD_H */


