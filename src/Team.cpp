#include "Team.h"

#include "FigureCreator.h"

Chess::Team::Team(TeamColor Color)
	: Color(Color)
{
}

Chess::Team::~Team()
{
}

void Chess::Team::setupFiguresForStart(Board* BoardPtr)
{
	switch (this->Color)
	{
	case TeamColor::BLACK:
		this->Figures = FigureCreator::setupStartForBlack(BoardPtr);
		this->TeamKing = FigureCreator::setupBlackKing(BoardPtr);
		break;

	case TeamColor::WHITE:
		this->Figures = FigureCreator::setupStartForWhite(BoardPtr);
		this->TeamKing = FigureCreator::setupWhiteKing(BoardPtr);
		break;
	}

}
