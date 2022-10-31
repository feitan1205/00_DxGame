#pragma once

#include <vector>
#include "SceneBase.h"
#include "SceneMenuWindow.h"
#include "Object.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	// 初期化
	void init();
	// 終了処理
	void end();

	// 毎フレームの処理
	void update();
	// 毎フレームの描画
	void draw();

	bool isMenuOpen() { return m_isMenu; }
	bool getisGameEnd() { return m_isGameEnd; }

private:

	bool m_isMenu;

	bool m_isPlayerHit;

	bool m_isEnemyHit;

	bool m_isOpenWindow;

	bool m_isGameEnd;

	SceneMenuWindow m_menuWindow;

	Object m_object[16];

};