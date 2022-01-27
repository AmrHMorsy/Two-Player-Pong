#include "Includes.hpp"




class Window_Renderer
{
    
private:
    
    int ProcNum ;
    TTF_Font * Font ;
    SDL_Color Color ;
    SDL_Surface * Surface ;
    SDL_Texture * Texture ;
    SDL_Rect Text , Ball ; 
    SDL_Renderer * Renderer ;
    
public:
    
    Window_Renderer( SDL_Renderer * renderer, int procnum ) ;
    void Paint_Window() ;
    void Draw_Boards( int BoardYPos ) ;
    void Draw_Ball( int CenterX, int CenterY ) ;
    void Write_Scores( int Score ) ;
    void Write_Word( std::string Word ) ; 
    ~Window_Renderer() ;
    
} ;
