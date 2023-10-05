#pragma once

#include "Figure.h"
#include "Figures/King.h"

#include <list>
#include <memory>

namespace Chess
{
    class Board;

    class FigureCreator
    {
    public:
        static std::shared_ptr<Figure> createFigure(BoardPosition Poisition, FigureType Type, TeamColor Color, Board* BoardPtr);
        
        static std::list<std::shared_ptr<Figure>> setupStartForBlack(Board* BoardPtr);

        static std::list<std::shared_ptr<Figure>> setupStartForWhite(Board* BoardPtr);

        static std::unique_ptr<King> setupWhiteKing(Board* BoardPtr);
        
        static std::unique_ptr<King> setupBlackKing(Board* BoardPtr);

    private:
        static void setupWhiteFigures(std::list<std::shared_ptr<Figure>>& Figures, Board* BoardPtr);

        static void setupBlackFigures(std::list<std::shared_ptr<Figure>>& Figures, Board* BoardPtr);
    };
}

