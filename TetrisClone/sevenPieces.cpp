#include "sevenPieces.h"
/*
* Filename: Blocks.c
* Author: Tommy Truong
* Description: Gets a block w/a specific rotation.
* Date: 06/17/2015
*/

/* The sizes of the multiD ary that holds every piece & their rotations */
static const int TYPES = 7, /* The different types of falling pieces */
				 ROTATIONS = 4, /* The # of variations of a piece */
				 WIDTH = 5, /* The width of the matrix holding the piece */
				 HEIGHT = 5,/* The height of the matrix holding the piece */
				 XY = 2;	/* The X & Y offset to center the piece */

/* The 7 Pieces are represented by a 5x5 matrix */
/* Each iteration are clockwise rotations */
char piece[TYPES][ROTATIONS][WIDTH][HEIGHT] =
{
	/* 1 - S Piece */
	{
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 1, 2, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 1, 2, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 2, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 2, 1, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		}
	}, /* End of S Piece */

	/* 2 - Z Piece  */
	{
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 2, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 2, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 2, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 2, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		}
	}, /* End of Z Piece */

	/* 3 - L Piece */
	{
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 2, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 2, 1, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 2, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 1, 2, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		}
	}, /* End of L Piece */

	/* 4 - Inverted-L Piece */
	{
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 2, 0, 0 },
			{ 0, 1, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 1, 2, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 2, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 2, 1, 0 },
			{ 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		}
	}, /* End of Inverted-L Piece */

	/* 5 - Bar Piece */
	{
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 2, 1, 1 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 2, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 1, 1, 2, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 2, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		}
	}, /* End of Bar Piece */

	/* 6 - Square Piece */
	{
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 2, 1, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 2, 1, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 2, 1, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 2, 1, 0 },
			{ 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0 }
		}
	}, /* End of Square Piece */

	/* 7 - T Piece */
	{
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 1, 2, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 2, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},	
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 1, 2, 1, 0 },
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 2, 1, 0 },
			{ 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 0 }
		}
	}
};

/* Offsets for each Pieces' rotations */
int fourRotations[TYPES][ROTATIONS][XY] =
{
	/* 1 - S Piece */
	{
		{ -2, -3 },
		{ -2, -2 },
		{ -2, -3 },
		{ -2, -3 }
	},

	/* 2 - Z Piece */
	{
		{ -2, -3 },
		{ -2, -3 },
		{ -2, -3 },
		{ -2, -2 }
	},

	/* 3 - L Piece */
	{
		{ -2, -3 },
		{ -2, -3 },
		{ -2, -3 },
		{ -2, -2 }
	},

	/* 4 - Inverted-L Piece */
	{
		{ -2, -3 },
		{ -2, -2 },
		{ -2, -3 },
		{ -2, -3 }
	},

	/* 5 - Bar Piece */
	{
		{ -2, -2 },
		{ -2, -4 },
		{ -2, -2 },
		{ -2, -2 }
	},

	/* 6 - Square Piece */
	{
		{ -2, -3 },
		{ -2, -3 },
		{ -2, -3 },
		{ -2, -3 }
	},

	/* 7 - T Piece */
	{
		{ -2, -2 },
		{ -2, -3 },
		{ -2, -3 },
		{ -2, -3 }
	}
};

/*
 * Function name: getABlock 
 * Function prototype: int getABlock(int type, int rotation, int x, int y);
 *
 * Description: Gets the type of a block from a piece. 
 *				0 represents no block, 1 represents a normal block 
 *				and 2 represents a pivot block.
 *
 * Parameters: int type -- The type of block.
 *             int rotation -- The rotation of the selected block.
 *             int x -- Horizontal position in blocks
 *             int y -- Vertical position in blocks
 *
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

int sevenPieces::getBlockType(int type, int rotation, int x, int y) {
    
    return piece[type][rotation][x][y];
}

/*
 * Function name: getStartX
 * Function prototype: int getStartX(int type, int rotation);
 *
 * Description: Gets the horizontal offset of the block to center the block.
 *
 * Parameters: int type -- The type of block.
 *             int rotation -- The rotation of the selected block.
 *
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

int sevenPieces::getStartX(int type, int rotation) {

	/* Last element is 0 to isolate the X-coordinte */
    return fourRotations[type][rotation][0];
}

/*
 * Function name: getStartY
 * Function prototype: int getStartY(int type, int rotation);
 *
 * Description: Gets the vertical offset of the block to center the block.
 *
 * Parameters: int type -- The type of block.
 *             int rotation -- The rotation of the selected block.
 *
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

int sevenPieces::getStartY(int type, int rotation) {
	
	/* Last element is 1 to isolate the Y-coordinate */
    return fourRotations[type][rotation][1];
}
