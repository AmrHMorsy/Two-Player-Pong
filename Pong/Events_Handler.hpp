#include "Includes.hpp"



class Events_Handler
{
    
private:
    
    char Buffer[100] ;
    std::string Msg, KeyPrssd ;
    bool QuitGame, QuitP2, QuitP1 ;
    int fd1, fd2, fd3, fd4, BrdYPos1, BrdYPos2 ;
    
public:
    
    Events_Handler( int fd_1, int fd_2, int fd_3, int fd_4 ) ;
    void Launch() ;
    void Handle_Events() ;
    void Handle_Key_Press( std::string Msg ) ;
    std::string Recieve_Message( int fd ) ;
    void Send_Message( std::string msg1, std::string msg2 ) ;
    ~Events_Handler() ;

} ;
