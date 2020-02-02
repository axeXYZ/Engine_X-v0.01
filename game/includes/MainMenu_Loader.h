#ifndef MAINMENU_LOADER_H
#define MAINMENU_LOADER_H

#include <GameState.h>

class MainMenu_Loader : public bart::GameState
{
public:
	virtual ~MainMenu_Loader() = default;
	void Load() override;
};

#endif
