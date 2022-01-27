#include "Game_Manager.hpp"



Game_Manager::Game_Manager()
{
    ParentID = getpid() ;
}

void Game_Manager::Launch_Processes()
{
    printf("\033[1;34mForking Parent Process..............\033[0m \n") ;
    
    fork() ;
    ProcID = getpid() ;
    if( ProcID != ParentID ){
        Child1ID = ProcID ;
        printf("\033[1;34mBooting Process 1..............\033[0m \n")  ;
        if( execv("P1", argV ) == -1 )
            printf("\033[1;31mProcess 1 Booting Failed X\033[0m \n") ;
    }
    else
        fork() ;
    ProcID = getpid() ;
    if( (ProcID!=ParentID) && (ProcID!=Child1ID) ){
        Child2ID = ProcID ;
        printf("\033[1;34mBooting Process 2..............\033[0m \n") ;
        if( execv("P2", argV ) == -1 )
            printf("\033[1;31mProcess 2 Booting Failed X\033[0m \n") ;
    }
    if( ProcID == ParentID ){
        printf("\033[1;32mForking Completed ✔\033[0m \n") ;
        Open_Pipes() ;
    }
}

void Game_Manager::Open_Pipes()
{
    printf("\033[1;34mOpening Forward Pipes..............\033[0m \n") ;
    fd1 = open("../External/Pipe1W.txt", O_RDONLY | O_CREAT) ;
    fd2 = open("../External/Pipe2W.txt", O_RDONLY | O_CREAT) ;
    fd3 = open("../External/Pipe1R.txt", O_RDWR);
    fd4 = open("../External/Pipe2R.txt", O_RDWR);
    
    if( (fd1==-1) || (fd2==-1) || (fd3==-1) || (fd4==-1) )
        printf("\033[1;31mFailure To Open Forward Pipes X\033[0m \n") ;
    printf("\033[1;32mForward Pipes Opened ✔\033[0m \n") ;
    
    E = new Events_Handler(fd1,fd2,fd3,fd4) ;
    E->Handle_Events() ;
}

Game_Manager::~Game_Manager()
{
    printf("\033[1;34mClosing Pipes..............\033[0m \n") ;
    close(fd1) ;
    close(fd2) ;
    close(fd3) ;
    close(fd4) ;
    printf("\033[1;32mPipes Closed ✔\033[0m \n") ;
    delete E ;
    E = NULL ; 
}
