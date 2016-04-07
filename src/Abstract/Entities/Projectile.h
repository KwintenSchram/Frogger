/*
 * Projectile.h
 *
 *  Created on: 4-apr.-2016
 *      Author: msn-w
 */

#ifndef ABSTRACT_ENTITIES_PROJECTILE_H_
#define ABSTRACT_ENTITIES_PROJECTILE_H_
#include "Props.h"

class Projectile :public Props{
public:
	Projectile();
	virtual ~Projectile();
	bool roomForItem(){return false;};
	bool itemAbsent(){return true;};
	int coll(int xPos,int YPos, int height,int width,bool type);
private:

};


#endif /* ABSTRACT_ENTITIES_PROJECTILE_H_ */