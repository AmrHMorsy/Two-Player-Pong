#include "Events_Manager.hpp"




class System_Manager
{
    
private:
    
    Events_Manager * V ;
    SDL_Window * Window ;
    SDL_Renderer * Renderer ;
    Mix_Chunk * SoundEffect ;
    Mix_Music * BckgrndMusic ;
    int WindowPosX, WindowPosY , ProcNum, fd1, fd2, fd3, fd4 ;
    
public:
    
    System_Manager( int windowposX, int windowposY, int procnum ) ;
    void Initialize_SDL() ;
    void Initialize_TTF() ;
    void Create_Window() ;
    void Create_Renderer() ;
    void Launch_Audio() ;
    void Load_Background_Music() ;
    void Load_Sound_Effect() ;
    void Open_Pipes() ;
    ~System_Manager() ;
    
} ;
