#include "Gameplay/PlayerBase.hpp"

using namespace Engine::Gameplay;
using namespace Engine::Utilities;

PlayerBase* PlayerBase::s_activePlayer = nullptr;

void PlayerBase::SetActivePlayer(PlayerBase* pPlayer)
{
	s_activePlayer = pPlayer;
	if (!(s_activePlayer->m_initialized))
	{
		s_activePlayer->Init();
		s_activePlayer->m_initialized = true;
	}
}

void PlayerBase::Init()
{
}

void PlayerBase::Process()
{
}

PlayerBase::PlayerBase()
	:m_initialized(false)
{
}

PlayerBase::~PlayerBase()
{
}
