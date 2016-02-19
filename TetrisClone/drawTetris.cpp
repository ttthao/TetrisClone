/*
* Filename: drawTetris.cpp
* Author: Tommy Truong
* Description: Handles rendering and drawing through SDL2.0.
* Date: 06/23/2015
*/

#include "drawTetris.h"
#include <stdio.h>
#include <string>
#include <cmath>


/* The window that will be rendered */
SDL_Window* gWindow = NULL;

/* The window renderer */
SDL_Renderer* gRenderer = NULL;


/*
* Constructor name: drawTetris
* Constructor prototype: drawTetris();
*
* Description: drawTetris constructor.
*
* Parameters: None. 
* Side Effects: None.
* Error Conditions: None.
* Return Value: None.
*/

drawTetris::drawTetris()
{
	if(!init())
		printf("Error in SDL!\n");
}

/*
 * Function name: init
 * Function prototype: bool init();
 *
 * Description: Initializes SDL rendering.
 *
 * Parameters: None.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: True if successful otherwise false.
 */

bool drawTetris::init()
{
	/* Initialization flag */
	bool success = true;

	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		/* Set texture filtering to linear */
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"))
			printf("Warning: Linear texture filtering not enabled!");

		/* Create window */
		gWindow = SDL_CreateWindow("SDL Tutorial", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			/* Create renderer for window */
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
		}
	}
	return success;
}

/*
 * Function name: close
 * Function prototype: void close();
 *
 * Description: Shuts down SDL rendering.
 *
 * Parameters: None.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

void drawTetris::close()
{
	/* Destroy window */
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	/* Quit SDL subsystems */
	SDL_Quit();
}

/*
 * Function name: clearScreen
 * Function prototype: void clearScreen();
 *
 * Description: Clears the window by setting it black.
 *
 * Parameters: None.
 * Side Effects: None.
 * Error Conditions: None.
 * Return Value: None.
 */

void drawTetris::clearScrn() 
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gRenderer);
}


/*
* Function name: drawFilledRect
* Function prototype: void drawFilledRect;
*
* Description: Draws a colored block.
*
* Parameters: None.
* Side Effects: None.
* Error Conditions: None.
* Return Value: None.
*/

void drawTetris::drawFilledRect(int x, int y, int width, int height, enum color type)
{
	/* Set the (x,y) and dimensions of the rectangle */
	SDL_Rect fillRect = { x, y, width, height };

	/* Determine the color of the block */
	switch (type)
	{
		case BLUE:
			SDL_SetRenderDrawColor(gRenderer, 0x33, 0x66, 0x99, 0xFF);
			break;

		case GREEN:
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x33, 0x00, 0xFF);
			break;

		case RED:
			SDL_SetRenderDrawColor(gRenderer, 0x80, 0x00, 0x00, 0xFF);
			break;

		case GREY:
			SDL_SetRenderDrawColor(gRenderer, 0x5A, 0x5A, 0x5A, 0xFF);
			break;
	}

	/* Render the block onto the window */
	SDL_RenderFillRect(gRenderer, &fillRect);
}


/*
* Function name: getScrnHt
* Function prototype: void getScrnHt();
*
* Description: Retrieves the screen's height.
*
* Parameters: None.
* Side Effects: None.
* Error Conditions: None.
* Return Value: The screen's height.
*/

int drawTetris::getScrnHt()
{
	return SCREEN_HEIGHT;
}


/*
* Function name: updateScrn
* Function prototype: void updateScrn;
*
* Description: Retrieves the screen's height.
*
* Parameters: None.
* Side Effects: None.
* Error Conditions: None.
* Return Value: The screen's height.
*/

void drawTetris::updateScrn()
{
	SDL_RenderPresent(gRenderer);
}

/*
* Function name: pollEvent
* Function prototype: int pollEvent();
*
* Description: Retrievs an event.
*
* Parameters: None.
* Side Effects: None.
* Error Conditions: None.
* Return Value: An SDL event.
*/

int drawTetris::pollEvent()
{
	SDL_Event event;

	while(SDL_PollEvent(&event)) 
	{
		switch (event.type) 
		{
			case SDL_KEYDOWN:
				return event.key.keysym.sym;
			case SDL_QUIT:
				return 0;
		}
	}
	return -1;
}

/*
* Function name: getKey
* Function prototype: int getKey();
*
* Description: Waits indefinitely until key or quit pressed.
*
* Parameters: None.
* Side Effects: None.
* Error Conditions: None.
* Return Value: The key from the event.
*/

int drawTetris::getKey()
{
	SDL_Event event;

	while(true)
	{
	  SDL_WaitEvent(&event);

	  if (event.type == SDL_KEYDOWN)
		  break;

      if (event.type == SDL_QUIT)
		  exit(3);
	};
	return event.key.keysym.sym;
}
