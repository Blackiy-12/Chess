#pragma once

#include "../Figure.h"

namespace Chess
{
    class Bishop : public Figure
    {
    public:
        Bishop(BoardPosition StartPosition, TeamColor Color, Board* BoardPtr);

        Bishop(const Bishop&) = delete;

        Bishop(Bishop&&) = delete;

        Bishop& operator=(const Bishop&) = delete;

        Bishop& operator=(Bishop&&) =delete;

        ~Bishop();

        std::vector<BoardPosition> getPosibleNewPosition() override;

        FigureType getFigureType() override { return FigureType::BISHOP; };

        void updatePosiblePosition() override;
    };
}