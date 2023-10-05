#include "Render.h"

#include "RenderBuffer.h"

Chess::Render::Render()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	this->Window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);

	this->Renderer = SDL_CreateRenderer(this->Window, -1, SDL_RENDERER_SOFTWARE);
	
	this->Textures = new TextureHolder();

	this->Textures->loadTextures(this->Renderer);
}

Chess::Render::~Render()
{
	SDL_DestroyWindow(this->Window);

	SDL_DestroyRenderer(this->Renderer);

	SDL_Quit();
}

void Chess::Render::startRenderThread()
{
	this->RenderThread = std::thread(&Render::render, this);
}

void Chess::Render::stopRender()
{
	this->RunnigRender = false;
}

void Chess::Render::render()
{
	while (this->RunnigRender)
	{
		auto Bufffer = RenderBuffer::getRenderBuffer();	

		std::unique_lock<std::mutex> lck(RenderBuffer::getRenderBuffer()->RenderInfoMutex);

		this->RenderNextFrame.wait(lck);

		this->RenderFinished = false;

		SDL_SetRenderDrawColor(this->Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		
		SDL_RenderClear(this->Renderer);
		
		this->renderBoard();

		this->renderPosiblePosition();

		this->renderFigures();

		this->renderSwapPawn();

		SDL_RenderPresent(this->Renderer);

		this->RenderFinished = true;

		this->RenderFinished.notify_one();
	}
}

void Chess::Render::renderBoard()
{
	if (RenderBuffer::getRenderBuffer()->Board == true)
		SDL_RenderCopy(this->Renderer, this->Textures->getBoardTexture(), NULL, NULL);
}

void Chess::Render::renderFigures()
{
	for (auto Figure : RenderBuffer::getRenderBuffer()->Figures)
	{
		auto Pos = this->getXYForFigure(Figure->getPosition());

		SDL_RenderCopy(this->Renderer, this->Textures->getFigureTexture(Figure->getTeam(), Figure->getType()), NULL, &Pos);
	}
}

void Chess::Render::renderPosiblePosition()
{
	for (auto& PosPosition : RenderBuffer::getRenderBuffer()->PosiblePosition)
	{
		auto Pos = this->getXYForFigure(PosPosition);
		SDL_RenderCopy(this->Renderer, this->Textures->getPosiblePositionTexture(), NULL, &Pos);
	}
}

void Chess::Render::renderSwapPawn()
{
	if (RenderBuffer::getRenderBuffer()->SwapPawn)
	{
		if (RenderBuffer::getRenderBuffer()->SwapPawnColor == TeamColor::WHITE)
			SDL_SetRenderDrawColor(this->Renderer, 0x00, 0x00, 0x00, 0x00);
		else 
			SDL_SetRenderDrawColor(this->Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		int Width, Height;

		SDL_GetWindowSize(this->Window, &Width, &Height);

		SDL_Rect Background{Width * 0.1, Height * 0.2, Width * 0.8, Height * 0.6};

		SDL_RenderFillRect(this->Renderer, &Background);

		SDL_Rect QueeenPosition { Width * 0.125, Height * 0.35, Width * 0.15, Height * 0.3 };

		SDL_RenderCopy(this->Renderer, this->Textures->getFigureTexture(RenderBuffer::getRenderBuffer()->SwapPawnColor, FigureType::QUEEN), NULL, &QueeenPosition);

		SDL_Rect BishopPosition{ Width * 0.325, Height * 0.35, Width * 0.15, Height * 0.3 };

		SDL_RenderCopy(this->Renderer, this->Textures->getFigureTexture(RenderBuffer::getRenderBuffer()->SwapPawnColor, FigureType::BISHOP), NULL, &BishopPosition);

		SDL_Rect KnightPosition{ Width * 0.525, Height * 0.35, Width * 0.15, Height * 0.3 };

		SDL_RenderCopy(this->Renderer, this->Textures->getFigureTexture(RenderBuffer::getRenderBuffer()->SwapPawnColor, FigureType::KNIGHT), NULL, &KnightPosition);

		SDL_Rect RookPosition{ Width * 0.725, Height * 0.35, Width * 0.15, Height * 0.3 };

		SDL_RenderCopy(this->Renderer, this->Textures->getFigureTexture(RenderBuffer::getRenderBuffer()->SwapPawnColor, FigureType::ROOK), NULL, &RookPosition);
	}
}

SDL_Rect Chess::Render::getXYForFigure(BoardPosition Position)
{
	SDL_Rect Result;

	int Width, Height;

	SDL_GetWindowSize(this->Window, &Width, &Height);

	Result.w = Width * 0.125;
	Result.h = Height * 0.125;

	Result.x = Result.w * (Position.x - 1);
	Result.y = Result.h * ( 8 - Position.y);

	return Result;

}

Chess::BoardPosition Chess::Render::transformMousePosition(int x, int y)
{
	int Width, Height;

	SDL_GetWindowSize(this->Window, &Width, &Height);

	int CellX = Width / 8;

	int CellY = Height / 8;

	return BoardPosition{static_cast<uint8_t>((x / CellX) + 1), static_cast<uint8_t>(8 - (y / CellY))};
}

Chess::FigureType Chess::Render::getFigurePawnSwap(int x, int y)
{
	int Width, Height;

	SDL_GetWindowSize(this->Window, &Width, &Height);
	SDL_Rect QueeenPosition{ Width * 0.125, Height * 0.35, Width * 0.15, Height * 0.3 };
	SDL_Rect BishopPosition{ Width * 0.325, Height * 0.35, Width * 0.15, Height * 0.3 };
	SDL_Rect KnightPosition{ Width * 0.525, Height * 0.35, Width * 0.15, Height * 0.3 };
	SDL_Rect RookPosition{ Width * 0.725, Height * 0.35, Width * 0.15, Height * 0.3 };
	

	if (x >= QueeenPosition.x && x <= QueeenPosition.x + QueeenPosition.w && y >= QueeenPosition.y && y <= QueeenPosition.y + QueeenPosition.h)
		return FigureType::QUEEN;

	if (x >= BishopPosition.x && x <= BishopPosition.x + BishopPosition.w && y >= BishopPosition.y && y <= BishopPosition.y + BishopPosition.h)
		return FigureType::BISHOP;
	
	if (x >= KnightPosition.x && x <= KnightPosition.x + KnightPosition.w && y >= KnightPosition.y && y <= KnightPosition.y + KnightPosition.h)
		return FigureType::KNIGHT;
		
	if (x >= RookPosition.x && x <= RookPosition.x + RookPosition.w && y >= RookPosition.y && y <= RookPosition.y + RookPosition.h)
		return FigureType::ROOK;

	return FigureType::NONE;
}
