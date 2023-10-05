#include "Texture.h"

#include <SDL_image.h>

Chess::Texture::Texture(SDL_Texture* Texture)
	: TexturePtr(Texture)
{
}

Chess::Texture::~Texture()
{
	SDL_DestroyTexture(this->TexturePtr);
}

SDL_Texture* Chess::Texture::getTexturePtr()
{
	return this->TexturePtr;
}
