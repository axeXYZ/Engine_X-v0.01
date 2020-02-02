#ifndef QUESTBOX_H
#define QUESTBOX_H

#include <Entity.h>

using namespace bart;

class QuestBox final : public Entity
{
public:
	bool CanDraw() override { return true; }
	bool CanUpdate() override { return true; }

	void Draw() override;
	void Update(float aDeltaTime) override;
	void Start() override;
	void Destroy() override;

private:

};

#endif
