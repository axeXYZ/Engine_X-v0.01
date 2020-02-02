#include "Dwarf_Player.h"

//#include <RectEntity.h>
#include <PixelMiner_Map.h>

Dwarf_Player::Dwarf_Player()
{
}

void Dwarf_Player::Draw()
{
	m_Animation.Draw();

	

	bart::Engine::Instance().GetGraphic().Draw(m_Collider);
}

void Dwarf_Player::Update(float aDeltaTime)
{
	IInput& tInput = Engine::Instance().GetInput();
	
	SetCollX(m_Transform.X);
	SetCollY(m_Transform.Y);

	//aplly gravity	
	
	if (m_GravityActivated)
	{
		m_Transform.Translate(0.0f, m_Gravity);

		SetCollY(m_Transform.Y);

		if (m_CollisionLayer->IsColliding(m_Collider) != 0)
		{
			m_IsGrounded = true;
			m_Transform.Y = oldY;
			SetCollY(oldY);
		}
		else
		{
			m_IsGrounded = false;
		}
	}

	

	

	OnUpdate(mState, aDeltaTime);


	if (tInput.IsKeyDown(KEY_ESCAPE))
	{
		Load("GamePlay");
	}

	m_Animation.Update(&m_Transform, aDeltaTime);

	m_Camera->SetPosition(m_Transform.X - (400 - 32), m_Transform.Y - (300 - 32));
}

void Dwarf_Player::Start()
{
	IGraphic& tGraphic = GetGraphics();
	
	m_Animation.Load("Assets/Sprites/Humain01_Sprite.png");
	m_Animation.InitAnimation(13, 64, 64);
	
	//m_Transform.SetPosition(3670, 3790);
	//m_Transform.SetHeight(64);
	//m_Transform.SetWidth(64);

	OnEnter(STATE::IDLE);

	//m_Animation.Update(&m_Transform, 0);

	// --- Camera setup
	//m_Camera.SetViewport(0, 0, 816, 616);
	//tGraphic.SetCamera(&m_Camera);

	bart::IScene& scene = bart::Engine::Instance().GetScene();
	PixelMiner_Map* mapEntity = static_cast<PixelMiner_Map*>(scene.FindEntity("Map"));
	m_Camera = mapEntity->GetCamera();
	bart::TileMap* map = mapEntity->GetMap();

	m_CollisionLayer = map->GetLayer<bart::TileLayer>("MapAndCollider");
	m_Collider.Set(m_Transform.X +32 - 12, m_Transform.Y +32 - 12, 24, 24);

}

void Dwarf_Player::Destroy()
{
	//m_Map.Clean();
}

void Dwarf_Player::SetPosition(int aX, int aY)
{
	m_Transform.SetPosition(aX, aY);
}

void Dwarf_Player::SetSize(int aW, int aH)
{
	m_Transform.SetWidth(aW);
	m_Transform.SetHeight(aH);
}

void Dwarf_Player::OnEnter(STATE aState)
{
	if (mState != STATE::invialid)
	{
		OnExit(aState);
	}
	mState = aState;

	switch (mState)
	{
	case STATE::IDLE:
		m_Animation.Play(40, 1, 0.8f, true);
		break;

	case STATE::WALK:
		m_Animation.Play(11*13, 8, 0.1f, true);
		break;

	case STATE::MINE:
		m_Animation.Play(15*13, 5, 0.1f, false);
		break;

	case STATE::JUMP:
		m_GravityActivated = false;
		m_Delay = m_JumpDelay;
		break;

	case STATE::FREEFALL:

		break;
	default:
		break;
	}
}

void Dwarf_Player::OnExit(STATE aState)
{
	switch (mState)
	{
	case STATE::IDLE:			
		break;

	case STATE::WALK:
		break;

	case STATE::MINE:
		break;

	case STATE::JUMP:
		m_GravityActivated = true;
		break;

	case STATE::FREEFALL:
		break;

	case STATE::invialid:
		break;
	default:
		break;
	}
}

void Dwarf_Player::OnUpdate(STATE aState, float aDeltaTime)
{

	switch (mState)
	{
	case STATE::IDLE:
		OnIdleUpdate( aDeltaTime);
		break;

	case STATE::WALK:
		OnWalkUpdate( aDeltaTime);
		break;

	case STATE::MINE:
		OnMineUpdate( aDeltaTime);
		break;

	case STATE::JUMP:
		OnJumpUpdate( aDeltaTime);
		break;

	case STATE::FREEFALL:
		OnFreeFallUpdate(aDeltaTime);
		break;

	case STATE::invialid:
		break;
	default:
		break;
	}
}

void Dwarf_Player::OnIdleUpdate(float aDeltaTime)
{
	IInput& tInput = Engine::Instance().GetInput();
	oldY = m_Transform.Y;

	if (tInput.IsKeyDown(bart::EKeys::KEY_A))
	{
		m_Transform.SetFlip(true, false);
		m_Transform.Translate(-1 * m_SpeedMovement, 0);
		OnExit(STATE::IDLE);
		OnEnter(STATE::WALK);
		return;
	}
	if (tInput.IsKeyDown(bart::EKeys::KEY_D))
	{
		m_Transform.SetFlip(false, false);
		m_Transform.Translate(1 * m_SpeedMovement, 0);
		OnExit(STATE::IDLE);
		OnEnter(STATE::WALK);
		return;
	}

	if (tInput.IsKeyDown(bart::EKeys::KEY_SPACE))
	{
		OnExit(STATE::IDLE);
		OnEnter(STATE::JUMP);
		return;
	}

	if (tInput.IsKeyDown(bart::EKeys::KEY_F))
	{
		OnExit(STATE::IDLE);
		OnEnter(STATE::MINE);
		return;
	}

	
}

void Dwarf_Player::OnWalkUpdate(float aDeltaTime)
{
	IInput& tInput = Engine::Instance().GetInput();
	int oldX = m_Transform.X;

	if (tInput.IsKeyDown(bart::EKeys::KEY_A))
	{
		m_Transform.SetFlip(true, false);
		m_Transform.Translate(-1 * m_SpeedMovement, 0);
	}
	else if (tInput.IsKeyDown(bart::EKeys::KEY_D))
	{
		m_Transform.SetFlip(false, false);
		m_Transform.Translate(1 * m_SpeedMovement, 0);
	}
	else
	{
		OnExit(STATE::WALK);
		OnEnter(STATE::IDLE);
		return;
	}

	if (tInput.IsKeyDown(bart::EKeys::KEY_SPACE))
	{
		OnExit(STATE::IDLE);
		OnEnter(STATE::JUMP);
		return;
	}

	SetCollX(m_Transform.X);
	if (m_CollisionLayer->IsColliding(m_Collider))
	{
		m_Transform.X = oldX;
		SetCollX(oldX);
	}
	
}

void Dwarf_Player::OnJumpUpdate(float aDeltaTime)
{
	m_Transform.Translate(0, -1 * (m_JumpForce -= m_JumpDegradation));
	
	if (m_JumpForce < 0)
	{
		m_JumpForce = 4.0f;
		m_JumpDegradation = 0.2f;
		OnExit(STATE::JUMP);
		OnEnter(STATE::FREEFALL);
		return;
	}

	m_JumpDegradation * 2;
}

void Dwarf_Player::OnFreeFallUpdate(float aDeltaTime)
{
	IInput& tInput = Engine::Instance().GetInput();

	if (tInput.IsKeyDown(bart::EKeys::KEY_A))
	{
		m_Transform.SetFlip(true, false);
		m_Transform.Translate(-1 * m_SpeedMovement, 0);
	}
	else if (tInput.IsKeyDown(bart::EKeys::KEY_D))
	{
		m_Transform.SetFlip(false, false);
		m_Transform.Translate(1 * m_SpeedMovement, 0);
	}

	if (m_IsGrounded)
	{
		OnExit(STATE::FREEFALL);
		OnEnter(STATE::IDLE);
		return;
	}
}

void Dwarf_Player::SetCollX(int oX)
{
	m_Collider.X = oX +32 -12;
}
void Dwarf_Player::SetCollY(int oY)
{
	m_Collider.Y = oY +32;
}

void Dwarf_Player::OnMineUpdate(float aDeltaTime)
{
	IInput& tInput = Engine::Instance().GetInput();

	if (!m_Animation.GetPlaying())
	{
		OnExit(STATE::MINE);
		OnEnter(STATE::IDLE);
		return;
	}
}

void PlayerFactory::Create(const std::string & aName, const bart::Rectangle & aDest, float aAngle, bart::TiledProperties * aProps) const
{
	Dwarf_Player* newEntity = new Dwarf_Player();
	newEntity->SetPosition(aDest.X, aDest.Y);
	newEntity->SetSize(aDest.W, aDest.H);

	bart::Engine::Instance().GetScene().AddEntity(aName, newEntity);
}
