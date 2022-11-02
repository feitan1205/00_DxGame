#include "DxLib.h"
#include "Object.h"

Object::Object() :
	m_Index(0,0),
	m_objectNum(0),
	m_isExist(false),
	Red(0),
	Green(0),
	Blue(0)
{
}

Object::~Object() {



}

void Object::init() {
}

void Object::end() {
}

void Object::setData(float x, float y, int Num) {

	m_isExist = true;

	m_Index.x = x;
	m_Index.y = y;
	m_objectNum = Num;

	if (m_objectNum == 2)	{ Red = 255; Green = 0; Blue = 0; }
	if (m_objectNum == 4)	{ Red = 0; Green = 255; Blue = 0; }
}

void Object::update() {



}

void Object::draw() {

	DrawBox(100 * (static_cast<int>(m_Index.x) + 1) + 1, 100 * (static_cast<int>(m_Index.y) + 1) + 1, 100 * (static_cast<int>(m_Index.x) + 1) + 99, 100 * (static_cast<int>(m_Index.y) + 1) + 99, GetColor(Red,Green, Blue), true);
	SetFontSize(50);
	DrawFormatString(100 * (m_Index.x + 1), 100 * (m_Index.y + 1), GetColor(255, 255, 255), "%d", m_objectNum);
	SetFontSize(16);
}

void Object::moveObject(float vec_x, float vec_y) {

	m_Index.x += vec_x;
	m_Index.y += vec_y;

}
