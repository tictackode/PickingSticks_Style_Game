/*
    <<<Developed by Regson Jaques>>>
    https://www.youtube.com/c/RegsonJaquesMA
    https://github.com/tictackode
    https://twitter.com/regsonj
*/

#include <allegro.h>
#include "Audio.h"

class MapObject
{
    public:  
    unsigned short x;
    unsigned short y;
    unsigned short colided;
    BITMAP* image;
    
    MapObject()
    {
         this->x=0;
         this->x=0;
         this->colided=0;
         this->image;
                
    }
    ~MapObject()
    {
        destroy_bitmap(this->image);
    
    }
    
    void checkCollision(MapObject &wodden_stick)
    {
  
        if((this->x==wodden_stick.x)&&(this->y==wodden_stick.y))
        {
            wodden_stick.x=rand()%NUMBER_OF_BLOCKS;
            wodden_stick.y=rand()%NUMBER_OF_BLOCKS;

            this->colided++;
            
            gameAudio.playSample(gameAudio.hit);
        }
        
    }
    
    void setImage(BITMAP* image)
    {
         this->image=image;
    }
    
    void loadImage(const char* image_path)
    {

        this->image=create_bitmap(BLOCK_SIDE_SIZE,BLOCK_SIDE_SIZE);
        this->image=load_bitmap(image_path,0);
        
        
        if(!image)
        {
            key[KEY_ESC]=false;
            
            while(!key[KEY_ESC])
            {
                textprintf_ex(screen, font, 20, 20, makecol(255, 0, 0),-1,"error: couldn't find image ESC to exit : ");
            }
            
            readkey();
            
            exit(1);
        }
     }
         
}player1,wooden_stick,grass;
