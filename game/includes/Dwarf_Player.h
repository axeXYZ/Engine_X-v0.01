#ifndef DWARF_PLAYER_H
#define DWARF_PLAYER_H

#include <Entity.h>
#include <Animation.h>

#include <Camera.h>
#include <TileMap.h>
#include <TileLayer.h>


using namespace bart;

class Dwarf_Player final : public Entity
{
public:
	Dwarf_Player();
	virtual ~Dwarf_Player() = default;

	enum STATE
	{
		IDLE,
		WALK,
		MINE,
		JUMP,
		FREEFALL,
		invialid
	};

	bool CanDraw() override { return true; }
	bool CanUpdate() override { return true; }

	void Draw() override;
	void Update(float aDeltaTime) override;
	void Start() override;
	void Destroy() override;

	void SetPosition(int aX, int aY);
	void SetSize(int aW, int aH);

	Animation* GetAnimation() { return &m_Animation; }

	Transform* GetTransform() { return &m_Transform; }

private:

	const float m_Gravity = 2.0f;
	const float m_SpeedMovement{ 1 };

	float m_JumpForce = 4.0f;
	const float m_JumpDelay = 0.20f;
	float m_JumpDegradation = 0.2f;
	float m_Delay = 0;

	bool m_GravityActivated{ true };
	bool m_IsGrounded{ false };

	//int oldX = 0;
	int oldY = 0;

	STATE mState = STATE::invialid;

	void OnEnter(STATE aState);
	void OnExit(STATE aState);
	void OnUpdate(STATE aState, float aDeltaTime);

	void OnIdleUpdate(float aDeltaTime);
	void OnWalkUpdate(float aDeltaTime);
	void OnMineUpdate(float aDeltaTime);
	void OnJumpUpdate(float aDeltaTime);
	void OnFreeFallUpdate(float aDeltaTime);

	Animation m_Animation;
	Transform m_Transform;
	Camera* m_Camera;
	TileLayer* m_CollisionLayer{nullptr};

	Rectangle m_Collider;
	void SetCollX(int oX);
	void SetCollY(int oY);

	bool m_LeftCollision{ false };
	bool m_RightCollision{ false };

};

class PlayerFactory final : public bart::BaseFactory
{
public:
	void Create(const std::string& aName,
		const bart::Rectangle& aDest,
		float aAngle,
		bart::TiledProperties* aProps) const override;
};

#endif
