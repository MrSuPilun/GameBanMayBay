#include "Object.h"

// Khoi tao cac gia tri mac dinh cho Object
Object::Object(){
	position = Vector2(0,0);
	size = Vector2(0,0);		
	speed = Vector2(0,0);
	life = 1;
	isShowBox = false;
}
Object::~Object(){
	position = Vector2(0,0);
	size = Vector2(0,0);		
	speed = Vector2(0,0);
	life = 0;
	isShowBox = false;
}
// Lay Vector VI TRI
Vector2 Object::getPosition(){ return position.get(); }

// Lay Vector KICH THUOC
Vector2 Object::getSize(){ return size; }

// Lay Vector TOC DO
Vector2 Object::getSpeed(){ return speed; }

// Kiem tra va cham
bool Object::checkCollision(Vector2 c){
	int x=position.getX();						// Lay toa do x cua doi tuong
	int y=position.getY();						// Lay toa do y cua doi tuong
	int w=size.getX();							// Lay chieu rong x cua doi tuong
	int h=size.getY();							// Lay chieu cao y cua doi tuong
	int ox=c.getX();							// Lay toa do y cua doi tuong c
	int oy=c.getY();							// Lay toa do y cua doi tuong c
	if((x<ox && ox<x+w) && (y<oy && oy<y+h))
		return true;
	return false;
}

// Lay so MANG SONG
int Object::getLife(){ return life; }

// Gan gia tri ve check box
void Object::setShowBox(bool x){ isShowBox=x; }

// Dat MANG SONG
void Object::setLife(int x){ life=x; }

// Dat VI TRI
void Object::setPostion(Vector2 p){ position=p; }

// Dat KICH THUOC
void Object::setSize(Vector2 s){ size=s; }

// Dat TOC DO
void Object::setSpeed(Vector2 b){ speed=b; }

// Tru 1 mang
void Object::subLife(){
	--life;
	if(life<0)
		life=0;
}

// Them 1 mang
void Object::addLife(){
	++life;
	if(life>3)
		life=3;
}

// Ve
void Object::draw(){
	if(isShowBox){
		setcolor(RED);
		rectangle(position.getX(),position.getY(),position.getX()+size.getX(),position.getY()+size.getY());
		setcolor(WHITE);
	}
}


