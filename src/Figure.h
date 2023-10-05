#pragma once

#include <cinttypes>
#include <vector>

namespace Chess
{
	class FigureRenderInfo;
	
	class Board;

	struct BoardPosition
	{
		std::uint8_t x;
		std::uint8_t y;

		BoardPosition(std::uint8_t x, std::uint8_t y) : x(x), y(y) {};

		bool isInBoard()
		{
			if (x > 8 || x < 1 || y < 1 || y > 8)
				return false;
			
			return true;
		}

		bool operator==(const BoardPosition& right)
		{
			return (this->x == right.x && this->y == right.y);
		}
	};

	enum class TeamColor
	{
		NONE,
		WHITE,
		BLACK
	};

	enum class FigureType
	{
		NONE,
		PAWN,
		BISHOP,
		KNIGHT,
		ROOK,
		QUEEN,
		KING
	};

	class Figure
	{
	public:
		Figure(BoardPosition StartPosition, TeamColor Color, Board* BoardPtr);

		Figure(const Figure&) = delete;
		
		Figure(Figure&&) = delete;
		
		Figure& operator=(const Figure&) = delete;

		Figure& operator=(Figure&&) = delete;

		virtual ~Figure() {};

		BoardPosition getPosition();

		TeamColor getColor() { return this->Color; };

		virtual void setNewPosition(BoardPosition NewPosition);

		virtual std::vector<BoardPosition> getPosibleNewPosition() = 0;

		virtual FigureType getFigureType() { return FigureType::NONE; };

		virtual void updatePosiblePosition() {};

		virtual bool wasLastMoveLong() { return false; };

		virtual bool isMoved() { return false; };

	protected:
		BoardPosition Position;

		TeamColor Color;

		FigureRenderInfo* RenderInfo;

		std::vector<BoardPosition> PosiblePosition;

		Board* BoardPtr;

	protected:
		void checkPosiblePosition(BoardPosition Position);
	};

}

