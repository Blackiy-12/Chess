#pragma once

#include "../Figure.h"

namespace Chess
{
    class Queen : public Figure
    {
    public:
        Queen(BoardPosition StartPosition, TeamColor Color, Board* BoardPtr);

        Queen(const Queen&) = delete;

        Queen(Queen&&) = delete;

        Queen& operator=(const Queen&) = delete;

        Queen& operator=(Queen&&) =delete;

        ~Queen();

        std::vector<BoardPosition> getPosibleNewPosition() override;

        FigureType getFigureType() override { return FigureType::QUEEN; };
        
        void updatePosiblePosition() override;
    };
}