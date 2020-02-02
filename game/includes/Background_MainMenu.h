#ifndef BACKGROUND_MAINMENU_H
#define BACKGROUND_MAINMENU_H

#include <Entity.h>
#include <Sprite.h>
#include <Atlas.h>

using namespace bart;

class Background_MainMenu final : public Entity
{
public:
	virtual ~Background_MainMenu() = default;

	bool CanDraw() override { return true; }
	bool CanUpdate() override { return true; }

	void Draw() override;
	void Update(float aDeltaTime) override;
	void Start() override;
	void Destroy() override;

	Sprite* GetBackground() { return &m_Background; }

	Transform* GetTransform() { return &m_Transform; }

private:

	Sprite m_Background;

	Transform m_Transform;
};

#endif
