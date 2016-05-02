/*
 * Animator.cpp
 *
 *  Created on: 25-mrt.-2016
 *      Author: msn-w
 */

#include <Animator.h>
#include <iostream>
using namespace frogger;

Animator::Animator(std::vector<SDL_Texture*> textures, std::vector<int> ratio) :
		textures(textures), ratio(ratio), counter(abs(ratio.at(0))), currentTexture(0)
{
	size = textures.size();
}

Animator::~Animator()
{
}

SDL_Texture* Animator::getTexture()
{
	SDL_Texture* texture;
	if (size > 1)
	{
		if (counter >1000)
		{
			//MANUAL MODE
		}
		else if (counter > 0)
		{
			counter--;
		}
		else
		{
			if (size > (currentTexture + 1)
					&& abs(ratio.at(currentTexture + 1)) > 0)
			{
				currentTexture = currentTexture + 1;
				counter = abs(ratio.at(currentTexture));
				turned = (ratio.at(currentTexture) < 0);
			}
			else
			{
				currentTexture = 0;
				counter = abs(ratio.at(currentTexture));
				turned = (ratio.at(currentTexture) < 0);
			}
		}
		texture = textures.at(currentTexture);
		return texture;
	}
	else
	{
		return textures.back();
	}
}

int Animator::getCounter() const
{
	return counter;
}

void Animator::setCounter(int counter)
{
	this->counter = counter;
}

int Animator::getCurrentTexture() const
{
	return currentTexture;
}

void Animator::setCurrentTexture(int currentTexture)
{
	this->currentTexture = currentTexture;
}

void Animator::triggerNext(int counter)
{
	if (ratio.size() < (unsigned)currentTexture + 1)
	{
		currentTexture = currentTexture + 1;
		this->counter = counter;
	}
}

Animator* Animator::clone()
{
	return new Animator(*this);
}

bool Animator::isTurned() const
{
	return turned;
}

void Animator::setTurned(bool turned)
{
	this->turned = turned;
}

void Animator::setCurrentTextureFor(int texture, int counter)
{
	currentTexture = texture;
	this->counter = counter;
}