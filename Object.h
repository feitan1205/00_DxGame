#pragma once

#include "Vec2.h"

class Object {

public:

	Object();
	~Object();

	void init();
	void end();

	void setData(int Num);

	void update();
	void draw(int x, int y);

	void increaseNum();

	bool getisExist() { return m_isExist; }
	int getObjectNum() { return m_objectNum; }
	bool getisIncrease() { return m_isIncrease; }

private:


	unsigned int Red;
	unsigned int Green;
	unsigned int Blue;

	int m_objectNum;

	bool m_isExist;

	bool m_isIncrease;
};