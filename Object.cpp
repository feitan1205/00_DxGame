#include "DxLib.h"
#include "Object.h"

Object::Object() :
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

	m_isExist = false;

}

void Object::end() {
}

void Object::setData(int Num) {

	m_isExist = true;

	m_objectNum = Num;

	if (m_objectNum == 2)	{ Red = 255; Green = 200; Blue = 200; }
	if (m_objectNum == 4) { Red = 255; Green = 150; Blue = 150; }
}

void Object::update() {

	m_isIncrease = false;

	if (m_objectNum == 2) { Red = 255; Green = 200; Blue = 200; }
	if (m_objectNum == 4) { Red = 255; Green = 150; Blue = 150; }
	if (m_objectNum == 8) { Red = 255; Green = 100; Blue = 100; }
	if (m_objectNum == 16) { Red = 255; Green = 50; Blue = 50; }
	if (m_objectNum == 32) { Red = 255; Green = 0; Blue = 0; }
	if (m_objectNum == 64) { Red = 200; Green = 255; Blue = 200; }
	if (m_objectNum == 128) { Red = 150; Green = 255; Blue = 150; }
	if (m_objectNum == 256) { Red = 100; Green = 255; Blue = 100; }
}

void Object::draw(int x,int y) {

	DrawBox(100 * (x + 1) + 1, 100 * (y + 1) + 1, 100 * (x + 1) + 99, 100 * (y + 1) + 99, GetColor(Red,Green, Blue), true);
	SetFontSize(50);
	DrawFormatString(100 * (x + 1), 100 * (y + 1), GetColor(255, 255, 255), "%d", m_objectNum,true);
	SetFontSize(16);
}

void Object::increaseNum() {

	m_objectNum *= 2;

	m_isIncrease = true;
}
