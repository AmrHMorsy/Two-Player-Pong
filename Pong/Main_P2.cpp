#include "System_Manager.hpp"



int main()
{
    printf("\033[1;32mProcess 2 Booted ✔\033[0m \n") ;
    
    System_Manager * S = new System_Manager(P2_WINDOW_POS_X,P2_WINDOW_POS_Y,2) ;
    S->Initialize_SDL() ;
    delete S ;
    S = NULL ;
    
    return 0 ;
}
