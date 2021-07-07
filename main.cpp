/*
    <<<Developed by Regson Jaques>>>
    https://www.youtube.com/c/RegsonJaquesMA
    https://github.com/tictackode
    https://twitter.com/regsonj
*/

#include <time.h>
#include "MapObject.h"
#include "GameScreen.h"



void initImages()
{
     gameScreen.buffer=create_bitmap(gameScreen.SCREEN_X,gameScreen.SCREEN_Y);
     
     player1.loadImage("images/player.bmp");
     grass.loadImage("images/grass.bmp");
     wooden_stick.loadImage("images/stick.bmp");   
}

void initStickPosition()
{
     //set the random location of the wooden stick                   
     wooden_stick.x=rand()%NUMBER_OF_BLOCKS;
     wooden_stick.y=rand()%NUMBER_OF_BLOCKS;
}


void controls()
{

    if(key[KEY_A]||key[KEY_LEFT]) 
    { 
        if(player1.x>0)
        {
            player1.x--;  
        }
    }
    else if(key[KEY_S]||key[KEY_DOWN]) 
    {
        if(player1.y<gameScreen.NUMBER_OF_BLOCKS-1)
        {
             player1.y++;  
        }
    }
    else if(key[KEY_D]||key[KEY_RIGHT]) 
    {
        if(player1.x<gameScreen.NUMBER_OF_BLOCKS-1)
        {
            player1.x++;
        }
    }
    else if(key[KEY_W]||key[KEY_UP]) 
    {
        if(player1.y>0)
        {
            player1.y--;  
        }
    }
    else if(key[KEY_Z])
    {
        //increase zoom (experimental)
        gameScreen.BLOCK_SIDE_SIZE++;
        gameScreen.SCREEN_X = gameScreen.BLOCK_SIDE_SIZE * gameScreen.NUMBER_OF_BLOCKS;
        gameScreen.SCREEN_Y = gameScreen.BLOCK_SIDE_SIZE * gameScreen.NUMBER_OF_BLOCKS;
        gameScreen.buffer = create_bitmap(gameScreen.SCREEN_X,gameScreen.SCREEN_Y);
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, gameScreen.SCREEN_X, gameScreen.SCREEN_Y, 0, 0);
        
        gameScreen.drawScreen();

    }
    else if(key[KEY_X])
    { 
         //decrease zoom (experimental)
         gameScreen.BLOCK_SIDE_SIZE--;
         gameScreen.SCREEN_X = gameScreen.BLOCK_SIDE_SIZE * gameScreen.NUMBER_OF_BLOCKS;
         gameScreen.SCREEN_Y = gameScreen.BLOCK_SIDE_SIZE * gameScreen.NUMBER_OF_BLOCKS;
         gameScreen.buffer = create_bitmap(gameScreen.SCREEN_X, gameScreen.SCREEN_Y);
         set_gfx_mode(GFX_AUTODETECT_WINDOWED, gameScreen.SCREEN_X, gameScreen.SCREEN_Y, 0, 0);

         gameScreen.drawScreen();

    }
     else if(key[KEY_N])
    {
          //increase map size
          gameScreen.NUMBER_OF_BLOCKS++;
          gameScreen.SCREEN_X = gameScreen.BLOCK_SIDE_SIZE * gameScreen.NUMBER_OF_BLOCKS;
          gameScreen.SCREEN_Y = gameScreen.BLOCK_SIDE_SIZE * gameScreen.NUMBER_OF_BLOCKS;
          gameScreen.buffer = create_bitmap(gameScreen.SCREEN_X, gameScreen.SCREEN_Y);
          set_gfx_mode(GFX_AUTODETECT_WINDOWED, gameScreen.SCREEN_X, gameScreen.SCREEN_Y, 0, 0);
          
          player1.x=1;
          player1.y=1;
          initStickPosition();
          gameScreen.drawScreen(); 
          
    
    }
    else if(key[KEY_M])
    {
         //reduce map size
         gameScreen.NUMBER_OF_BLOCKS--;
         gameScreen.SCREEN_X = gameScreen.BLOCK_SIDE_SIZE * gameScreen.NUMBER_OF_BLOCKS;
         gameScreen.SCREEN_Y = gameScreen.BLOCK_SIDE_SIZE * gameScreen.NUMBER_OF_BLOCKS;
         gameScreen.buffer = create_bitmap(gameScreen.SCREEN_X, gameScreen.SCREEN_Y);
         set_gfx_mode(GFX_AUTODETECT_WINDOWED, gameScreen.SCREEN_X, gameScreen.SCREEN_Y, 0, 0);

         player1.x=1;
         player1.y=1;
         initStickPosition();
         gameScreen.drawScreen();
         
    }
    
    key[KEY_A]=false;
    key[KEY_S]=false;
    key[KEY_D]=false;
    key[KEY_W]=false;
    key[KEY_LEFT]=false;
    key[KEY_DOWN]=false;
    key[KEY_RIGHT]=false;
    key[KEY_UP]=false;
    key[KEY_Z]=false;
    key[KEY_X]=false;
    key[KEY_N]=false;
    key[KEY_M]=false;
}

int main() 
{
	gameScreen.init();
    	
    //sets the size of the console window
    set_window_title("tictacShooter >>> an opensource spaceship shooter game");
    
    //to generate real random numbers
    srand(time(0));  
    
    //load images used in the game
    initImages();    
    
    //plays a sound in the begining of the game
    gameAudio.playSample(gameAudio.intro);
    
    //sets the first random position of the wooden stick
    initStickPosition();
    
	while (!key[KEY_ESC]) 
    {
        
        gameScreen.drawScreen();
        controls();
        player1.checkCollision(wooden_stick);

    }

	gameScreen.deinit();
	return 0;
}
END_OF_MAIN();


 
