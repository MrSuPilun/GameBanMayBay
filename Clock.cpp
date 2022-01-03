#include "Clock.h"

// Khoi tao cac gia tri ban dau cua DONG HO
Clock::Clock(){
	msec=0;
	waitTime=0;
	isRun=false;
	isLoop=true;
}

// Huy cac gia tri cua dong ho
Clock::~Clock(){
	msec=0;
	waitTime=0;
	isRun=false;
	isLoop=false;
}

// Khoi tao cac gia tri ban dau cua DONG HO co tham so
Clock::Clock(int waitTime1, bool isRun1, bool isLoop1){
	msec=0;
	waitTime=waitTime1;
	isRun=isRun1;
	isLoop=isLoop1;
}

// Ham tre ve TRUE neu het gio
bool Clock::timeOut(){
	if(msec == waitTime)	
		return true;
	else
		return false;
}

// Lay thoi gian dem nguoc
int Clock::getWaitTime(){ return waitTime; }

// Lay so lan dem
int Clock::getMsec(){ return msec; } 

// Bat dau dem gio
void Clock::stop(){ Clock(); }

// Dung dem gio	
void Clock::start(){ isRun=true;}

// Tam dung dem gio
void Clock::pause(){ isRun=false; }

// Chay DONG HO
void Clock::run(){
	if(isRun){
		if(msec == waitTime){
			msec=0;
			isRun=isLoop;
		}		
		msec++;
	}
}

// Dat thoi gian dem nguoc
void Clock::setWaitTime(int x){ waitTime=x; }

// Dat thoi gian hien tai cua DONG HO
void Clock::setMsec(int x){ msec=x; }

