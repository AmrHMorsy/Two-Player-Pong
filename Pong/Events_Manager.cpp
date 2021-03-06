#include "Events_Manager.hpp"



Events_Manager::Events_Manager(SDL_Renderer * renderer, int procnum, int f_d1, int f_d2, int f_d3, int f_d4 )
{
    fd1 = f_d1 ;
    fd2 = f_d2 ;
    fd3 = f_d3 ;
    fd4 = f_d4 ;
    BallInProc = 1 ;
    ProcNum = procnum ;
    Renderer = renderer ;
    BounceAngle = Score = 0 ;
    BallXPos = INITIAL_BOARD_XPOS ;
    BoardYPos = BallYPos = INITIAL_BOARD_YPOS ;
    W = new Window_Renderer(Renderer,ProcNum) ;
    GameStarted = GameEnded = Quit = Left = Pause = false ; Right = true ;
    Msg = MsgRcv = boardYpos = ballYpos = BallinProc = bounceAngle = score = "" ;
}

void Events_Manager::Manage_Events()
{
    while( !Quit ){
        if( GameStarted ){
            Recieve_Message() ;
            if( !Pause )
                Update_Ball_Position() ;
            Update_Gameplay() ;
        }
        while( SDL_PollEvent(&Event) > 0 ){
            switch(Event.type){
                case SDL_QUIT:
                    ProcNum = 0 ;
                    End_Game() ;
                    break ;
                case SDL_KEYDOWN:
                    Send_Message(fd1,Get_KeyPrssd()) ;
                    break ;
                case SDL_MOUSEBUTTONDOWN:
                    Pause = false ;
            }
        }
        if( !GameStarted )
            Start_Game() ;
        if( GameEnded )
            End_Game() ;
        else if( IsGameOver() )
            GameEnded = true ;
    }
}

void Events_Manager::Start_Game()
{
    W->Paint_Window() ;
    if( ProcNum == 1 )
        W->Write_Word("PO") ;
    else
        W->Write_Word("NG") ;
    GameStarted = true ;
    sleep(1) ;
}

bool Events_Manager::IsGameOver()
{
    if( Score == MAX_SCORE ){
        Send_Message(fd3,"x") ;
        return true ;
    }
    return false ;
}

void Events_Manager::End_Game()
{
    W->Paint_Window() ;
    if( ProcNum == 1 )
        W->Write_Word("GAME") ;
    else if( ProcNum == 2 )
        W->Write_Word("OVER") ;
    if( ProcNum != 0 )
        sleep(1) ;
    Quit = true ;
    Send_Message(fd1,"x") ;
}

void Events_Manager::Update_Ball_Position()
{
    if( BallYPos <= 5 ){
        BounceAngle = (50*PI)/180 ;
        Sin = 50 * sin((double)BounceAngle) ;
        Cos = 50 * cos((double)BounceAngle) ;
        BallXPos = BallXPos - Sin ;
        BallYPos = BallYPos + Cos ;
    }
    
    if( BallYPos >= 480 ){
        BounceAngle = (50*PI)/180 ;
        Sin = 50 * sin((double)BounceAngle) ;
        Cos = 50 * cos((double)BounceAngle) ;
        BallXPos = BallXPos - Sin ;
        BallYPos = BallYPos - Cos ;
    }

    if( ProcNum == 1 ){
        if( (BallYPos>=BoardYPos) && (BallYPos<=(BoardYPos+100)) && (BallXPos<=50) ){
            Left = false ;
            Right = true ;
            BounceAngle = ((((BoardYPos+BoardYPos+100)/2)-BallYPos)/50) * 75 * -1 ;
        }
        if( BallXPos <= -50 ){
            BallXPos = 80 ;
            BallYPos = (BoardYPos+BoardYPos+100)/2 ;
            Pause = Left = true ;
            Right = false ;
            sleep(1) ;
            Send_Message(fd3,("1 "+ std::to_string(BallYPos) + " " + std::to_string(BounceAngle) + " 1 ")) ;
        }
        if( BallXPos >= 650 ){
            Left = true ;
            Right = false ;
            BallInProc = 2 ;
            BallXPos = 649 ;
            Send_Message(fd3,("2 "+ std::to_string(BallYPos) + " " + std::to_string(BounceAngle) + " 0 ")) ;
        }
    }
    else if( ProcNum == 2 ){
        if( (BallYPos>=BoardYPos) && (BallYPos<=(BoardYPos+100)) && (BallXPos>=550) ){
            Left = true ;
            Right = false ;
            BounceAngle = ((((BoardYPos+BoardYPos+100)/2)-BallYPos)/50) * 75 * 1 ;
        }
        if( BallXPos >= 650 ){
            BallXPos = 570 ;
            BallYPos = (BoardYPos+BoardYPos+100)/2 ;
            Left = Pause = true ;
            Right = false ;
            sleep(1) ;
            Send_Message(fd3,("2 "+ std::to_string(BallYPos) + " " + std::to_string(BounceAngle) + " 1 ")) ;
        }
        if( BallXPos <= 0 ){
            Left = false ;
            Right = true ;
            BallInProc = 1 ;
            BallXPos = 1 ;
            Send_Message(fd3,("1 "+ std::to_string(BallYPos) + " " + std::to_string(BounceAngle) + " 0 ")) ;
        }
    }
    if( ProcNum == BallInProc ){
        Sin = 30 * sin((double)BounceAngle) ;
        Cos = 30 * cos((double)BounceAngle) ;
        if( Left ){
            BallXPos = BallXPos - Cos ;
            BallYPos = BallYPos + Sin ;
        }
        else if( Right ){
            BallXPos = BallXPos + Cos ;
            BallYPos = BallYPos - Sin ;
        }
    }
}

void Events_Manager::Recieve_Message()
{
    NumCharRead = read(fd2,Buffer, 14 ) ;
    if( NumCharRead > 0 ){
        Buffer[NumCharRead] = '\0' ;
        MsgRcv = Buffer ;
        std::stringstream SS(MsgRcv) ;
        SS >> boardYpos ;
        BoardYPos = stoi(boardYpos) ;
    }
    NumCharRead = read(fd4,Buffer,20) ;
    if( NumCharRead > 0 ){
        Buffer[NumCharRead] = '\0' ;
        MsgRcv = Buffer ;
        std::stringstream S(MsgRcv) ;
        S >> BallinProc ;
        if( BallinProc == "x" )
            GameEnded = true ;
        else{
            S >> ballYpos ;
            S >> bounceAngle ;
            S >> score ;
            BallInProc = stoi(BallinProc) ;
            BallYPos = stoi(ballYpos) ;
            BounceAngle = stoi(bounceAngle) ;
            Score = Score + stoi(score) ;
        }
    }
}

void Events_Manager::Send_Message( int fd, std::string Msg )
{
    write(fd, Msg.c_str(), strlen(Msg.c_str()) ) ;
}

void Events_Manager::Update_Gameplay()
{
    W->Paint_Window() ;
    W->Draw_Boards(BoardYPos) ;
    if( BallInProc == ProcNum )
        W->Draw_Ball(BallXPos,BallYPos) ;
    W->Write_Scores(Score) ;
}

std::string Events_Manager::Get_KeyPrssd()
{
    std::string msg = SDL_GetKeyName(Event.key.keysym.sym) ;
    msg = msg + " " ;
    return msg ;
}

Events_Manager::~Events_Manager()
{
    delete W ;
    W = NULL ; 
}
