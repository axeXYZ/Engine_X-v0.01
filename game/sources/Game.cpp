#include <Engine.h>

//#include <MainMenu.h>
//#include <GamePlay.h>
//#include <TestMaps.h>

#include <GamePlay_Loader.h>
#include <MainMenu_Loader.h>

using namespace bart;

#if USE_VLD
#include <vld.h>
#pragma comment(lib, "vld.lib")
#endif

void RegisterGameStates()
{
    //Engine::Instance().GetScene().Register("MainMenu", new MainMenu());
    //Engine::Instance().GetScene().Register("GamePlay", new GamePlay());
    //Engine::Instance().GetScene().Register("TestMap", new TestMap());

    Engine::Instance().GetScene().Register("MainMenu", new MainMenu_Loader());
    Engine::Instance().GetScene().Register("GamePlay", new GamePlay_Loader());
}

int main()
{
    if (Engine::Instance().Initialize("BLOKS", 800, 600))
    {
        RegisterGameStates();

        Engine::Instance().GetScene().Load("MainMenu");
        Engine::Instance().Start();
    }
    return 0;
}
