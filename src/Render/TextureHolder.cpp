#include "TextureHolder.h"

#include <SDL_image.h>

const char BOARD_FILE_PATH[] =			"../data/textures/board.png";

const char POSIBLEPOS_FILE_PATH[] =	"../data/textures/posible_pos.png";

const char W_PAWN_FILE_PATH[] =		"../data/textures/w_pawn.png";

const char B_PAWN_FILE_PATH[] =		"../data/textures/b_pawn.png";

const char W_ROOK_FILE_PATH[] =		"../data/textures/w_rook.png";

const char B_ROOK_FILE_PATH[] =		"../data/textures/b_rook.png";

const char W_BISHOP_FILE_PATH[] =		"../data/textures/w_bishop.png";

const char B_BISHOP_FILE_PATH[] =		"../data/textures/b_bishop.png";

const char W_KNIGHT_FILE_PATH[] =		"../data/textures/w_knight.png";

const char B_KNIGHT_FILE_PATH[] =		"../data/textures/b_knight.png";

const char W_QUEEN_FILE_PATH[] =		"../data/textures/w_queen.png";

const char B_QUEEN_FILE_PATH[] =		"../data/textures/b_queen.png";

const char W_KING_FILE_PATH[] =		"../data/textures/w_king.png";

const char B_KING_FILE_PATH[] =		"../data/textures/b_king.png";


Chess::TextureHolder::TextureHolder()
	: Board(nullptr), PosiblePosition(nullptr), FiguresTextures()
{
	IMG_Init(IMG_INIT_PNG);
}

Chess::TextureHolder::~TextureHolder()
{
	IMG_Quit();
}

void Chess::TextureHolder::loadTextures(SDL_Renderer* Renderer)
{
	this->Board = std::make_unique<Texture>(IMG_LoadTexture(Renderer, BOARD_FILE_PATH));

	this->PosiblePosition = std::make_unique<Texture>(IMG_LoadTexture(Renderer, POSIBLEPOS_FILE_PATH));

	SDL_SetTextureAlphaMod(this->PosiblePosition->getTexturePtr(), 120);

	this->FiguresTextures[FigureTextureName[0]]  = std::make_unique<Texture>(IMG_LoadTexture(Renderer, W_PAWN_FILE_PATH));

	this->FiguresTextures[FigureTextureName[1]]  = std::make_unique<Texture>(IMG_LoadTexture(Renderer, B_PAWN_FILE_PATH));

	this->FiguresTextures[FigureTextureName[2]]  = std::make_unique<Texture>(IMG_LoadTexture(Renderer, W_ROOK_FILE_PATH));

	this->FiguresTextures[FigureTextureName[3]]  = std::make_unique<Texture>(IMG_LoadTexture(Renderer, B_ROOK_FILE_PATH));

	this->FiguresTextures[FigureTextureName[4]]  = std::make_unique<Texture>(IMG_LoadTexture(Renderer, W_BISHOP_FILE_PATH));

	this->FiguresTextures[FigureTextureName[5]]  = std::make_unique<Texture>(IMG_LoadTexture(Renderer, B_BISHOP_FILE_PATH));

	this->FiguresTextures[FigureTextureName[6]]  = std::make_unique<Texture>(IMG_LoadTexture(Renderer, W_KNIGHT_FILE_PATH));

	this->FiguresTextures[FigureTextureName[7]]  = std::make_unique<Texture>(IMG_LoadTexture(Renderer, B_KNIGHT_FILE_PATH));

	this->FiguresTextures[FigureTextureName[8]]  = std::make_unique<Texture>(IMG_LoadTexture(Renderer, W_QUEEN_FILE_PATH ));

	this->FiguresTextures[FigureTextureName[9]]  = std::make_unique<Texture>(IMG_LoadTexture(Renderer, B_QUEEN_FILE_PATH ));

	this->FiguresTextures[FigureTextureName[10]] = std::make_unique<Texture>(IMG_LoadTexture(Renderer, W_KING_FILE_PATH));

	this->FiguresTextures[FigureTextureName[11]] = std::make_unique<Texture>(IMG_LoadTexture(Renderer, B_KING_FILE_PATH));


}

SDL_Texture* Chess::TextureHolder::getBoardTexture()
{
	return this->Board->getTexturePtr();
}

SDL_Texture* Chess::TextureHolder::getFigureTexture(Chess::TeamColor Color, FigureType Type)
{
	switch (Type)
	{
	case Chess::FigureType::PAWN:
		if (Color == TeamColor::WHITE)
			return this->FiguresTextures[FigureTextureName[0]]->getTexturePtr();
		else
			return this->FiguresTextures[FigureTextureName[1]]->getTexturePtr();
		break;
	case Chess::FigureType::BISHOP:
		if (Color == TeamColor::WHITE)
			return this->FiguresTextures[FigureTextureName[4]]->getTexturePtr();
		else
			return this->FiguresTextures[FigureTextureName[5]]->getTexturePtr();
		break;
	case Chess::FigureType::KNIGHT:
		if (Color == TeamColor::WHITE)
			return this->FiguresTextures[FigureTextureName[6]]->getTexturePtr();
		else
			return this->FiguresTextures[FigureTextureName[7]]->getTexturePtr();
		break;
	case Chess::FigureType::ROOK:
		if (Color == TeamColor::WHITE)
			return this->FiguresTextures[FigureTextureName[2]]->getTexturePtr();
		else
			return this->FiguresTextures[FigureTextureName[3]]->getTexturePtr();
		break;
	case Chess::FigureType::QUEEN:
		if (Color == TeamColor::WHITE)
			return this->FiguresTextures[FigureTextureName[8]]->getTexturePtr();
		else
			return this->FiguresTextures[FigureTextureName[9]]->getTexturePtr();
		break;
	case Chess::FigureType::KING:
		if (Color == TeamColor::WHITE)
			return this->FiguresTextures[FigureTextureName[10]]->getTexturePtr();
		else
			return this->FiguresTextures[FigureTextureName[11]]->getTexturePtr();
		break;
	}
}

SDL_Texture* Chess::TextureHolder::getPosiblePositionTexture()
{
	return this->PosiblePosition->getTexturePtr();
}
