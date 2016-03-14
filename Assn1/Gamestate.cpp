#include "Gamestate.h"

State GameState::getState()
{
	return state;
}
void GameState::setState(GameState::State state) {
	this->state = state;
}
