#include "Game.h"
#include <Windows.h>

/* Implement a pause & a hold functionality */
 
/*
 * Filename: main.cpp
 * Author: Tommy Truong
 * Description: This function will drive the rest of the program. It will draw
 *              the board & pieces, and handle keyboard input. It keeps 
 *              track of the fall time to keep the pieces falling, and checks
 *              if a rotation/movement is possible. Lastly, it will check for
 *              game over if the top row has a single block.
 *
 * Start Date: 06/19/2015
 */

int main(int argc, char* args[])
{

	/* Instantiate SDL tools */
	drawTetris mainDrawTetris;

	/* Get the screen height */
	int mainScrnHt = mainDrawTetris.getScrnHt();
 
    /* Instantiate a piece */
    sevenPieces mainPiece;
 
    /* Instantiate a board */
    Board mainBoard (&mainPiece, mainScrnHt);
 
    /* Instantiate and initialize the game */
    Game mainGame (&mainBoard, &mainPiece, &mainDrawTetris, mainScrnHt);
 
    /* Get time before key check */
    unsigned long time1 = SDL_GetTicks();

	/* Stop flag */
	bool stop = false;

    /* Run game while ESC isn't pressed */
	while (!stop)
	{
        /***Draw the game***/

        /* Clear the screen */
		mainDrawTetris.clearScrn();

        /* Draw the board, pieces, and borders */
		mainGame.drawScene();
        
        /* Update the screen */
		mainDrawTetris.updateScrn();

        /* Keyboard input (Up, down, left, right or quit) */
		int mainKey = mainDrawTetris.pollEvent();

        /* Determine which direction was pressed */
		switch (mainKey)
		{
			/* If exited out, stop the game */
			case(0):
			{
				stop = true;
				break;
			}

			/* If ESC pressed, stop the game */
			case (SDLK_ESCAPE):
			{
				stop = true;
				break;
			}

            /* Right means +1 in x plane */
			case (SDLK_RIGHT): 
			{
				if (mainBoard.isMvmntPoss (mainGame.xCurrent + 1, mainGame.yCurrent, 
                            mainGame.pieceType, mainGame.rotationType))
					mainGame.xCurrent++;
					break;
			}

            /* Left means -1 in x plane */
			case (SDLK_LEFT): 
			{
				if (mainBoard.isMvmntPoss (mainGame.xCurrent - 1, mainGame.yCurrent, mainGame.pieceType, 
                            mainGame.rotationType))
					mainGame.xCurrent--;	
				break;
			}

            /* Down means +1 in the y plane (towards bottom) */
			case (SDLK_DOWN):
			{
				if (mainBoard.isMvmntPoss (mainGame.xCurrent, mainGame.yCurrent + 1, mainGame.pieceType,
                            mainGame.rotationType))
					mainGame.yCurrent++;	
				break;
			}

			/* Rotate clockwise (Iterate to next rotation) */
			case (SDLK_UP):
			{
				if (mainBoard.isMvmntPoss (mainGame.xCurrent, mainGame.yCurrent, mainGame.pieceType, 
                            (mainGame.rotationType + 1) % 4))
					mainGame.rotationType = (mainGame.rotationType + 1) % 4;

				break;
			}

			/* Rotate counterclockwise (Iterate to previous rotation) */
            /* XXX USEFUL ITERATION ALGORITHM HERE XXX */
			case (SDLK_z):
			{

				if (mainGame.rotationType != 0)
				{

					/* Rotate ctrclkwise for rotations 1/2/3 */
					if (mainBoard.isMvmntPoss (mainGame.xCurrent, mainGame.yCurrent, 
						mainGame.pieceType, (mainGame.rotationType - 1) % 4))
						mainGame.rotationType = (mainGame.rotationType - 1) % 4;
				}
				else
				{
					/* At 0th rotation type, set it to 4 to rotate ctrclkwise properly */
					/* This also checks if it can rotate along the walls */
					if (mainBoard.isMvmntPoss(mainGame.xCurrent, mainGame.yCurrent, 
						mainGame.pieceType, (mainGame.rotationType + 4) - 1) % 4)
						mainGame.rotationType = (((mainGame.rotationType + 4) - 1) % 4);
				}

				break;
			}

            /* Drop piece instantly */
			case (SDLK_SPACE):
			{
				/* Loop downards fall until bottom is hit */
				while (mainBoard.isMvmntPoss(mainGame.xCurrent, mainGame.yCurrent, 
                            mainGame.pieceType, mainGame.rotationType)) { 
                    mainGame.yCurrent++; 
                }
	
				/* Set the piece on the floor */
				mainBoard.setPiece (mainGame.xCurrent, mainGame.yCurrent - 1, 
                        mainGame.pieceType, mainGame.rotationType);
			
				/* Delete any lines */
				mainBoard.deletePossLines();

				if (mainBoard.gameOver())
				{
					mainDrawTetris.getKey();
					exit(0);
				}

				mainGame.createNewPiece();

				break;
			}
		}

        /* Check the elapsed time */
		unsigned long time2 = SDL_GetTicks();

		/* If change in time is more than delay time, shift piece downwards by one */
		if ((time2 - time1) > FALL_DELAY)
		{
			/* Check if piece can fall */
			if (mainBoard.isMvmntPoss (mainGame.xCurrent, mainGame.yCurrent + 1, 
                        mainGame.pieceType, mainGame.rotationType))
				mainGame.yCurrent++;
			else
			{
				/* Set piece at bottom if reached */
				mainBoard.setPiece (mainGame.xCurrent, mainGame.yCurrent, 
                        mainGame.pieceType, mainGame.rotationType);

				/* Check if any lines made after setting the piece */
				mainBoard.deletePossLines ();

				/* Check if piece set a block at the top line */
				if (mainBoard.gameOver())
				{
					mainDrawTetris.getKey();
					exit(0);
				}

				/* Generate next piece */
				mainGame.createNewPiece();
			}

			/* Start timer again */
			time1 = SDL_GetTicks();
		}
	}

	mainDrawTetris.close();

	return 0;
}
