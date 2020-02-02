#ifndef PIXELMINER_MAP_H
#define PIXELMINER_MAP_H

#include <Entity.h>
#include <TileMap.h>
#include <Camera.h>
#include <FpsCounter.h>



using namespace bart;

class PixelMiner_Map final : public Entity
{
public:
	PixelMiner_Map();
	virtual ~PixelMiner_Map() = default;

	bool CanDraw() override { return true; }
	bool CanUpdate() override { return true; }

	void Draw() override;
	void Update(float aDeltaTime) override;
	void Start() override;
	void Destroy() override;

	TileMap* GetMap() { return &m_Map; }
	Camera* GetCamera() { return &m_Camera; }

private:

	TileMap m_Map;
	Camera m_Camera;

	FpsCounter* m_Fps;
	Transform* m_Transform{ nullptr };

};

#endif
