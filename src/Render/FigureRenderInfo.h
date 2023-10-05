#pragma once 

#include "../Figure.h"

namespace Chess
{
	class FigureRenderInfo
	{
	public:
		FigureRenderInfo(BoardPosition Position, TeamColor Team, FigureType Type)
			: Position(Position), Team(Team), Type(Type) {};

		~FigureRenderInfo() {};

		void setNewPosition(BoardPosition NewPosition) { this->Position = NewPosition; };

		BoardPosition getPosition() { return this->Position; };

		TeamColor getTeam() { return this->Team; };

		FigureType getType() { return this->Type; };

	private:
		BoardPosition Position;

		TeamColor Team;

		FigureType Type;		
	};
}