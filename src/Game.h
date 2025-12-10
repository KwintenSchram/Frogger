/*
 * Game.h
 *  Created on: 22 Feb 2016
 *      Author: Kwinten
 */

#ifndef GAME_H_
#define GAME_H_
#include <abstract/entities/Obstacle.h>
#include <abstract/entities/Player.h>
#include <abstract/entities/Projectile.h>
#include <abstract/entities/Props.h>
#include <abstract/Events.h>
#include <abstract/Factory.h>
#include <abstract/Row.h>
#include <abstract/Window.h>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <stdlib.h>
#include <ratio>
#include "Level.h"
#include "levelGenerator/LevelProperties.h"
#include "menu/Menu.h"
#include "GameEnums.h"
#include "GameConstants.h"
namespace frogger
{
	class Game
	{
		public:
			explicit Game(Factory* F);
			virtual ~Game();
			bool playersAlive(std::list<Player*>* players);
			void addPlayers(Factory* F, std::list<Player*>* players, int amount,	int X, int Y,
					int W, int H, int speed,char gameMode, char difficulty,
					LevelProperties* lvlProp,Window* win);
			void addHighScore(std::list<Player*>* players, char gameMode);
		protected:
			// Initialize highscore vectors with zeros based on HIGHSCORE_ENTRIES constant
			std::vector<int> highScoreClassic = std::vector<int>(GameConstants::HIGHSCORE_ENTRIES, 0);
			std::vector<int> highScoreEndless = std::vector<int>(GameConstants::HIGHSCORE_ENTRIES, 0);
	};
}

#endif /* GAME_H_ */
