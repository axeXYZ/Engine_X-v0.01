#ifndef GAMEPLAY_LOADER_H
#define GAMEPLAY_LOADER_H

#include <GameState.h>

class GamePlay_Loader : public bart::GameState
{
public:
	virtual ~GamePlay_Loader() = default;
	void Load() override;
};

#endif
