#pragma once

#include "FigureRenderInfo.h"

#include <mutex>
#include <list>

namespace Chess
{
	class RenderBuffer
	{
	public:
		std::mutex RenderInfoMutex;

	public:
		static RenderBuffer* getRenderBuffer();

		void drawBoard();

		void stopDrawingBoard();

		void drawFigure(FigureRenderInfo* Figure);

		void stopDrawFigure(FigureRenderInfo* Figure);

		void setupPosiblePosition(std::vector<BoardPosition> NewPosiblePosition);

		void drawSpawnPawn(TeamColor Color);

		void stopDrawSpawnPawn();

		void freePosiblePosition();

	private:
		static RenderBuffer* RenderBufferPtr;

		static std::mutex RenderBufferMutex;

		bool Board;

		std::list<FigureRenderInfo*> Figures;

		std::vector<BoardPosition> PosiblePosition;

		bool SwapPawn = false;

		TeamColor SwapPawnColor = TeamColor::NONE;

	private:
		RenderBuffer();

		RenderBuffer(const RenderBuffer&) = delete;

		RenderBuffer(RenderBuffer&&) = delete;

		RenderBuffer& operator=(const RenderBuffer&) = delete;

		RenderBuffer& operator=(RenderBuffer&&) = delete;

		friend class Render;
	};
}