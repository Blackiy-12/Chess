#pragma once

#include "../Figure.h"

namespace Chess
{
    class Pawn : public Figure
    {
    public:
        Pawn(BoardPosition StartPosition, TeamColor Color, Board* BoardPtr);

        Pawn(const Pawn&) = delete;

        Pawn(Pawn&&) = delete;

        Pawn& operator=(const Pawn&) = delete;

        Pawn& operator=(Pawn&&) =delete;

        ~Pawn();
        
        void setNewPosition(BoardPosition NewPosition);

        std::vector<BoardPosition> getPosibleNewPosition() override;

        FigureType getFigureType() override { return FigureType::PAWN; };

        void updatePosiblePosition() override;

        bool wasLastMoveLong() override;
    private:

        bool DontMove = true;

        bool FirstLongMove = false;

        bool Protection = false;
    };
}