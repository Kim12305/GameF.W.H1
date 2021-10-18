#pragma once
#include "SDL.h"
#include "TextureManager.h"
#define W_width 640
#define W_height 480

class Game
{
  public:
    Game() {} //생성자
    ~Game() {} //소멸자

    //초기화 함수
    bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
    bool Init_Sprite();
    void Init_Map();
    void Init_var();
    void render(); //렌더링 하는 함수
    void update();

   
    //추가함수들
    bool running();
    void handleEvents();
    void clean();
    void MoveSprite();
    void RotateSprite();
    void MoveBall();

    void Maze();
    
  private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_bRunning;

    int m_currentFrame; 
    int s_currentFrame;
    int sprite_x;
    int sprite_Speed;
    int sprite_Hit;

    int rotate_Angle;
    int rotate_Speed;

    int msSpeedX;
    int msSpeedY;
    int msHit_w;
    int msHit_h;
    int ms_x;
    int ms_y;

    int map[19][19] = 
    {
      {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
      {1,0,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1},
      {1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
      {1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1},
      {1,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1},
      {1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1},
      {1,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1},
      {1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1},
      {1,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1},
      {1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
      {1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1},
      {1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
      {1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1},
      {1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1},
      {1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1},
      {1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1},
      {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    
   SDL_Rect rt[19*19]; //x,y,w,h
   int rt_count;

    

    
};

