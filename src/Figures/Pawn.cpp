#include "Pawn.h"

#include "../Render/RenderBuffer.h"
#include "../BoardRepresantation.h"
#include "../Board.h"

Chess::Pawn::Pawn(BoardPosition StartPosition, TeamColor Color, Board* BoardPtr)
	: Figure(StartPosition, Color, BoardPtr)
{
	this->RenderInfo = new FigureRenderInfo(this->Position, this->Color, FigureType::PAWN);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.lock();

	RenderBuffer::getRenderBuffer()->drawFigure(this->RenderInfo);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.unlock();
}

Chess::Pawn::~Pawn()
{
	RenderBuffer::getRenderBuffer()->RenderInfoMutex.lock();

	RenderBuffer::getRenderBuffer()->stopDrawFigure(this->RenderInfo);

	RenderBuffer::getRenderBuffer()->RenderInfoMutex.unlock();

	delete RenderInfo;
}

void Chess::Pawn::setNewPosition(BoardPosition NewPosition)
{
	this->DontMove = false;

	if (std::abs(this->Position.y - NewPosition.y) == 2)
	{
		this->FirstLongMove = true;
		this->Protection = true;
	}


	if (NewPosition.y == 1 || NewPosition.y == 8)
	{
		BoardPtr->swapPawn(this->Position, this->Color, NewPosition);
	}
	else
		Figure::setNewPosition(NewPosition);
}

std::vector<Chess::BoardPosition> Chess::Pawn::getPosibleNewPosition()
{
	return this->PosiblePosition;
}

void Chess::Pawn::updatePosiblePosition()
{
	if (Protection == true)
		this->Protection = false;
	else
		this->FirstLongMove = false;

	this->PosiblePosition.clear();

	ByteBoard BoadrRep = this->BoardPtr->getBoardRepresantation();

	BoardPosition New = { 0, 0 };


	if (this->Color == TeamColor::BLACK)
	{
		New = { static_cast<uint8_t>(this->Position.x), static_cast<uint8_t>(this->Position.y - 1) };
		if (New.isInBoard())
			if (BoadrRep.getColor(New.x, New.y) == TeamColor::NONE)
				this->checkPosiblePosition(New);
	}
	else
	{
		New = { static_cast<uint8_t>(this->Position.x), static_cast<uint8_t>(this->Position.y + 1) };

		if (New.isInBoard())
			if (BoadrRep.getColor(New.x, New.y) == TeamColor::NONE)
				this->checkPosiblePosition(New);
	}

	if (this->Color == TeamColor::BLACK)
	{
		New = { static_cast<uint8_t>(this->Position.x + 1), static_cast<uint8_t>(this->Position.y - 1) };

		if (New.isInBoard())
			if (BoadrRep.getColor(New.x, New.y) == TeamColor::WHITE)
				this->checkPosiblePosition(New);
	}
	else
	{
		New = { static_cast<uint8_t>(this->Position.x + 1), static_cast<uint8_t>(this->Position.y + 1) };

		if (New.isInBoard())
			if (BoadrRep.getColor(New.x, New.y) == TeamColor::BLACK)
				this->checkPosiblePosition(New);
	}

	if (this->Color == TeamColor::BLACK)
	{
		New = { static_cast<uint8_t>(this->Position.x - 1), static_cast<uint8_t>(this->Position.y - 1) };

		if (New.isInBoard())
			if (BoadrRep.getColor(New.x, New.y) == TeamColor::WHITE)
				this->checkPosiblePosition(New);
	}
	else
	{
		New = { static_cast<uint8_t>(this->Position.x - 1), static_cast<uint8_t>(this->Position.y + 1) };

		if (New.isInBoard())
			if (BoadrRep.getColor(New.x, New.y) == TeamColor::BLACK)
				this->checkPosiblePosition(New);
	}

	if (this->DontMove == true)
	{
		auto Prev = this->Position;
		if (this->Color == TeamColor::BLACK)
		{
			Prev = { static_cast<uint8_t>(this->Position.x), static_cast<uint8_t>(this->Position.y - 1) };
			New = { static_cast<uint8_t>(this->Position.x), static_cast<uint8_t>(this->Position.y - 2) };
		}
		else
		{
			Prev = { static_cast<uint8_t>(this->Position.x), static_cast<uint8_t>(this->Position.y + 1) };
			New = { static_cast<uint8_t>(this->Position.x), static_cast<uint8_t>(this->Position.y + 2) };
		}

		if (BoadrRep.getColor(Prev.x, Prev.y) == TeamColor::NONE && BoadrRep.getColor(New.x, New.y) == TeamColor::NONE)
		{
			this->checkPosiblePosition(New);
		}

	}
	

	New = { static_cast<uint8_t>(this->Position.x + 1), static_cast<uint8_t>(this->Position.y) };

	if (New.isInBoard())
	{
		if (BoadrRep.getFigure(New.x, New.y) == FigureType::PAWN)
		{
			auto Color = BoadrRep.getColor(New.x, New.y);
			if (Color != TeamColor::NONE && Color != this->Color)
			{
				if (BoadrRep.wasLastMoveLong(New.x, New.y) == true)
				{
					if (this->Color == TeamColor::BLACK)
						New.y -= 1;
					else
						New.y += 1;

					this->checkPosiblePosition(New);
				}
			}
		}
	}

	New = { static_cast<uint8_t>(this->Position.x - 1), static_cast<uint8_t>(this->Position.y) };

	if (New.isInBoard())
	{
		if (BoadrRep.getFigure(New.x, New.y) == FigureType::PAWN)
		{
			auto Color = BoadrRep.getColor(New.x, New.y);
			if (Color != TeamColor::NONE && Color != this->Color)
			{
				if (BoadrRep.wasLastMoveLong(New.x, New.y) == true)
				{
					if (this->Color == TeamColor::BLACK)
						New.y -= 1;
					else
						New.y += 1;

					this->checkPosiblePosition(New);
				}
			}
		}
	}
}

bool Chess::Pawn::wasLastMoveLong()
{
	return this->FirstLongMove;
}
