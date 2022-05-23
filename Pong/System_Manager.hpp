#include "Events_Manager.hpp"




class System_Manager
{
    
private:
    
    char Buffer[100] ;
    Events_Manager * V ;
    SDL_Window * Window ;
    SDL_Renderer * Renderer ;
    Mix_Chunk * SoundEffect ;
    int WindowPosX, WindowPosY , ProcNum, fd1, fd2, fd3, fd4, NumCharRead ;
    
public:
    
    System_Manager( int windowposX, int windowposY, int procnum ) ;
    void Open_Pipes() ;
    void Initialize_SDL() ;
    void Initialize_TTF() ;
    void Create_Window() ;
    void Create_Renderer() ;
    void Launch_Audio() ;
    void Load_Sound_Effect() ;
    void Send_Message( int fd, std::string Msg ) ;
    std::string Recieve_Message( int fd ) ;
    ~System_Manager() ;
    
} ;
