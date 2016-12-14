#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GameStateMachine.h"
#include "Vector2D.h"
#include <vector>

class Game
{
public:

    static Game* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }

        return s_pInstance;
    }


    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void render();
    void update();
    void handleEvents();
    void clean();

    SDL_Renderer* getRenderer() const { return m_pRenderer; }
    SDL_Window* getWindow() const { return m_pWindow; }
    GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

    void setPlayerLives(int lives) { m_playerLives = lives; }
    int getPlayerLives() { return m_playerLives; }

    void setCurrentLevel(int currentLevel);
    const int getCurrentLevel() { return m_currentLevel; }

    void setNextLevel(int nextLevel) { m_nextLevel = nextLevel; }
    const int getNextLevel() { return m_nextLevel; }

    void setLevelComplete(bool levelComplete) { m_bLevelComplete = levelComplete; }
    const bool getLevelComplete() { return m_bLevelComplete; }

    int getScore() const { return m_score; }
    void setScore(int score) { m_score = score;}
    void incScore() { m_score = m_score + 1; }

    bool running() { return m_bRunning; }

    void quit() { m_bRunning = false; }

    int getGameWidth() const { return m_gameWidth; }
    int getGameHeight() const { return m_gameHeight; }

    void setTextColor(int c){
      if( c == 1) {
        textColor = { 255, 255, 255 };
      } else {
        textColor = { 0, 0, 0 };
      }
    }

    void resetCustom(){
      m_currentLevel = 1;
      m_score = 0;
      textColor = { 0, 0, 0};
    }

    std::vector<std::string> getLevelFiles() { return m_levelFiles; }

private:

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    SDL_Texture* m_texture;
    SDL_Surface* m_surface;
    SDL_Rect m_lrec;
    SDL_Rect m_srec;
    SDL_Rect m_lerec;
    TTF_Font* m_font;
    SDL_Color textColor;

    GameStateMachine* m_pGameStateMachine;

    bool m_bRunning;

    static Game* s_pInstance;

    int m_gameWidth;
    int m_gameHeight;
    int m_playerLives;

    int m_currentLevel;
    int m_nextLevel;
    int m_score;
    bool m_bLevelComplete;

    std::vector<std::string> m_levelFiles;

    Game();
    ~Game();

    Game(const Game&);
	Game& operator=(const Game&);
};

typedef Game TheGame;

#endif
