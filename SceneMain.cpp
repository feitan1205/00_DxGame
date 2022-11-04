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
	m_movecount = 0;
	m_existcount = 0;
	m_score = 0;
}

SceneMain::~SceneMain()
{

}

// 初期化
void SceneMain::init()
{

	m_menuWindow.init();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_object[i][j].init();
		}
	}

	for (int i = 0; i < 2; i++) {

		m_tmpx = GetRand(3);
		m_tmpy = GetRand(3);

		if (i == 1) {
			if (m_object[m_tmpx][m_tmpy].getisExist()) {
				i--;
				continue;
			}
		}

		m_object[m_tmpx][m_tmpy].setData(((GetRand(1) + 1) * 2));
	}

	/*m_object[2][3].setData(16);
	m_object[2][2].setData(16);
	m_object[3][1].setData(8);
	m_object[3][2].setData(8);
	m_object[3][3].setData(4);*/

	m_isMenu = false;
	m_isOpenWindow = false;

	
}

// 終了処理
void SceneMain::end()
{

	m_menuWindow.end();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_object[i][j].end();
		}
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
	

	m_tmpx = 0;
	m_tmpy = 0;

	if (Pad::isTrigger(PAD_INPUT_UP)) {
		
		moveObject(0, -1,0,4);

		if (m_movecount != 0) {
			creatObject();
		}

	}
	else if (Pad::isTrigger(PAD_INPUT_DOWN)) {

		moveObject(0, 1,4,0);

		if (m_movecount != 0) {
			creatObject();
		}
	}
	else if (Pad::isTrigger(PAD_INPUT_LEFT)) {

		moveObject(-1, 0,0,4);

		if (m_movecount != 0) {
			creatObject();
		}
	}
	else if (Pad::isTrigger(PAD_INPUT_RIGHT)) {

		moveObject(1, 0,4,0);

		if (m_movecount != 0) {
			creatObject();
		}
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


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_object[i][j].update();
		}
	}

	if (Pad::isTrigger(PAD_INPUT_8)) {
		m_isMenu = true;
	}

}

// 毎フレームの描画
void SceneMain::draw()
{

	SetFontSize(30);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "スコア：%d", m_score, true);
	SetFontSize(16);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			DrawBox(100 * (i + 1), 100 * (j + 1), 100 * (i + 1) + 100, 100 * (j + 1) + 100, GetColor(255, 255, 255), false);
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (m_object[i][j].getisExist()) {
				m_object[i][j].draw(i,j);
			}
		}
	}

	if (m_isOpenWindow) DrawFormatString(0, 0, GetColor(255, 0, 0), "・", true);

	if (m_isOpenWindow) {

		m_menuWindow.draw();

	}

}

void SceneMain::moveObject(int vec_x, int vec_y, int minNum, int maxNum){

	m_existcount = 0;
	m_movecount = 0;

	if (minNum == 0) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {


				if (m_object[i][j].getisExist()) {

					if (vec_x != 0) {

						for (int s = i - 1; s > -1; s--) {

							if (m_object[s][j].getisExist()) {

								if (m_object[s][j].getisIncrease()) {
									break;
								}

								if (m_object[s][j].getObjectNum() == m_object[i][j].getObjectNum() ||
									m_object[s][j].getObjectNum() == m_object[s + 1][j].getObjectNum()) {
									m_object[s][j].increaseNum();
									m_object[s + 1][j].init();
									m_object[i][j].init();
									m_score += m_object[s][j].getObjectNum();
									m_movecount++;
								}

								break;
							}

							if (s == i - 1) {
								m_object[s][j] = m_object[i][j];
								m_object[i][j].init();
								m_movecount++;
							}
							else {
								m_object[s][j] = m_object[s + 1][j];
								m_object[s + 1][j].init();
								m_movecount++;
							}

						}

					}

					if (vec_y != 0) {

						for (int s = j - 1; s > -1; s--) {

							if (m_object[i][s].getisExist()) {

								if (m_object[i][s].getisIncrease()) {
									break;
								}

								if (m_object[i][s].getObjectNum() == m_object[i][j].getObjectNum() ||
									m_object[i][s].getObjectNum() == m_object[i][s + 1].getObjectNum()) {
									m_object[i][s].increaseNum();
									m_object[i][s + 1].init();
									m_object[i][j].init();
									m_score += m_object[i][s].getObjectNum();
									m_movecount++;
								}
								break;
							}

							if (s == j - 1) {
								m_object[i][s] = m_object[i][j];
								m_object[i][j].init();
								m_movecount++;
							}
							else {
								m_object[i][s] = m_object[i][s + 1];
								m_object[i][s + 1].init();
								m_movecount++;
							}

						}

					}

				}
			}
		}
	}


	if (minNum == 4) {
		for (int i = 3; i >= 0; i--) {
			for (int j = 3; j >= 0; j--) {


				if (m_object[i][j].getisExist()) {

					if (vec_x != 0) {

						for (int s = i + 1; s < 4; s++) {

							if (m_object[s][j].getisExist()) {

								if (m_object[s][j].getisIncrease()) {
									break;
								}

								if (m_object[s][j].getObjectNum() == m_object[i][j].getObjectNum() ||
									m_object[s][j].getObjectNum() == m_object[s - 1][j].getObjectNum()) {
									m_object[s][j].increaseNum();
									m_object[s - 1][j].init();
									m_object[i][j].init();
									m_score += m_object[s][j].getObjectNum();
									m_movecount++;
								}
								break;
							}

							if (s == i + 1) {
								m_object[s][j] = m_object[i][j];
								m_object[i][j].init();
								m_movecount++;
							}
							else {
								m_object[s][j] = m_object[s - 1][j];
								m_object[s - 1][j].init();
								m_movecount++;
							}

						}

					}

					if (vec_y != 0) {

						for (int s = j + 1; s < 4; s++) {

							if (m_object[i][s].getisExist()) {

								if (m_object[i][s].getisIncrease()) {
									break;
								}

								if (m_object[i][s].getObjectNum() == m_object[i][j].getObjectNum() ||
									m_object[i][s].getObjectNum() == m_object[i][s - 1].getObjectNum()) {
									m_object[i][s].increaseNum();
									m_object[i][s - 1].init();
									m_object[i][j].init();
									m_score += m_object[i][s].getObjectNum();
									m_movecount++;
								}
								break;
							}

							if (s == j + 1) {
								m_object[i][s] = m_object[i][j];
								m_object[i][j].init();
								m_movecount++;
							}
							else {
								m_object[i][s] = m_object[i][s - 1];
								m_object[i][s - 1].init();
								m_movecount++;
							}

						}

					}

				}
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (m_object[i][j].getisExist()) {
				m_existcount++;
			}
		}
	}

	if (m_movecount == 0 && m_existcount == 16) m_isGameEnd = true;

}

void SceneMain::creatObject() {

	bool isCreat = false;

	int address = -1;

	int creatNum = GetRand(4);

	while (!isCreat) {

		m_tmpx = GetRand(3);
		m_tmpy = GetRand(3);

		if (!m_object[m_tmpx][m_tmpy].getisExist()) isCreat = true;
			
		if (isCreat && creatNum == 0) {
			m_object[m_tmpx][m_tmpy].setData(4);
		}
		if (isCreat && creatNum != 0) {
			m_object[m_tmpx][m_tmpy].setData(2);
		}

	}
}