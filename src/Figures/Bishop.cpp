#include "Bishop.h"

#include "../Render/RenderBuffer.h"
#include "../BoardRepresantation.h"
#include "../Board.h"

Chess::Bishop::Bishop(BoardPosition StartPosition, TeamColor Color, Board* BoardPtr)
	: Figure(StartPosition, Color, BoardPtr)
{
	this->RenderInfo = new FigureRenderInfo(this->Position, this->Color, FigureType::BISHOP);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.lock();

	RenderBuffer::getRenderBuffer()->drawFigure(this->RenderInfo);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.unlock();
}

Chess::Bishop::~Bishop()
{
	RenderBuffer::getRenderBuffer()->RenderInfoMutex.lock();

	RenderBuffer::getRenderBuffer()->stopDrawFigure(this->RenderInfo);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.unlock();

	delete RenderInfo;
}

std::vector<Chess::BoardPosition> Chess::Bishop::getPosibleNewPosition()
{
	return this->PosiblePosition;
}

void Chess::Bishop::updatePosiblePosition()
{
	this->PosiblePosition.clear();

	ByteBoard BoardRep = this->BoardPtr->getBoardRepresantation();

	BoardPosition New = this->Position;
	while (true)
	{
		New.x += 1;
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
		New.x -= 1;
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
		New.x += 1;
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

	New = this->Position;
	while (true)
	{
		New.x -= 1;
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
