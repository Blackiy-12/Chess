#include "Knight.h"

#include "../Render/RenderBuffer.h"

Chess::Knight::Knight(BoardPosition StartPosition, TeamColor Color, Board* BoardPtr)
	: Figure(StartPosition, Color, BoardPtr)
{
	this->RenderInfo = new FigureRenderInfo(this->Position, this->Color, FigureType::KNIGHT);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.lock();

	RenderBuffer::getRenderBuffer()->drawFigure(this->RenderInfo);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.unlock();
}

Chess::Knight::~Knight()
{
	RenderBuffer::getRenderBuffer()->RenderInfoMutex.lock();

	RenderBuffer::getRenderBuffer()->stopDrawFigure(this->RenderInfo);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.unlock();

	delete RenderInfo;
}

std::vector<Chess::BoardPosition> Chess::Knight::getPosibleNewPosition()
{
	return this->PosiblePosition;
}

void Chess::Knight::updatePosiblePosition()
{
	this->PosiblePosition.clear();

	BoardPosition New = { static_cast<uint8_t>(this->Position.x - 2), static_cast<uint8_t>(this->Position.y + 1) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);

	New = { static_cast<uint8_t>(this->Position.x - 2), static_cast<uint8_t>(this->Position.y - 1) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);

	New = { static_cast<uint8_t>(this->Position.x + 2), static_cast<uint8_t>(this->Position.y - 1) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);

	New = { static_cast<uint8_t>(this->Position.x + 2), static_cast<uint8_t>(this->Position.y + 1) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);

	New = { static_cast<uint8_t>(this->Position.x - 1), static_cast<uint8_t>(this->Position.y + 2) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);

	New = { static_cast<uint8_t>(this->Position.x + 1), static_cast<uint8_t>(this->Position.y + 2) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);

	New = { static_cast<uint8_t>(this->Position.x - 1), static_cast<uint8_t>(this->Position.y - 2) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);

	New = { static_cast<uint8_t>(this->Position.x + 1), static_cast<uint8_t>(this->Position.y - 2) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);
}
