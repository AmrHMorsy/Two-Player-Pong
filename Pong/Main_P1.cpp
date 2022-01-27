#include "System_Manager.hpp"



int main()
{
    printf("\033[1;32mProcess 1 Booted ✔\033[0m \n") ;

    System_Manager * S = new System_Manager(P1_WINDOW_POS_X,P1_WINDOW_POS_Y,1) ;
    S->Initialize_SDL() ;
    delete S ;
    S = NULL ; 
        
    return 0 ;
}
