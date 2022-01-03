#ifndef Player_H
#define Player_H
#include "Object.h"
class Player: public Object{		
	public:	
		Player();
		~Player();	
		draw();
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
};
#endif
