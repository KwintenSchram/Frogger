/*
 * RowProperties.h
 *
 *  Created on: 23-apr.-2016
 *      Author: Kwinten
 */

#ifndef LEVELGENERATOR_ROWPROP_H_
#define LEVELGENERATOR_ROWPROP_H_
#include <vector>
#include <stdlib.h>
namespace frogger
{
	class RowProp
	{
		public:
			RowProp(int speed, int divider, char type, char mode, int obstRate,
					int itemRate, int shootRate, bool obstacleVis, bool laneVis,
					std::vector<int> obstIndexes, std::vector<int> laneIndexes,
					std::vector<int> itemTypeChance);
			virtual ~RowProp();
			int* getDivider();
			int* getItemRate();
			int getObsticleRate() const;
			int* getShootRate();
			int* getSpeed();
			char getType() const;
			bool getLaneVis() const;
			bool getObstacleVis() const;
			std::vector<int> getItemTypeChance();
			const std::vector<int>& getLaneIndexes() const;
			const std::vector<int>& getObstIndexes() const;
			void increaseProp(int deltaSpe, int deltaDiv, int deltaObsRate,
					int deltaItemRate, int deltaShootRate);
			int getItemType();
			char getMode() const;
		private:
			int speed;
			int divider;
			char type;
			char mode;
			int obstRate;
			int itemRate;
			int shootRate;
			bool obstacleVis;
			bool laneVis;
			std::vector<int> obstIndexes;
			std::vector<int> laneIndexes;
			std::vector<int> itemTypeChance;
	};
}

#endif /* LEVELGENERATOR_ROWPROP_H_ */
