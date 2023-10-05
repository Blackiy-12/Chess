#pragma once

#include "Board.h"
#include "Render/Render.h"

#include <thread>

namespace Chess
{
    class Game
    {   
    public:
        Game();

        ~Game();

        void  startLoop();

    private:
        std::unique_ptr<Board> GameBoard;

        std::unique_ptr<Render> RenderPtr;

        std::thread RenderThread;
    private:
        void playGameLoop();
    };
}