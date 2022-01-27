#include "Includes.hpp"



class Events_Handler
{
    
private:
    
    char * Buffer ;
    bool QuitGame, QuitP2, QuitP1 ;
    int fd1, fd2, fd3, fd4, NumCharRead, BrdYPos1, BrdYPos2 ;
    std::string MsgRecvP1, MsgRecvP2, MsgSentP1, MsgSentP2, KeyPrssd ;
    
public:
    
    Events_Handler( int fd_1, int fd_2, int fd_3, int fd_4 ) ;
    void Handle_Events() ;
    void Handle_Key_Press( std::string Msg ) ;
    std::string Recieve_Message( int fd ) ;
    void Send_Message() ;
    ~Events_Handler() ;

} ;
