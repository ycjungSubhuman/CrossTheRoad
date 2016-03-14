#pragma once

class GameState {
private:
	enum STATE {GAMEON, GAMEOVER};
	int score;
public:
	STATE getState();
	void setstate(STATE state);
};
