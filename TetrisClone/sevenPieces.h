 /* 
  * Filename: Blocks.h
  * Author: Tommy Truong
  * Description: Selects a block.
  */
  
#ifndef SEVENPIECES_H
#define SEVENPIECES_H

  class sevenPieces
  {
      public:
        
        /* Returns the type of block in a piece */
        int getBlockType(int type, int rotation, int x, int y);

        /* Gets the (x,y) offsets to center the piece */
        int getStartX(int type, int rotation);
        int getStartY(int type, int rotation);
  };

#endif /* SEVENPIECES_H */
