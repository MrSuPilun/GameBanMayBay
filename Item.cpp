#include "Item.h"

void Item::move(){
	if(life)
		position = position + speed;
}
Bullet::Bullet(){
	size = Vector2(0,0);
}
Bullet::draw(){
	if(life){
		int x=position.getX();
		int y=position.getY();
		rectangle(x-1, y-5, x+2, y+5);	
	}	
}
BulletBall::BulletBall(){
	BulletBall::Object();
	radius=5;
}
BulletBall::draw(){
	if(life){
		int x=position.getX();
		int y=position.getY();
		circle(x, y, radius);
	}	
}
void BulletBall::setRadius(int x){ radius=x; };

Items::Items(){
	itemType=0;
	size=Vector2(30,30);
}
Items::Items(Vector2 pos, Vector2 siz, int item){
	Items::Object();
	Items::setSize(siz);
	Items::setPostion(pos);
	itemType=item;
}
//========================
//itemType = 0; Health
//itemType = 1; Gun +1
//itemType = 2; BulletType L
//itemType = 3; BulletType B
//itemType = 4; BulletType R
Items::draw(){
	int x = position.getX();
	int y = position.getY();
	if(life){
		if(itemType==0){
			line(x+16,y+4,x+20,y);
			line(x+20,y,x+28,y);
			line(x+28,y,x+32,y+4);
			line(x+32,y+4,x+32,y+18);
			line(x+32,y+18,x+16,y+32);	
			//=======================	
			line(x+16,y+32,x,y+18);
			line(x,y+18,x,y+4);
			line(x,y+4,x+4,y);
			line(x+4,y,x+12,y);	
			line(x+12,y,x+16,y+4);
			//======================
			settextstyle(2, 0, 6);
			outtextxy(x+9,y+5,"H");
		} else {
			rectangle(x,y,x+30,y+30);
			rectangle(x+3,y+3,x+27,y+27);
			switch(itemType){
				case 1:
					settextstyle(2, 0, 6);
					outtextxy(x+5,y+5,"+1");
					break;
				case 2:
					settextstyle(2, 0, 6);
					outtextxy(x+8,y+5,"L");
					break;
				case 3:
					settextstyle(2, 0, 6);
					outtextxy(x+8,y+5,"B");
					break;			
			}
		}
	}
}
int Items::getItemType(){ return itemType; }
void Items::setItemType(int x){ itemType = x; }

