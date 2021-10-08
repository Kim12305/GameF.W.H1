#pragma once
#include "SDL.h"
#include "TextureManager.h"

class Game
{
  public:
    Game() {} //생성자
    ~Game() {} //소멸자

    //초기화 함수
    bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
    bool Init_Sprite();
    void render(); //렌더링 하는 함수
    void update();

    //추가함수들
    bool running();
    void handleEvents();
    void clean();
    void Init_var();
    void MoveSprite();
    
  private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_bRunning;

    int m_currentFrame; 
    int s_currentFrame;
    int sprite_x;
    int sprite_Speed;
    int sprite_Hit;
    
  

    SDL_Texture* m_pTexture;

    SDL_Rect m_sourceRectangle; //원본 사각형
    SDL_Rect m_destinationRectangle; //대상 사각형

};

