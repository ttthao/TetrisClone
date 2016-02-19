#ifndef drawTetris_H
#define drawTetris_H

#include "SDL.h"
#include "Board.h"

/* Color definitions */
enum color { BLACK, GREY, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, COLOR_MAX };

class drawTetris
{
public:

	/* Ctor */
	drawTetris();

	/* Intializes the SDL functionalities */
	bool init();
	
	/* Shuts down all SDL functionalities */
	void close();

	/* Draws a colored block */
	void drawFilledRect(int x, int y, int width, int height, enum color type);
	
	/* Gets the screen height */
	int getScrnHt();

	/* Polls an event */
	int pollEvent();

	/* Waits for a key press */
	int getKey();

	/* Updates the rendered window */
	void updateScrn();

	/* Clears the widow*/
	void clearScrn();

};

#endif /* DRAWTETRIS_H */
