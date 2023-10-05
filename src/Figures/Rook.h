#pragma once

#include "../Figure.h"

namespace Chess
{
    class Rook : public Figure
    {
    public:
        Rook(BoardPosition StartPosition, TeamColor Color, Board* BoardPtr);

        Rook(const Rook&) = delete;

        Rook(Rook&&) = delete;

        Rook& operator=(const Rook&) = delete;

        Rook& operator=(Rook&&) =delete;

        ~Rook();

        std::vector<BoardPosition> getPosibleNewPosition() override;

        void setNewPosition(BoardPosition NewPosition) override;

        FigureType getFigureType() override { return FigureType::ROOK; };

        void updatePosiblePosition() override;

        bool isMoved() override { return this->alreadyMoved; } ;

    private:

        bool alreadyMoved = false;
    };
}