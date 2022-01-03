#ifndef Object_H
#define Object_H
#include "Vector2.h"
#include "graphics.h"
class Object{
	protected:
		Vector2 position;	// Toa do
		Vector2 size;		// Kich thuoc
		Vector2 speed;		// Toc do
		bool isShowBox;		// True: ve check box
		int life;			// gSLife=0 => chet
	public:		
		Object();								// Khoi tao cac gia tri mac dinh cho Object
		~Object();
		Vector2 getPosition();					// Lay Vector VI TRI
		Vector2 getSize();						// Lay Vector KICH THUOC
		Vector2 getSpeed();						// Lay Vector TOC DO
		bool checkCollision(Vector2 c);			// Kiem tra va cham
		int getLife();							// Lay so MANG SONG
		void setShowBox(bool x);				// Gan gia tri ve check box
		void setLife(int x);					// Dat MANG SONG
		void setPostion(Vector2 p);				// Dat VI TRI
		void setSize(Vector2 s);				// Dat KICH THUOC
		void setSpeed(Vector2 b);				// Dat TOC DO
		void subLife();							// Tru 1 mang
		void addLife();							// Them 1 mang
		void draw();							// Ve
};
#endif 
