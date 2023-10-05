#pragma once

#include "../Figure.h"

namespace Chess
{
    class King : public Figure
    {
    public:
        King(BoardPosition StartPosition, TeamColor Color, Board* BoardPtr);

        King(const King&) = delete;

        King(King&&) = delete;

        King& operator=(const King&) = delete;

        King& operator=(King&&) =delete;

        ~King();

        std::vector<BoardPosition> getPosibleNewPosition() override;

        FigureType getFigureType() override { return FigureType::KING; };

        void updatePosiblePosition() override;

        void setNewPosition(BoardPosition NewPosition) override;

        bool isMoved() override { return this->alreadyMoved; };

    private:
        bool alreadyMoved = false;

    private:
        void checkCastling(BoardPosition RookPosition);
    };
}