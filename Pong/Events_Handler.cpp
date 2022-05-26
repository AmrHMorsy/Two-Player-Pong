#include "Events_Handler.hpp"



Events_Handler::Events_Handler( int fd_1, int fd_2, int fd_3, int fd_4 )
{
    fd1 = fd_1 ;
    fd2 = fd_2 ;
    fd3 = fd_3 ;
    fd4 = fd_4 ;
    BrdYPos1 = BrdYPos2 = INITIAL_BOARD_YPOS ;
    QuitGame = QuitP2 = QuitP1 = false ;
}

void Events_Handler::Launch()
{
    usleep(800000);
    if( (Recieve_Message(fd1)=="R") && (Recieve_Message(fd2)=="R") ){
        Send_Message("S","S") ;
        Handle_Events() ;
    }
}

void Events_Handler::Handle_Events()
{
    while( !QuitGame ){
        if( !QuitP1 ){
            Msg = Recieve_Message(fd1) ;
            if( Msg != "" ){
                if( Msg == "x" )
                    QuitP1 = true ;
                else{
                    Handle_Key_Press(Msg) ;
                    Send_Message((std::to_string(BrdYPos1)+" "), (std::to_string(BrdYPos2)+" ")) ;
                }
            }
        }
        if( !QuitP2 ){
            Msg = Recieve_Message(fd2) ;
            if( Msg != "" ){
                if( Msg == "x" )
                    QuitP2 = true ;
                else{
                    Handle_Key_Press(Msg) ;
                    Send_Message((std::to_string(BrdYPos1)+" "), (std::to_string(BrdYPos2)+" ")) ;
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

    int NumCharRead = read( fd, Buffer, 10 ) ;
    if( NumCharRead > 0 ){
        Buffer[NumCharRead] = '\0' ;
        Msg = Buffer ;
    }
    return Msg ;
}

void Events_Handler::Handle_Key_Press( std::string Msg )
{
    std::stringstream S(Msg) ;
    
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

void Events_Handler::Send_Message( std::string msg1, std::string msg2 )
{
    write(fd3, msg1.c_str(), strlen(msg1.c_str()) ) ;
    write(fd4, msg2.c_str(), strlen(msg2.c_str()) ) ;
}

Events_Handler::~Events_Handler(){}
