#include "Figure.h"

#include "Render/FigureRenderInfo.h"
#include "Render/RenderBuffer.h"
#include "BoardRepresantation.h"
#include "Board.h"

Chess::Figure::Figure(BoardPosition StartPosition, TeamColor Color, Board* BoardPtr)
	: Position(StartPosition), Color(Color), PosiblePosition(), BoardPtr(BoardPtr)
{
}

Chess::BoardPosition Chess::Figure::getPosition()
{
	return this->Position;
}

void Chess::Figure::setNewPosition(BoardPosition NewPosition)
{
	this->Position = NewPosition;
	
	RenderBuffer::getRenderBuffer()->RenderInfoMutex.lock();

	this->RenderInfo->setNewPosition(NewPosition);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.unlock();
}

void Chess::Figure::checkPosiblePosition(BoardPosition Position)
{
	auto BoardRep = this->BoardPtr->getBoardRepresantation();

	if (BoardRep.getColor(Position.x, Position.y) != this->Color)
	{
		auto TMPBoard = BoardRep;
		TMPBoard.setFigure(this->Position, TeamColor::NONE, FigureType::NONE);
		TMPBoard.setFigure(Position, this->Color, this->getFigureType());

		if (TMPBoard.isKingUnderAttack(this->Color) == false)
			this->PosiblePosition.push_back(Position);
	}
}
