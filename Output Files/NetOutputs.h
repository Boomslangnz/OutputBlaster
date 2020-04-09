/*This file is part of Output Blaster.

Output Blaster is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Output Blaster is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Output Blaster.If not, see < https://www.gnu.org/licenses/>.*/

 /*
  * WinOutputs.h
  *
  * Implementation of COutputs that sends MAMEHooker compatible messages via Windows messages.
  */

#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "Outputs.h"
#include <vector>

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

// Struct that represents a client (eg MAMEHooker) currently registered with the emulator
struct RegisteredClientTcp
{
	SOCKET  ClientSocket;	// Client socket
};


class CNetOutputs : public COutputs
{
public:
	/*
	 * CWinOutputs():
	 * ~CWinOutputs():
	 *
	 * Constructor and destructor.
	 */
	CNetOutputs();

	virtual ~CNetOutputs();

	/*
	 * Initialize():
	 *
	 * Initializes this class.
	 */
	bool Initialize();

	/*
	 * Attached():
	 *
	 * Lets the class know that it has been attached to the emulator.
	 */
	void Attached();
protected:
	/*
	 * SendOutput():
	 *
	 * Sends the appropriate output message to all registered clients.
	 */
	void SendOutput(EOutputs output, UINT8 prevValue, UINT8 value);

private:
	const int TcpPort = 8000;
	const int UdpBroadcastPort = 8001;

	bool s_createdClass = false;

	/*
	 * CreateServerThread():
	 *
	 * Registers the server and wait for new client
	 */
	LRESULT CreateServerThread();

	static DWORD WINAPI ThreadEntry(LPVOID pUserData) {
		return ((CNetOutputs*)pUserData)->TcpServerThread();
	}

	HANDLE ThreadHandle;
	DWORD ThreadId;
	bool Running = false;

	SOCKET ServerSocket;
	WSADATA WSAData;
	SOCKADDR_IN server_sin;
	vector<RegisteredClientTcp> m_clients;

	DWORD TcpServerThread();
	LRESULT CreateTcpServerSocket();
	LRESULT SendUdpBroadcastWithId();

	/*
	 * AllocateMessageId(regId, str):
	 *
	 * Defines a new window message type with the given name and returns the allocated message id.
	 */
	bool AllocateMessageId(UINT &regId, LPCSTR str);

	/*
	 * RegisterClient(hwnd, id):
	 *
	 * Registers a client (eg MAMEHooker) with the emulator.
	 */
	LRESULT RegisterClient(SOCKET hwnd);

	/*
	 * SendAllToClient(client):
	 *
	 * Sends the current state of all the outputs to the given registered client.
	 * Called whenever a client is registered with the emulator.
	 */
	void SendAllToClient(RegisteredClientTcp& client);

	/*
	 * UnregisterClient(hwnd, id):
	 *
	 * Unregisters a client from the emulator.
	 */
	LRESULT UnregisterClient(SOCKET hwnd);

	LRESULT SendStarIdtString(RegisteredClientTcp& client);
	LRESULT SendStopString(RegisteredClientTcp& client, bool stopped);
	LRESULT SendPauseString(RegisteredClientTcp& client, bool paused);

	/*
	 * SendIdString(hwnd, id):
	 *
	 * Sends the name of the requested output back to a client, or the name of the current running game if an id of zero is requested.
	 */
	LRESULT SendIdString(RegisteredClientTcp& client, LPARAM id);

	/*
	 * MapIdToName(id):
	 *
	 * Maps the given id to an output's name.
	 */
	const char *MapIdToName(LPARAM id);

	/*
	 * MapNameToId(name):
	 *
	 * Maps the given name to an output's id.
	 */
	LPARAM MapNameToId(const char *name);
};

