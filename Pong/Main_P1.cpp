#include "System_Manager.hpp"



int main()
{
    System_Manager * S = new System_Manager(P1_WINDOW_POS_X,P1_WINDOW_POS_Y,1) ;
    S->Open_Pipes() ;
    delete S ;
    S = NULL ; 
        
    return 0 ;
}
