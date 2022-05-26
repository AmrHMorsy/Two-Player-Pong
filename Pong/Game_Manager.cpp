#include "Game_Manager.hpp"



Game_Manager::Game_Manager()
{
    ParentID = getpid() ;
}

void Game_Manager::Launch_Processes()
{
    fork() ;
    ProcID = getpid() ;
    if( ProcID != ParentID ){
        Child1ID = ProcID ;
        if( execv("P1", argV ) == -1 )
            printf("\033[1;31mProcess 1 Booting Failed X\033[0m \n") ;
    }
    else
        fork() ;
    ProcID = getpid() ;
    if( (ProcID!=ParentID) && (ProcID!=Child1ID) ){
        Child2ID = ProcID ;
        if( execv("P2", argV ) == -1 )
            printf("\033[1;31mProcess 2 Booting Failed X\033[0m \n") ;
    }
    if( ProcID == ParentID )
        Open_Pipes() ;
}

void Game_Manager::Open_Pipes()
{
    fclose(fopen("Pipe1R.txt", "w"));
    fclose(fopen("Pipe1W.txt", "w"));
    fclose(fopen("Pipe2R.txt", "w"));
    fclose(fopen("Pipe2W.txt", "w"));
    fclose(fopen("Pipe3W.txt", "w"));
    fclose(fopen("Pipe3R.txt", "w"));
    fd1 = open("Pipe1W.txt", O_RDONLY | O_CREAT) ;
    fd2 = open("Pipe2W.txt", O_RDONLY | O_CREAT) ;
    fd3 = open("Pipe1R.txt", O_RDWR);
    fd4 = open("Pipe2R.txt", O_RDWR);
    
    if( (fd1==-1) || (fd2==-1) || (fd3==-1) || (fd4==-1) )
        printf("\033[1;31mFailure To Open Forward Pipes X\033[0m \n") ;
    
    E = new Events_Handler(fd1,fd2,fd3,fd4) ;
    E->Launch() ; 
}

Game_Manager::~Game_Manager()
{
    close(fd1) ;
    close(fd2) ;
    close(fd3) ;
    close(fd4) ;
    delete E ;
    E = NULL ; 
}
