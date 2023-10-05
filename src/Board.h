#pragma once

#include "Team.h"
#include "BoardRepresantation.h"

namespace Chess
{
	struct SwapPawn
	{
		BoardPosition Position;

		TeamColor Color;
	};

	class Board
	{
	public:
		Board();

		~Board();
		
		bool needToSwapPawn();

		void pressPosition(BoardPosition Position);
		
		void pressSwapPosition(FigureType NewFigure);

		void unselectFigure();

		ByteBoard getBoardRepresantation();

		void swapPawn(BoardPosition Position, TeamColor Color, BoardPosition NewPosition);

		void moveRookForCasttleing(BoardPosition RookPosition, BoardPosition NewPosition);

	private:
		Team White;

		Team Black;

		Figure* SelectedFigure = nullptr;

		ByteBoard BoardRepresantation;

		TeamColor CurrentTurn = TeamColor::WHITE;

		bool Mate = false;

		SwapPawn* PawnToSwap;

		bool LockSwap = false;

	private:
		void selectFigure(BoardPosition Position);
		
		void updatePosiblePosition();

		void updateBoardRepresantation();

		void updateFigures();

		void moveOrAtact(BoardPosition NewPos, TeamColor ColorOfFigure);

		void swapTeam();

		void checkMate();

	};
}