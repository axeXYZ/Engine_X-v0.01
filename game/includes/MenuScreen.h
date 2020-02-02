#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <Entity.h>
#include <Sprite.h>
#include <Camera.h>

using namespace bart;

class MenuScreen final : public Entity
{
public:
    virtual ~MenuScreen() = default;
    MenuScreen();

    bool CanDraw() override { return true; }
    bool CanUpdate() override { return true; }
    void Draw() override;
    void Update(float aDeltaTime) override;
    void Start() override;
    void Destroy() override;

private:
    Sprite* m_MenuImage{nullptr};
    Transform* m_Transform{nullptr};
    Camera m_Camera;
};

#endif
