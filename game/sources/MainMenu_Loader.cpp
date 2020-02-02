#include <MainMenu_Loader.h>

#include <Background_MainMenu.h>

void MainMenu_Loader::Load()
{
	Engine::Instance().GetScene().AddEntity("Background_MainMenu", new Background_MainMenu());
}
