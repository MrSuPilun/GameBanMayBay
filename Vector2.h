#ifndef Vector2_H
#define Vector2_H
class Vector2{
	private:
		float x;	// Toa do X
		float y;	// Toa do Y
	public:
		Vector2();								// Khoi tao cac gia tri ban dau cua Vector2
		~Vector2();
		Vector2(float x1, float y1);			// Khoi tao co tham so cac gia tri ban dau cua Vector2
		Vector2 get();							// Lay gia tri
		Vector2 UP();							// Tra ve Vector2(0,-1)
		Vector2 DOWN();							// Tra ve Vector2(0, 1)
		Vector2 LEFT();							// Tra ve Vector2(-1,0)
		Vector2 RIGHT();						// Tra ve Vector2(1, 0)
		Vector2 X();							// Tra ve Vector2(x, 0)
		Vector2 Y();							// Tra ve Vector2(0, y)
		Vector2 operator+(Vector2 b);			// Nap chong toan tu +
		Vector2 operator-(Vector2 b);			// Nap chong toan tu -
		Vector2 operator/(float b);				// Nap chong toan tu /
		Vector2 operator*(float b);				// Nap chong toan tu *
		int getX();								// Lay toa do X
		int getY();								// Lay toa do Y
		void setX(float x1);					// Gan gia tri X
		void setY(float y1);					// Gan gia tri Y
		void set(Vector2 b);					// Gan gia tri X, Y cho Vector
		void add(Vector2 b);					// Phep +
		void sub(Vector2 b);					// Phep -
};
#endif
