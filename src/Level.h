/*
 * Level.h
 *
 *  Created on: 8-apr.-2016
 *      Author: Kwinten
 */

#ifndef LEVEL_H_
#define LEVEL_H_
#include <abstract/entities/Obstacle.h>
#include <abstract/entities/Player.h>
#include <abstract/entities/Projectile.h>
#include <abstract/entities/Props.h>
#include <abstract/Events.h>
#include <abstract/Factory.h>
#include <abstract/Row.h>
#include <abstract/Window.h>
#include "levelGenerator/LevelProperties.h"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iterator>
#include <list>
#include <ratio>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

namespace frogger
{
	class Level
	{
		public:
			Level(Factory* F, Window* win, std::list<Player*>* players,
					int rowHeight, LevelProperties* lvlprop);
			virtual ~Level();
			void levelExecution(std::string keyStroke);
			void rowGenerator(int rowHeight, int screenHight, Factory* F,
					std::vector<Row*>* rows, std::vector<std::list<Props*>>* propsOnRow,
					LevelProperties* lvlprop);
			void propsGenerator(Factory* F, std::vector<Row*>* rows,
					std::vector<std::list<Props*>>* propsOnRow);
			int collisionDetection(std::vector<std::list<Props*>>* propsOnRow,std::list<Player*>* players);
			void fillEnemyList(Factory* F, std::vector<Row*>* rows,
					std::vector<std::list<Props*>>* propsOnRow,
					int screenWidth);
			void drawGameElements(std::vector<std::list<Props*>>* propsOnRow,std::list<Player*>* players);
			Props* obsOrLane(std::list<Props*>* PreProp, Row* row, bool frontOrBack, int x);
			Props* obsOrLane(std::list<Props*>* PreProp, Row* row);
			bool followFrog(std::vector<Row*>* rows, std::list<Player*>* players, int factor);
			bool objectiveCompleteCheck(std::vector<std::list<Props*>>* propsOnRow);
			bool isObjectiveDone() const;
			void resetLevel();
			void initLevel();
			void extraRowNeeded(int screenHeight,
					int screenWidth, Factory* F, std::vector<Row*>* rows,
					std::vector<std::list<Props*>>* propsOnRow, LevelProperties* lvlprop);
			void fillOneRow(Factory* F, Row* rows, std::vector<std::list<Props*>>* propsOnRow, int screenWidth);

			struct drawMoveRemove
			{
					bool operator()(Props* prop) const;
			};

		private:
			Factory* F;
			Window* win;
			std::list<Player*>* players;
			int rowHeight;
			std::string keyStroke;
			std::vector<Row*> rowsR;
			std::vector<std::list<Props*>> propsOnRowR;
			std::vector<Row*>* rows = &rowsR;
			std::vector<std::list<Props*>>* propsOnRow = &propsOnRowR;
			bool objectiveDone = false;
			LevelProperties* lvlprop;
	};
}

#endif /* LEVEL_H_ */
