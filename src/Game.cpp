#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "Player.h"
#include "ScrollingBackground.h"
#include "SoundManager.h"
#include "GameOverState.h"
#include "PlayState.h"
#include "Ninja.h"
#include "Bird.h"
#include "Coin.h"
#include <iostream>
#include <string>

using namespace std;

Game* Game::s_pInstance = 0;

Game::Game():
m_pWindow(0),
m_pRenderer(0),
m_bRunning(false),
m_pGameStateMachine(0),
m_playerLives(3),
m_bLevelComplete(false)
{
    // add some level files to an array
    m_levelFiles.push_back("assets/maps/level-1.tmx"); // level 1
    m_levelFiles.push_back("assets/maps/level-2.tmx"); // level 2


    // start at this level
    // for debug, edit also resetCustom, currentLevel = level_to_Test;
    m_currentLevel = 1;
    m_score = 0;

    if ( TTF_Init() != -1 ){
      m_font = NULL;
      textColor = { 0, 0, 0 };
      m_lrec.x = 0;
      m_lrec.y = 34;
      m_lrec.w = 100;
      m_lrec.h = 30;
      m_srec.x = 0;
      m_srec.y = 0;
      m_srec.w = 100;
      m_srec.h = 30;
      m_lerec.w = 100;
      m_lerec.x = 525;
      m_lerec.y = 0;
      m_lerec.h = 30;
    } else {
      std::cout << TTF_GetError() << std::endl;
    }
}

Game::~Game()
{
    // we must clean up after ourselves to prevent memory leaks
    m_pRenderer= 0;
    m_pWindow = 0;
}


bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;

    // store the game width and height
    m_gameWidth = width;
    m_gameHeight = height;

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // attempt to initialise SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "SDL init success\n";
        // init the window
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if(m_pWindow != 0) // window init success
        {
            cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

            if(m_pRenderer != 0) // renderer init success
            {
                cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 0,0,0,255);
            }
            else
            {
                cout << "renderer init fail\n";
                return false; // renderer init fail
            }
        }
        else
        {
            cout << "window init fail\n";
            return false; // window init fail
        }
    }
    else
    {
        cout << "SDL init fail\n";
        return false; // SDL init fail
    }

    m_font = TTF_OpenFont("assets/fonts/sansation.ttf", 18);
    if ( m_font == NULL ) {
      std::cout << TTF_GetError() << std::endl;
    }

    // add some sound effects
    TheSoundManager::Instance()->load("level-1.mp3", "music1", SOUND_MUSIC);
    TheSoundManager::Instance()->load("jump.wav", "jump", SOUND_SFX);
    TheSoundManager::Instance()->load("coin.wav", "coin", SOUND_SFX);

    TheInputHandler::Instance()->initialiseJoysticks();

    // register the types for the game
    TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    TheGameObjectFactory::Instance()->registerType("ScrollingBackground", new ScrollingBackgroundCreator());
    TheGameObjectFactory::Instance()->registerType("Ninja", new NinjaCreator());
    TheGameObjectFactory::Instance()->registerType("Bird", new BirdCreator());
    TheGameObjectFactory::Instance()->registerType("Coin", new CoinCreator());


    // start the menu state
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());

    m_bRunning = true; // everything inited successfully, start the main loop
    return true;
}

void Game::setCurrentLevel(int currentLevel)
{
    // m_currentLevel = currentLevel;
    if( currentLevel <= 2){
      m_pGameStateMachine->changeState(new PlayState());
      m_bLevelComplete = false;
    } else {
      m_pGameStateMachine->changeState(new GameOverState());
    }
}

void Game::render()
{
    std::string s = "Collected: " + std::to_string(m_score) + "/26";
    std::string l = "Lives: " + std::to_string(m_playerLives);
    std::string lv = "Level: " + std::to_string(m_currentLevel);

    SDL_RenderClear(m_pRenderer);

    m_pGameStateMachine->render();

    m_surface = TTF_RenderText_Solid( m_font, s.c_str(), textColor );
    if( m_surface == NULL ){
      std::cout << TTF_GetError() << std::endl;
    }
    m_texture = SDL_CreateTextureFromSurface( m_pRenderer, m_surface );
    if( m_texture == NULL ){
      std::cout << TTF_GetError() << std::endl;
    }

    SDL_FreeSurface( m_surface );
    SDL_RenderCopy( m_pRenderer, m_texture, NULL , &m_srec);

    m_surface = TTF_RenderText_Solid( m_font, l.c_str(), textColor );
    if( m_surface == NULL ){
      std::cout << TTF_GetError() << std::endl;
    }
    m_texture = SDL_CreateTextureFromSurface( m_pRenderer, m_surface );
    if( m_texture == NULL ){
      std::cout << TTF_GetError() << std::endl;
    }

    SDL_FreeSurface( m_surface );
    SDL_RenderCopy( m_pRenderer, m_texture, NULL , &m_lrec);

    m_surface = TTF_RenderText_Solid( m_font, lv.c_str(), textColor );
    if( m_surface == NULL ){
      std::cout << TTF_GetError() << std::endl;
    }
    m_texture = SDL_CreateTextureFromSurface( m_pRenderer, m_surface );
    if( m_texture == NULL ){
      std::cout << TTF_GetError() << std::endl;
    }

    SDL_FreeSurface( m_surface );
    SDL_RenderCopy( m_pRenderer, m_texture, NULL , &m_lerec);

    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    m_pGameStateMachine->update();
    if( m_score == 26 ){
      m_currentLevel = m_currentLevel + 1;
      setCurrentLevel(m_currentLevel);
    }
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();
}

void Game::clean()
{
    cout << "cleaning game\n";

    TheInputHandler::Instance()->clean();

    m_pGameStateMachine->clean();

    m_pGameStateMachine = 0;
    delete m_pGameStateMachine;

    TheTextureManager::Instance()->clearTextureMap();

    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}
