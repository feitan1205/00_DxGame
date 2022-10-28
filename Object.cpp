#include "DxLib.h"
#include "Object.h"

Object::Object() :
	m_Index(0,0),
	m_objectNum(0)
{
}

Object::~Object() {



}

void Object::init() {
}

void Object::end() {



}

void Object::setData(int x,int y,int Num) {

	m_Index.x = x;
	m_Index.y = y;
	m_objectNum = Num;
}

void Object::update() {



}

void Object::draw() {

	DrawBox(100 * (m_Index.x + 1) + 1, 100 * (m_Index.y + 1) + 1, 100 * (m_Index.x + 1) + 99, 100 * (m_Index.y + 1) + 99, GetColor(255,0, 0), true);

}