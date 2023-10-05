#include "BoardRepresantation.h"

Chess::ByteBoard::ByteBoard()
{
	Figures.fill(0x00);
}

const int8_t PAWN_MASK   = 1;
const int8_t BISHOP_MASK = 2;
const int8_t KNIGHT_MASK = 4;
const int8_t ROOK_MASK   = 8;
const int8_t QUEEN_MASK  = 16;
const int8_t KING_MASK   = 32;

void Chess::ByteBoard::setFigure(BoardPosition Position, TeamColor Team, FigureType Figure, bool LastWasLongMove, bool isMoved)
{
	int8_t NewValue = 0x00;

	if (Team != TeamColor::NONE)
	{
		if (Team == TeamColor::WHITE)
			NewValue = 1 << 7;

		if (LastWasLongMove == true || isMoved == true)
			NewValue += 1 << 6;

		switch (Figure)
		{
		case Chess::FigureType::PAWN:
			NewValue |= PAWN_MASK;
			break;
		case Chess::FigureType::BISHOP:
			NewValue |= BISHOP_MASK;
			break;
		case Chess::FigureType::KNIGHT:
			NewValue |= KNIGHT_MASK;
			break;
		case Chess::FigureType::ROOK:
			NewValue |= ROOK_MASK;
			break;
		case Chess::FigureType::QUEEN:
			NewValue |= QUEEN_MASK;
			break;
		case Chess::FigureType::KING:
			NewValue |= KING_MASK;
			break;
		default:
			break;
		}
	}

	this->Figures[(Position.x - 1) + ((Position.y - 1) * 8)] = NewValue;

}

Chess::TeamColor Chess::ByteBoard::getColor(int x, int y)
{
	auto Figure = this->Figures[(x - 1) + ((y - 1) * 8)];

	if (Figure == 0)
		return TeamColor::NONE;

	if (Figure & 1 << 7) 
		return TeamColor::WHITE;
	else
		return TeamColor::BLACK;

}

Chess::FigureType Chess::ByteBoard::getFigure(int x, int y)
{
	auto Figure = this->Figures[(x - 1) + ((y - 1) * 8)];

	if (Figure == 0)
		return FigureType::NONE;

	auto TMP = Figure & 0b00111111;

	switch (TMP)
	{
	case PAWN_MASK:
		return FigureType::PAWN;

	case QUEEN_MASK:
		return FigureType::QUEEN;
	
	case KING_MASK:
		return FigureType::KING;
	
	case KNIGHT_MASK:
		return FigureType::KNIGHT;
	
	case BISHOP_MASK:
		return FigureType::BISHOP;
	
	case ROOK_MASK:
		return FigureType::ROOK;
	default:
		break;
	}

	return FigureType::NONE;
}

bool Chess::ByteBoard::wasLastMoveLong(int x, int y)
{
	auto Figure = this->Figures[(x - 1) + ((y - 1) * 8)];

	auto TMP = Figure & 0b01000000;

	if (TMP)
		return true;
	
	return false;
}

bool Chess::ByteBoard::isKingUnderAttack(TeamColor KingTeam)
{
	BoardPosition KingPoisiotn = this->findKing(KingTeam);

	return checkBishopAttack(KingPoisiotn, KingTeam) || checkKnightAttack(KingPoisiotn, KingTeam)
		|| checkRookAttack(KingPoisiotn, KingTeam) || checkPawnAttack(KingPoisiotn, KingTeam);
}

bool Chess::ByteBoard::isAlredyMove(int x, int y)
{
	auto Figure = this->Figures[(x - 1) + ((y - 1) * 8)];

	auto TMP = Figure & 0b01000000;

	if (TMP)
		return true;

	return false;
}

void Chess::ByteBoard::free()
{
	Figures.fill(0x00);
}

Chess::BoardPosition Chess::ByteBoard::findKing(TeamColor Team)
{
	int8_t Ref = KING_MASK;
	if (Team == TeamColor::WHITE)
		Ref = KING_MASK | 1 << 7;
	
	for (int i = 0; i < this->Figures.size(); i++)
	{
		if (Figures[i] == Ref)
			return BoardPosition{static_cast<uint8_t>((i % 8) + 1), static_cast<uint8_t>((i / 8) + 1)};
	}	

	return BoardPosition{ static_cast<uint8_t>(-1), static_cast<uint8_t>(-1)};
}

bool Chess::ByteBoard::checkPawnAttack(BoardPosition KingPosition, TeamColor Team)
{
	BoardPosition TMP = KingPosition;

	if (Team == TeamColor::BLACK)
	{
		TMP.x = KingPosition.x - 1;
		TMP.y = KingPosition.y - 1;

		if (TMP.isInBoard())
		{
			if (this->getColor(TMP.x, TMP.y) != Team)
			{
				if (this->getFigure(TMP.x, TMP.y) == FigureType::PAWN)
					return true;
			}
		}

		TMP.x = KingPosition.x + 1;
		TMP.y = KingPosition.y - 1;

		if (TMP.isInBoard())
		{
			if (this->getColor(TMP.x, TMP.y) != Team)
			{
				if (this->getFigure(TMP.x, TMP.y) == FigureType::PAWN)
					return true;
			}
		}
	}
	else
	{
		TMP.x = KingPosition.x - 1;
		TMP.y = KingPosition.y + 1;

		if (TMP.isInBoard())
		{
			if (this->getColor(TMP.x, TMP.y) != Team)
			{
				if (this->getFigure(TMP.x, TMP.y) == FigureType::PAWN)
					return true;
			}
		}


		TMP.x = KingPosition.x + 1;
		TMP.y = KingPosition.y + 1;

		if (TMP.isInBoard())
		{
			if (this->getColor(TMP.x, TMP.y) != Team)
			{
				if (this->getFigure(TMP.x, TMP.y) == FigureType::PAWN)
					return true;
			}
		}
	}

	return false;
}

bool Chess::ByteBoard::checkBishopAttack(BoardPosition KingPosition, TeamColor Team)
{
	BoardPosition TMP = KingPosition;

	while (true)
	{
		TMP.x = TMP.x + 1;
		TMP.y = TMP.y + 1;

		if (TMP.isInBoard() == false)
			break;

		if (this->getColor(TMP.x, TMP.y) == TeamColor::NONE)
			continue;

		if (this->getColor(TMP.x, TMP.y) == Team)
			break;

		if (this->getFigure(TMP.x, TMP.y) == FigureType::BISHOP || this->getFigure(TMP.x, TMP.y) == FigureType::QUEEN)
			return true;

		break;
	}

	TMP = KingPosition;
	while (true)
	{
		TMP.x = TMP.x - 1;
		TMP.y = TMP.y + 1;

		if (TMP.isInBoard() == false)
			break;

		if (this->getColor(TMP.x, TMP.y) == TeamColor::NONE)
			continue;

		if (this->getColor(TMP.x, TMP.y) == Team)
			break;

		if (this->getFigure(TMP.x, TMP.y) == FigureType::BISHOP || this->getFigure(TMP.x, TMP.y) == FigureType::QUEEN)
			return true;

		break;
	}

	TMP = KingPosition;

	while (true)
	{
		TMP.x = TMP.x + 1;
		TMP.y = TMP.y - 1;

		if (TMP.isInBoard() == false)
			break;

		if (this->getColor(TMP.x, TMP.y) == TeamColor::NONE)
			continue;

		if (this->getColor(TMP.x, TMP.y) == Team)
			break;

		if (this->getFigure(TMP.x, TMP.y) == FigureType::BISHOP || this->getFigure(TMP.x, TMP.y) == FigureType::QUEEN)
			return true;

		break;
	}

	TMP = KingPosition;

	while (true)
	{
		TMP.x = TMP.x - 1;
		TMP.y = TMP.y - 1;

		if (TMP.isInBoard() == false)
			break;

		if (this->getColor(TMP.x, TMP.y) == TeamColor::NONE)
			continue;

		if (this->getColor(TMP.x, TMP.y) == Team)
			break;

		if (this->getFigure(TMP.x, TMP.y) == FigureType::BISHOP || this->getFigure(TMP.x, TMP.y) == FigureType::QUEEN)
			return true;

		break;
	}

	return false;
}

bool Chess::ByteBoard::checkRookAttack(BoardPosition KingPosition, TeamColor Team)
{
	BoardPosition TMP = KingPosition;

	while (true)
	{
		TMP.x = TMP.x + 1;

		if (TMP.isInBoard() == false)
			break;

		if (this->getColor(TMP.x, TMP.y) == TeamColor::NONE)
			continue;

		if (this->getColor(TMP.x, TMP.y) == Team)
			break;

		if (this->getFigure(TMP.x, TMP.y) == FigureType::BISHOP || this->getFigure(TMP.x, TMP.y) == FigureType::QUEEN)
			return true;

		break;
	}

	TMP = KingPosition;

	while (true)
	{
		TMP.x = TMP.x - 1;

		if (TMP.isInBoard() == false)
			break;

		if (this->getColor(TMP.x, TMP.y) == TeamColor::NONE)
			continue;

		if (this->getColor(TMP.x, TMP.y) == Team)
			break;

		if (this->getFigure(TMP.x, TMP.y) == FigureType::BISHOP || this->getFigure(TMP.x, TMP.y) == FigureType::QUEEN)
			return true;

		break;
	}

	TMP = KingPosition;

	while (true)
	{
		TMP.y = TMP.y + 1;

		if (TMP.isInBoard() == false)
			break;

		if (this->getColor(TMP.x, TMP.y) == TeamColor::NONE)
			continue;

		if (this->getColor(TMP.x, TMP.y) == Team)
			break;

		if (this->getFigure(TMP.x, TMP.y) == FigureType::BISHOP || this->getFigure(TMP.x, TMP.y) == FigureType::QUEEN)
			return true;

		break;
	}

	TMP = KingPosition;

	while (true)
	{
		TMP.y = TMP.y - 1;

		if (TMP.isInBoard() == false)
			break;

		if (this->getColor(TMP.x, TMP.y) == TeamColor::NONE)
			continue;

		if (this->getColor(TMP.x, TMP.y) == Team)
			break;

		if (this->getFigure(TMP.x, TMP.y) == FigureType::BISHOP || this->getFigure(TMP.x, TMP.y) == FigureType::QUEEN)
			return true;

		break;
	}

	return false;
}

bool Chess::ByteBoard::checkKnightAttack(BoardPosition KingPosition, TeamColor Team)
{
	BoardPosition TMP = KingPosition;

	TMP.x += 2;
	TMP.y += 1;

	if (TMP.isInBoard())
	{
		if (this->getFigure(TMP.x, TMP.y) == FigureType::KNIGHT)
		{
			if (this->getColor(TMP.x, TMP.y) != Team)
				return true;
		}
	}

	TMP = KingPosition;

	TMP.x += 2;
	TMP.y -= 1;

	if (TMP.isInBoard())
	{
		if (this->getFigure(TMP.x, TMP.y) == FigureType::KNIGHT)
		{
			if (this->getColor(TMP.x, TMP.y) != Team)
				return true;
		}
	}

	TMP = KingPosition;

	TMP.x -= 2;
	TMP.y += 1;

	if (TMP.isInBoard())
	{
		if (this->getFigure(TMP.x, TMP.y) == FigureType::KNIGHT)
		{
			if (this->getColor(TMP.x, TMP.y) != Team)
				return true;
		}
	}

	TMP = KingPosition;

	TMP.x -= 2;
	TMP.y -= 1;

	if (TMP.isInBoard())
	{
		if (this->getFigure(TMP.x, TMP.y) == FigureType::KNIGHT)
		{
			if (this->getColor(TMP.x, TMP.y) != Team)
				return true;
		}
	}

	TMP = KingPosition;

	TMP.x += 1;
	TMP.y += 2;

	if (TMP.isInBoard())
	{
		if (this->getFigure(TMP.x, TMP.y) == FigureType::KNIGHT)
		{
			if (this->getColor(TMP.x, TMP.y) != Team)
				return true;
		}
	}

	TMP = KingPosition;

	TMP.x -= 1;
	TMP.y += 2;

	if (TMP.isInBoard())
	{
		if (this->getFigure(TMP.x, TMP.y) == FigureType::KNIGHT)
		{
			if (this->getColor(TMP.x, TMP.y) != Team)
				return true;
		}
	}

	TMP = KingPosition;

	TMP.x += 1;
	TMP.y -= 2;

	if (TMP.isInBoard())
	{
		if (this->getFigure(TMP.x, TMP.y) == FigureType::KNIGHT)
		{
			if (this->getColor(TMP.x, TMP.y) != Team)
				return true;
		}
	}

	TMP = KingPosition;

	TMP.x -= 1;
	TMP.y -= 2;

	if (TMP.isInBoard())
	{
		if (this->getFigure(TMP.x, TMP.y) == FigureType::KNIGHT)
		{
			if (this->getColor(TMP.x, TMP.y) != Team)
				return true;
		}
	}

	return false;
}
