#include "Events_Handler.hpp"



Events_Handler::Events_Handler( int fd_1, int fd_2, int fd_3, int fd_4 )
{
    fd1 = fd_1 ;
    fd2 = fd_2 ;
    fd3 = fd_3 ;
    fd4 = fd_4 ;
    BrdYPos1 = BrdYPos2 = INITIAL_BOARD_YPOS ;
    QuitGame = QuitP2 = QuitP1 = false ;
    Buffer = (char *) calloc(BUFFER_SIZE, sizeof(char)) ;
}

void Events_Handler::Handle_Events()
{
    while( !QuitGame ){
        if( !QuitP1 ){
            MsgRecvP1 = Recieve_Message(fd1) ;
            if( MsgRecvP1 != "" ){
                if( MsgRecvP1 == "x" )
                    QuitP1 = true ;
                else{
                    Handle_Key_Press(MsgRecvP1) ;
                    Send_Message() ;
                }
            }
        }
        if( !QuitP2 ){
            MsgRecvP2 = Recieve_Message(fd2) ;
            if( MsgRecvP2 != "" ){
                if( MsgRecvP2 == "x" )
                    QuitP2 = true ;
                else{
                    Handle_Key_Press(MsgRecvP2) ;
                    Send_Message() ;
                }
            }
        }
        if( QuitP1 || QuitP2 )
            QuitGame = true ;
    }
}

std::string Events_Handler::Recieve_Message( int fd )
{
    std::string Msg = "" ;
    
    NumCharRead = read( fd, Buffer, 10 ) ;
    if( NumCharRead > 0 ){
        Buffer[NumCharRead] = '\0' ;
        Msg = Buffer ;
    }
    
    return Msg ;
}

void Events_Handler::Handle_Key_Press( std::string Message )
{
    std::stringstream S(Message) ;
    
    S >> KeyPrssd ;
    if( KeyPrssd == "W" )
        BrdYPos1-= BOARD_MOTION_INDEX ;
    if( KeyPrssd == "S" )
        BrdYPos1+= BOARD_MOTION_INDEX ;
    if( KeyPrssd == "Up" )
        BrdYPos2-= BOARD_MOTION_INDEX ;
    if( KeyPrssd == "Down" )
        BrdYPos2+= BOARD_MOTION_INDEX ;
    if( BrdYPos2 >= WINDOW_BOTTOM_BOUNDARIES )
        BrdYPos2 = WINDOW_BOTTOM_BOUNDARIES ;
    else if( BrdYPos2 <= WINDOW_UPPER_BOUNDARIES )
        BrdYPos2 = WINDOW_UPPER_BOUNDARIES ;
    if( BrdYPos1 >= WINDOW_BOTTOM_BOUNDARIES )
        BrdYPos1 = WINDOW_BOTTOM_BOUNDARIES ;
    else if( BrdYPos1 <= WINDOW_UPPER_BOUNDARIES )
        BrdYPos1 = WINDOW_UPPER_BOUNDARIES ;
}

void Events_Handler::Send_Message()
{
    MsgSentP1 = std::to_string(BrdYPos1) + " " ;
    MsgSentP2 = (std::to_string(BrdYPos2) + " ") ;
    write(fd3, MsgSentP1.c_str(), strlen(MsgSentP1.c_str()) ) ;
    write(fd4, MsgSentP2.c_str(), strlen(MsgSentP2.c_str()) ) ;
}

Events_Handler::~Events_Handler(){}
