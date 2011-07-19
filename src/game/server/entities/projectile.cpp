/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>
//#include <game/server/gamecontroller.h>
#include "projectile.h"
//#include "character.h"

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
		this->pick_up_again = abs(Dir.x * (float)Server()->TickSpeed() * GameServer()->Tuning()->m_GrenadeSpeed / 4000.0);
	else
		this->pick_up_again = abs(Dir.y * (float)Server()->TickSpeed() * GameServer()->Tuning()->m_GrenadeSpeed / 4000.0);

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
	

	if(str_comp(g_Config.m_SvGametype, "foot") == 0 && m_Weapon == WEAPON_GRENADE)
	{
		bool CanExplode = false; //<- should the grenade explode?

		float Pt = (Server()->Tick()-m_StartTick-1)/(float)Server()->TickSpeed();
		float Ct = (Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed();
		float Nt = (Server()->Tick()-m_StartTick+1)/(float)Server()->TickSpeed();

		vec2 NextP = GetPos(Nt);
		vec2 CurP = GetPos(Ct);
		vec2 PrevP = GetPos(Pt);
		
		CCharacter *OwnerChar = GameServer()->GetPlayerChar(m_Owner);
		CCharacter *TargetChr = GameServer()->m_World.IntersectCharacter(PrevP, CurP, 6.0f, CurP, OwnerChar);
		CCharacter *TChar;

		float FreeTime = -1.0f;
		for(float i = Ct; i <= Nt; i += (Nt-Ct)/30.0f)
		{
			vec2 tmp_pos = GetPos(i);
			if(GameServer()->Collision()->col_is_solid((int) tmp_pos.x, (int) tmp_pos.y))
			{
				break;
			}
			FreeTime = i;
		}
		vec2 ColPos = vec2(0,0);
		vec2 FreePos = vec2(0,0);
		if(FreeTime == -1.0f)
		{
			pick_up_again = 0;
			CanExplode = true;
			for(float St = Ct; St > Ct-1.0f; St-=0.02f)
			{
				vec2 SearchPos = GetPos(St);
				if(!GameServer()->Collision()->col_is_solid((int)SearchPos.x, (int)SearchPos.y))
				{
					FreeTime = St;
					ColPos = GetPos(St+0.02f);
					FreePos = GetPos(St);
					CanExplode = false;
					break;
				}
			}
		}
		else
		{
			FreeTime += Ct;
			ColPos = GetPos(FreeTime+(Nt-Ct)/30.0f);
			FreePos = GetPos(FreeTime);
		}
		if(FreeTime < Nt-(Nt-Ct)/30.0f)
		{
			bool coll_x = false;
			bool coll_y = false;
			if(GameServer()->Collision()->col_is_solid((int)FreePos.x, (int)ColPos.y))
			{
				coll_y = true;
			}
			if(GameServer()->Collision()->col_is_solid((int)ColPos.x, (int)FreePos.y))
			{
				coll_x = true;
			}
			if(coll_x)
			{
				m_Direction.x = -m_Direction.x/(g_Config.m_SvBounceLossX+100)*100;
				if (colbx >= 50)
				{	
					GameServer()->m_pController->BallSpawning = Server()->Tick() + 4 * Server()->TickSpeed();
					GameServer()->m_World.DestroyEntity(this);
					GameServer()->CreateSound(CurP, m_SoundImpact);
					
                   if(m_Explosive && g_Config.m_SvExplosions == 1)
						GameServer()->CreateExplosion(CurP, m_Owner, m_Weapon, false);
				}
				colbx = colbx + 1;
			}
			else
			{
				m_Direction.x = m_Direction.x/(g_Config.m_SvBounceLossX+100)*100;
				colbx = 0;
			}
			if(coll_y)
			{
				m_Direction.y = -(m_Direction.y + 2*GameServer()->Tuning()->m_GrenadeCurvature/10000*GameServer()->Tuning()->m_GrenadeSpeed*(Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed())/(g_Config.m_SvBounceLossY+100)*100;
				if (colby >= 50)
				{
					GameServer()->m_pController->BallSpawning = Server()->Tick() + 4 * Server()->TickSpeed();
					GameServer()->m_World.DestroyEntity(this);
                    GameServer()->CreateSound(CurP, m_SoundImpact);

                   if(m_Explosive && g_Config.m_SvExplosions == 1)
						GameServer()->CreateExplosion(CurP, m_Owner, m_Weapon, false);
				}
				colby = colby + 1;
			}
			else
			{
				m_Direction.y = (m_Direction.y + 2*GameServer()->Tuning()->m_GrenadeCurvature/10000*(Server()->Tick()-m_StartTick)/(float)Server()->TickSpeed()*GameServer()->Tuning()->m_GrenadeSpeed)/(g_Config.m_SvBounceLossY+100)*100;
				colby = 0;
			}

			m_Pos = FreePos;
			m_StartTick = Server()->Tick();
			pick_up_again = 0;
		}
		if(pick_up_again == 0)
		{
			TChar = GameServer()->m_World.IntersectCharacter(PrevP, CurP, 6.0f, CurP, NULL);
		}
		else
		{
			pick_up_again--;
			TChar = GameServer()->m_World.IntersectCharacter(PrevP, CurP, 6.0f, CurP, OwnerChar);
		}
		if(TChar)
		{
			   TChar->PlayerGetBall();
			   GameServer()->m_World.DestroyEntity(this);
			   m_LastOwner = m_Owner;
			   TChar->HoldBallTick = Server()->Tick() + Server()->TickSpeed() * 3;
		}
		else if(GameServer()->Collision()->col_is_red((int)CurP.x,(int)CurP.y) && GameServer()->m_apPlayers[m_Owner]->GetTeam() != -1)// && m_Owner > -1)
		{
			GameServer()->m_World.DestroyEntity(this);
			GameServer()->CreateExplosion(CurP, m_Owner, m_Weapon, true);
			GameServer()->m_pController->OnGoalRed(m_Owner);
			//game.controller->on_player_goal(game.players[owner], 0);
		}
		else if(GameServer()->Collision()->col_is_blue((int)CurP.x,(int)CurP.y) && GameServer()->m_apPlayers[m_Owner]->GetTeam() != -1)// && m_Owner > -1)
		{
			GameServer()->m_World.DestroyEntity(this);
			GameServer()->CreateExplosion(CurP, m_Owner, m_Weapon, true);
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
		else if (col_is_red((int)curpos.x,(int)curpos.y) && owner > -1 && game.players[owner] && game.players[owner]->team != -1)
		{
			game.world.destroy_entity(this);
			game.controller->on_player_goal(game.players[owner], 0);
		}
		else if (col_is_blue((int)curpos.x,(int)curpos.y) && owner > -1 && game.players[owner] && game.players[owner]->team != -1)
		{
			game.world.destroy_entity(this);
			game.controller->on_player_goal(game.players[owner], 1);
		}*/
	}
	else
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
