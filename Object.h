#pragma once

#include "Vec2.h"

class Object {

public:

	Object();
	~Object();

	void init();
	void end();

	void setData(float x, float y, int Num);

	void update();
	void draw();

	void moveObject(float vec_x, float vec_y);

	bool getisExist() { return m_isExist; }
	Vec2 getisIndex() { return m_Index; }

private:

	Vec2 m_Index;

	unsigned int Red;
	unsigned int Green;
	unsigned int Blue;

	int m_objectNum;

	bool m_isExist;
};