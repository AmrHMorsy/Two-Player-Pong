#include "Window_Renderer.hpp"




class Events_Manager
{
    
private:
    
    char Buffer[100] ;
    SDL_Event Event ;
    Window_Renderer * W ;
    SDL_Renderer * Renderer ;
    bool Quit, Left, Right, Pause, GameStarted, GameEnded ;
    double Center, DistanceFromBoardCenter, NormalizedY ;
    std::string Msg, MsgRcv, boardYpos, ballYpos, score, BallinProc, bounceAngle ; 
    int ProcNum , fd1, fd2 , fd3, fd4, NumCharRead, BoardYPos, BallXPos, BallYPos, Score, BounceAngle, Cos, Sin, BallInProc ;
    
public:
    
    Events_Manager( SDL_Renderer * renderer, int procnum, int f_d1, int f_d2, int f_d3, int f_d4 ) ;
    void Manage_Events() ;
    void Start_Game() ;
    bool IsGameOver() ;
    void End_Game() ;
    void Update_Ball_Position() ;
    void Send_Message( int fd, std::string Msg ) ;
    void Recieve_Message() ;
    void Update_Gameplay() ;
    std::string Get_KeyPrssd() ; 
    ~Events_Manager() ;
} ;
