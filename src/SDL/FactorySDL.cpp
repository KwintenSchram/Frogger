/*
 * FactorySDL.cpp
 *
 *  Created on: 22 Feb 2016
 *      Author: msn-w
 */

#include "Obstacle.h"
#include "ObstacleSDL.h"
#include "Player.h"
#include <PlayerSDL.h>
#include "FactorySDL.h"
#include "SDL.h"
#include "EventsSDL.h"
#include "LaneSDL.h"
#include "ItemSDL.h"
#include "ProjectileSDL.h"

#include "Window.h"
#include "WindowSDL.h"
#include "Row.h"


using namespace std;

FactorySDL::FactorySDL() {sdldata=new SDLdata();}

FactorySDL::~FactorySDL() {}

Player* FactorySDL::createPlayer(int x,int y,int w,int h,int speedH,int speedV)
{
	sdldata->resetPlayerRange();
	return new PlayerSDL(sdldata,x,y,w,h,speedH,speedV);
}
Obstacle* FactorySDL::createObstacle(Row* row,int x,int y,int w,int h)
{
	sdldata->resetObstacleRange();
	return new ObstacleSDL(sdldata,row,x,y,w,h);
}
Window* FactorySDL::createWindow()
{
	return new WindowSDL(sdldata);
}

Events* FactorySDL::createEvents()
{
	return new EventsSDL();
}

Lane* FactorySDL::createLane(Row* row, int x, int y, int w,int h)
{
	sdldata->resetLaneRange();
	return new LaneSDL(sdldata,row,x,y,w,h);
}

Item* FactorySDL::createItem(Row* row, int x, int y, int w,int h,int type)
{
	return new ItemSDL(sdldata,row,x,y,w,h,type);
}

Obstacle* FactorySDL::createObstacle(Row* row)
{
	sdldata->resetObstacleRange();
	return new ObstacleSDL(sdldata,row);
}

Lane* FactorySDL::createLane(Row* row)
{
	sdldata->resetLaneRange();
	return new LaneSDL(sdldata,row);
}

Item* FactorySDL::createItem(Row* row,int type)
{
	return new ItemSDL(sdldata,row,type);
}

Projectile* FactorySDL::createProjectile(Entity* entity,int speed,int type)
{
	return new ProjectileSDL(sdldata,entity->getDirection(),entity->getX(),entity->getY(),entity->getH(),speed,type);
}
