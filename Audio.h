/*
    <<<Developed by Regson Jaques>>>
    https://www.youtube.com/c/RegsonJaquesMA
    https://github.com/tictackode
    https://twitter.com/regsonj
*/

class Audio
{
      
      public:
      SAMPLE* hit;
      SAMPLE* intro;
      
      Audio()
      {
          this->hit = load_sample("sound/phase2.wav");
          this->intro = load_sample("sound/chime.wav");
             
      }
      ~Audio()
      {
          delete(this->hit);
          delete(this->intro);
      }
      
      void playSample(SAMPLE* sound)
      { 
          play_sample(sound, 255, 128, 1000, 0);
      }
    
}gameAudio;
