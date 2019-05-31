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

//General headers go here
#include <windows.h>
#include "Common Files/Game.h"
#include "Common Files/CRCCheck.h"

//Game headers go here
#include "Game Files/AfterburnerClimax.h"
#include "Game Files/BattleGear4Tuned.h"
#include "Game Files/ChaseHQ2.h"
#include "Game Files/DaytonaChampionshipUSA.h"
#include "Game Files/GTIClubSuperminiFesta.h"
#include "Game Files/InitialD4.h"
#include "Game Files/InitialD4Japan.h"
#include "Game Files/InitialD5.h"
#include "Game Files/InitialD6.h"
#include "Game Files/InitialD7.h"
#include "Game Files/InitialD8.h"
#include "Game Files/LGI.h"
#include "Game Files/LGI3D.h"
#include "Game Files/Machstorm.h"
#include "Game Files/MarioKartGPDXJP1.10.h"
#include "Game Files/Outrun2SP.h"
#include "Game Files/SegaRacingClassic.h"
#include "Game Files/SonicAllStarsRacing.h"
#include "Game Files/WackyRaces.h"
#include "Game Files/WMMT5.h"

Game* game;
bool OutputsRunning = true;

DWORD WINAPI OutputsLoop(LPVOID lpParam)
{
		uint32_t crcResult = GetCRC32(GetModuleHandle(nullptr), 0x400);
		switch (crcResult)
		{
		case 0xF8CEEC5D:
			game = new SegaRacingClassic;
			break;
		case 0x7787da54:
			game = new MarioKartGPDXJP110;
			break;
		case 0xb8f2836d:
			game = new DaytonaChampionshipUSA;
			break;
		case 0x14eb3c8a:
			game = new BattleGear4Tuned;
			break;
		case 0x1f2f9497:
			game = new ChaseHQ2;
			break;
		case 0x326ebcd6:
			game = new GTIClubSuperminiFesta;
			break;
		case 0x379FA53E:
			game = new InitialD6;
			break;
		case 0x1cd40f9e:
			game = new InitialD7;
			break;
		case 0xeddea93e:
			game = new InitialD8;
			break;
		case 0x82FED329:
			game = new LGI;
			break;
		case 0x3f74055e:
			game = new LGI3D;
			break;
		case 0xE7EAAEAD:
			game = new SonicAllStarsRacing;
			break;
		case 0x185fd019:
			game = new WackyRaces;
			break;
		}

		if (game != 0)
		{
			game->OutputsGameLoop();
			Sleep(16);
		}

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	BOOL result = TRUE;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, OutputsLoop, (LPVOID)&OutputsRunning, 0, NULL);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		Outputs->~COutputs();
		OutputsRunning = false;
		break;
	}
	return TRUE;
}