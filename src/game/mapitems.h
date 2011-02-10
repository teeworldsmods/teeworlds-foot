/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_MAPITEMS_H
#define GAME_MAPITEMS_H
#include<engine/shared/protocol.h>

// layer types
enum
{
	LAYERTYPE_INVALID=0,
	LAYERTYPE_GAME, // not used
	LAYERTYPE_TILES,
	LAYERTYPE_QUADS,
	
	MAPITEMTYPE_VERSION=0,
	MAPITEMTYPE_INFO,
	MAPITEMTYPE_IMAGE,
	MAPITEMTYPE_ENVELOPE,
	MAPITEMTYPE_GROUP,
	MAPITEMTYPE_LAYER,
	MAPITEMTYPE_ENVPOINTS,
	

	CURVETYPE_STEP=0,
	CURVETYPE_LINEAR,
	CURVETYPE_SLOW,
	CURVETYPE_FAST,
	CURVETYPE_SMOOTH,
	NUM_CURVETYPES,
	
	// game layer tiles
	ENTITY_NULL=0,
	ENTITY_SPAWN,
	ENTITY_SPAWN_RED,
	ENTITY_SPAWN_BLUE,
	ENTITY_FLAGSTAND_RED,
	ENTITY_FLAGSTAND_BLUE,
	ENTITY_ARMOR_1,
	ENTITY_HEALTH_1,
	ENTITY_WEAPON_SHOTGUN,
	ENTITY_WEAPON_GRENADE,
	ENTITY_POWERUP_NINJA,
	ENTITY_WEAPON_RIFLE,
	//DDRace - Main Lasers
	ENTITY_LASER_FAST_CW,
	ENTITY_LASER_NORMAL_CW,
	ENTITY_LASER_SLOW_CW,
	ENTITY_LASER_STOP,
	ENTITY_LASER_SLOW_CCW,
	ENTITY_LASER_NORMAL_CCW,
	ENTITY_LASER_FAST_CCW,
	//DDRace - Laser Modifiers
	ENTITY_LASER_SHORT,
	ENTITY_LASER_MEDIUM,
	ENTITY_LASER_LONG,
	ENTITY_LASER_C_SLOW,
	ENTITY_LASER_C_NORMAL,
	ENTITY_LASER_C_FAST,
	ENTITY_LASER_O_SLOW,
	ENTITY_LASER_O_NORMAL,
	ENTITY_LASER_O_FAST,
	//DDRace - Plasma
	ENTITY_PLASMAE=29,
	ENTITY_PLASMAF,
	ENTITY_PLASMA,
	ENTITY_PLASMAU,
	//DDRace - Shotgun
	ENTITY_CRAZY_SHOTGUN_EX,
	ENTITY_CRAZY_SHOTGUN,
	//DDRace - Draggers
	ENTITY_DRAGGER_WEAK=42,
	ENTITY_DRAGGER_NORMAL,
	ENTITY_DRAGGER_STRONG,
	//Draggers Behind Walls
	ENTITY_DRAGGER_WEAK_NW,
	ENTITY_DRAGGER_NORMAL_NW,
	ENTITY_DRAGGER_STRONG_NW,
	//Doors
	ENTITY_DOOR=49,
	//End Of Lower Tiles
	NUM_ENTITIES,
	//Start From Top Left
	//Tile Controllers
	TILE_AIR=0,
	TILE_SOLID,
	TILE_DEATH,
	TILE_NOHOOK,
	TILE_NOLASER,
	TILE_THROUGH = 6,
	TILE_FREEZE = 9,
	TILE_TELEINEVIL,
	TILE_UNFREEZE,
	TILE_DFREEZE,
	TILE_DUNFREEZE,
	TILE_EHOOK_START = 17,
	TILE_EHOOK_END,
	//Switches
	TILE_SWITCHTIMEDOPEN = 22,
	TILE_SWITCHTIMEDCLOSE,
	TILE_SWITCHOPEN,
	TILE_SWITCHCLOSE,
	TILE_TELEIN,
	TILE_TELEOUT,
	TILE_BOOST,
	TILE_BEGIN = 33,
	TILE_END,
	TILE_STOP = 60,
	TILE_STOPS,
	TILE_STOPA,
	TILE_CP = 64,
	TILE_CP_F,
	TILE_OLDLASER = 71,
	TILE_NPC,
	TILE_EHOOK,
	TILE_NOHIT,
	TILE_NPH,//Remember to change this in collision.cpp if you add anymore tiles
	//End of higher tiles
	//Layers
	LAYER_GAME=0,
	LAYER_FRONT,
	LAYER_TELE,
	LAYER_SPEEDUP,
	LAYER_SWITCH,
	NUM_LAYERS,
	//Flags
	TILEFLAG_VFLIP=1,
	TILEFLAG_HFLIP=2,
	TILEFLAG_OPAQUE=4,
	TILEFLAG_ROTATE=8,
	//Rotation
	ROTATION_0 = 0,
	ROTATION_90 = TILEFLAG_ROTATE,
	ROTATION_180 = (TILEFLAG_VFLIP|TILEFLAG_HFLIP),
	ROTATION_270 = (TILEFLAG_VFLIP|TILEFLAG_HFLIP|TILEFLAG_ROTATE),
	
	LAYERFLAG_DETAIL=1,
	
	ENTITY_OFFSET=255-16*4,
	//OLD ENTITIES FROM STABLE + Fluxid's HookThrough
	OLD_NULL=0,
	OLD_SPAWN,
	OLD_SPAWN_RED,
	OLD_SPAWN_BLUE,
	OLD_FLAGSTAND_RED,
	OLD_FLAGSTAND_BLUE,
	OLD_ARMOR_1,
	OLD_HEALTH_1,
	OLD_WEAPON_SHOTGUN,
	OLD_WEAPON_GRENADE,
	OLD_POWERUP_NINJA,
	OLD_WEAPON_RIFLE,

	//DDRace
	OLD_LASER_FAST_CW,
	OLD_LASER_NORMAL_CW,
	OLD_LASER_SLOW_CW,
	OLD_LASER_STOP,
	OLD_LASER_SLOW_CCW,
	OLD_LASER_NORMAL_CCW,
	OLD_LASER_FAST_CCW,

	OLD_LASER_SHORT,
	OLD_LASER_MIDDLE,
	OLD_LASER_LONG,

	OLD_LASER_C_SLOW,
	OLD_LASER_C_NORMAL,
	OLD_LASER_C_FAST,

	OLD_LASER_O_SLOW,
	OLD_LASER_O_NORMAL,
	OLD_LASER_O_FAST,

	OLD_DRAGER_WEAK,
	OLD_DRAGER_NORMAL,
	OLD_DRAGER_STRONG,

	OLD_PLASMA,
	OLD_CRAZY_SHOTGUN_U_EX,
	OLD_CRAZY_SHOTGUN_R_EX,
	OLD_CRAZY_SHOTGUN_D_EX,
	OLD_CRAZY_SHOTGUN_L_EX,
	OLD_CRAZY_SHOTGUN_U,
	OLD_CRAZY_SHOTGUN_R,
	OLD_CRAZY_SHOTGUN_D,
	OLD_CRAZY_SHOTGUN_L,
	OLD_DOOR,
	OLD_CONNECTOR_D,
	OLD_CONNECTOR_DR,
	OLD_CONNECTOR_R,
	OLD_CONNECTOR_RU,
	OLD_CONNECTOR_U,
	OLD_CONNECTOR_UL,
	OLD_CONNECTOR_L,
	OLD_CONNECTOR_LD,
	OLD_TRIGGER,
	NUM_OLD,

	TOLD_AIR=0,
	TOLD_SOLID,
	TOLD_DEATH,
	TOLD_NOHOOK,
	TOLD_NOLASER,
	TOLD_BOOST_L,
	TOLD_BOOST_R,
	TOLD_BOOST_D,
	TOLD_BOOST_U,
	TOLD_FREEZE,
	TOLD_KICK,
	TOLD_UNFREEZE,
	TOLD_BOOST_L2,
	TOLD_BOOST_R2,
	TOLD_BOOST_D2,
	TOLD_BOOST_U2,

	TOLD_BOOST_FL=21,
	TOLD_BOOST_FR,
	TOLD_BOOST_FD,
	TOLD_BOOST_FU,
	TOLD_THROUGHF,
	TOLD_THROUGH,
	TOLD_BOOST_FL2=28,
	TOLD_BOOST_FR2,
	TOLD_BOOST_FD2,
	TOLD_BOOST_FU2,
};

struct CPoint
{
	int x, y; // 22.10 fixed point
};

struct CColor
{
	int r, g, b, a;
};

struct CQuad
{
	CPoint m_aPoints[5];
	CColor m_aColors[4];
	CPoint m_aTexcoords[4];
	
	int m_PosEnv;
	int m_PosEnvOffset;
	
	int m_ColorEnv;
	int m_ColorEnvOffset;
};

class CTile
{
public:
	unsigned char m_Index;
	unsigned char m_Flags;
	unsigned char m_Skip;
	unsigned char m_Reserved;
};

class CTeleTile
{
public:
	unsigned char m_Number;
	unsigned char m_Type;
};

class CSpeedupTile
{
public:
	unsigned char m_Force;
	unsigned char m_MaxSpeed;
	unsigned char m_Type;
	short m_Angle;
};

class CSwitchTile
{
public:
	unsigned char m_Number;
	unsigned char m_Type;
	unsigned char m_Flags;
	unsigned char m_Delay;
};

struct CMapItemImage
{
	int m_Version;
	int m_Width;
	int m_Height;
	int m_External;
	int m_ImageName;
	int m_ImageData;
} ;

class CDoorTile
{
public:
	unsigned char m_Index;
	unsigned char m_Flags;
	int m_Number;
};

struct CMapItemGroup_v1
{
	int m_Version;
	int m_OffsetX;
	int m_OffsetY;
	int m_ParallaxX;
	int m_ParallaxY;

	int m_StartLayer;
	int m_NumLayers;
} ;


struct CMapItemGroup : public CMapItemGroup_v1
{
	enum { CURRENT_VERSION=2 };
	
	int m_UseClipping;
	int m_ClipX;
	int m_ClipY;
	int m_ClipW;
	int m_ClipH;
} ;

struct CMapItemLayer
{
	int m_Version;
	int m_Type;
	int m_Flags;
} ;

struct CMapItemLayerTilemap
{
	CMapItemLayer m_Layer;
	int m_Version;
	
	int m_Width;
	int m_Height;
	int m_Flags;
	
	CColor m_Color;
	int m_ColorEnv;
	int m_ColorEnvOffset;
	
	int m_Image;
	int m_Data;
	
	int m_Tele;
	int m_Speedup;
	int m_Front;
	int m_Switch;
} ;

struct CMapItemLayerQuads
{
	CMapItemLayer m_Layer;
	int m_Version;
	
	int m_NumQuads;
	int m_Data;
	int m_Image;
} ;

struct CMapItemVersion
{
	int m_Version;
} ;

struct CEnvPoint
{
	int m_Time; // in ms
	int m_Curvetype;
	int m_aValues[4]; // 1-4 depending on envelope (22.10 fixed point)
	
	bool operator<(const CEnvPoint &Other) { return m_Time < Other.m_Time; }
} ;

struct CMapItemEnvelope
{
	int m_Version;
	int m_Channels;
	int m_StartPoint;
	int m_NumPoints;
	int m_aName[8];
} ;

#endif
