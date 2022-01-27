#include "System_Manager.hpp"



System_Manager::System_Manager( int windowposX, int windowposY, int procnum )
{
    WindowPosX = windowposX ;
    WindowPosY = windowposY ;
    ProcNum = procnum ;
}

void System_Manager::Initialize_SDL()
{
    printf("\033[1;34mInitializing SDL For Process %d..............\033[0m \n", ProcNum ) ;
    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 ){
        printf("\033[1;31mFailure To Initialize SDL For Process %d X\033[0m \n", ProcNum ) ;
        exit(1) ;
    }
    printf("\033[1;32mSDL Initialized For Process %d ✔\033[0m \n", ProcNum ) ;
    
    Initialize_TTF() ;
}

void System_Manager::Initialize_TTF()
{
    printf("\033[1;34mInitializing TTF For Process %d..............\033[0m \n", ProcNum ) ;
    if( TTF_Init() != 0 ){
        printf("\033[1;31mFailure To Initialize TTF For Process %d X\033[0m \n", ProcNum ) ;
        exit(1) ;
    }
    printf("\033[1;32mTTF Initialized For Process %d ✔\033[0m \n", ProcNum ) ;
    
    Create_Window() ;
}

void System_Manager::Create_Window()
{
    printf("\033[1;34mCreating Process %d Window..............\033[0m \n", ProcNum ) ;
    Window = SDL_CreateWindow( "Pong" ,WindowPosX ,WindowPosY ,WINDOW_LENGTH, WINDOW_WIDTH, 0) ;
    if( Window==NULL ){
        printf("\033[1;31mFailure To Create Process %d Window X\033[0m \n", ProcNum ) ;
        exit(1) ;
    }
    printf("\033[1;32mProcess %d Window Created ✔\033[0m \n",ProcNum) ;
    
    Create_Renderer() ;
}

void System_Manager::Create_Renderer()
{
    printf("\033[1;34mCreating Process %d Renderer..............\033[0m \n", ProcNum ) ;
    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if(Renderer==NULL){
       printf("\033[1;31mFailure To Create Process %d Renderer X\033[0m \n", ProcNum) ;
        exit(1) ;
    }
    printf("\033[1;32mProcess %d Renderer Created ✔\033[0m \n", ProcNum) ;
    
    Launch_Audio() ;
}

void System_Manager::Launch_Audio()
{
    printf("\033[1;34mLaunching Audio System..............\033[0m \n") ;
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == 0 ){
        printf("\033[1;32mAudio System Launched ✔\033[0m \n") ;
        Load_Background_Music() ;
    }
    else{
        printf("\033[1;31mFailure To Launch Audio System X\033[0m \n") ;
        exit(1) ;
    }
}

void System_Manager::Load_Background_Music()
{
    printf("\033[1;34mLoading Background Music..............\033[0m \n") ;
    BckgrndMusic = Mix_LoadMUS( "../Assets/Ecolove.WAV" ) ;
    
    if( BckgrndMusic != NULL ){
        printf("\033[1;32mBackground Music Loaded ✔\033[0m \n") ;
        Load_Sound_Effect() ;
    }
    else{
        printf("\033[1;31mFailure To Load Background Music X\033[0m \n") ;
        exit(1) ;
    }
}

void System_Manager::Load_Sound_Effect()
{
    printf("\033[1;34mLoading Sound Effects..............\033[0m \n") ;
    SoundEffect = Mix_LoadWAV( "../Assets/Tick.wav" ) ;
    
    if( SoundEffect != NULL ){
        printf("\033[1;32mSound Effects Loaded ✔\033[0m \n") ;
        Open_Pipes() ;
    }
    else{
        printf("\033[1;31mFailure To Load Sound Effects X\033[0m \n") ;
        exit(1) ;
    }
}

void System_Manager::Open_Pipes()
{
    printf("\033[1;34mOpening Backward Pipes..............\033[0m \n") ;
    if( ProcNum == 1 ){
        fd1 = open("../External/Pipe1W.txt", O_RDWR);
        fd2 = open("../External/Pipe1R.txt", O_RDONLY | O_CREAT) ;
        fd3 = open("../External/Pipe3W.txt", O_RDWR ) ;
        fd4 = open("../External/Pipe3R.txt", O_RDONLY | O_CREAT) ;
    }
    else{
        fd1 = open("../External/Pipe2W.txt", O_RDWR);
        fd2 = open("../External/Pipe2R.txt", O_RDONLY | O_CREAT) ;
        fd3 = open("../External/Pipe3R.txt", O_RDWR ) ;
        fd4 = open("../External/Pipe3W.txt", O_RDONLY | O_CREAT) ;
    }
    if( (fd1==-1) || (fd2==-1) || (fd3==-1) || (fd4==-1) ){
        printf("\033[1;31mFailure To Open Backward Pipes X\033[0m \n") ;
        exit(1) ;
    }
    printf("\033[1;32mBackward Pipes Opened✔\033[0m \n") ;
    
    V = new Events_Manager(Renderer,BckgrndMusic,SoundEffect,ProcNum,fd1,fd2,fd3,fd4) ;
    V->Manage_Events() ;
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
