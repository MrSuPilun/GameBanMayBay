#include <bits/stdc++.h>
#include <windows.h>
#include <pthread.h>
#include "graphics.h"
#include "Vector2.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Clock.h"
using namespace std;
//------------------------------------------------------------------------------
//					KHAI BAO CAC BIEN MOI TRUONG, DOI TUONG
//------------------------------------------------------------------------------

// Kich thuoc man hinh game
const int SIZE_X = 800, SIZE_Y = 800; 

// Ma phim bam
enum KeyCode{
	ESC = 27,
	ENTER = 13,
	KEY_P = 112,
	KEY_T = 116
};

// Cac trang thai game
enum GameState{
	START = 0,		// Load man hinh cho
	PLAY = 1,		// Load man hinh game
	PAUSE = 2, 		// Tam dung tro choi
	END = 3 		// Load man hinh ket thuc game
};

// Cac loai dan
enum BulletType{
	BALL=0,			// Dan tron, sat thuong = 2
	LINE=1			// Dan vien, sat thuong = 1
};

// Khai bao cac bien moi truong
GameState gGameState = START;	// Trang thai game hien tai 
BulletType gBulletType = LINE;	// Loai dan hien tai
Player gShip;					// Phi thuyen cua nguoi choi

// Khai bao cac bo dem thoi gian
Clock gClockFire;			// Thoi gian load dan
Clock gClockNeonPlay;		// Thoi gian nhap nhay chu PLAY
Clock gClockSpamItem;		// Thoi gian xuat hien vat pham
Clock gClockSpamEnemy; 		// Thoi gian xuat hien ke dich
Clock gClockUpLevel;		// Thoi gian tang gLevel

// Khai bao cac danh dach lien ket
list<Enemy*> gpEnemyList; 				// Danh sach lien ket ke dich duoc tao ra
list<Bullet*> gpBulletList; 			// Danh sach lien ket cac vien dan duoc tao ra
list<BulletBall*> gpBulletBallList;		// Danh sach lien ket cac vien dan tron duoc tao ra
list<Items*> gpItemsList;				// Danh sach lien ket cac vat pham

// Cac bien moi truong trong tro choi
bool gIsShowBox = false; 		// Hien thi cac check box trong tro choi

// Khai bao, khoi tao cac bien trong tro choi
bool gIsFire = true;			// Cho phep ban cac VIEN DAN
bool gIsSound = true;			// Cho phep bat am thanh
int	gGunType = 1;				// So NONG SUNG
int gScore = 0;					// Diem
int gShotNum = gGunType;		// So VIEN DAN ban ra bang so NONG SUNG
char gSScore[] = "   0";		// Chuoi ky tu hien DIEM
char gSLife[] = "   0";			// Chuoi ky tu hien MANG
char gSLevel[] = "   0";		// Chuoi ky tu hien LEVEL

// UP LEVEL
int gLevel = 0;					// Level
int gTimeUpLevel = 500;			// Thoi gian dem nguoc tang gLevel
int gTimeSpamEnemy = 100;		// Thoi gian dem nguoc tao ke dich moi
int gSpeedEnemy = 1;			// Toc do cua ke dich

//------------------------------------------------------------------------------
//								KHAI BAO CAC HAM
//------------------------------------------------------------------------------
// Cac ham xu ly cac su kien trong game
void upLevel();					// Ham tang gLevel trong game

// Cac ham khoi tao cac doi tuong trong game
void newGame();
void newClocks();				// Ham khoi tao DONG HO DEM NGUOC
void newShip();					// Ham khoi tao PHI THUYEN
void newEnemy();				// Ham khoi tao KE DICH
void newItem();					// Ham khoi tao VAT PHAM
void newBullet(Vector2 x);		// Ham khoi tao VIEN DAN

// Cac ham thuc thi cac doi tuong
void applyEnemy();				// Ham ve, di chuyen, xoa cac doi tuong KE DICH
void applyBullet();				// Ham ve, di chuyen, xoa cac doi tuong VIEN DAN
void applyBulletBall();			// Ham ve, di chuyen, xoa cac doi tuong VIEN DAN TRON
void applyItem();				// HAM ve, di chuyen, xoa cac doi tuong VAT PHAM

void freeObject();
// Cac ham xu ly giao dien game UX/UI
void textSetting(int size);		// Ham thay doi cai dat font, size cua game 
char numToString(int n);		// Ham chuyen doi so thanh ky tu
void toString(int x, char s[]);	// Ham chuyen so sang chuoi
void uiStart();					// Ham ve giao dien bat dau game
void uiPlay();					// Ham ve giao dien cua game
void uiPause();					// Ham ve giao dien dung game
void uiEnd();					// Ham ve giao dien ket thuc game

// Cac ham thuc thi cac hoat dong cua PHI THUYEN
void fireBullet(Vector2 x);		// Ham ban cac VIEN DAN
void move(Player &x); 				// Ham kiem tra phim nhap va thuc hien di chuyen phi thuyen
void checkOutScreen(Player &x);	// Ham kiem tra phi thuyen co ra ngoai man hinh hay khong?

// Cac ham thuc thi tao vong lap, xu ly trong game
void _init(); 					// Ham khoi tao cac gia tri truoc khi vo game
void _input();					// Ham thuc hien cac su kien khi phim duoc nhan
void _sounds();					// Ham xu ly am thanh
void *_loop(void *threadid); 	// Thuc thi cac ham kiem tra va cham
void _physics();				// Ham tao thread de thuc hien cac tinh toan va cham
void _process();				// Noi chay cac ham ve, load man hinh
void _draw();					// Ham ve cac doi tuong
void _timer();					// Ham chua cac doi tuong tinh thoi gian

//------------------------------------------------------------------------------
//										MAIN
//------------------------------------------------------------------------------
main() {
	_init();
	_physics();
	while(true){	
		_sounds();
		_process();
	}	
}

//------------------------------------------------------------------------------
//					KHOI TAO CAC HAM THUC THI VONG LAP CUA GAME
//------------------------------------------------------------------------------
// Ham _init() khoi tao cac gia tri ban dau cho game
void _init(){	
	// Khoi tao man hinh game kich thuoc 800x800
	initwindow(SIZE_X, SIZE_Y); 	
	// Khoi tao cac doi tuong trong game
	newShip();			// Khoi tao PHII THUYEN
	newClocks();		// Khoi tao DONG HO DEM NGUOC
}

void _input(){
	if(gGameState==PLAY)
		move(gShip);
	fflush(stdin);
	if(kbhit())
		switch(getch()){
			case ESC:
				exit(0);
				break;
			case ENTER:
				switch(gGameState){
					case START:
						gGameState = PLAY;
						break;
					case END:
						gGameState = START;
						break;
				}
				break;
			case KEY_P:				
				switch(gGameState){
					case PLAY:
						gGameState = PAUSE;
						break;
					case PAUSE:
						gGameState = PLAY;
						break;
				}
				break;
			case KEY_T:
				gIsSound = !gIsSound;
				if(gIsSound)
					_sounds();			
				else					
					PlaySound(NULL, NULL, NULL);							
				break;			
		}
}
void _sounds(){
	if(gIsSound){
		switch(gGameState){
			case START:
				PlaySound(TEXT("HarnessTheWinds.wav"), NULL, SND_ASYNC);
				break;
			case PLAY:
				PlaySound(TEXT("ElementalSkylands.wav"), NULL, SND_ASYNC);
				break;
			case END:
				PlaySound(TEXT("GameOver.wav"), NULL, SND_ASYNC);
				break;
		}			
	}
	
}
void *_loop(void *threadid){
	while(true){		
		Vector2 LU = gShip.getPosition();
		Vector2 RU = gShip.getPosition() + gShip.getSize().X();
		Vector2 LD = gShip.getPosition() + gShip.getSize().Y();
		Vector2 RD = gShip.getPosition() + gShip.getSize();
		Vector2 MU = gShip.getPosition() + Vector2(45,0);
		Vector2 MD = gShip.getPosition() + Vector2(45,50);							
		checkOutScreen(gShip);
		if(!gpEnemyList.empty()){
			list<Enemy*>::iterator p;
			for(p = gpEnemyList.begin(); p != gpEnemyList.end(); p++){
				Enemy *e = *p;
				if(!gpBulletList.empty()){
					list<Bullet*>::iterator q;
					for(q = gpBulletList.begin(); q != gpBulletList.end(); q++)
					{
						Bullet *t = *q;
						if(e->checkCollision(t->getPosition()) && t->getLife()>0){
							t->subLife();
							e->subLife();
							if(e->getLife()==0)
								gScore++;							
						}
					}
				}
				if(!gpBulletBallList.empty()){
					list<BulletBall*>::iterator q;
					for(q = gpBulletBallList.begin(); q != gpBulletBallList.end(); q++)
					{
						BulletBall *t = *q;
						if(e->checkCollision(t->getPosition()) && t->getLife()>0){
							t->subLife();
							e->subLife();
							e->subLife();
							if(e->getLife()==0)
								gScore++;							
						}
					}
				}				
				if(e->getLife() > 0 && (e->checkCollision(LU) || e->checkCollision(RU) || e->checkCollision(LD) || e->checkCollision(RD) || e->checkCollision(MU) || e->checkCollision(MD))){
					e->setLife(0);
					gShip.subLife();
				}					
			}
		}
		if(!gpItemsList.empty()){
			list<Items*>::iterator q;
			for(q = gpItemsList.begin(); q != gpItemsList.end(); q++)
			{
				Items *i = *q;
				if(i->getLife() > 0 && (i->checkCollision(LU) || i->checkCollision(RU) || i->checkCollision(LD) || i->checkCollision(RD) || i->checkCollision(MU) || i->checkCollision(MD))){					
					switch(i->getItemType()){
						case 0:
							gShip.addLife();
							break;
						case 1:
							gGunType+=1;
							if(gGunType>3)
								gGunType=3;
							break;
						case 2:
							gBulletType = LINE;						
							break;
						case 3:
							gBulletType = BALL;							
							break;
					}
					i->setLife(0);					
				}	
			}
		}		
	}
}
void _physics(){
	pthread_t thread1;
	pthread_create(&thread1, NULL, _loop, (void *)1); // Tao 1 luong xu ly moi la threa1 chay ham _loop
}
void _timer(){
	switch(gGameState){
		case START:
			gClockNeonPlay.run();
			break;
		case PLAY:
			if(gClockFire.timeOut()){
				gIsFire=true;
				gShotNum=gGunType;
			}
			gClockFire.run();
			if(gClockSpamEnemy.timeOut()){
				newEnemy();				
			}
			gClockSpamEnemy.run();
			if(gClockSpamItem.timeOut()){
				newItem();
			}
			gClockSpamItem.run();
			if(gClockUpLevel.timeOut()){
				upLevel();
				gClockSpamEnemy.setWaitTime(gTimeSpamEnemy);				
				gClockSpamEnemy.setMsec(0);
			}
			gClockUpLevel.run();
			break;
	}
}
void _draw(){
	switch(gGameState){
		case START:
			uiStart();
			break;
		case PLAY:
			gShip.draw();
			applyEnemy();
			applyItem();
			applyBullet();
			applyBulletBall();
			uiPlay();
			break;
		case PAUSE:
			uiPause();
			break;
		case END:
			uiEnd();
			break;
	}	
	delay(1); // Dung man hinh 1 msec
	clearviewport(); // Xoa man hinh	
}
void _process(){
	switch(gGameState){
		case START:
			while(gGameState==START){
				_timer();				
				_input();
				_draw();							
			}
			newGame();
			break;
		case PLAY:			
			while(gGameState==PLAY){
				_timer();			
				_input();
				if(gShip.getLife()==0 || gLevel == 21){
					gGameState=END;					
					break;
				}	
				_draw();																																														
			}
			break;
		case PAUSE:
			while(gGameState==PAUSE){				
				_input();			
				_draw();					
			}					
			break;
		case END:
			freeObject();
			while(gGameState==END){			
				_timer();
				_input();
				_draw();							
			}
			break;
	}	
}
//------------------------------------------------------------------------------
//					KHOI TAO CAC HAM TAO CAC DOI TUONG TRONG GAME
//------------------------------------------------------------------------------
void newGame(){
	gIsFire=true;
	gScore = 0;
	gLevel = 0;		
	gGunType = 1;
	gTimeUpLevel = 500;
	gTimeSpamEnemy = 100;
	gSpeedEnemy = 1;
	gBulletType = LINE;
	newClocks();
	newShip();
}
void newClocks(){	
	gClockFire 		= Clock(10,true,true);
	gClockNeonPlay 	= Clock(100,true,true);
	gClockSpamItem 	= Clock(700,true,true);
	gClockSpamEnemy = Clock(gTimeSpamEnemy,true,true);
	gClockUpLevel 	= Clock(gTimeUpLevel,true,true);
}
void newShip(){
	gShip.setLife(3);	
	gShip.setPostion(Vector2(SIZE_X/2-35, SIZE_Y - 100));
	gShip.setSpeed(Vector2(5,5));
	gShip.setShowBox(gIsShowBox);	
}
void newEnemy(){
	int x = rand() % ((SIZE_X-70) - 0 + 1) + 0;
	Enemy *e = new Enemy();
	e->setPostion(Vector2(x,0));
	e->setSpeed(Vector2(2, gSpeedEnemy));
	e->setShowBox(gIsShowBox);
	if(gLevel<5)
		e->setDirection(0);
	else if(gLevel<10){
		int dir = rand() % (1-0+1) + 0;;
		e->setDirection(dir);	
	} else {
		if(gLevel>14)
			e->setSpeed(Vector2(5, gSpeedEnemy));
		e->setDirection(1);
	}
	gpEnemyList.push_front(e);
}
void newItem(){
	int x = rand() % ((SIZE_X-30) - 0 + 1) + 0;
	int t = rand() % (3-0+1) + 0;
	Items *i = new Items(Vector2(x, 0), Vector2(30,30), t);
	if(t==0)
		i->setSize(Vector2(32,32));
	i->setSpeed(Vector2(0,1));
	i->setShowBox(gIsShowBox);
	i->setLife(1);
	gpItemsList.push_front(i);
}
void newBullet(Vector2 x){	
	switch(gBulletType){
		case BALL:
			if(gIsFire){		
				BulletBall *b= new BulletBall();
				b->setRadius(5);
				b->setPostion(x);
				b->setSpeed(Vector2(0,-10));
				gpBulletBallList.push_front(b);
			}
			break;
		case LINE:
			if(gIsFire){		
				Bullet *b = new Bullet();
				b->setPostion(x);
				b->setSpeed(Vector2(0,-10));
				gpBulletList.push_front(b);							
			}
			break;
	}
	if(gShotNum==1){
		gIsFire=false;
	}	
	gShotNum--;
}
//------------------------------------------------------------------------------
//				KHOI TAO CAC HAM THUC THI CAC DOI TUONG TRONG GAME
//------------------------------------------------------------------------------
void applyEnemy(){
	if(!gpEnemyList.empty()){
		list<Enemy*>::iterator p;
		for(p = gpEnemyList.begin(); p != gpEnemyList.end(); p++){			
			Enemy *e = *p;
			e->draw();			
			e->move();
			if(e->getPosition().getY() > 810 || e->getLife() == 0){					
				delete e;
				gpEnemyList.remove(e);
			}						
		}
	}
}
void applyBullet(){
	if(!gpBulletList.empty()){
		list<Bullet*>::iterator p;
		for(p = gpBulletList.begin(); p != gpBulletList.end(); p++){
			Bullet *t = *p;
			t->draw();			
			t->move();			
			if(t->getPosition().getY() < -10 || t->getLife() == 0){	
				delete t;			
				gpBulletList.remove(t);								
			}				
		}
	}
}
void applyBulletBall(){
	if(!gpBulletBallList.empty()){
		list<BulletBall*>::iterator p;
		for(p = gpBulletBallList.begin(); p != gpBulletBallList.end(); p++){
			BulletBall *t = *p;
			t->draw();			
			t->move();			
			if(t->getPosition().getY() < -10 || t->getLife() == 0){	
				delete t;			
				gpBulletBallList.remove(t);								
			}				
		}
	}
}
void applyItem(){
	if(!gpItemsList.empty()){
		list<Items*>::iterator p;
		for(p = gpItemsList.begin(); p != gpItemsList.end(); p++){
			Items *i = *p;
			i->draw();
			i->move();			
			if(i->getPosition().getY() < -10 || i->getLife() == 0){	
				delete i;			
				gpItemsList.remove(i);								
			}				
		}
	}
}
void freeObject(){
	if(!gpEnemyList.empty()){
		list<Enemy*>::iterator p;
		for(p = gpEnemyList.begin(); p != gpEnemyList.end(); p++){
			Enemy *e = *p;						
			delete e;
			gpEnemyList.remove(e);
		}						
	}			
}
//------------------------------------------------------------------------------
//				KHOI TAO CAC HAM XU LY CAC SU KIEN TRONG GAME
//------------------------------------------------------------------------------
void move(Player &x){
	if(GetAsyncKeyState(VK_LEFT)){ x.moveLeft(); } 						// Di chuyen phi thuyen sang trai
	if(GetAsyncKeyState(VK_RIGHT)){ x.moveRight(); } 					// Di chuyen phi thuyen sang phai 
	if(GetAsyncKeyState(VK_UP)){ x.moveUp(); } 							// Di chuyen phi thuyen di len
	if(GetAsyncKeyState(VK_DOWN)){ x.moveDown(); } 						// Di chuyen phi thuyen di xuong
	if(GetAsyncKeyState(VK_SPACE)){ fireBullet(x.getPosition()); } 		// Ban dan	
}
void checkOutScreen(Player &p){
	int W = p.getSize().getX() + 5;
	int H = p.getSize().getY() + 5;
	int L = p.getPosition().getX();
	int R = p.getPosition().getX() + W;
	int U = p.getPosition().getY();
	int D = p.getPosition().getY() + H;
	if(L<0)
		p.setPostion(Vector2(0, U));
	if(R>SIZE_X)
		p.setPostion(Vector2(SIZE_X - W, U));
	if(U<0)
		p.setPostion(Vector2(L, 0));
	if(D>SIZE_Y - 100)
		p.setPostion(Vector2(L, SIZE_Y - H - 100));
}
void fireBullet(Vector2 x){
	Vector2 pos = x + (gShip.getSize()/2).X();	
	switch(gGunType){
		case 1:
			newBullet(pos);
			break;
		case 2:
			newBullet(x+Vector2(0,35));		
			newBullet(x+Vector2(65,35));
			break;
		case 3:
			newBullet(x+Vector2(0,35));			
			newBullet(pos);			
			newBullet(x+Vector2(65,35));
			break;
	}
}
void upLevel(){
	gLevel++;
	if(gLevel < 5)
		gTimeSpamEnemy-=20;
	else
		gTimeSpamEnemy--;
	if(gLevel < 10)
		gSpeedEnemy++;
}
//------------------------------------------------------------------------------
//				KHOI TAO CAC HAM VE GIAO DIEN TRONG GAME
//------------------------------------------------------------------------------
void textSetting(int size){
	settextstyle(SMALL_FONT, HORIZ_DIR, size);
}
char numToString(int n)     // chuyen so sang char
{
    return (char)(n+48);
}
void toString(int x, char s[]){
	int i=3;
	if(x==0)
		s[3] = '0';
	else
		while(x!=0){
			s[i--] = numToString(x%10);
			x/=10;
		}
}
void uiStart(){
	// ten game
	textSetting(20);
	outtextxy(120, 250, "GAME BAN MAY BAY");
	// tac gia
	textSetting(5);
	outtextxy(140, 300, "created by: Pham Ngoc An (pan)");
	// play button
	textSetting(8);
	if(gClockNeonPlay.getMsec()>40)
		outtextxy(220, 400, "press play [enter]");
	// tutorial
	textSetting(7);
	outtextxy(280, 450, "->TUTORIAL<-");
	outtextxy(220, 480, "-> Di chuyen: cac phim mui ten");
	outtextxy(220, 510, "-> Shot: phim SPACE");
	outtextxy(220, 540, "-> Pause: phim P");
	outtextxy(220, 570, "-> Sound on/off: phim T");
	outtextxy(220, 600, "-> Exit: phim ESC");
}
void uiPlay(){
	textSetting(7);
	toString(gScore, gSScore);
	toString(gLevel, gSLevel);
	toString(gShip.getLife(),gSLife);
	outtextxy(130, 720, gSScore);
	outtextxy(230, 720, gSLife);
	outtextxy(720, 720, gSLevel);
	rectangle(45, 715, 260, 745);
	outtextxy(50, 720, "Score: ");
	outtextxy(170,720, "Life:  ");
	outtextxy(650,720, "LEVEL:  ");
}
void uiPause(){
	textSetting(20);
	outtextxy(300, 250, "PAUSE");
	outtextxy(180, 350, "return to play [enter]");
}
void uiEnd(){	
	textSetting(20);
	if(gLevel==21)
		outtextxy(300, 200, "WINNER");
	else
		outtextxy(300, 200, "LOSER");
	outtextxy(200, 300, "SCORE: ");
	outtextxy(400, 300, gSScore);
	rectangle(180, 270, 600, 390);
	textSetting(8);
	outtextxy(180, 400, "outside the lobby [enter]");			
}

