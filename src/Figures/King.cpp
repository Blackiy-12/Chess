#include "King.h"

#include "../Render/RenderBuffer.h"
#include "../Board.h"
#include "BoardRepresantation.h"

Chess::King::King(BoardPosition StartPosition, TeamColor Color, Board* BoardPtr)
	: Figure(StartPosition, Color, BoardPtr)
{
	this->RenderInfo = new FigureRenderInfo(this->Position, this->Color, FigureType::KING);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.lock();

	RenderBuffer::getRenderBuffer()->drawFigure(this->RenderInfo);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.unlock();
}

Chess::King::~King()
{
	RenderBuffer::getRenderBuffer()->RenderInfoMutex.lock();

	RenderBuffer::getRenderBuffer()->stopDrawFigure(this->RenderInfo);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.unlock();

	delete RenderInfo;
}

std::vector<Chess::BoardPosition> Chess::King::getPosibleNewPosition()
{
	return this->PosiblePosition;
}

void Chess::King::updatePosiblePosition()
{
	this->PosiblePosition.clear();

	BoardPosition New = { static_cast<uint8_t>(this->Position.x - 1), static_cast<uint8_t>(this->Position.y + 1) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);

	New = { static_cast<uint8_t>(this->Position.x), static_cast<uint8_t>(this->Position.y + 1) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);

	New = { static_cast<uint8_t>(this->Position.x + 1), static_cast<uint8_t>(this->Position.y + 1) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);

	New = { static_cast<uint8_t>(this->Position.x - 1), static_cast<uint8_t>(this->Position.y) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);

	New = { static_cast<uint8_t>(this->Position.x + 1), static_cast<uint8_t>(this->Position.y) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);

	New = { static_cast<uint8_t>(this->Position.x - 1), static_cast<uint8_t>(this->Position.y - 1) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);

	New = { static_cast<uint8_t>(this->Position.x), static_cast<uint8_t>(this->Position.y - 1) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);

	New = { static_cast<uint8_t>(this->Position.x + 1), static_cast<uint8_t>(this->Position.y - 1) };

	if (New.isInBoard())
		this->checkPosiblePosition(New);


	if (this->alreadyMoved == true)
		return;

	//Castling
	ByteBoard BoardRep = this->BoardPtr->getBoardRepresantation();

	if (BoardRep.isKingUnderAttack(this->Color) == true)
		return;
	
	if (BoardRep.getFigure(8, this->Position.y) == FigureType::ROOK)
	{
		if (BoardRep.getColor(8, this->Position.y) == this->Color)
		{
			if (BoardRep.isAlredyMove(8, this->Position.y) == false)
			{
				this->checkCastling(BoardPosition{8, this->Position.y});
			}
		}
	}

	if (BoardRep.getFigure(1, this->Position.y) == FigureType::ROOK)
	{
		if (BoardRep.getColor(1, this->Position.y) == this->Color)
		{
			if (BoardRep.isAlredyMove(1, this->Position.y) == false)
			{
				this->checkCastling(BoardPosition{ 1, this->Position.y });
			}
		}
	}
	
}

void Chess::King::setNewPosition(BoardPosition NewPosition)
{
	this->alreadyMoved = true;

	if (std::abs(NewPosition.x - Position.x) > 1)
	{
		BoardPosition RookPos = NewPosition;
		BoardPosition NewRookPos = NewPosition;
		if ((NewPosition.x - Position.x) > 0)
		{
			RookPos.x = 8;
			NewRookPos.x = Position.x + 1;
		}
		else
		{
			RookPos.x = 1;
			NewRookPos.x = Position.x - 1;
		}

		this->BoardPtr->moveRookForCasttleing(RookPos, NewRookPos);
	}

	Figure::setNewPosition(NewPosition);
}

void Chess::King::checkCastling(BoardPosition RookPosition)
{
	auto BoardRep = this->BoardPtr->getBoardRepresantation();

	BoardPosition NewKingPos = this->Position;
	
	int Dest = ((RookPosition.x- NewKingPos.x) / std::abs(RookPosition.x - NewKingPos.x));

	for (int x = Position.x + Dest; x != RookPosition.x; x += Dest)
	{
		if (BoardRep.getFigure(x, Position.y) != FigureType::NONE)
			return;
	}

	NewKingPos.x += 2 * Dest;

	auto NewRookPos = RookPosition;

	RookPosition.x = this->Position.x + Dest;

	BoardRep.setFigure(this->Position, TeamColor::NONE, FigureType::NONE);
	BoardRep.setFigure(RookPosition, TeamColor::NONE, FigureType::NONE);
	BoardRep.setFigure(NewKingPos, this->Color, this->getFigureType());
	BoardRep.setFigure(NewRookPos, this->Color, FigureType::ROOK);

	if (BoardRep.isKingUnderAttack(this->Color) == false)
		this->PosiblePosition.push_back(NewKingPos);
}

