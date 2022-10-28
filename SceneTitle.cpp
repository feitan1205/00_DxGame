#include "SceneTitle.h"
#include "DxLib.h"
#include "game.h"

void SceneTitle::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isGameStart = false;
	m_isGameEnd = false;

	m_menu.init();
	m_menu.addItem("ゲームスタート");
	m_menu.addItem("オプション");
	m_menu.addItem("ゲーム終了");

	m_menu.setPos(Game::kScreenWidth / 2 - 73, Game::kScreenHeight / 2 - 50);
	m_menu.setupCorsor();
}

void SceneTitle::update()
{
	// 文字の移動
	m_textPosY += m_textVecY;
	if (m_textPosY < 0)
	{
		m_textPosY = 0;
		m_textVecY = 4;
	}
	if (m_textPosY > 200)
	{
		m_textPosY = 200;
		m_textVecY = -4;
	}

	m_menu.update();

	m_isGameStart = m_menu.getisGameStart();

	m_isGameEnd = m_menu.getisGameEnd();
}

void SceneTitle::draw()
{
	m_menu.draw();
	//DrawString(0, m_textPosY, "タイトル画面", GetColor(255, 255, 255));
}