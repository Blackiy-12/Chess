#pragma once

#include "Texture.h"
#include "Render/FigureRenderInfo.h"

#include <unordered_map>
#include <memory>

namespace Chess
{

	const std::string FigureTextureName[]
	{
		"W_PAWN", "B_PAWN",
		"W_ROOK", "B_ROOK",
		"W_BISHOP", "B_BISHOP",
		"W_KNIGHT", "B_KNIGHT",
		"W_QUEEN", "B_QUEEN",
		"W_KING", "B_KING"
	};

	class TextureHolder
	{
	public:
		TextureHolder();

		~TextureHolder();

		void loadTextures(SDL_Renderer* Renderer);

		SDL_Texture* getBoardTexture();

		SDL_Texture* getFigureTexture(TeamColor Color, FigureType Type);

		SDL_Texture* getPosiblePositionTexture();

	private:		
		std::unique_ptr<Texture> Board;

		std::unique_ptr<Texture> PosiblePosition;

		std::unordered_map<std::string, std::unique_ptr<Texture>> FiguresTextures;

	};
}