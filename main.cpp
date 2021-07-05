/*
    <<<Developed by Regson Jaques>>>
    https://www.youtube.com/c/RegsonJaquesMA
    https://github.com/tictackode
    https://twitter.com/regsonj
*/

#include <time.h>
#include "MapObject.h"

unsigned short SCREEN_X=BLOCK_SIDE_SIZE * NUMBER_OF_BLOCKS;
unsigned short SCREEN_Y=BLOCK_SIDE_SIZE * NUMBER_OF_BLOCKS;

BITMAP* buffer;

void init();
void deinit();

void init() 
{
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_X, SCREEN_Y, 0, 0);
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

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}

void initImages()
{
     buffer=create_bitmap(SCREEN_X,SCREEN_Y);
     
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

void printPaneltoBuffer()
{
    //imprime informações do painel lateral - Print information
    textprintf_ex(buffer, font, 0,0, makecol(0, 0, 255),-1,"Move player: W,A,S,D or arrow keys");
    textprintf_ex(buffer, font, 0,10, makecol(0, 0, 255),-1,"Caught wooden sticks: %hu",player1.colided);
}

void drawScreen()
{
    //draws the grass field 
    for(int i=0;i<NUMBER_OF_BLOCKS;i++)
    {
         for(int j=0;j<NUMBER_OF_BLOCKS;j++)
         {
                blit(grass.image, buffer, 0, 0, (i * BLOCK_SIDE_SIZE), (j * BLOCK_SIDE_SIZE), (i * BLOCK_SIDE_SIZE) + BLOCK_SIDE_SIZE, (j * BLOCK_SIDE_SIZE) + BLOCK_SIDE_SIZE);
         }  
    }
    
    //Player 1 label  
    textprintf_ex(buffer, font, (player1.x * BLOCK_SIDE_SIZE),(player1.y * BLOCK_SIDE_SIZE-20), makecol(0, 0,255 ),-1,"Player 1");
          
    //Printing the player on screen
    blit(player1.image, buffer, 0, 0, (player1.x * BLOCK_SIDE_SIZE), (player1.y * BLOCK_SIDE_SIZE), (player1.x * BLOCK_SIDE_SIZE) + BLOCK_SIDE_SIZE, (player1.y * BLOCK_SIDE_SIZE) + BLOCK_SIDE_SIZE);
    //stretch_blit(player1.image, buffer, 0, 0, 40, 40, player1.x * BLOCK_SIDE_SIZE, player1.y * BLOCK_SIDE_SIZE, (player1.x * BLOCK_SIDE_SIZE)+BLOCK_SIDE_SIZE, (player1.y * BLOCK_SIDE_SIZE)+BLOCK_SIDE_SIZE);
    
    //printing the wodden stick
    blit(wooden_stick.image, buffer, 0, 0, (wooden_stick.x * BLOCK_SIDE_SIZE), (wooden_stick.y * BLOCK_SIDE_SIZE), (wooden_stick.x * BLOCK_SIDE_SIZE) + BLOCK_SIDE_SIZE, (wooden_stick.y * BLOCK_SIDE_SIZE) + BLOCK_SIDE_SIZE);
    
    //print game information on screen
    printPaneltoBuffer();  
    
    //draws buffer on the screen
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_X, SCREEN_Y);
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
        if(player1.y<NUMBER_OF_BLOCKS-1)
        {
             player1.y++;  
        }
    }
    else if(key[KEY_D]||key[KEY_RIGHT]) 
    {
        if(player1.x<NUMBER_OF_BLOCKS-1)
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
        BLOCK_SIDE_SIZE++;
        SCREEN_X = BLOCK_SIDE_SIZE * NUMBER_OF_BLOCKS;
        SCREEN_Y = BLOCK_SIDE_SIZE * NUMBER_OF_BLOCKS;
        buffer = create_bitmap(SCREEN_X,SCREEN_Y);
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_X, SCREEN_Y, 0, 0);
        
        drawScreen();

    }
    else if(key[KEY_X])
    { 
         //decrease zoom (experimental)
         BLOCK_SIDE_SIZE--;
         SCREEN_X = BLOCK_SIDE_SIZE * NUMBER_OF_BLOCKS;
         SCREEN_Y = BLOCK_SIDE_SIZE * NUMBER_OF_BLOCKS;
         buffer = create_bitmap(SCREEN_X, SCREEN_Y);
         set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_X, SCREEN_Y, 0, 0);

         drawScreen();

    }
     else if(key[KEY_N])
    {
          //increase map size
          NUMBER_OF_BLOCKS++;
          SCREEN_X = BLOCK_SIDE_SIZE * NUMBER_OF_BLOCKS;
          SCREEN_Y = BLOCK_SIDE_SIZE * NUMBER_OF_BLOCKS;
          buffer = create_bitmap(SCREEN_X, SCREEN_Y);
          set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_X, SCREEN_Y, 0, 0);
          
          player1.x=1;
          player1.y=1;
          initStickPosition();
          drawScreen();  
          
    
    }
    else if(key[KEY_M])
    {
         //reduce map size
         NUMBER_OF_BLOCKS--;
         SCREEN_X = BLOCK_SIDE_SIZE * NUMBER_OF_BLOCKS;
         SCREEN_Y = BLOCK_SIDE_SIZE * NUMBER_OF_BLOCKS;
         buffer = create_bitmap(SCREEN_X, SCREEN_Y);
         set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_X, SCREEN_Y, 0, 0);

         player1.x=1;
         player1.y=1;
         initStickPosition();
         drawScreen();
         
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
    init();
    	
    //sets the size of the console window
    set_window_title("C language + Allegro4 Picking Sticks style game");
    
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
        
        drawScreen();
        controls();
        player1.checkCollision(wooden_stick);

    }

    deinit();
    return 0;
}
END_OF_MAIN();


 
