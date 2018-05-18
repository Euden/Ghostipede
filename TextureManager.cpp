#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = SDL_LoadBMP(fileName.c_str());

	if (pTempSurface == 0)
	{
		return false;
	}

	SDL_Texture* pTexture =
		SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	// everything went okay, add the texture to the list
	if (pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

	// something went wrong
	return false;
}

void TextureManager::draw(std::string id, int x, int y, int wiTicksh, int height,
	SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = wiTicksh;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);

}

void TextureManager::drawFrame(std::string id, int x, int y, int wiTicksh, int height, int currentRow, int currentFrame, SDL_Renderer
	*pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = wiTicksh * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = wiTicksh;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::clean(std::string id)
{
	SDL_DestroyTexture(m_textureMap[id]);
}
