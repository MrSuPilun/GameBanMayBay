#include "Enemy.h"

Enemy::Enemy(){
	life=3;
	direction=0;
	position=Vector2(0,0);
	size=Vector2(50,50);
	isGoLeft=rand() % (1-0+1) + 0;
}
Enemy::~Enemy(){
	life=0;
	direction=0;
	position=Vector2(0,0);
	size=Vector2(0,0);
	speed=Vector2(0,0);
	isGoLeft=false;
}
Enemy::draw(){
	if(life){
		int x=position.getX();
		int y=position.getY();
		// body
		rectangle(x, y, 50+x, 40+y);
		// 3 cai rang
		rectangle(37+x, 40+y, 47+x, 50+y);
		if(life>1)
			rectangle(3+x, 40+y, 13+x, 50+y);
		if(life>2)
			rectangle(20+x, 40+y, 30+x, 50+y);
		// 2 con mat
		rectangle(3+x, 10+y, 20+x, 30+y);
		rectangle(30+x, 10+y, 47+x, 30+y);		
	}
	Object::draw();	
}
void Enemy::move(){
	if(life)
		switch(direction){
			case 0:
				position = position + speed.Y();
				break;
			case 1:
				position = position + speed.Y();
				if(isGoLeft){
					position = position - speed.X();
				} else {
					position = position + speed.X();
				}
				if(position.getX() > 800-60)
					isGoLeft = true;
				else if(position.getX() < 10)
					isGoLeft = false;
				break;
		}
		
}
void Enemy::setDirection(int dir){ direction = dir; }
