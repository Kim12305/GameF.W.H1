#include "Game.h"

Game* g_game = 0; 

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

int main(int argc, char* argv[])
{
  g_game = new Game();//객체생성
  g_game -> init("Setting up SDL", 100, 100, 640, 480, 0);

  while (g_game -> running())
  {
    g_game->handleEvents();
    g_game->update();
    g_game->render();
  }

  g_game->clean();

  return 0;
}
