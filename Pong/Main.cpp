#include "Game_Manager.hpp"



int main()
{
    Game_Manager * G = new Game_Manager() ;
    G->Launch_Processes() ;
    delete G ;
    
    printf("\033[1;31mProgram Terminated\033[0m \n\n") ;
    
    return 0;
}
