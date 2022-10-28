#pragma once

#include "Vec2.h"

class Object {

public:

	Object();
	~Object();

	void init();
	void end();

	void setData(int x,int y, int Num);

	void update();
	void draw();

	bool getisExist() { return m_isExist; }

private:

	Vec2 m_Index;

	int m_objectNum;

	bool m_isExist;
};