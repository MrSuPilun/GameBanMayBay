#include "Vector2.h"

// Khoi tao cac gia tri ban dau cua Vector2
Vector2::Vector2(){ x=0; y=0; }

// Huy cac gia tri cua Vector2
Vector2::~Vector2(){ x=0; y=0; }

// Khoi tao co tham so cac gia tri ban dau cua Vector2
Vector2::Vector2(float x1, float y1){ x=x1; y=y1; }	

// Lay gia tri
Vector2 Vector2::get(){ return Vector2(x, y); }

// Tra ve Vector2(0,-1)
Vector2 Vector2::UP(){ return Vector2(0,-1); }

// Tra ve Vector2(0, 1)
Vector2 Vector2::DOWN(){ return Vector2(0,1); }

// Tra ve Vector2(-1,0)
Vector2 Vector2::LEFT(){ return Vector2(-1,0); }

// Tra ve Vector2(1, 0)
Vector2 Vector2::RIGHT(){ return Vector2(1,0); }

// Tra ve Vector2(x, 0)
Vector2 Vector2::X(){ return Vector2(this->x,0); }

// Tra ve Vector2(y, 0)
Vector2 Vector2::Y(){ return Vector2(0,this->y); }

// Nap chong toan tu +
Vector2 Vector2::operator+(Vector2 b){
	Vector2 temp;
	temp.x=this->x + b.getX();
	temp.y=this->y + b.getY();
	return temp;
}

// Nap chong toan tu -
Vector2 Vector2::operator-(Vector2 b){
	Vector2 temp;
	temp.x=this->x - b.x;
	temp.y=this->y - b.y;
	return temp;
}

// Nap chong toan tu /
Vector2 Vector2::operator/(float b){
	Vector2 temp;
	temp.x=this->x / b;
	temp.y=this->y / b;
	return temp;
}

// Nap chong toan tu *
Vector2 Vector2::operator*(float b){
	Vector2 temp;
	temp.x=this->x * b;
	temp.y=this->y * b;
	return temp;
}

// Lay toa do X
int Vector2::getX(){ return x; }

// Lay toa do Y
int Vector2::getY(){ return y; }

// Lay toa do X
void Vector2::setX(float x1){ x=x1; }

// Lay toa do Y
void Vector2::setY(float y1){ y=y1; }

// Gan gia tri X, Y cho Vector
void Vector2::set(Vector2 b){ 
	x=b.getX(); 
	y=b.getY(); 
}

// Phep +
void Vector2::add(Vector2 b){
	x = x + b.getX();
	y = y + b.getY();
}

// Phep +
void Vector2::sub(Vector2 b){
	x = x - b.getX();
	y = y - b.getY();
}
