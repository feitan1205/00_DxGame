#include "SceneManager.h"
#include "SelectMenu.h"
#include "Pad.h"
#include <cassert>

SceneManager::SceneManager()
{
	m_kind = kSceneKindTitle;


}
SceneManager::~SceneManager()
{

}

void SceneManager::init(SceneKind kind)
{
	m_kind = kind;
	switch (m_kind)
	{
	case SceneManager::kSceneKindTitle:
		m_title.init();
		break;
	case SceneManager::kSceneKindMain:
		m_main.init();
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}

void SceneManager::end()
{
	switch (m_kind)
	{
	case SceneManager::kSceneKindTitle:
		m_title.end();
		break;
	case SceneManager::kSceneKindMain:
		m_main.end();
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}

void SceneManager::update()
{
	Pad::update();

	bool isEnd = false;
	switch (m_kind)
	{
	case SceneManager::kSceneKindTitle:
		m_title.update();
		isEnd = m_title.isGameStart();
		break;
	case SceneManager::kSceneKindMain:
		m_main.update();
		isEnd = m_main.isMenuOpen();
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
	if (isEnd)
	{
		switch (m_kind)
		{
		case SceneManager::kSceneKindTitle:
			m_title.end();
			m_main.init();
			m_kind = kSceneKindMain;
			break;
		case SceneManager::kSceneKindMain:
			m_main.end();
			m_title.init();
			m_kind = kSceneKindTitle;
			break;
		case SceneManager::kSceneKindNum:
		default:
			assert(false);
			break;
		}
	}

	m_isGameEnd = m_title.getisGameEnd();
	if (m_isGameEnd)		return;
	m_isGameEnd = m_main.getisGameEnd();
}

void SceneManager::draw()
{
	switch (m_kind)
	{
	case SceneManager::kSceneKindTitle:
		m_title.draw();
		break;
	case SceneManager::kSceneKindMain:
		m_main.draw();
		break;
	case SceneManager::kSceneKindNum:
	default:
		assert(false);
		break;
	}
}