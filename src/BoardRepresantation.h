#pragma once 

#include <array>
#include "Render/FigureRenderInfo.h"

namespace Chess
{

	class ByteBoard
	{
	public:
		ByteBoard();

		~ByteBoard() {};

		void setFigure(BoardPosition Position, TeamColor Team, FigureType Figure, bool LastWasLongMove = false, bool isMoved = false);

		TeamColor getColor(int x, int y);

		FigureType getFigure(int x, int y);

		bool wasLastMoveLong(int x, int y);

		bool isKingUnderAttack(TeamColor KingTeam);

		bool isAlredyMove(int x, int y);

		void free();

	private:
		std::array<int8_t, 64> Figures;

	private:
		BoardPosition findKing(TeamColor Team);

		bool checkPawnAttack(BoardPosition KingPosition, TeamColor Team);

		bool checkBishopAttack(BoardPosition KingPosition, TeamColor Team);

		bool checkRookAttack(BoardPosition KingPosition, TeamColor Team);

		bool checkKnightAttack(BoardPosition KingPosition, TeamColor Team);
	};
}