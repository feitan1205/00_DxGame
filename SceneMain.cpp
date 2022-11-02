#include "DxLib.h"
#include <cassert>
#include <vector>
#include "game.h"
#include "SceneMain.h"
#include "Pad.h"
#include "Vec2.h"

//bool CheckHit(Vec2 playerMinHitBox,Vec2 playerMaxHitBox,Vec2 objectMinHitBox,Vec2 objectMaxHitBox) {
//
//
//	if (playerMinHitBox.y > objectMaxHitBox.y)		return false;
//	if (playerMaxHitBox.y < objectMinHitBox.y)		return false;
//	if (playerMinHitBox.x > objectMaxHitBox.x)		return false;
//	if (playerMaxHitBox.x < objectMinHitBox.x)		return false;
//
//	return true;
//
//}

//bool CheckOutMap(Vec2 playerMinHitBox, Vec2 playerMaxHitBox, Vec2 minMapSize, Vec2 maxMapSize) {
//
//	bool OutMap = false;
//
//	if (playerMinHitBox.y < minMapSize.y)		OutMap = true;
//	if (playerMaxHitBox.y > maxMapSize.y)		OutMap = true;
//	if (playerMinHitBox.x < minMapSize.x)		OutMap = true;
//	if (playerMaxHitBox.x > maxMapSize.x)		OutMap = true;
//	
//	return OutMap;
//
//
//	//return false;
//}

SceneMain::SceneMain()
{
	m_isMenu = false;
	m_isPlayerHit = false;
	m_isEnemyHit = false;
	m_tmpx = 0;
	m_tmpy = 0;
}

SceneMain::~SceneMain()
{

}

// 初期化
void SceneMain::init()
{

	m_menuWindow.init();

	for (int i = 0; i < 16; i++) {
		m_object[i].init();
	}

	for (int i = 0; i < 2; i++) {
		m_object[i].setData(GetRand(3), GetRand(3), ((GetRand(1) + 1) * 2));
		if (i == 1) {
			if (m_object[i].getisIndex().x == m_object[i - 1].getisIndex().x &&
				m_object[i].getisIndex().y == m_object[i - 1].getisIndex().y) {
				i--;
				continue;
			}
		}
	}
	

	m_isMenu = false;
	m_isOpenWindow = false;

	
}

// 終了処理
void SceneMain::end()
{

	m_menuWindow.end();
	for (int i = 0; i < 16; i++) {
		m_object[i].end();
	}
	
}

// 毎フレームの処理
void SceneMain::update()
{

	if (m_isOpenWindow) {

		m_menuWindow.update();

		m_isGameEnd = m_menuWindow.getisGameEnd();

		return;
	}
	
	//m_object[0].setData(0, 0, 0);

	m_tmpx = 0;
	m_tmpy = 0;

	if (Pad::isTrigger(PAD_INPUT_UP)) {
		
		moveObject(0, -1);

		creatObject();

	}
	else if (Pad::isTrigger(PAD_INPUT_DOWN)) {

		creatObject();

	}
	else if (Pad::isTrigger(PAD_INPUT_LEFT)) {

		creatObject();

	}
	else if (Pad::isTrigger(PAD_INPUT_RIGHT)) {

		creatObject();

	}
	
	if (!m_isOpenWindow) {
		if (Pad::isTrigger(PAD_INPUT_4)) {
			m_isOpenWindow = true;
		}
	}
	else {
		if (Pad::isTrigger(PAD_INPUT_4)) {
			m_isOpenWindow = false;
		}
	}


	for (int i = 0; i < 16; i++) {
		m_object[i].update();
	}

	if (Pad::isTrigger(PAD_INPUT_8)) {
		m_isMenu = true;
	}

}

// 毎フレームの描画
void SceneMain::draw()
{

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			DrawBox(100 * (i + 1), 100 * (j + 1), 100 * (i + 1) + 100, 100 * (j + 1) + 100, GetColor(255, 255, 255), false);
		}
	}

	for (int i = 0; i < 16; i++) {
		if (m_object[i].getisExist()) {
			m_object[i].draw();
			DrawFormatString(0, i * 16, GetColor(255, 255, 255), "%f,%f", m_object[i].getisIndex().x, m_object[i].getisIndex().y, true);
		}
		if (!m_object[i].getisExist()) {
			DrawFormatString(0, i * 16, GetColor(255, 0, 0), "%d", i, true);
		}

	}

	if (m_isOpenWindow) DrawFormatString(0, 0, GetColor(255, 0, 0), "・", true);

	if (m_isOpenWindow) {

		m_menuWindow.draw();

	}

}

void SceneMain::moveObject(float vec_x, float vec_y) {



	for (int i = 0; i < 16; i++) {
		if (m_object[i].getisExist()) {
			for (int j = 0; j < 4; j++) {
				if (m_object[i].getisIndex().x + vec_x < 0 ||
					m_object[i].getisIndex().x + vec_x > 3 ||
					m_object[i].getisIndex().y + vec_y < 0 ||
					m_object[i].getisIndex().y + vec_y > 3) {
					break;
				}

				for (int k = 0; k < 16; k++) {
					if (i == k)		continue;


				}

				m_object[i].moveObject(vec_x, vec_y);
			}
		}
	}

}

void SceneMain::creatObject() {

	bool isCreat = false;
	int address = -1;

	while (!isCreat) {

		m_tmpx = GetRand(3);
		m_tmpy = GetRand(3);

		for (int i = 0; i < 16; i++) {

			if (!m_object[i].getisExist()) {

				for (int j = 0; j < 16; j++) {
					if (i == j)	continue;

					if (m_object[j].getisExist() &&
						static_cast<int>(m_object[j].getisIndex().x) == m_tmpx &&
						static_cast<int>(m_object[j].getisIndex().y) == m_tmpy) {
						isCreat = false;
						break;
					}

					isCreat = true;
					address = i;
				}
			}
			if (isCreat)	break;
		}

		if (isCreat) {
			m_object[address].setData(m_tmpx, m_tmpy, ((GetRand(1) + 1) * 2));
		}

	}

}