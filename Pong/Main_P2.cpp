#include "System_Manager.hpp"



int main()
{
    System_Manager * S = new System_Manager(P2_WINDOW_POS_X,P2_WINDOW_POS_Y,2) ;
    S->Open_Pipes() ;
    delete S ;
    S = NULL ;
    
    return 0 ;
}
