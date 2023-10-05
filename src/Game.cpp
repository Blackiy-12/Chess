#include "Game.h"

Chess::Game::Game()
{
    this->GameBoard = std::make_unique<Board>();

    this->RenderPtr = std::make_unique<Render>();
}

Chess::Game::~Game()
{
}

void Chess::Game::startLoop()
{
    //Start Render Thread
    this->RenderPtr->startRenderThread();

    playGameLoop();    

    RenderPtr->RenderThread.join();
}

void Chess::Game::playGameLoop()
{
    bool run = true;
    BoardPosition BoardPos{0,0};

    while (run)
    {
        this->RenderPtr->RenderFinished.wait(false);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

            case SDL_MOUSEBUTTONDOWN:
                if (SDL_GetWindowID(this->RenderPtr->Window) != event.button.windowID)
                    continue;

                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    this->GameBoard->unselectFigure();
                }

                else if (event.button.button == SDL_BUTTON_LEFT)
                {

                   int x, y;
                    SDL_GetMouseState(&x, &y);

                    if (this->GameBoard->needToSwapPawn())
                    {
                        this->GameBoard->pressSwapPosition(this->RenderPtr->getFigurePawnSwap(x, y));
                    }
                    else
                    {
                        BoardPos = this->RenderPtr->transformMousePosition(x, y);

                        this->GameBoard->pressPosition(BoardPos);
                    }
                }

                break;
            case SDL_QUIT:
                RenderPtr->stopRender();
                run = false;
                break;
            }
        }

        this->RenderPtr->RenderNextFrame.notify_one();
    }
}
