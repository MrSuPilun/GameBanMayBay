#ifndef Item_H
#define Item_H
#include "Object.h"
class Item: public Object{
	public:
		void move();
};
class Bullet: public Item{
	public:
		Bullet();
		draw();
};
class BulletBall: public Item{
	private:
		int radius;
	public:
		BulletBall();
		draw();
		void setRadius(int x);
};
class Items: public Item{
	private:
		int itemType;
	public:
		Items();
		Items(Vector2 pos, Vector2 siz, int item);
		draw();
		int getItemType();
		void setItemType(int x);
};
#endif
