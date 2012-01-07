/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef ENGINE_SHARED_CONFIG_VARIABLES_H
#define ENGINE_SHARED_CONFIG_VARIABLES_H
#undef ENGINE_SHARED_CONFIG_VARIABLES_H // this file will be included several times

// TODO: remove this
#include "././game/variables.h"


MACRO_CONFIG_STR(PlayerName, player_name, 16, "nameless tee", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Name of the player")
MACRO_CONFIG_STR(PlayerClan, player_clan, 12, "", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Clan of the player")
MACRO_CONFIG_INT(PlayerCountry, player_country, -1, -1, 1000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Country of the player")
MACRO_CONFIG_STR(Password, password, 32, "", CFGFLAG_CLIENT|CFGFLAG_SERVER, "Password to the server")
MACRO_CONFIG_STR(Logfile, logfile, 128, "", CFGFLAG_SAVE|CFGFLAG_CLIENT|CFGFLAG_SERVER, "Filename to log all output to")
MACRO_CONFIG_INT(ConsoleOutputLevel, console_output_level, 0, 0, 2, CFGFLAG_CLIENT|CFGFLAG_SERVER, "Adjusts the amount of information in the console")

MACRO_CONFIG_INT(ClCpuThrottle, cl_cpu_throttle, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(ClEditor, cl_editor, 0, 0, 1, CFGFLAG_CLIENT, "")

MACRO_CONFIG_INT(ClAutoDemoRecord, cl_auto_demo_record, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Automatically record demos")
MACRO_CONFIG_INT(ClAutoDemoMax, cl_auto_demo_max, 10, 0, 1000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Maximum number of automatically recorded demos (0 = no limit)")
MACRO_CONFIG_INT(ClAutoScreenshot, cl_auto_screenshot, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Automatically take game over screenshot")
MACRO_CONFIG_INT(ClAutoScreenshotMax, cl_auto_screenshot_max, 10, 0, 1000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Maximum number of automatically created screenshots (0 = no limit)")

MACRO_CONFIG_INT(ClEventthread, cl_eventthread, 0, 0, 1, CFGFLAG_CLIENT, "Enables the usage of a thread to pump the events")

MACRO_CONFIG_INT(InpGrab, inp_grab, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Use forceful input grabbing method")

MACRO_CONFIG_STR(BrFilterString, br_filter_string, 25, "", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Server browser filtering string")
MACRO_CONFIG_INT(BrFilterFull, br_filter_full, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out full server in browser")
MACRO_CONFIG_INT(BrFilterEmpty, br_filter_empty, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out empty server in browser")
MACRO_CONFIG_INT(BrFilterSpectators, br_filter_spectators, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out spectators from player numbers")
MACRO_CONFIG_INT(BrFilterFriends, br_filter_friends, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out servers with no friends")
MACRO_CONFIG_INT(BrFilterCountry, br_filter_country, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out servers with non-matching player country")
MACRO_CONFIG_INT(BrFilterCountryIndex, br_filter_country_index, -1, -1, 999, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Player country to filter by in the server browser")
MACRO_CONFIG_INT(BrFilterPw, br_filter_pw, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out password protected servers in browser")
MACRO_CONFIG_INT(BrFilterPing, br_filter_ping, 999, 0, 999, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Ping to filter by in the server browser")
MACRO_CONFIG_STR(BrFilterGametype, br_filter_gametype, 128, "", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Game types to filter")
MACRO_CONFIG_INT(BrFilterGametypeStrict, br_filter_gametype_strict, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Strict gametype filter")
MACRO_CONFIG_STR(BrFilterServerAddress, br_filter_serveraddress, 128, "", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Server address to filter")
MACRO_CONFIG_INT(BrFilterPure, br_filter_pure, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out non-standard servers in browser")
MACRO_CONFIG_INT(BrFilterPureMap, br_filter_pure_map, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out non-standard maps in browser")
MACRO_CONFIG_INT(BrFilterCompatversion, br_filter_compatversion, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out non-compatible servers in browser")

MACRO_CONFIG_INT(BrSort, br_sort, 0, 0, 256, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(BrSortOrder, br_sort_order, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(BrMaxRequests, br_max_requests, 25, 0, 1000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Number of requests to use when refreshing server browser")

MACRO_CONFIG_INT(SndBufferSize, snd_buffer_size, 512, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sound buffer size")
MACRO_CONFIG_INT(SndRate, snd_rate, 48000, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sound mixing rate")
MACRO_CONFIG_INT(SndEnable, snd_enable, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sound enable")
MACRO_CONFIG_INT(SndMusic, snd_enable_music, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Play background music")
MACRO_CONFIG_INT(SndVolume, snd_volume, 100, 0, 100, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sound volume")
MACRO_CONFIG_INT(SndDevice, snd_device, -1, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "(deprecated) Sound device to use")

MACRO_CONFIG_INT(SndNonactiveMute, snd_nonactive_mute, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")

MACRO_CONFIG_INT(GfxScreenWidth, gfx_screen_width, 800, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Screen resolution width")
MACRO_CONFIG_INT(GfxScreenHeight, gfx_screen_height, 600, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Screen resolution height")
MACRO_CONFIG_INT(GfxFullscreen, gfx_fullscreen, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Fullscreen")
MACRO_CONFIG_INT(GfxAlphabits, gfx_alphabits, 0, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Alpha bits for framebuffer (fullscreen only)")
MACRO_CONFIG_INT(GfxColorDepth, gfx_color_depth, 24, 16, 24, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Colors bits for framebuffer (fullscreen only)")
MACRO_CONFIG_INT(GfxClear, gfx_clear, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Clear screen before rendering")
MACRO_CONFIG_INT(GfxVsync, gfx_vsync, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Vertical sync")
MACRO_CONFIG_INT(GfxDisplayAllModes, gfx_display_all_modes, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(GfxTextureCompression, gfx_texture_compression, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Use texture compression")
MACRO_CONFIG_INT(GfxHighDetail, gfx_high_detail, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "High detail")
MACRO_CONFIG_INT(GfxTextureQuality, gfx_texture_quality, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(GfxFsaaSamples, gfx_fsaa_samples, 0, 0, 16, CFGFLAG_SAVE|CFGFLAG_CLIENT, "FSAA Samples")
MACRO_CONFIG_INT(GfxRefreshRate, gfx_refresh_rate, 0, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Screen refresh rate")
MACRO_CONFIG_INT(GfxFinish, gfx_finish, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(GfxAsyncRender, gfx_asyncrender, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Do rendering async from the the update")

MACRO_CONFIG_INT(GfxThreaded, gfx_threaded, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Use the threaded graphics backend")

MACRO_CONFIG_INT(InpMousesens, inp_mousesens, 100, 5, 100000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Mouse sensitivity")

MACRO_CONFIG_STR(SvName, sv_name, 128, "unnamed Foot server", CFGFLAG_SERVER, "Server name")
MACRO_CONFIG_STR(SvBindaddr, sv_bindaddr, 128, "", CFGFLAG_SERVER, "Address to bind the server to")
MACRO_CONFIG_INT(SvPort, sv_port, 8303, 0, 0, CFGFLAG_SERVER, "Port to use for the server")
MACRO_CONFIG_INT(SvExternalPort, sv_external_port, 0, 0, 0, CFGFLAG_SERVER, "External port to report to the master servers")
MACRO_CONFIG_STR(SvMap, sv_map, 128, "foot", CFGFLAG_SERVER, "Map to use on the server")
MACRO_CONFIG_INT(SvMaxClients, sv_max_clients, 8, 1, MAX_CLIENTS, CFGFLAG_SERVER, "Maximum number of clients that are allowed on a server")
MACRO_CONFIG_INT(SvMaxClientsPerIP, sv_max_clients_per_ip, 4, 1, MAX_CLIENTS, CFGFLAG_SERVER, "Maximum number of clients with the same IP that can connect to the server")
MACRO_CONFIG_INT(SvHighBandwidth, sv_high_bandwidth, 0, 0, 1, CFGFLAG_SERVER, "Use high bandwidth mode. Doubles the bandwidth required for the server. LAN use only")
MACRO_CONFIG_INT(SvRegister, sv_register, 1, 0, 1, CFGFLAG_SERVER, "Register server with master server for public listing")
MACRO_CONFIG_STR(SvRconPassword, sv_rcon_password, 32, "", CFGFLAG_SERVER, "Remote console password (full access)")
MACRO_CONFIG_STR(SvRconModPassword, sv_rcon_mod_password, 32, "", CFGFLAG_SERVER, "Remote console password for moderators (limited access)")
MACRO_CONFIG_INT(SvRconMaxTries, sv_rcon_max_tries, 3, 0, 100, CFGFLAG_SERVER, "Maximum number of tries for remote console authentication")
MACRO_CONFIG_INT(SvRconBantime, sv_rcon_bantime, 5, 0, 1440, CFGFLAG_SERVER, "The time a client gets banned if remote console authentication fails. 0 makes it just use kick")
MACRO_CONFIG_INT(SvAutoDemoRecord, sv_auto_demo_record, 0, 0, 1, CFGFLAG_SERVER, "Automatically record demos")
MACRO_CONFIG_INT(SvAutoDemoMax, sv_auto_demo_max, 10, 0, 1000, CFGFLAG_SERVER, "Maximum number of automatically recorded demos (0 = no limit)")

MACRO_CONFIG_STR(EcBindaddr, ec_bindaddr, 128, "localhost", CFGFLAG_ECON, "Address to bind the external console to. Anything but 'localhost' is dangerous")
MACRO_CONFIG_INT(EcPort, ec_port, 0, 0, 0, CFGFLAG_ECON, "Port to use for the external console")
MACRO_CONFIG_STR(EcPassword, ec_password, 32, "", CFGFLAG_ECON, "External console password")
MACRO_CONFIG_INT(EcBantime, ec_bantime, 0, 0, 1440, CFGFLAG_ECON, "The time a client gets banned if econ authentication fails. 0 just closes the connection")
MACRO_CONFIG_INT(EcAuthTimeout, ec_auth_timeout, 30, 1, 120, CFGFLAG_ECON, "Time in seconds before the the econ authentification times out")
MACRO_CONFIG_INT(EcOutputLevel, ec_output_level, 1, 0, 2, CFGFLAG_ECON, "Adjusts the amount of information in the external console")

MACRO_CONFIG_INT(Debug, debug, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SERVER, "Debug mode")
MACRO_CONFIG_INT(DbgStress, dbg_stress, 0, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SERVER, "Stress systems")
MACRO_CONFIG_INT(DbgStressNetwork, dbg_stress_network, 0, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SERVER, "Stress network")
MACRO_CONFIG_INT(DbgPref, dbg_pref, 0, 0, 1, CFGFLAG_SERVER, "Performance outputs")
MACRO_CONFIG_INT(DbgGraphs, dbg_graphs, 0, 0, 1, CFGFLAG_CLIENT, "Performance graphs")
MACRO_CONFIG_INT(DbgHitch, dbg_hitch, 0, 0, 0, CFGFLAG_SERVER, "Hitch warnings")
MACRO_CONFIG_STR(DbgStressServer, dbg_stress_server, 32, "localhost", CFGFLAG_CLIENT, "Server to stress")
MACRO_CONFIG_INT(DbgResizable, dbg_resizable, 0, 0, 0, CFGFLAG_CLIENT, "Enables window resizing")

// TeeFoot

MACRO_CONFIG_INT(SvBounceLoss, sv_bounce_loss, 50, 0, 100000, CFGFLAG_SERVER, "The ball looses that much speed after a bounce")
MACRO_CONFIG_INT(SvExplosions, sv_explosions, 0, 0, 1, CFGFLAG_SERVER, "Should the grenades explode")
MACRO_CONFIG_INT(SvSpawnDelay, sv_spawn_delay, 2000, 0, 100000, CFGFLAG_SERVER, "Spawn delay for players after a kill")
MACRO_CONFIG_INT(SvBallRespawn, sv_ball_respawn, 5, 0, 100000, CFGFLAG_SERVER, "Respawn time of the ball")
MACRO_CONFIG_INT(SvScoreDiff, sv_score_diff, 1, 0, 1000, CFGFLAG_SERVER, "Difference between the team-scores before a team can win")
MACRO_CONFIG_INT(SvSuddenDeathScoreDiff, sv_sudden_death_score_diff, 2, 0, 1000, CFGFLAG_SERVER, "Difference between the team-scores before a team can win in sudden death")

/*
	MACRO_CONFIG_INT(sv_real_foot, 0, 0, 1, CFGFLAG_SERVER, "Disables the hammer",2)
	MACRO_CONFIG_INT(sv_start_hammer, 1, 0, 1, CFGFLAG_SERVER, "The player has a hammer after respawn.",2)
	MACRO_CONFIG_INT(sv_start_pistol, 0, 0, 10, CFGFLAG_SERVER, "The player has a pistol after respawn with this ammo.",2)
	MACRO_CONFIG_INT(sv_start_shotgun, 0, 0, 10, CFGFLAG_SERVER, "The player has a shotgun after respawn with this ammo.",2)
	MACRO_CONFIG_INT(sv_start_grenade, 0, 0, 10, CFGFLAG_SERVER, "The player has a grenadelauncher after respawn with this ammo.",2)
	MACRO_CONFIG_INT(sv_start_ninja, 0, 0, 1, CFGFLAG_SERVER, "The player has a ninja after respawn.",2)
	MACRO_CONFIG_INT(sv_start_rifle, 0, 0, 10, CFGFLAG_SERVER, "The player has a rifle after respawn with this ammo.",2)
	MACRO_CONFIG_INT(sv_goaler_score, 1, 0, 1000, CFGFLAG_SERVER, "Score for the goaler",2)
	MACRO_CONFIG_INT(sv_passer_score, 1, 0, 1000, CFGFLAG_SERVER, "Score for the passer",2)
	MACRO_CONFIG_INT(sv_team_score, 1, 0, 1000, CFGFLAG_SERVER, "Score for the team",2)
	MACRO_CONFIG_INT(sv_team_pass_score, 1, 0, 1000, CFGFLAG_SERVER, "Score for the team through a goal with pass",2)
	MACRO_CONFIG_INT(sv_own_goal, 1, 0, 1000, CFGFLAG_SERVER, "Negative score for a wrong goal",2)
	MACRO_CONFIG_INT(sv_suicide_score, 1, 0, 1, CFGFLAG_SERVER, "Count selfkills as negative score",2)
	MACRO_CONFIG_INT(sv_kill_score, 1, 0, 1, CFGFLAG_SERVER, "Are there points for a kill",2)
	MACRO_CONFIG_INT(sv_generate_pro_pw, 0, 0, 1, CFGFLAG_SERVER, "Gives good players a password at the end of a round.",2)
	MACRO_CONFIG_STR(sv_pre_password_msg, 512, "Here is your password for the professional server. It's the correct one for this day and your nick, noone else.", CFGFLAG_SERVER, "Message the server gives the player who receives a password for pro-server",2)
	MACRO_CONFIG_INT(sv_player_keeptime, 3, 0, 100000, CFGFLAG_SERVER, "The player fires the ball automatically after this time (0 immediately)",2)
	MACRO_CONFIG_INT(sv_use_pro_pw, 0, 0, 1, CFGFLAG_SERVER, "The player have to type in the custom password for his name or the general password.",2)
	MACRO_CONFIG_STR(sv_pro_password, 32, "", CFGFLAG_SERVER, "The general password for the professional server (is needed to generate and check passwords)",2)
	MACRO_CONFIG_INT(sv_pickup_with_no_armor, 1, 0, 1, CFGFLAG_SERVER, "Pickup the ball without any armor?",2)
	MACRO_CONFIG_INT(sv_ball_reloader, 10, 0, 1000, CFGFLAG_SERVER, "Reload the ball",2)
	MACRO_CONFIG_INT(sv_hammer_team_att_loss, 0, 0, 10, CFGFLAG_SERVER, "The attacker looses this health, if he attacks a teammate",2)
	MACRO_CONFIG_INT(sv_hammer_att_loss, 0, 0, 10, CFGFLAG_SERVER, "The attacker looses this health",2)
	MACRO_CONFIG_INT(sv_hammer_def_loss, 0, 0, 10, CFGFLAG_SERVER, "The victim player looses this armor",2)
	MACRO_CONFIG_INT(sv_grenade_startspeed, 0, 0, 1000000, CFGFLAG_SERVER, "startspeed of the grenade (the sum of player-speed and normal grenade-speed)",2)
	MACRO_CONFIG_INT(sv_partly_dead, 0, 0, 10000, CFGFLAG_SERVER, "If the player only has 1hp, the player is partly dead for this value seconds. In this time there is no health/armor regeneration and the player can't hook other players or take the ball",2)
	MACRO_CONFIG_INT(sv_respawn_powerups, 1, 0, 1, CFGFLAG_SERVER, "Should the powerups respawn",2)
	MACRO_CONFIG_INT(sv_show_votings, 1, 0, 2, CFGFLAG_SERVER, "0 disables, 1 enables for all and 2 enables only for admin",2)

	MACRO_CONFIG_INT(sv_reserved_slots, 0, 0, 12, CFGFLAG_SERVER, "Number of reserved slots",2)
	MACRO_CONFIG_STR(sv_reserved_slots_pass, 32, "", CFGFLAG_SERVER, "Password for reserver slots",2)

	MACRO_CONFIG_STR(sv_message, 300, "", CFGFLAG_SERVER, "Message displayed all sv_message_time seconds, max 100 symbols",2)
	MACRO_CONFIG_INT(sv_message_time, 5, 1, 30, CFGFLAG_SERVER, "Time between two sv_messages in minutes",2)
	MACRO_CONFIG_INT(sv_max_idle, 300, 0, 600, CFGFLAG_SERVER, "Time after a player got ask state to wait with kick him",2)
	MACRO_CONFIG_INT(sv_set_afk_idle, 60, 0, 600, CFGFLAG_SERVER, "Time how long a player doesn�t get afk state afte his last input",2)
	MACRO_CONFIG_INT(sv_max_noob_time, 20, 0, 600, CFGFLAG_SERVER, "Time how long a nooblisted player can be on the server",2)

	MACRO_CONFIG_INT(sv_dev_powers, 0, 0, 1, CFGFLAG_SERVER, "Special powers for developers :)",2)

	MACRO_CONFIG_STR(sv_blacklist, 32, "Blacklist.TEEFOOT", CFGFLAG_SERVER, "Blacklist for some fuckign ip refreshing noobs!",2)
*/

#endif
