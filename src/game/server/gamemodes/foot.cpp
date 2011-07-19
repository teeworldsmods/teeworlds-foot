/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "foot.h"
//#include <engine/shared/config.h>
//#include <game/server/entities/character.h>
//#include <game/server/player.h>
//#include <game/server/gamecontext.h>

CGameControllerFOOT::CGameControllerFOOT(class CGameContext *pGameServer)
: IGameController(pGameServer)
{
	m_pGameType = "Teefoot";
	
	m_GameFlags = GAMEFLAG_TEAMS;
}

void CGameControllerFOOT::Tick()
{
	DoTeamScoreWincheck();
	
	IGameController::Tick();
}

void CGameControllerFOOT::StartRound()
{
	IGameController::StartRound();

	BallSpawning = 5 * Server()->TickSpeed() + Server()->Tick();
}

int CGameControllerFOOT::OnGoalRed(int Owner)
{	//do scoreing teams
	IGameController::OnGoalRed(Owner);

	CCharacter* Character = GameServer()->m_apPlayers[Owner]->GetCharacter();
	if(!Character)
		return 0;

	CPlayer* Player = Character->GetPlayer();

	if(Player->GetTeam() == 1)
		m_aTeamscore[TEAM_BLUE]++;
	else if(Player->GetTeam() == 0)
		m_aTeamscore[TEAM_RED]--;

	GameServer()->CreateSoundGlobal(SOUND_CTF_DROP);

	//ResetEverything();

	return 0;
}

int CGameControllerFOOT::OnGoalBlue(int Owner)
{	//do scoreing teams
	IGameController::OnGoalBlue(Owner);

	CCharacter* Character = GameServer()->m_apPlayers[Owner]->GetCharacter();
	if(!Character)
		return 0;

	CPlayer* Player = Character->GetPlayer();

	if(Player->GetTeam() == 0)
		m_aTeamscore[TEAM_RED]++;
	else if(Player->GetTeam() == 1)
		m_aTeamscore[TEAM_BLUE]--;

	GameServer()->CreateSoundGlobal(SOUND_CTF_DROP);

	//ResetEverything();

	return 0;
}

void CGameControllerFOOT::Snap(int SnappingClient)
{
	IGameController::Snap(SnappingClient);

	CNetObj_GameData *pGameDataObj = (CNetObj_GameData *)Server()->SnapNewItem(NETOBJTYPE_GAMEDATA, 0, sizeof(CNetObj_GameData));
	if(!pGameDataObj)
		return;

	pGameDataObj->m_TeamscoreRed = m_aTeamscore[TEAM_RED];
	pGameDataObj->m_TeamscoreBlue = m_aTeamscore[TEAM_BLUE];

	pGameDataObj->m_FlagCarrierRed = 0;
	pGameDataObj->m_FlagCarrierBlue = 0;
}