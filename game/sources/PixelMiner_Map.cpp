#include <PixelMiner_Map.h>
#include <Engine.h>
#include <RectEntity.h>
#include <Assets.h>
#include <Dwarf_Player.h>

#include <iostream>

PixelMiner_Map::PixelMiner_Map()
{
	m_Transform = new Transform();
	m_Fps = new FpsCounter();
}

void PixelMiner_Map::Draw()
{
	//m_Map.Draw();
	m_Map.Draw(m_Camera.GetViewport());

	m_Fps->Draw();
}

void PixelMiner_Map::Update(float aDeltaTime)
{
	//m_Camera.SetPosition(m_Player->GetTransform()->X, m_Player->GetTransform()->Y);

	m_Transform->SetPosition(m_Camera.GetX(), m_Camera.GetY());

	m_Fps->Update(m_Transform, aDeltaTime);
}

void PixelMiner_Map::Start()
{
	m_Map.Register("Player", new PlayerFactory());

	if (!m_Map.Load("Assets/Demo/PixelMinerMap.tmx"))
	{
		Engine::Instance().GetLogger().Log("Error loading map\n");
	}

	int tW = m_Map.GetMapWidth();
	int tH = m_Map.GetMapHeight();

	int tPW = tW * m_Map.GetTileWidth();
	int tPH = tH * m_Map.GetTileHeight();

	int tCenterX = (tPW / 2) - 400;
	int tCenterY = (tPH / 2) - 300;

	m_Camera.SetViewport(0, 0, 816, 616);
	m_Camera.SetPosition(tCenterX, tCenterY);
	
	Engine::Instance().GetGraphic().SetCamera(&m_Camera);

	
	m_Fps->Load(Assets::EIGHTBIT_WONDER_FONT);

	
}

void PixelMiner_Map::Destroy()
{
	m_Map.Clean();

	m_Fps->Unload();
	SAFE_DELETE(m_Fps);
	SAFE_DELETE(m_Transform);
}
