#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "sevenPieces.h"
#include "drawTetris.h"
#include <time.h>

#define FALL_DELAY 1000	/* Delay in millisecnds for falling piece to move down once*/
#define MAX_PIECES 6	/* The largest index in the pieces matrice */ 
#define MAX_ROTATIONS 3 /* The largest index in the rotations matrice */
#define NEXT_PIECE_X 15 /* The x-position of the image of the next piece */
#define NEXT_PIECE_Y 5  /* The y-position of the image of the next piece */

class Game
{
    public:
        Game (Board *cBoard, sevenPieces *cPiece, drawTetris *cDrawTetris, int cScrnHt);

        void drawScene();
        void createNewPiece();

        int xCurrent, yCurrent,				/* Centered position of the falling piece */
            pieceType, rotationType;		/* Type & rotation of current piece */

    private:

        int gScrnHt,                /* Screen height in pixels */
            nextX, nextY,			/* Centered position of the next piece */
            nextPiece, nextRotation;/* Type & rotation of the next piece */

        Board *gBoard;
        sevenPieces *gPiece;
        drawTetris *gDrawTetris;

        int getRand(int a, int b);

        void startGame();
        void drawPiece(int x, int y, int pieceType, int rotationType);
        void drawBoard();
};

#endif /* GAME_H */
