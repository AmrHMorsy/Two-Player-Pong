all: P1 P2 Pong

Pong: Main.cpp Game_Manager.cpp Events_Handler.cpp
	g++ -std=c++11 -O3 -I/usr/local/include Main.cpp Game_Manager.cpp Events_Handler.cpp -o Pong -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

P1: Main_P1.cpp System_Manager.cpp Events_Manager.cpp Window_Renderer.cpp
	g++ -std=c++11 -O3 -I/usr/local/include Main_P1.cpp System_Manager.cpp Events_Manager.cpp Window_Renderer.cpp -o P1 -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

P2: Main_P2.cpp System_Manager.cpp Events_Manager.cpp Window_Renderer.cpp
	g++ -std=c++11 -O3 -I/usr/local/include Main_P2.cpp System_Manager.cpp Events_Manager.cpp Window_Renderer.cpp -o P2 -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer