#include <Background_MainMenu.h>
#include <Engine.h>
#include <RectEntity.h>
#include <Assets.h>

void Background_MainMenu::Draw()
{
	IGraphic& tGraphic = GetGraphics();

	m_Background.Draw();
}

void Background_MainMenu::Update(float aDeltaTime)
{
	IInput& tInput = Engine::Instance().GetInput();

	if (tInput.IsKeyDown(KEY_SPACE))
	{
		Load("GamePlay");
	}

	m_Background.Update(&m_Transform, aDeltaTime);
}

void Background_MainMenu::Start()
{
	IGraphic& tGraphic = GetGraphics();

	m_Transform.SetPosition(0, 0);
	m_Transform.SetHeight(600);
	m_Transform.SetWidth(800);

	m_Background.Load("Assets/Sprites/BackgroundMainMenu.jpg");
}

void Background_MainMenu::Destroy()
{
}
