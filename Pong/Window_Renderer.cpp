#include "Window_Renderer.hpp"



Window_Renderer::Window_Renderer( SDL_Renderer * renderer, int procnum )
{
    Renderer = renderer ;
    ProcNum = procnum ;
    Color.r = Color.g = Color.b = WHITE ;
    Font = TTF_OpenFont( "/Library/Fonts/Arial.ttf" , FONT_SIZE ) ;
}

void Window_Renderer::Paint_Window()
{
    SDL_SetRenderDrawColor( Renderer , BLACK , BLACK , BLACK , BLACK ) ;
    SDL_RenderClear( Renderer ) ;
}

void Window_Renderer::Draw_Boards( int BoardYPos )
{
    SDL_SetRenderDrawColor( Renderer , WHITE , WHITE , WHITE , WHITE ) ;
    for ( int i = 0 ; i < BOARD_THICKNESS ; i++ )
        SDL_RenderDrawLine( Renderer , (50+(525*(ProcNum-1)))+i , BoardYPos , (50+(525*(ProcNum-1)))+i, BoardYPos+100 ) ;
}

void Window_Renderer::Draw_Ball( int x, int y )
{
    Ball.w = BALL_WIDTH ;
    Ball.h = BALL_HEIGHT ; 
    Ball.x = x ; Ball.y = y ;
    Texture = IMG_LoadTexture(Renderer, "../Assets/Ball.png");
    SDL_RenderCopy(Renderer, Texture, NULL, &Ball ) ;
}

void Window_Renderer::Write_Scores( int Score )
{
    Surface = TTF_RenderText_Solid(Font, (std::to_string(Score)).c_str(), Color) ;
    Texture = SDL_CreateTextureFromSurface( Renderer, Surface ) ;
    Text.x = 550-((ProcNum-1)*500) ; Text.y = 25 ; Text.w = 25 ; Text.h = 65 ;
    SDL_RenderCopy(Renderer, Texture, NULL, &Text) ;
    SDL_RenderPresent( Renderer ) ;
}

void Window_Renderer::Write_Word(std::string Word)
{
    Surface = TTF_RenderText_Solid(Font, Word.c_str(), Color) ;
    Texture = SDL_CreateTextureFromSurface( Renderer, Surface ) ;
    Text.x = 430+((ProcNum-1)*20)-((ProcNum-1)*430) ;
    Text.y = 170 ;  Text.w = 200 ; Text.h = 100 ;
    SDL_RenderCopy(Renderer, Texture, NULL, &Text) ;
    SDL_RenderPresent( Renderer ) ;
}

Window_Renderer::~Window_Renderer(){}
