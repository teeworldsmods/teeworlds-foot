/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "foot.h"
//#include <game/server/entities/character.h>
//#include <game/server/player.h>
//#include <game/server/gamecontext.h>
#include <engine/shared/config.h>

CGameControllerFoot::CGameControllerFoot(class CGameContext *pGameServer) :
		IGameController(pGameServer)
{
	m_pGameType = "Foot";

	m_GameFlags = GAMEFLAG_TEAMS;
}

void CGameControllerFoot::Tick()
{
	IGameController::Tick();
}

void CGameControllerFoot::Reset()
{
	m_Passer = -1;
	CCharacter* pTemp;
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (GameServer()->m_apPlayers[i])
		{
			if ((pTemp = GameServer()->GetPlayerChar(i)) != NULL)
			{
				GameServer()->m_apPlayers[i]->m_RespawnTick = Server()->Tick()
						+ (g_Config.m_SvSpawnDelay *  Server()->TickSpeed()) / 1000;
				pTemp->Reset();
			}
			else if (GameServer()->m_apPlayers[i]->m_RespawnTick
					< Server()->Tick()
							+ (g_Config.m_SvSpawnDelay * Server()->TickSpeed())
									/ 1000)
			{
				GameServer()->m_apPlayers[i]->m_RespawnTick = Server()->Tick()
						+ (g_Config.m_SvSpawnDelay * Server()->TickSpeed()) / 1000;
			}
		}
	}
	GameServer()->CreateSoundGlobal(SOUND_CTF_CAPTURE);
	m_BallSpawning = Server()->Tick() + g_Config.m_SvBallRespawn * Server()->TickSpeed();
	GameServer()->m_World.RemoveEntities();
	GameServer()->m_World.RemoveProjectiles();
	GameServer()->m_World.m_ResetAtGoal = true;
}

void CGameControllerFoot::StartRound()
{
	IGameController::StartRound();

	m_BallSpawning = g_Config.m_SvBallRespawn * Server()->TickSpeed() + Server()->Tick();
}

int CGameControllerFoot::OnGoalRed(int Owner)
{ //do scoreing teams
	IGameController::OnGoalRed(Owner);
	if(!GameServer()->m_apPlayers[Owner])
	{
		Reset();
		return 0;
	}
	char aBuf[512];
	if(m_Passer != Owner && // Passer and Goaler not the same person
			m_Passer >= 0 && m_Passer < MAX_CLIENTS && // Passer ID is valid
			GameServer()->m_apPlayers[m_Passer] && // Passer player is valid
			GameServer()->m_apPlayers[m_Passer]->GetTeam() == GameServer()->m_apPlayers[Owner]->GetTeam() && // Goaler and Passer are in the same team
			GameServer()->m_apPlayers[Owner]->GetTeam() == TEAM_BLUE // Make sure it's not an own goal
			)
	{
		str_format(aBuf, sizeof(aBuf), "%s scored for the blue team with a pass from %s", Server()->ClientName(Owner), Server()->ClientName(m_Passer));
		IGameController::OnGoalRed(m_Passer);
		m_aTeamscore[TEAM_BLUE]++;
	}
	else
		str_format(aBuf, sizeof(aBuf), "%s scored for the blue team", Server()->ClientName(Owner));
	if (GameServer()->m_apPlayers[Owner]->GetTeam() == TEAM_BLUE)
		m_aTeamscore[TEAM_BLUE]++;
	else if (GameServer()->m_apPlayers[Owner]->GetTeam() == TEAM_RED)
		m_aTeamscore[TEAM_RED]--;

	GameServer()->CreateSoundGlobal(SOUND_CTF_DROP);

	GameServer()->SendBroadcast(aBuf, -1);
	Reset();

	return 0;
}

int CGameControllerFoot::OnGoalBlue(int Owner)
{ //do scoreing teams
	IGameController::OnGoalBlue(Owner);
	if(!GameServer()->m_apPlayers[Owner])
	{
		Reset();
		return 0;
	}
	char aBuf[512];
	if(m_Passer != Owner && // Passer and Goaler not the same person
			m_Passer >= 0 && m_Passer < MAX_CLIENTS && // Passer ID is valid
			GameServer()->m_apPlayers[m_Passer] && // Passer player is valid
			GameServer()->m_apPlayers[m_Passer]->GetTeam() == GameServer()->m_apPlayers[Owner]->GetTeam() && // Goaler and Passer are in the same team
			GameServer()->m_apPlayers[Owner]->GetTeam() == TEAM_RED // Make sure it's not an own goal
			)
	{
		str_format(aBuf, sizeof(aBuf), "%s scored for the red team with a pass from %s", Server()->ClientName(Owner), Server()->ClientName(m_Passer));
		IGameController::OnGoalBlue(m_Passer);
		m_aTeamscore[TEAM_RED]++;
	}
	else
		str_format(aBuf, sizeof(aBuf), "%s scored for the red team", Server()->ClientName(Owner));
	if (GameServer()->m_apPlayers[Owner]->GetTeam() == TEAM_RED)
		m_aTeamscore[TEAM_RED]++;
	else if (GameServer()->m_apPlayers[Owner]->GetTeam() == TEAM_BLUE)
		m_aTeamscore[TEAM_BLUE]--;

	GameServer()->CreateSoundGlobal(SOUND_CTF_DROP);

	GameServer()->SendBroadcast(aBuf, -1);
	Reset();

	return 0;
}

void CGameControllerFoot::Snap(int SnappingClient)
{
	IGameController::Snap(SnappingClient);

	CNetObj_GameData *pGameDataObj = (CNetObj_GameData *) Server()->SnapNewItem(
			NETOBJTYPE_GAMEDATA, 0, sizeof(CNetObj_GameData));
	if (!pGameDataObj)
		return;

	pGameDataObj->m_TeamscoreRed = m_aTeamscore[TEAM_RED];
	pGameDataObj->m_TeamscoreBlue = m_aTeamscore[TEAM_BLUE];

	pGameDataObj->m_FlagCarrierRed = 0;
	pGameDataObj->m_FlagCarrierBlue = 0;
}

void CGameControllerFoot::DoWincheck()
{
	if(m_GameOverTick == -1 && !m_Warmup && !GameServer()->m_World.m_ResetRequested)
	{
		if(IsTeamplay())
		{

			if(m_SuddenDeath)
			{
				if(abs(m_aTeamscore[TEAM_RED] - m_aTeamscore[TEAM_BLUE]) >= g_Config.m_SvSuddenDeathScoreDiff)
					EndRound();
			}
			// check score win condition
			else if((g_Config.m_SvScorelimit > 0 && (m_aTeamscore[TEAM_RED] >= g_Config.m_SvScorelimit || m_aTeamscore[TEAM_BLUE] >= g_Config.m_SvScorelimit)) ||
				(g_Config.m_SvTimelimit > 0 && (Server()->Tick()-m_RoundStartTick) >= g_Config.m_SvTimelimit*Server()->TickSpeed()*60))
			{
				if(m_aTeamscore[TEAM_RED] > m_aTeamscore[TEAM_BLUE] + g_Config.m_SvScoreDiff || m_aTeamscore[TEAM_BLUE] > m_aTeamscore[TEAM_RED] + g_Config.m_SvScoreDiff)
					EndRound();
				else
					m_SuddenDeath = 1;
			}
		}
	}
}
