#include "RenderBuffer.h"

Chess::RenderBuffer* Chess::RenderBuffer::RenderBufferPtr = nullptr;

std::mutex Chess::RenderBuffer::RenderBufferMutex;

Chess::RenderBuffer* Chess::RenderBuffer::getRenderBuffer()
{
	std::lock_guard<std::mutex> lock(RenderBufferMutex);

	if (RenderBuffer::RenderBufferPtr == nullptr)
	{
		RenderBuffer::RenderBufferPtr = new RenderBuffer();
	}

	return RenderBuffer::RenderBufferPtr;
}

void Chess::RenderBuffer::drawBoard()
{
	this->Board = true;
}

void Chess::RenderBuffer::stopDrawingBoard()
{
	this->Board = false;
}

void Chess::RenderBuffer::drawFigure(FigureRenderInfo* Figure)
{
	this->Figures.push_back(Figure);
}

void Chess::RenderBuffer::stopDrawFigure(FigureRenderInfo* Figure)
{
	this->Figures.remove(Figure);
}

void Chess::RenderBuffer::setupPosiblePosition(std::vector<BoardPosition> NewPosiblePosition)
{
	this->PosiblePosition = NewPosiblePosition;
}

void Chess::RenderBuffer::drawSpawnPawn(TeamColor Color)
{
	this->SwapPawn = true;
	this->SwapPawnColor = Color;
}

void Chess::RenderBuffer::stopDrawSpawnPawn()
{
	this->SwapPawn = false;
	this->SwapPawnColor = TeamColor::NONE;
}

void Chess::RenderBuffer::freePosiblePosition()
{
	this->PosiblePosition.clear();
}

Chess::RenderBuffer::RenderBuffer()
	: Board(true), Figures(), PosiblePosition(), RenderInfoMutex()
{
}
