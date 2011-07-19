/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "korace.h"
#include <game/server/gamecontext.h>
#include <engine/shared/config.h>

CGameControllerKORACE::CGameControllerKORACE(class CGameContext *pGameServer)
: IGameController(pGameServer)
{
	m_pGameType = "[K.o]Race";
	bNoDamage = true;
	g_Config.m_SvScorelimit = 0;
	g_Config.m_SvWarmup = 10;
	bRoundBegan = false;
	GameServer()->m_World.m_Paused = false;
}

void CGameControllerKORACE::Tick()
{	
	IGameController::Tick();

	PlayersInGame = 0;
		
	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		if(GameServer()->m_apPlayers[i] && GameServer()->m_apPlayers[i]->GetTeam() != TEAM_SPECTATORS)
		PlayersInGame += 1;
	}
	
	if(bRoundBegan)
	{
		if(PlayersInGame <= 0)
			EndRound(); //<- bug? O.o, we can't know, maybe a fail.. get sure..

		//get the lowest round and players in, if theres 1 last, kick him out of the game
		
		//we run max. 17 rounds if 16 players are in...
		int LowestRound = 17;
		int PlayersInLowestRound=0;
		bool TriedAgain = false;

TryAgain:
		//get the lowest round and how much players are in
		for(int i = 0; i < MAX_CLIENTS; i++)
	    {
			if(GameServer()->m_apPlayers[i] && GameServer()->m_apPlayers[i]->GetTeam() != TEAM_SPECTATORS)
			{
				if(GameServer()->m_apPlayers[i]->m_Score < LowestRound )
				{
						LowestRound = GameServer()->m_apPlayers[i]->m_Score;
						//Lower round found, active players in this round -> 1 and search if there more
						PlayersInLowestRound = 1;
				}
				else if(GameServer()->m_apPlayers[i]->m_Score == LowestRound)
					PlayersInLowestRound += 1;
			}
	    }

		//if there's only one last player in the last round, so kick him out
		if(LowestRound == 0 || LowestRound == 1)
		{
			//it's the beginn round, Round 0 and 1 are the same one, so search the last in round 0 and 1 and kick this noob out
			PlayersInLowestRound = 0;
			int PlayersCID = -1;
			for(int i = 0; i < MAX_CLIENTS; i++)
			{
				if(GameServer()->m_apPlayers[i] && GameServer()->m_apPlayers[i]->GetTeam() != TEAM_SPECTATORS && 
				(GameServer()->m_apPlayers[i]->m_Score == 0 || GameServer()->m_apPlayers[i]->m_Score == 1) )
				{
					PlayersInLowestRound += 1;
					PlayersCID = i;
				}
			}
			if(PlayersInLowestRound == 1)
			{
				GameServer()->m_apPlayers[PlayersCID]->SetTeam(-1);
				PlayersInGame -= 1;
				//last man standing? xD end round
				if(PlayersInGame == 1 && !m_Warmup)
				{
					bRoundBegan = false;
					EndRound();
				}
			}
		}
		else if(PlayersInLowestRound == 1)
		{
			//theres only 1 player left in this round, so kick this fucker out!
			for(int i = 0; i < MAX_CLIENTS; i++)
			{
				if(GameServer()->m_apPlayers[i] && GameServer()->m_apPlayers[i]->m_Score == LowestRound)
				{
					GameServer()->m_apPlayers[i]->SetTeam(-1);
					PlayersInGame -= 1;
					//last man standing? xD end round
					if(PlayersInGame == 1 && !m_Warmup)
					{
						bRoundBegan = false;
						EndRound();
					}
				}
			}
		}

		if(PlayersInLowestRound == 1 && !TriedAgain)
		{
			//maybe something went wrong, try again in this tick
			TriedAgain = true;
			goto TryAgain;
		}
	}

}
