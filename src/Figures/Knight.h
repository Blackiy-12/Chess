#pragma once

#include "../Figure.h"

namespace Chess
{
    class Knight : public Figure
    {
    public:
        Knight(BoardPosition StartPosition, TeamColor Color, Board* BoardPtr);

        Knight(const Knight&) = delete;

        Knight(Knight&&) = delete;

        Knight& operator=(const Knight&) = delete;

        Knight& operator=(Knight&&) =delete;

        ~Knight();

        std::vector<BoardPosition> getPosibleNewPosition() override;

        FigureType getFigureType() override { return FigureType::KNIGHT; };

        void updatePosiblePosition() override;
    };
}