/*
 * GameConstants.h
 * Constants for game configuration
 */

#ifndef GAMECONSTANTS_H_
#define GAMECONSTANTS_H_

namespace frogger
{
	namespace GameConstants
	{
		// Window dimensions
		constexpr int WINDOW_WIDTH = 700;
		constexpr int WINDOW_HEIGHT = 530;
		constexpr int ROW_HEIGHT = 45;
		constexpr int DATA_WINDOW_HEIGHT_DESIRED = 30;

		// Player dimensions and settings
		constexpr int PLAYER_START_WIDTH = ROW_HEIGHT;
		constexpr int PLAYER_START_HEIGHT = ROW_HEIGHT;
		constexpr int PLAYER_START_SPEED = ROW_HEIGHT;

		// Difficulty settings - Easy
		namespace Easy
		{
			constexpr int LIVES = 4;
			constexpr int TOTAL_TIME = 50;
			constexpr int SCORE_PER_STEP = 5;
			constexpr int PROJECTILES = 4;
		}

		// Difficulty settings - Medium
		namespace Medium
		{
			constexpr int LIVES = 3;
			constexpr int TOTAL_TIME = 40;
			constexpr int SCORE_PER_STEP = 10;
			constexpr int PROJECTILES = 3;
		}

		// Difficulty settings - Hard
		namespace Hard
		{
			constexpr int LIVES = 2;
			constexpr int TOTAL_TIME = 30;
			constexpr int SCORE_PER_STEP = 15;
			constexpr int PROJECTILES = 2;
		}

		// Endless mode settings
		namespace Endless
		{
			constexpr int LIVES = 0;               // No lives in endless mode
			constexpr int TOTAL_TIME = -1;         // No time limit
			constexpr int SCORE_FOR_LEVEL_UP = 100; // Score needed to level up
		}

		// Highscore settings
		constexpr int HIGHSCORE_ENTRIES = 4;
	}
}

#endif /* GAMECONSTANTS_H_ */
