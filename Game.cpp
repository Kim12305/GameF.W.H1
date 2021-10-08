#include "Game.h"
#include "TextureManager.h"
#define W_width 680
#define W_height 480

bool Game::init(const char* title, int xpos, int ypos, int height, int width, int flags) //초기화
{
  if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    m_pWindow = SDL_CreateWindow( title, xpos, ypos, height, width, flags); //윈도우 속성 설정

    if(m_pWindow != 0)
    {
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0); //렌더러 생성해서 설정한 윈도우 보여주기

      if(m_pRenderer != 0)
        //생성한 랜더러의 색을 변경한다.
         SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
      
      else return false; //랜더러 생성 실패
    }

    //윈도우 생성 실패
    else return false;
  }

  else //SDL 초기화 실패
    return false;

  if(Init_Sprite() == false) //Texture 초기화 실패하면
    return false;
  
  m_bRunning = true;
  Init_var();

  return true;   
}

bool Game::Init_Sprite()
{
 //이미지 로드
  if(!TheTextureManager::Instance()->load("Assets/배경.png", "배경", m_pRenderer))
    return false;
      
  if(!TheTextureManager::Instance()->load("Assets/새.png", "새", m_pRenderer))
    return false;

  if(!TheTextureManager::Instance()->load("Assets/별.png", "별", m_pRenderer))  
    return false;
      
  if(!TheTextureManager::Instance()->load("Assets/우주선.png", "우주선", m_pRenderer))  
    return false;

  return true;
      
}

void Game::Init_var()
{
  sprite_x = 0;
  sprite_Hit = 150;
  sprite_Speed = 1;
}

void Game::update()
{
  m_currentFrame = ( (SDL_GetTicks() / 100) % 4);
  s_currentFrame = ( (SDL_GetTicks() / 500) % 3);
  
  MoveSprite();
}

void Game::MoveSprite() 
{
   sprite_x += sprite_Speed;

  if((0 >= sprite_x)||(sprite_x + sprite_Hit) >= W_width)
    sprite_Speed *= -1;
   
}

void Game::render() 
{
  SDL_RenderClear(m_pRenderer); //지정색으로 랜더러 지우기

  TheTextureManager::Instance()->draw("배경", 0,0, 680 , 480, 
     m_pRenderer);
  TheTextureManager::Instance()->draw("새", 30, 350, 102 , 86, 
     m_pRenderer);

  TheTextureManager::Instance()->drawFrame("별", 10, 100, 38, 
    34, 0, s_currentFrame, m_pRenderer);

  TheTextureManager::Instance()->drawFrame("별", 30, 350, 38, 
    34, 0, s_currentFrame, m_pRenderer);

  TheTextureManager::Instance()->drawFrame("우주선", sprite_x, 20, 114, 
    50, 0, m_currentFrame, m_pRenderer, sprite_Speed > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
    
    
  SDL_RenderPresent(m_pRenderer);//실질적으로 표시하기
}

bool Game::running()
{
  return m_bRunning;
}

void Game::handleEvents()
{
  SDL_Event event;
  if(SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
      m_bRunning = false; //x버튼 클릭 시 게임 루프 종료
      break;

      default:
      break;
    }
  }
}

void Game::clean() 
{
  //윈도우, 랜더러 삭제
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  //SDL 서브 시스템 종료
  SDL_Quit();
}