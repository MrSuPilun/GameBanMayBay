#include "Player.h"

Player::Player(){
	life = 3;
	size = Vector2(70,50);
	speed = Vector2(0,0);
}
Player::~Player(){
	life = 0;
	position = Vector2(0,0);
	size = Vector2(0,0);
	speed = Vector2(0,0);
}
Player::draw(){
	if(life){		
		int x=position.getX();
		int y=position.getY();		
		//====================== Then
		line(x+30,y,x+40,y);
		line(x+40,y,x+50,y+15);
		line(x+50,y+15,x+50,y+40);
		line(x+50,y+50,x+20,y+50);
		line(x+20,y+40,x+20,y+15);
		line(x+20,y+15,x+30,y);
		//====================== Canh Trai
		line(x+20,y+40,x+10,y+43);
		line(x+10,y+43,x+10,y+50);
		line(x+10,y+50,x+20,y+50);
		//====================== Canh Phai
		line(x+50,y+40,x+60,y+43);
		line(x+60,y+43,x+60,y+50);
		line(x+60,y+50,x+50,y+50);
		//====================== Kinh
		line(x+30,y+5,x+40,y+5);
		line(x+40,y+5,x+47,y+17);
		line(x+30,y+5,x+23,y+17);
		line(x+23,y+17,x+23,y+22);
		line(x+47,y+17,x+47,y+22);
		//
		line(x+32,y+17,x+38,y+17);
		//
		line(x+23,y+22,x+27,y+22);
		line(x+47,y+22,x+43,y+22);
		line(x+27,y+22,x+32,y+17);
		line(x+43,y+22,x+38,y+17);
		//======================= Canh To Trai
		line(x+20,y+30,x+5,y+40);
		line(x+5,y+40,x+5,y+48);
		line(x+5,y+48,x+10,y+48);
		rectangle(x,y+35,x+5,y+48);
		//======================= Canh To Phai
		line(x+50,y+30,x+65,y+40);
		line(x+65,y+40,x+65,y+48);
		line(x+65,y+48,x+60,y+48);
		rectangle(x+65,y+35,x+70,y+48);
		// size(70,50)
		Object::draw();
	}
}
void Player::moveLeft(){ position=position-speed.X(); }
void Player::moveRight(){ position=position+speed.X(); }
void Player::moveUp(){ position.sub(speed.Y());}
void Player::moveDown(){ position.add(speed.Y());}
