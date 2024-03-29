/*
 * Item.cpp
 *
 * These are the bonus item you can collect in game.
 * They can the increase the score/life/ammo of the player that collects them
 *
 *  Created on: 18-mrt.-2016
 *      Author: Kwinten
 */

#include <abstract/entities/Item.h>
using namespace frogger;
Item::Item():	effect(0)
{
}

Item::~Item()
{
}

void Item::collision(Player* player)
{
}

void frogger::Item::effectOnPlayer(Player* player)
{
	if (effect == 0)
	{
		if (row->getRowProperties()->getMode() == 'C')
			player->addLife(1);
		else //no extra lifes in endless mode
		{
			player->addScore(10);
			player->addProjectiles(1);
		}
	}
	else if (effect == 1)
		player->addScore(10);
	else
		player->addProjectiles(1);
}

bool frogger::Item::itemListEmpty()
{
	return false;
}

void frogger::Item::setEffect(int effect)
{
	this->effect=effect;
}

int frogger::Item::getEffect()
{
	return effect;
}
