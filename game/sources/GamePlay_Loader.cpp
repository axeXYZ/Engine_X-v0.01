#include <GamePlay_Loader.h>
#include <Engine.h>

#include <PixelMiner_Map.h>
#include <Dwarf_Player.h>
#include <QuestBox.h>


void GamePlay_Loader::Load()
{
	//Engine::Instance().GetScene().AddEntity("Dwarf", new Dwarf_Player());
	Engine::Instance().GetScene().AddEntity("Map", new PixelMiner_Map());
	Engine::Instance().GetScene().AddEntity("QuestBox", new QuestBox());
}

