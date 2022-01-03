#ifndef Clock_H
#define Clock_H
class Clock{
	private:
		int msec;			// Thoi gian hien tai
		int waitTime;		// Thoi gian dem nguoc
		bool isRun;			// Cho phep chay dong ho
		bool isLoop;		// Cho phep lap lai bo dem gio
	public:
		Clock();												// Khoi tao cac gia tri ban dau cua DONG HO
		~Clock();
		Clock(int waitTime1, bool isRun1, bool isLoop1);		// Khoi tao cac gia tri ban dau cua DONG HO co tham so
		bool timeOut();											// Ham tre ve TRUE neu het gio
		int getWaitTime();										// Lay thoi gian dem nguoc
		int getMsec();											// Lay so lan dem
		void start();											// Bat dau dem gio
		void stop();											// Dung dem gio		
		void pause();											// Tam dung dem gio
		void run();												// Chay DONG HO
		void setWaitTime(int x);								// Dat thoi gian dem nguoc
		void setMsec(int x);									// Dat thoi gian hien tai cua DONG HO
};
#endif
