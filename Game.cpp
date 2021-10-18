#include "Game.h"

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
    
  Init_var();
  Maze();
  
  m_bRunning = true;

  return true;   
}

bool Game::Init_Sprite()
{
 //이미지 로드
  if(!TheTextureManager::Instance()->load("Assets/배경.png", "background", m_pRenderer))
    return false;
      
  if(!TheTextureManager::Instance()->load("Assets/새.png", "birdSp", m_pRenderer))
    return false;

  if(!TheTextureManager::Instance()->load("Assets/별.png", "starSp", m_pRenderer))  
    return false;
  
  if(!TheTextureManager::Instance()->load("Assets/외계인.png", "strangerSp", m_pRenderer))  
    return false;

  if(!TheTextureManager::Instance()->load("Assets/말풍선.png", "talkSp", m_pRenderer))  
    return false;
      
  if(!TheTextureManager::Instance()->load("Assets/우주선.png", "roketSp", m_pRenderer))  
    return false;

  SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255); //미로 사각형 색상


  return true;
      
}


void Game::Init_var() //변수 초기화
{
  sprite_x = 0;
  sprite_Hit = 114;
  sprite_Speed = 1;
  rotate_Angle = 1;
  rotate_Speed = 1;
  msSpeedX = 1;
  msSpeedY = 1;
  ms_x = 0;
  ms_y = 0;
  msHit_w = 88;
  msHit_h = 73;

  rt_count = 0;
}

void Game::Maze() //미로
{
  for(int i = 0; i < 19; i++)
  {
    for(int j = 0; j < 19; j++)
    {
      if(map[i][j] == 1)
      {
        rt_count += 1;
        rt[rt_count] = {j*5, i*5, 5, 5};//x,y,w,h
      }
    }
  }
}

void Game::update()
{
  m_currentFrame = ( (SDL_GetTicks() / 100) % 4);
  s_currentFrame = ( (SDL_GetTicks() / 500) % 3);
  
  MoveSprite();
  RotateSprite();
  MoveBall();
}

void Game::MoveSprite() //우주선 좌우로 움직이게 만들기
{
  sprite_x += sprite_Speed;

  if((0 >= sprite_x)||(sprite_x + sprite_Hit) >= W_width)
    sprite_Speed *= -1;
   
}

void Game::RotateSprite() //회전하는 외계인
{
  rotate_Angle += rotate_Speed;

  if(rotate_Angle >= 360)
    rotate_Angle = 0;
}

void Game::MoveBall() //회전하는 말풍선
{
  ms_x += msSpeedX;
  ms_y += msSpeedY;
  
  if(0 >= ms_x || (ms_x + msHit_w) >= W_width)
    msSpeedX *= -1;

  if(0 >= ms_y || (ms_y + msHit_h) >= W_height)
    msSpeedY *= -1;

}

void Game::render() 
{
  SDL_RenderClear(m_pRenderer); //지정색으로 랜더러 지우기

  TheTextureManager::Instance()->draw("background", 0,0, 640 , 480, 
     m_pRenderer);

  TheTextureManager::Instance()->drawFrame("starSp", 10, 100, 39, 
    34, 0, s_currentFrame, m_pRenderer);

  TheTextureManager::Instance()->drawFrame("starSp", 350, 30, 39, 
    34, 0, s_currentFrame, m_pRenderer);

  TheTextureManager::Instance()->drawFrame("starSp", 100, 20, 39, 
    34, 0, s_currentFrame, m_pRenderer);

  TheTextureManager::Instance()->drawFrame("roketSp", sprite_x, 20, 114, 
    50, 0, m_currentFrame, m_pRenderer, sprite_Speed > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

  TheTextureManager::Instance()->drawFrameRotate("talkSp", ms_x, ms_y, 88, 
    73, 0, 0, m_pRenderer, 0, SDL_FLIP_NONE);
    
  TheTextureManager::Instance()->drawFrameRotate("strangerSp", 250, 150, 126, 
    64, 0, 0, m_pRenderer, rotate_Angle, SDL_FLIP_NONE);
    
  TheTextureManager::Instance()->draw("birdSp", 30, 350, 102 , 86, m_pRenderer);

  SDL_RenderFillRects(m_pRenderer, rt, 19*19);
 

  
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