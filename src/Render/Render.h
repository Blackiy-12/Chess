#pragma once

#include <SDL.h>
#include <thread>
#include <mutex>
#include <atomic>

#include "TextureHolder.h"

namespace Chess
{
    class Render
    {
    public:
        Render();

        ~Render();

        void startRenderThread();

        void stopRender();

    private:
        std::thread RenderThread;

        std::condition_variable RenderNextFrame;

        std::atomic<bool> RenderFinished {true};

        SDL_Window* Window;

        SDL_Renderer* Renderer;

        TextureHolder* Textures;

        bool RunnigRender = true;

    private:
        void render();

        void renderBoard();

        void renderFigures();

        void renderPosiblePosition();

        void renderSwapPawn();
        
        SDL_Rect getXYForFigure(BoardPosition Position);

        BoardPosition transformMousePosition(int x, int y);

        FigureType getFigurePawnSwap(int x, int y);

        friend class Game;
    };
}