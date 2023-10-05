#pragma once

#include <SDL.h>
#include <string>

namespace Chess
{
	class Texture
	{
	public:
		Texture(SDL_Texture* Texture);

		~Texture();

		SDL_Texture* getTexturePtr();

	private:
		SDL_Texture* TexturePtr;

	};
}