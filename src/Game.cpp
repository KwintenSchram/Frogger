/*
 * Game.cpp
 * Manages the game.
 * Consist mainly of a state machine that updates its state by executing a level or executing the menu. Also keeps track of the highscore.
 *  Created on: 22 Feb 2016
 *      
 */

/*
 * States:
 * B: start menu
 * H: highscore display menu
 * S: settings menu
 * V: victory screen
 * G: game over screen
 * A: help screen
 * E: Endless game mode
 * C: classic game mode
 * Q: quit state
 */

/* Row types:
* A: First row (players starts here)
* B: Obstacle row (row where obstacles are visible and lanes invisible)
* C: Lane row (row where obstacles are invisible and lanes visible)
* D: middle row (no movement, can contain some bushes)
* E: last row (row where player wants to go)
 */

/*
 * int life = 4, totalTime = 50, scorePerStep = 5, projectiles = 4; //easy diff
 * int life = 3, totalTime = 40, scorePerStep = 10, projectiles = 3; //medium diff
 * int life = 2, totalTime = 30, scorePerStep = 15, projectiles = 2; //hard diff
 */

#include "Game.h"
using namespace frogger;

Game::Game(Factory* F)
{
	char state = 'B';
	char PrevState = 'B';
	int amountOfPlayers = 1;
	char gameMode = 'E';
	char difficulty = 'E';

	// Window configuration using constants
	const int WindowWidth = GameConstants::WINDOW_WIDTH;
	const int WindowHeight = GameConstants::WINDOW_HEIGHT;
	const int rowHeight = GameConstants::ROW_HEIGHT;
	const int dataWindowHeightDesired = GameConstants::DATA_WINDOW_HEIGHT_DESIRED;
	const int dataWindowHeight =
			((WindowHeight - dataWindowHeightDesired) % rowHeight)
					+ dataWindowHeightDesired;
	const int gameWindowHeight = WindowHeight - dataWindowHeight;
	const int gameWindowWidth = WindowWidth;

	// Player start configuration using constants
	const int plStartW = GameConstants::PLAYER_START_WIDTH;
	const int plStartH = GameConstants::PLAYER_START_HEIGHT;
	const int plStartSpeed = GameConstants::PLAYER_START_SPEED;
	const int plStartX = (gameWindowWidth / 2);
	const int plStartY = (gameWindowHeight - plStartW);
	std::string keyStroke;

	std::list<Player*> playersR;
	std::list<Player*>* players = &playersR;
	Events* event = F->createEvents();
	Window* win = F->createWindow();
	LevelProperties* lvlprop=nullptr;
	Level* level=nullptr;
	bool newHighscore;

	win->makeWindow(WindowWidth, WindowHeight, dataWindowHeight, "frogger");

	Menu* men = new Menu(win, &gameMode, &amountOfPlayers, &difficulty);

	int prevScore = 0;
	while (true)
	{
		int x, y;

		keyStroke = event->getEvent();
		event->getMousePos(&x, &y);

		switch (state)
		{
			case 'B':
			case 'H':
			case 'G':
			case 'S':
			case 'V':
			case 'A':
				//menu case modes
				if (state == 'G' && PrevState != state)
				{
					addHighScore(players, gameMode);
					for(Player* player:*players)
						delete(player);
					players->clear();
					delete(level);
					level=nullptr;
					delete(lvlprop);
					lvlprop=nullptr;
					prevScore = 0;
				}

				newHighscore=PrevState!='H';

				PrevState = state;
				state = men->menuExecution(keyStroke, state, x, y);
				if (state == 'H')
				{
					if (gameMode == 'E')
						win->displayHighScore(highScoreEndless,(newHighscore));
					else
						win->displayHighScore(highScoreClassic,(newHighscore));
				}
				win->updateScreen();

				break;
			case 'E':
			case 'C':
				//level execution modes
				if (PrevState == state)
				{
					level->levelExecution(keyStroke);

					state = playersAlive(players) ? state : 'G';
					state = level->isObjectiveDone() ? 'V' : state;
					const int scoreForLevelUp = GameConstants::Endless::SCORE_FOR_LEVEL_UP;
					if (gameMode == 'E'	&& ((players->back()->getScore()-prevScore) >= scoreForLevelUp)	&& (players->back()->getScore() > prevScore))
					{
						lvlprop->levelUp();
						prevScore = players->back()->getScore()-(players->back()->getScore()%scoreForLevelUp);
					}
					win->dislayData(players);
					win->updateScreen();
				}

				else if (PrevState == 'B' || PrevState == 'G')
				{
					lvlprop = new LevelProperties(gameMode, difficulty);
					addPlayers(F, players, amountOfPlayers, plStartX, plStartY,
							plStartW, plStartH, plStartSpeed,
							gameMode, difficulty,lvlprop,win);

					level = new Level(F, win, players, rowHeight, lvlprop);

					state = gameMode;
					PrevState = state;
				}
				else if (PrevState == 'V')
				{
					if(level!=nullptr)
										delete(level);
					lvlprop->levelUp();
					level = new Level(F, win, players, rowHeight, lvlprop);
					state = 'C';
					PrevState = state;
				}
				break;

			case 'Q':
				delete(event);
				delete(win);
				if(lvlprop!=nullptr)
					delete(lvlprop);
				if(level!=nullptr)
					delete(level);
				for(Player* player:*players)
					delete(player);
				return;
				break;
		}
		if (keyStroke =="Escape")
			if(state=='B')
				state='Q';
			else
				state='B';
	}
}

Game::~Game()
{
}

bool Game::playersAlive(std::list<Player*>* players)
{
	bool temp = false;
	for (Player* player : *players)
	{
		temp = temp || !player->isDead();
	}
	return temp;
}

void frogger::Game::addPlayers(Factory* F, std::list<Player*>* players, int amount,
		int X, int Y, int W, int H, int speed, char gameMode,
		char difficulty,LevelProperties* lvlProp,Window* win)
{
	for(Player* player:*players)
							delete(player);
	players->clear();

	// Initialize with easy mode defaults
	int life = GameConstants::Easy::LIVES;
	int totalTime = GameConstants::Easy::TOTAL_TIME;
	int scorePerStep = GameConstants::Easy::SCORE_PER_STEP;
	int projectiles = GameConstants::Easy::PROJECTILES;
	bool counterEnabled;

	counterEnabled = (gameMode == 'E') ? false : true;

	// Apply difficulty settings
	if (difficulty == 'M') {
		life = GameConstants::Medium::LIVES;
		totalTime = GameConstants::Medium::TOTAL_TIME;
		scorePerStep = GameConstants::Medium::SCORE_PER_STEP;
		projectiles = GameConstants::Medium::PROJECTILES;
	} else if (difficulty == 'H') {
		life = GameConstants::Hard::LIVES;
		totalTime = GameConstants::Hard::TOTAL_TIME;
		scorePerStep = GameConstants::Hard::SCORE_PER_STEP;
		projectiles = GameConstants::Hard::PROJECTILES;
	}

	// Apply endless mode overrides
	if (gameMode == 'E') {
		life = GameConstants::Endless::LIVES;
		totalTime = GameConstants::Endless::TOTAL_TIME;
	}

	players->clear();
	if (amount >= 1)
	{
		Player* player = F->createPlayer1();
		player->setAni(lvlProp->getPlayerAni(0).clone());
		player->setF(F);
		player->setProjAniList(lvlProp->getProjAni());
		player->initPlayer(speed,speed,W,H,X,Y,X,Y,win->getWidth(),win->getGameWindowHeight());

		player->setParameters(life, totalTime, counterEnabled, scorePerStep, projectiles);
		players->push_back(player);
	}
	if (amount >= 2)
	{
		Player* player2 = F->createPlayer1();
		player2->setAni(lvlProp->getPlayerAni(1).clone());
		player2->setF(F);
		player2->setProjAniList(lvlProp->getProjAni());
		player2->initPlayer(speed,speed,W,H,X-W,Y,X-W,Y,win->getWidth(),win->getGameWindowHeight());
		player2->setDifferentControls('A');
		player2->setParameters(life, totalTime, counterEnabled, scorePerStep, projectiles);
		players->push_back(player2);
	}
	if (amount >= 3)
	{
		Player* player3 = F->createPlayer1();
		player3->setAni(lvlProp->getPlayerAni(2).clone());
		player3->setF(F);
		player3->setProjAniList(lvlProp->getProjAni());
		player3->initPlayer(speed,speed,W,H,X+W,Y,X+W,Y,win->getWidth(),win->getGameWindowHeight());
		player3->setDifferentControls('B');
		player3->setParameters(life, totalTime, counterEnabled, scorePerStep, projectiles);
		players->push_back(player3);
	}
}

void frogger::Game::addHighScore(std::list<Player*>* players, char gameMode)
{
	for (Player* play : *players)
	{
		int score = play->getScore();
		if (gameMode == 'C')
		{
			highScoreClassic.push_back(score);
			std::sort(highScoreClassic.begin(), highScoreClassic.end());
			std::reverse(highScoreClassic.begin(), highScoreClassic.end());
			highScoreClassic.pop_back();
		}
		else
		{
			highScoreEndless.push_back(score);
			std::sort(highScoreEndless.begin(), highScoreEndless.end());
			std::reverse(highScoreEndless.begin(), highScoreEndless.end());
			highScoreEndless.pop_back();
		}
	}
}
