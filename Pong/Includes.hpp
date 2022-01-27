#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <spawn.h>
#include <fcntl.h>
#include <errno.h>
#include <sstream>



#define PI 3.14159265
#define INITIAL_BOARD_YPOS 170
#define INITIAL_BOARD_XPOS 60
#define BOARD_MOTION_INDEX 50
#define WINDOW_BOTTOM_BOUNDARIES 380
#define WINDOW_UPPER_BOUNDARIES 2
#define BUFFER_SIZE 100
#define P1_WINDOW_POS_X 100
#define P1_WINDOW_POS_Y 100
#define P2_WINDOW_POS_X 740
#define P2_WINDOW_POS_Y 100
#define WINDOW_LENGTH 640
#define WINDOW_WIDTH 480
#define BLACK 0
#define FONT_SIZE 100
#define BOARD_THICKNESS 10
#define WHITE 255
#define BALL_WIDTH 25
#define BALL_HEIGHT 25
#define BALL_SPEED 50
