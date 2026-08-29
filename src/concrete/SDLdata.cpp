/*
 * SDLstuff.cpp
 * Creates and keeps track of important SDL data. Renderer/textures
 *  Created on: 7-mrt.-2016
 *      Author: Kwinten
 */

#include <abstract/Animator.h>
#include <concrete/SDLdata.h>
#include <string>
#include <SDL_image.h>
#include <stdlib.h>
#include <math.h>
using namespace frogger_sdl;

SDLdata::SDLdata()
{
}
SDLdata::~SDLdata()
{
	deleteTextures(menu2Textures);
	deleteTextures(backTex);
	deleteTextures(playerTex);
	deleteTextures(ObstTex);
	deleteTextures(laneTex);
	deleteTextures(itemTex);
	deleteTextures(projTex);
}

void SDLdata::renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y,
		int* w, int h, int angle, bool ratio)
{
	if (ratio)
		*w = getDW(tex, h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = *w;
	dst.h = h;

	SDL_RendererFlip temp = SDL_FLIP_NONE;
	if (angle == 1)
	{
		temp = SDL_FLIP_HORIZONTAL;
		angle = 0;
	}
	SDL_RenderCopyEx(ren, tex, nullptr, &dst, angle, nullptr, temp);
}
int SDLdata::getDW(SDL_Texture* tex, int h)
{
	int aQ, wQ, hQ;
	Uint32 fQ;
	SDL_QueryTexture(tex, &fQ, &aQ, &wQ, &hQ);
	return (int) round((float)((h) / (float) hQ) * wQ);
}
SDL_Renderer* SDLdata::getRen()
{
	return re;
}
void SDLdata::setRen(SDL_Renderer* rende)
{
	re = rende;
}
void SDLdata::setBackground(SDL_Texture* texB)
{
	SDL_RenderCopy(re, texB, nullptr, nullptr);
}
void SDLdata::updateScreen()
{
	SDL_RenderPresent(re);
}
void SDLdata::createTextures()
{
	std::string recourcePath=SDL_GetBasePath();

	line = IMG_LoadTexture(re, (recourcePath+"frogger/menu/line.png").c_str());

	fillTextureVectors(&backTex,"back",2);

	fillTextureVectors(&playerTex,"frog",5);
	fillTextureVectors(&ObstTex,"o",15);
	fillTextureVectors(&laneTex,"lane",9);
	fillTextureVectors(&itemTex,"item",2);
	fillTextureVectors(&projTex,"proj",0);
	fillTextureVectors(&menu2Textures,"menu/m",15);
}



std::vector<SDL_Texture*>* SDLdata::getBackTextures()
{
	return &backTex;
}

void SDLdata::setScreenDimension(int* gameWidth, int* gameHeight)
{
	screenHeight = gameHeight;
	screenWidth = gameWidth;
}

int* SDLdata::getScrH() const
{
	return screenHeight;
}

void SDLdata::setScreenHeight(int* screenHeight)
{
	this->screenHeight = screenHeight;
}

int* SDLdata::getScrW() const
{
	return screenWidth;
}

void SDLdata::setScreenWidth(int* screenWidth)
{
	this->screenWidth = screenWidth;
}

std::vector<SDL_Texture*>* frogger_sdl::SDLdata::getMenuTextures()
{
	return &menu2Textures;
}

SDL_Texture* frogger_sdl::SDLdata::getLine()
{
	return line;
}

void frogger_sdl::SDLdata::deleteTextures(std::vector<SDL_Texture*> textureVector)
{
	for(SDL_Texture* tex:textureVector)
		SDL_DestroyTexture(tex);
}

void frogger_sdl::SDLdata::fillTextureVectors(std::vector<SDL_Texture*>* textureVector, std::string prefix,	int endNumber)
{
	std::string recourcePath=SDL_GetBasePath();
	std::string dir = recourcePath+"frogger\\"+prefix;
		for (int i=0;i<=endNumber;i++)
		{
			std::string completeDir=dir + std::to_string(i)+".png";
			SDL_Texture* tex=IMG_LoadTexture(re, (completeDir).c_str());
			textureVector->push_back(tex);
		}
}

std::vector<SDL_Texture*>* frogger_sdl::SDLdata::getTextureVector(char type)
{
	if(type=='O')
		return &ObstTex;
	else if(type=='L')
		return &laneTex;
	else if(type=='I')
		return &itemTex;
	else if(type=='B')
		return &projTex;
	else
		return &playerTex;
}
