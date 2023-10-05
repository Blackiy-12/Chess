#include "FigureCreator.h"

#include "Figures/Queen.h"
#include "Figures/Bishop.h"
#include "Figures/Knight.h"
#include "Figures/Rook.h"
#include "Figures/Pawn.h"


std::shared_ptr<Chess::Figure> Chess::FigureCreator::createFigure(BoardPosition Poisition, FigureType Type, TeamColor Color, Board* BoardPtr)
{
    switch (Type)
    {
    case Chess::FigureType::PAWN:
        return std::make_shared<Pawn>(Poisition, Color, BoardPtr);

    case Chess::FigureType::BISHOP:
        return std::make_shared<Bishop>(Poisition, Color, BoardPtr);

    case Chess::FigureType::KNIGHT:
        return std::make_shared<Knight>(Poisition, Color, BoardPtr);

    case Chess::FigureType::ROOK:
        return std::make_shared<Rook>(Poisition, Color, BoardPtr);

    case Chess::FigureType::QUEEN:
        return std::make_shared<Queen>(Poisition, Color, BoardPtr);

    case Chess::FigureType::KING:
        return std::make_shared<King>(Poisition, Color, BoardPtr);

    default:
        return nullptr;
    }
}

std::list<std::shared_ptr<Chess::Figure>> Chess::FigureCreator::setupStartForBlack(Board* BoardPtr)
{
    std::list<std::shared_ptr<Figure>> Blacks;

    setupBlackFigures(Blacks, BoardPtr);

    return Blacks;
}

std::list<std::shared_ptr<Chess::Figure>> Chess::FigureCreator::setupStartForWhite(Board* BoardPtr)
{
    std::list<std::shared_ptr<Figure>> Whites;

    setupWhiteFigures(Whites, BoardPtr);

    return Whites;
}

void Chess::FigureCreator::setupWhiteFigures(std::list<std::shared_ptr<Figure>>& Figures, Board* BoardPtr)
{
    Figures.push_back(std::make_shared<Queen>(BoardPosition{ 4 ,1 }, TeamColor::WHITE, BoardPtr));

    Figures.push_back(std::make_shared<Bishop>(BoardPosition{ 3 ,1 }, TeamColor::WHITE, BoardPtr));
    Figures.push_back(std::make_shared<Bishop>(BoardPosition{ 6 ,1 }, TeamColor::WHITE, BoardPtr));

    Figures.push_back(std::make_shared<Knight>(BoardPosition{ 2 ,1 }, TeamColor::WHITE, BoardPtr));
    Figures.push_back(std::make_shared<Knight>(BoardPosition{ 7 ,1 }, TeamColor::WHITE, BoardPtr));

    Figures.push_back(std::make_shared<Rook>(BoardPosition{ 1 ,1 }, TeamColor::WHITE, BoardPtr));
    Figures.push_back(std::make_shared<Rook>(BoardPosition{ 8 ,1 }, TeamColor::WHITE, BoardPtr));

    for (uint8_t i = 1; i <= 8; i++)
        Figures.push_back(std::make_shared<Pawn>(BoardPosition{ i ,2 }, TeamColor::WHITE, BoardPtr));

}

std::unique_ptr<Chess::King> Chess::FigureCreator::setupWhiteKing(Board* BoardPtr)
{
    return std::make_unique<King>(BoardPosition{ 5 ,1 }, TeamColor::WHITE, BoardPtr);
}

void Chess::FigureCreator::setupBlackFigures(std::list<std::shared_ptr<Figure>>& Figures, Board* BoardPtr)
{
    Figures.push_back(std::make_shared<Queen>(BoardPosition{ 4 ,8 }, TeamColor::BLACK, BoardPtr));

    Figures.push_back(std::make_shared<Bishop>(BoardPosition{ 3 ,8 }, TeamColor::BLACK, BoardPtr));
    Figures.push_back(std::make_shared<Bishop>(BoardPosition{ 6 ,8 }, TeamColor::BLACK, BoardPtr));

    Figures.push_back(std::make_shared<Knight>(BoardPosition{ 2 ,8 }, TeamColor::BLACK, BoardPtr));
    Figures.push_back(std::make_shared<Knight>(BoardPosition{ 7 ,8 }, TeamColor::BLACK, BoardPtr));

    Figures.push_back(std::make_shared<Rook>(BoardPosition{ 1 ,8 }, TeamColor::BLACK, BoardPtr));
    Figures.push_back(std::make_shared<Rook>(BoardPosition{ 8 ,8 }, TeamColor::BLACK, BoardPtr));

    for (uint8_t i = 1; i <= 8; i++)
        Figures.push_back(std::make_shared<Pawn>(BoardPosition{ i, 7 }, TeamColor::BLACK, BoardPtr));

}

std::unique_ptr<Chess::King> Chess::FigureCreator::setupBlackKing(Board* BoardPtr)
{
    return std::make_unique<King>(BoardPosition{ 5, 8 }, TeamColor::BLACK, BoardPtr);
}
