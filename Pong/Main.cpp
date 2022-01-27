#include "Game_Manager.hpp"



void Clean_Pipes()
{
    fclose(fopen("../External/Pipe1R.txt", "w"));
    fclose(fopen("../External/Pipe1W.txt", "w"));
    fclose(fopen("../External/Pipe2R.txt", "w"));
    fclose(fopen("../External/Pipe2W.txt", "w"));
    fclose(fopen("../External/Pipe3W.txt", "w"));
    fclose(fopen("../External/Pipe3R.txt", "w"));
}

int main()
{
    printf("\n\033[1;34mCleaning Pipes..............\033[0m \n") ;
    Clean_Pipes() ;
    printf("\033[1;32mPipes Cleaned✔\033[0m \n") ;
    
    
    Game_Manager * G = new Game_Manager() ;
    G->Launch_Processes() ;
    delete G ;
    
    
    printf("\033[1;31mProgram Terminated\033[0m \n\n") ;
    
    return 0;
}
