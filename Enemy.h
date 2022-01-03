#ifndef Enemy_H
#define Enemy_H
#include "Object.h"
class Enemy: public Object{
	private:
		bool isGoLeft;
		int direction;
	public:	
		Enemy();
		~Enemy();
		draw();
		void move();
		void setDirection(int dir);		
};
#endif
