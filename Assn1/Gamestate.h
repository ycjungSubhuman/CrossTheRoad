#pragma once

class GameState {
private:
	enum State {GAMEON, GAMEOVER};
	State state;
public:
	State getState();
	void setState(State state);
};
