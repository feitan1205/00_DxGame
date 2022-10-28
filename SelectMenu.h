#pragma once

#include<vector>
#include "Vec2.h"

class SelectMenu {

public:

	SelectMenu();
	~SelectMenu();

	void init();
	void end();

	void update();


	void draw();

	void setupCorsor();

	int getWindouWidth();
	int getWindouHeight() { ; }

	void setPos(float x, float y);
	void setPos(Vec2 vec);

	void addItem(const char* text);

	bool getisGameEnd() { return m_cursor.getGameEnd(); }
	bool getisGameStart() { return m_cursor.getGameStart(); }

private:
	class Item {

	public:

		Item();
		virtual ~Item();

		void init();

		void draw(int x, int y);

		void setText(const char* text);

		void end();

		int getTextWidth();

	private:

		const char* m_text;
	};

	class Cursor {

	public:

		Cursor();
		virtual ~Cursor();

		void init();

		void update();

		void draw();

		void setMenuPos(Vec2 pos) { m_menuPos = pos; }
		void setSize(Vec2 size) { m_size = size; }
		bool getGameEnd() { return m_isGameEnd; }
		bool getGameStart() { return m_isGameStart; }
	private:

		// メニューの表示位置
		Vec2 m_menuPos;
		// カーソルのサイズ
		Vec2 m_size;
		// メニューの項目数
		int m_itemNum;

		// リピート入力カウンタ
		int m_repeatUp;
		int m_repeatDown;

		// 選択している項目の番号
		int m_selectIndex;

		bool m_isGameEnd;
		bool m_isGameStart;
	};

private:

	Vec2 m_pos;

	std::vector<Item*> m_pItem;

	Cursor m_cursor;

	int width;
};