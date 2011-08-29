/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>
#include "projectile.h"

#include <engine/shared/config.h>

CProjectile::CProjectile(CGameWorld *pGameWorld, int Type, int Owner, vec2 Pos, vec2 Dir, int Span,
		int Damage, bool Explosive, float Force, int SoundImpact, int Weapon)
: CEntity(pGameWorld, CGameWorld::ENTTYPE_PROJECTILE)
{
	m_Type = Type;
	m_Pos = Pos;
	m_Direction = Dir;
	m_LifeSpan = Span;
	m_Owner = Owner;
	m_Force = Force;
	m_Damage = Damage;
	m_SoundImpact = SoundImpact;
	m_Weapon = Weapon;
	m_StartTick = Server()->Tick();
	m_Explosive = Explosive;
	if((Dir.x < 0?-Dir.x:Dir.x) > (Dir.y < 0?-Dir.y:Dir.y))
		this->m_FootPickupDistance = abs(Dir.x * (float)Server()->TickSpeed() * GameServer()->Tuning()->m_GrenadeSpeed / 4000.0);
	else
		this->m_FootPickupDistance = abs(Dir.y * (float)Server()->TickSpeed() * GameServer()->Tuning()->m_GrenadeSpeed / 4000.0);

	GameWorld()->InsertEntity(this);
}

void CProjectile::Reset()
{
	GameServer()->m_World.DestroyEntity(this);
}

vec2 CProjectile::GetPos(float Time)
{
	float Curvature = 0;
	float Speed = 0;

	switch(m_Type)
	{
		case WEAPON_GRENADE:
			Curvature = GameServer()->Tuning()->m_GrenadeCurvature;
			Speed = GameServer()->Tuning()->m_GrenadeSpeed;
			break;

		case WEAPON_SHOTGUN:
			Curvature = GameServer()->Tuning()->m_ShotgunCurvature;
			Speed = GameServer()->Tuning()->m_ShotgunSpeed;
			break;

		case WEAPON_GUN:
			Curvature = GameServer()->Tuning()->m_GunCurvature;
			Speed = GameServer()->Tuning()->m_GunSpeed;
			break;
	}

	return CalcPos(m_Pos, m_Direction, Curvature, Speed, Time);
}


void CProjectile::Tick()
{
	if(str_comp_nocase(g_Config.m_SvGametype, "foot"))
	{
		float Pt = (Server()->Tick()-m_StartTick-1)/(float)Server()->TickSpeed();
		float Ct = (Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed();
		vec2 PrevPos = GetPos(Pt);
		vec2 CurPos = GetPos(Ct);
		int Collide = GameServer()->Collision()->IntersectLine(PrevPos, CurPos, &CurPos, 0);
		CCharacter *OwnerChar = GameServer()->GetPlayerChar(m_Owner);
		CCharacter *TargetChr = GameServer()->m_World.IntersectCharacter(PrevPos, CurPos, 6.0f, CurPos, OwnerChar);

		m_LifeSpan--;

		if(TargetChr || Collide || m_LifeSpan < 0 || GameLayerClipped(CurPos))
		{
			if(m_LifeSpan >= 0 || m_Weapon == WEAPON_GRENADE)
				GameServer()->CreateSound(CurPos, m_SoundImpact);

			if(m_Explosive)
				GameServer()->CreateExplosion(CurPos, m_Owner, m_Weapon, false);

			else if(TargetChr)
				TargetChr->TakeDamage(m_Direction * max(0.001f, m_Force), m_Damage, m_Owner, m_Weapon);

			GameServer()->m_World.DestroyEntity(this);
		}
	}
	else if(m_Weapon == WEAPON_GRENADE)
	{
			bool CanExplode = false; //<- should the grenade explode?

			float PreviousTick = (Server()->Tick()-m_StartTick-1)/(float)Server()->TickSpeed();
			float CurrentTick = (Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed();
			float NextTick = (Server()->Tick()-m_StartTick+1)/(float)Server()->TickSpeed();

			vec2 NextPosition = GetPos(NextTick);
			vec2 CurPosition = GetPos(CurrentTick);
			vec2 PrevPosition = GetPos(PreviousTick);
			vec2 CollisionPosition = vec2(0,0);
			vec2 FreePosition = vec2(0,0);

			CCharacter *OwnerChar = GameServer()->GetPlayerChar(m_Owner);
			CCharacter *TargetChr = GameServer()->m_World.IntersectCharacter(PrevPosition, CurPosition, 6.0f, CurPosition, OwnerChar);
			CCharacter *TChar;

			float TimeToCollision = -1.0f;
			for(float SearchTick1 = CurrentTick; SearchTick1 <= NextTick; SearchTick1 += (NextTick-CurrentTick)/30.0f)
			{
				vec2 TempPosition = GetPos(SearchTick1);
				if(GameServer()->Collision()->IsTileSolid((int) TempPosition.x, (int) TempPosition.y))
				{
					break;
				}
				TimeToCollision = SearchTick1;
			}
			if(TimeToCollision == -1.0f)
			{
				m_FootPickupDistance = 0;
				CanExplode = true;
				for(float SearchTick2 = CurrentTick; SearchTick2 > CurrentTick-1.0f; SearchTick2-=0.02f)
				{
					vec2 SearchPosition = GetPos(SearchTick2);
					if(!GameServer()->Collision()->IsTileSolid((int)SearchPosition.x, (int)SearchPosition.y))
					{
						TimeToCollision = SearchTick2;
						CollisionPosition = GetPos(SearchTick2+0.02f);
						FreePosition = GetPos(SearchTick2);
						CanExplode = false;
						break;
					}
				}
			}
			else
			{
				TimeToCollision += CurrentTick;
				CollisionPosition = GetPos(TimeToCollision+(NextTick-CurrentTick)/30.0f);
				FreePosition = GetPos(TimeToCollision);
			}
			if(TimeToCollision < NextTick-(NextTick-CurrentTick)/30.0f)
			{
				bool CollidedAtX = false;
				bool CollidedAtY = false;
				if(GameServer()->Collision()->IsTileSolid((int)FreePosition.x, (int)CollisionPosition.y))
				{
					CollidedAtY = true;
				}
				if(GameServer()->Collision()->IsTileSolid((int)CollisionPosition.x, (int)FreePosition.y))
				{
					CollidedAtX = true;
				}
				if(CollidedAtX)
				{
					m_Direction.x = -m_Direction.x/(g_Config.m_SvBounceLoss+100)*100;
					if (m_CollisionsByX >= 50)
					{
						GameServer()->m_pController->m_BallSpawning = Server()->Tick() + 4 * Server()->TickSpeed();
						GameServer()->m_World.DestroyEntity(this);
						GameServer()->CreateSound(CurPosition, m_SoundImpact);

						if(m_Explosive && g_Config.m_SvExplosions == 1)
							GameServer()->CreateExplosion(CurPosition, m_Owner, m_Weapon, false);
					}
					m_CollisionsByX++;
				}
				else
				{
					m_Direction.x = m_Direction.x/(g_Config.m_SvBounceLoss+100)*100;
					m_CollisionsByX = 0;
				}
				if(CollidedAtY)
				{
					m_Direction.y = -(m_Direction.y + 2*GameServer()->Tuning()->m_GrenadeCurvature/10000*GameServer()->Tuning()->m_GrenadeSpeed*(Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed())/(g_Config.m_SvBounceLoss+100)*100;
					if (m_CollisionByY >= 50)
					{
						GameServer()->m_pController->m_BallSpawning = Server()->Tick() + 4 * Server()->TickSpeed();
						GameServer()->m_World.DestroyEntity(this);
						GameServer()->CreateSound(CurPosition, m_SoundImpact);

						if(m_Explosive && g_Config.m_SvExplosions == 1)
							GameServer()->CreateExplosion(CurPosition, m_Owner, m_Weapon, false);
					}
					m_CollisionByY = m_CollisionByY + 1;
				}
				else
				{
					m_Direction.y = (m_Direction.y + 2*GameServer()->Tuning()->m_GrenadeCurvature/10000*(Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed()*GameServer()->Tuning()->m_GrenadeSpeed)/(g_Config.m_SvBounceLoss+100)*100;
					m_CollisionByY = 0;
				}

				m_Pos = FreePosition;
				m_StartTick = Server()->Tick();
				m_FootPickupDistance = 0;
			}
			if(m_FootPickupDistance == 0)
			{
				TChar = GameServer()->m_World.IntersectCharacter(PrevPosition, CurPosition, 6.0f, CurPosition, NULL);
			}
			else
			{
				m_FootPickupDistance--;
				TChar = GameServer()->m_World.IntersectCharacter(PrevPosition, CurPosition, 6.0f, CurPosition, OwnerChar);
			}
			if(TChar)
			{
					TChar->PlayerGetBall();
					GameServer()->m_World.DestroyEntity(this);
					m_LastOwner = m_Owner;
					TChar->m_LoseBallTick = Server()->Tick() + Server()->TickSpeed() * 3;
					GameServer()->m_pController->m_Passer = m_Owner;
			}
			else if(GameServer()->Collision()->isGoal((int)CurPosition.x,(int)CurPosition.y, false) && GameServer()->m_apPlayers[m_Owner] && GameServer()->m_apPlayers[m_Owner]->GetTeam() != -1)// && m_Owner > -1)
			{
				GameServer()->m_World.DestroyEntity(this);
				GameServer()->CreateExplosion(CurPosition, m_Owner, m_Weapon, true);
				GameServer()->m_pController->OnGoalRed(m_Owner);
				//game.controller->on_player_goal(game.players[owner], 0);
			}
			else if(GameServer()->Collision()->isGoal((int)CurPosition.x,(int)CurPosition.y, true) && GameServer()->m_apPlayers[m_Owner] && GameServer()->m_apPlayers[m_Owner]->GetTeam() != -1)// && m_Owner > -1)
			{
				GameServer()->m_World.DestroyEntity(this);
				GameServer()->CreateExplosion(CurPosition, m_Owner, m_Weapon, true);
				GameServer()->m_pController->OnGoalBlue(m_Owner);
				//game.controller->on_player_goal(game.players[owner], 1);
			}
			/*if(TargetChr && m_Weapon == WEAPON_GRENADE)
			{
				   TargetChr->PlayerGetBall();
				   GameServer()->m_World.DestroyEntity(this);
			}*/
			//CHARACTER *targetchr;
			/*
			if(pick_up_again == 0)
			{
				targetchr = game.world.intersect_character(prevpos, curpos, 6.0f, curpos, NULL);
			}
			else
			{
				pick_up_again--;
				targetchr = game.world.intersect_character(prevpos, curpos, 6.0f, curpos, game.get_player_char(owner));
			}
			game.controller->ball = curpos;
			if((targetchr && (targetchr->armor > 0 || config.sv_pickup_with_no_armor)) || --lifespan < 0 || explode)
			{
				if(explode || lifespan < 0)
				{
					game.controller->spawning = server_tick();
				}
				if(config.sv_explosions && (lifespan >= 0 || weapon == WEAPON_GRENADE))
					game.create_sound(curpos, sound_impact);

				if(flags & PROJECTILE_FLAGS_EXPLODE && config.sv_explosions)
					game.create_explosion(curpos, owner, weapon, false);
				else if(targetchr)
				{
					game.controller->passer = owner;
					targetchr->weapons[WEAPON_GRENADE].got = true;
					if(targetchr->weapons[WEAPON_GRENADE].ammo < 10)
						targetchr->weapons[WEAPON_GRENADE].ammo++;
					targetchr->active_weapon = WEAPON_GRENADE;
					targetchr->last_weapon = WEAPON_GRENADE;
					targetchr->fire_ball_tick = server_tick()+server_tickspeed()*config.sv_player_keeptime;
					targetchr->reload_timer = config.sv_ball_reloader;
				}

				game.world.destroy_entity(this);
			}
			else if (IsRedGoal((int)curpos.x,(int)curpos.y) && owner > -1 && game.players[owner] && game.players[owner]->team != -1)
			{
				game.world.destroy_entity(this);
				game.controller->on_player_goal(game.players[owner], 0);
			}
			else if (IsBlueGoal((int)curpos.x,(int)curpos.y) && owner > -1 && game.players[owner] && game.players[owner]->team != -1)
			{
				game.world.destroy_entity(this);
				game.controller->on_player_goal(game.players[owner], 1);
			}*/
		}
}

void CProjectile::FillInfo(CNetObj_Projectile *pProj)
{
	pProj->m_X = (int)m_Pos.x;
	pProj->m_Y = (int)m_Pos.y;
	pProj->m_VelX = (int)(m_Direction.x*100.0f);
	pProj->m_VelY = (int)(m_Direction.y*100.0f);
	pProj->m_StartTick = m_StartTick;
	pProj->m_Type = m_Type;
}

void CProjectile::Snap(int SnappingClient)
{
	float Ct = (Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed();

	if(NetworkClipped(SnappingClient, GetPos(Ct)))
		return;

	CNetObj_Projectile *pProj = static_cast<CNetObj_Projectile *>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, m_ID, sizeof(CNetObj_Projectile)));
	if(pProj)
		FillInfo(pProj);
}
