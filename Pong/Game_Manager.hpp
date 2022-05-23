#include "Events_Handler.hpp"



class Game_Manager
{
    
private:
    
    Events_Handler * E ;
    int ParentID, Child1ID, Child2ID , fd1, fd2, fd3, fd4, ProcID ;
    char * argV[] ;
    
public:
    
    Game_Manager() ;
    void Launch_Processes() ;
    void Open_Pipes() ; 
    ~Game_Manager() ;
    
};
