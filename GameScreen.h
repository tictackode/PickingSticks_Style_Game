/*
    <<<Developed by Regson Jaques>>>
    https://www.youtube.com/c/RegsonJaquesMA
    https://github.com/tictackode
    https://twitter.com/regsonj
*/

#include "Glow.h"

class GameScreen
{
      public:
      
      unsigned short SCREEN_X;
      unsigned short SCREEN_Y;
      unsigned short NUMBER_OF_BLOCKS;
      unsigned short BLOCK_SIDE_SIZE;
      unsigned long int gameCicles;
      
      BITMAP* buffer;
      
      GameScreen()
      {
          this->NUMBER_OF_BLOCKS=20;
          this->BLOCK_SIDE_SIZE=40;
          this->SCREEN_X=BLOCK_SIDE_SIZE * NUMBER_OF_BLOCKS;
          this->SCREEN_Y=BLOCK_SIDE_SIZE * NUMBER_OF_BLOCKS;  
          this->gameCicles=0;     
                  
      }
      ~GameScreen()
      {
                   
      }
      
      
      void init() 
      {
	      int depth, res;
	      allegro_init();
	      depth = desktop_color_depth();
	      if (depth == 0) depth = 32;
	      set_color_depth(depth);
	      res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, this->SCREEN_X, this->SCREEN_Y, 0, 0);
	      if (res != 0) 
          {
		      allegro_message(allegro_error);
		          exit(-1);
          }

	      install_keyboard();
	      install_mouse();
	      install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT,NULL);
	      install_timer();
       }
       void deinit() 
       {
           clear_keybuf();
	           /* add other deinitializations here */
       }
       
       void printPaneltoBuffer()
       {
           //imprime informações do painel lateral - Print information
           textprintf_ex(this->buffer, font, 0,0, makecol(0, 0, 255),-1,"Move player: W,A,S,D or arrow keys");
           textprintf_ex(this->buffer, font, 0,10, makecol(0, 0, 255),-1,"Caught wooden sticks: %hu",player1.colided);
       }

       void drawScreen()
       {
            //update glowing color every 10 frames
            this->gameCicles++;
            if(this->gameCicles%3==0)
            {
                glow.glowingColor();
            }
            
            
           //draws the grass field 
           for(int i=0;i<this->NUMBER_OF_BLOCKS;i++)
           {
               for(int j=0;j<this->NUMBER_OF_BLOCKS;j++)
               {
                   blit(grass.image, this->buffer, 0, 0, (i * this->BLOCK_SIDE_SIZE), (j * this->BLOCK_SIDE_SIZE), (i * this->BLOCK_SIDE_SIZE) + this->BLOCK_SIDE_SIZE, (j * this->BLOCK_SIDE_SIZE) + this->BLOCK_SIDE_SIZE);
               }  
           }
    
           //Player 1 label  
           textprintf_ex(this->buffer, font, (player1.x * this->BLOCK_SIDE_SIZE),(player1.y * this->BLOCK_SIDE_SIZE-20), makecol(glow.fontaux, glow.fontaux,glow.fontaux ),-1,"Player 1");
          
           //Printing the player on screen
           blit(player1.image, this->buffer, 0, 0, (player1.x * this->BLOCK_SIDE_SIZE), (player1.y * this->BLOCK_SIDE_SIZE), (player1.x * this->BLOCK_SIDE_SIZE) + this->BLOCK_SIDE_SIZE, (player1.y * this->BLOCK_SIDE_SIZE) + this->BLOCK_SIDE_SIZE);
           //stretch_blit(player1.image, buffer, 0, 0, 40, 40, player1.x * BLOCK_SIDE_SIZE, player1.y * BLOCK_SIDE_SIZE, (player1.x * BLOCK_SIDE_SIZE)+BLOCK_SIDE_SIZE, (player1.y * BLOCK_SIDE_SIZE)+BLOCK_SIDE_SIZE);
    
           //printing the wodden stick
           blit(wooden_stick.image, this->buffer, 0, 0, (wooden_stick.x * this->BLOCK_SIDE_SIZE), (wooden_stick.y * this->BLOCK_SIDE_SIZE), (wooden_stick.x * this->BLOCK_SIDE_SIZE) + this->BLOCK_SIDE_SIZE, (wooden_stick.y * this->BLOCK_SIDE_SIZE) + this->BLOCK_SIDE_SIZE);
    
           //print game information on screen
           this->printPaneltoBuffer();  
    
           //draws buffer on the screen
           blit(this->buffer, screen, 0, 0, 0, 0, this->SCREEN_X, this->SCREEN_Y);
       }
     
      
}gameScreen;
