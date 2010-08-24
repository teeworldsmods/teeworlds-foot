#ifndef ENGINE_SERVER_REGISTER_H
#define ENGINE_SERVER_REGISTER_H

#include <engine/masterserver.h>

class CRegister
{
	enum
	{
		REGISTERSTATE_START=0,
		REGISTERSTATE_UPDATE_ADDRS,
		REGISTERSTATE_QUERY_COUNT,
		REGISTERSTATE_HEARTBEAT,
		REGISTERSTATE_REGISTERED,
		REGISTERSTATE_ERROR
	};

	struct CMasterserverInfo
	{
		NETADDR m_Addr;
		int m_Count;
		int m_Valid;
		int64 m_LastSend;
	};

	class CNetServer *m_pNetServer;
	class IEngineMasterServer *m_pMasterServer;

	int m_RegisterState;
	int64 m_RegisterStateStart;
	int m_RegisterFirst;
	int m_RegisterCount;

	class CMasterserverInfo m_aMasterserverInfo[IMasterServer::MAX_MASTERSERVERS];
	int m_RegisterRegisteredServer;

	void RegisterNewState(int State);
	void RegisterSendFwcheckresponse(NETADDR *pAddr);
	void RegisterSendHeartbeat(NETADDR Addr);
	void RegisterSendCountRequest(NETADDR Addr);
	void RegisterGotCount(class CNetChunk *pChunk);

public:
	CRegister();
	void Init(class CNetServer *pNetServer, class IEngineMasterServer *pMasterServer);
	void RegisterUpdate();
	int RegisterProcessPacket(class CNetChunk *pPacket);
};

#endif