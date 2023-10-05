#pragma once

#include "Figure.h"
#include "Figures/King.h"

#include <list>
#include <memory>

namespace Chess
{
    class Board;

    class Team
    {
    public:
        Team(TeamColor Color);

        Team(const Team&) = delete;

        Team(Team&&) = delete;

        Team& operator=(const Team&) = delete;

        Team& operator=(Team&&) = delete;

        ~Team();

        void setupFiguresForStart(Board* BoardPtr);

    private:
        TeamColor Color;

        std::unique_ptr<King> TeamKing;

        std::list<std::shared_ptr<Figure>> Figures;

        friend class Board;
    };
}

