#include "Rook.h"

#include "../Render/RenderBuffer.h"
#include "../Board.h"

Chess::Rook::Rook(BoardPosition StartPosition, TeamColor Color, Board* BoardPtr)
	: Figure(StartPosition, Color, BoardPtr)
{
	this->RenderInfo = new FigureRenderInfo(this->Position, this->Color, FigureType::ROOK);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.lock();

	RenderBuffer::getRenderBuffer()->drawFigure(this->RenderInfo);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.unlock();
}

Chess::Rook::~Rook()
{
	RenderBuffer::getRenderBuffer()->RenderInfoMutex.lock();

	RenderBuffer::getRenderBuffer()->stopDrawFigure(this->RenderInfo);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.unlock();

	delete RenderInfo;
}

std::vector<Chess::BoardPosition> Chess::Rook::getPosibleNewPosition()
{
    return this->PosiblePosition;
}

void Chess::Rook::setNewPosition(BoardPosition NewPosition)
{
	this->alreadyMoved = true;

	Figure::setNewPosition(NewPosition);
}

void Chess::Rook::updatePosiblePosition()
{
	this->PosiblePosition.clear();

	auto BoardRep = this->BoardPtr->getBoardRepresantation();

	BoardPosition New = this->Position;
	while (true)
	{
		New.x += 1;

		if (New.isInBoard() == false)
			break;

		auto CellColor = BoardRep.getColor(New.x, New.y);

		if (CellColor == this->Color)
			break;

		this->checkPosiblePosition(New);

		if (CellColor != this->Color && CellColor != TeamColor::NONE)
			break;
	}

	New = this->Position;
	while (true)
	{
		New.x -= 1;

		if (New.isInBoard() == false)
			break;

		auto CellColor = BoardRep.getColor(New.x, New.y);

		if (CellColor == this->Color)
			break;

		this->checkPosiblePosition(New);

		if (CellColor != this->Color && CellColor != TeamColor::NONE)
			break;
	}

	New = this->Position;
	while (true)
	{
		New.y += 1;

		if (New.isInBoard() == false)
			break;

		auto CellColor = BoardRep.getColor(New.x, New.y);

		if (CellColor == this->Color)
			break;

		this->checkPosiblePosition(New);

		if (CellColor != this->Color && CellColor != TeamColor::NONE)
			break;
	}

	New = this->Position;
	while (true)
	{
		New.y -= 1;

		if (New.isInBoard() == false)
			break;

		auto CellColor = BoardRep.getColor(New.x, New.y);

		if (CellColor == this->Color)
			break;

		this->checkPosiblePosition(New);

		if (CellColor != this->Color && CellColor != TeamColor::NONE)
			break;
	}
}
