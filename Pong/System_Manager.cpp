#include "System_Manager.hpp"



System_Manager::System_Manager( int windowposX, int windowposY, int procnum )
{
    WindowPosX = windowposX ;
    WindowPosY = windowposY ;
    ProcNum = procnum ;
    printf("\033[1;32mProcess %d Booted ✔\033[0m \n", ProcNum) ;
}

void System_Manager::Open_Pipes()
{
    if( ProcNum == 1 ){
        fd1 = open("Pipe1W.txt", O_RDWR);
        fd2 = open("Pipe1R.txt", O_RDONLY | O_CREAT) ;
        fd3 = open("Pipe3W.txt", O_RDWR ) ;
        fd4 = open("Pipe3R.txt", O_RDONLY | O_CREAT) ;
    }
    else{
        fd1 = open("Pipe2W.txt", O_RDWR);
        fd2 = open("Pipe2R.txt", O_RDONLY | O_CREAT) ;
        fd3 = open("Pipe3R.txt", O_RDWR ) ;
        fd4 = open("Pipe3W.txt", O_RDONLY | O_CREAT) ;
    }
    Initialize_SDL() ; 
}

void System_Manager::Initialize_SDL()
{
    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 ){
        printf("\033[1;31mProcess %d - Failure To Initialize SDL For X\033[0m \n", ProcNum ) ;
        Send_Message(fd1, "x") ;
    }
    else
        Initialize_TTF() ;
}

void System_Manager::Initialize_TTF()
{
    if( TTF_Init() != 0 ){
        printf("\033[1;31mProcess %d - Failure To Initialize TTF For X\033[0m \n", ProcNum ) ;
        Send_Message(fd1, "x") ;
    }
    else
        Create_Window() ;
}

void System_Manager::Create_Window()
{
    Window = SDL_CreateWindow( "Pong" ,WindowPosX ,WindowPosY ,WINDOW_LENGTH, WINDOW_WIDTH, 0) ;
    if( Window == NULL ){
        printf("\033[1;31mProcess %d - Failure To Create Window X\033[0m \n", ProcNum ) ;
        Send_Message(fd1, "x") ;
    }
    else
        Create_Renderer() ;
}

void System_Manager::Create_Renderer()
{
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if( Renderer == NULL ){
        printf("\033[1;31mProcess %d - Failure To Create Renderer X\033[0m \n", ProcNum) ;
        Send_Message(fd1, "x") ;
    }
    else
        Launch_Audio() ;
}

void System_Manager::Launch_Audio()
{
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == 0 )
        Load_Sound_Effect() ;
    else{
        printf("\033[1;31mProcess %d - Failure To Launch Audio System X\033[0m \n", ProcNum) ;
        Send_Message(fd1, "x") ;
    }
}

void System_Manager::Load_Sound_Effect()
{
    SoundEffect = Mix_LoadWAV( "../Assets/Tick.wav" ) ;
    
    if( SoundEffect != NULL ){
        Send_Message(fd1, "R") ;
        usleep(500000);
        if( Recieve_Message(fd2) == "S"  ){
            V = new Events_Manager(Renderer,SoundEffect,ProcNum,fd1,fd2,fd3,fd4) ;
            V->Manage_Events() ;
        }
    }
    else{
        printf("\033[1;31mProcess %d - Failure To Load Sound Effects X\033[0m \n", ProcNum) ;
        Send_Message(fd1, "x") ;
    }
}

void System_Manager::Send_Message( int fd, std::string Msg )
{
    write(fd, Msg.c_str(), strlen(Msg.c_str()) ) ;
}

std::string System_Manager::Recieve_Message( int fd )
{
    std::string Msg = "" ;
    
    NumCharRead = read( fd, Buffer, 10 ) ;
    if( NumCharRead > 0 ){
        Buffer[NumCharRead] = '\0' ;
        Msg = Buffer ;
    }
    return Msg ;
}

System_Manager::~System_Manager()
{
    close(fd1) ;
    close(fd2) ;
    close(fd3) ;
    close(fd4) ; 
    delete V ;
    V = NULL ; 
    TTF_Quit() ;
    SDL_DestroyRenderer(Renderer) ;
    SDL_DestroyWindow(Window) ;
    SDL_Quit() ;
}
