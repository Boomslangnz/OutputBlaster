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
#include "Common Files/Game.h"
#include "Common Files/CRCCheck.h"
#include <stdint.h>

//Game headers go here
#include "Game Files/AfterburnerClimax.h"
#include "Game Files/AliensExtermination.h"
#include "Game Files/ArcticThunder.h"
#include "Game Files/BattleGear4.h"
#include "Game Files/BattleGear4Tuned.h"
#include "Game Files/BattlePod.h"
#include "Game Files/Batman.h"
#include "Game Files/Cars.h"
#include "Game Files/ChaseHQ2.h"
#include "Game Files/CrazyRide.h"
#include "Game Files/CruisnBlast.h"
#include "Game Files/DaytonaChampionshipUSA.h"
#include "Game Files/DaytonaChampionshipUSANSE.h"
#include "Game Files/DirtyDrivin.h"
#include "Game Files/DeadHeat.h"
#include "Game Files/FNFDrift.h"
#include "Game Files/FNFSupercars.h"
#include "Game Files/GhostSquadEvo.h"
#include "Game Files/GTIClubSuperminiFesta.h"
#include "Game Files/GRID.h"
#include "Game Files/H2Overdrive.h"
#include "Game Files/HOTD4VerA.h"
#include "Game Files/HOTD4VerC.h"
#include "Game Files/HarleyDavidson.h"
#include "Game Files/Hummer.h"
#include "Game Files/HummerExtreme.h"
#include "Game Files/ID0V131.h"
#include "Game Files/ID0V211.h"
#include "Game Files/InitialD4.h"
#include "Game Files/InitialD5.h"
#include "Game Files/InitialD6.h"
#include "Game Files/InitialD6Update.h"
#include "Game Files/InitialD7.h"
#include "Game Files/InitialD8.h"
#include "Game Files/JurassicPark.h"
#include "Game Files/LGI.h"
#include "Game Files/LGI3D.h"
#include "Game Files/M2Emulator.h"
#include "Game Files/Machstorm.h"
#include "Game Files/MarioKartGPDXJP1.10.h"
#include "Game Files/MarioKart1.18.h"
#include "Game Files/MotoGP.h"
#include "Game Files/OperationGhost.h"
#include "Game Files/Outrun2SP.h"
#include "Game Files/R-Tuned.h"
#include "Game Files/SegaRaceTV.h"
#include "Game Files/SegaRacingClassic.h"
#include "Game Files/SegaRally3.h"
#include "Game Files/SRG.h"
#include "Game Files/SuperBikes2.h"
#include "Game Files/TheWalkingDead.h"
#include "Game Files/Transformers.h"
#include "Game Files/TransformersShadowsRising.h"
#include "Game Files/SonicAllStarsRacing.h"
#include "Game Files/VirtuaTennis4.h"
#include "Game Files/WackyRaces.h"
#include "Game Files/WMMT5.h"
#include "Game Files/WMMT5DX.h"
#include "Game Files/WMMT5DXPlus.h"
#include "Game Files/WMMT6.h"
#include "Game Files/WMMT6R.h"

static char newCrc[0x400];
Game* game;
bool OutputsRunning = true;

static uint32_t ReadWithoutCrashing(uint32_t* addr)
{
	if (addr == NULL || IsBadReadPtr(addr, 4))
		return 0;
	else
		return *addr;
}

DWORD WINAPI OutputsLoop(LPVOID lpParam)
{
	Sleep(2500);
	// Craft CRC detection without virtual address
	memcpy(newCrc, GetModuleHandle(nullptr), 0x400);
	DWORD pePTR = *(DWORD*)(newCrc + 0x3C);

	// Overwrite ImageBase with 8 bytes of 0
	*(DWORD*)(newCrc + pePTR + 0x18) = 0x00000000;
	*(DWORD*)(newCrc + pePTR + 0x18 + 4) = 0x00000000;
#ifdef _AMD64_
	* (DWORD*)(newCrc + pePTR + 50) = 0x00000000;
#endif
	* (DWORD*)(newCrc + pePTR + 54) = 0x00000000;
	uint32_t newCrcResult = GetCRC32(newCrc, 0x400);

	switch (newCrcResult)
	{
	case 0x4904b14d:
		game = new OperationGhost;
		break;
	case 0xf26ecfa9:
		game = new WackyRaces;
		break;
	case 0x1adfb24b:
		game = new Machstorm;
		break;
	case 0x7787da54:
		game = new MarioKartGPDXJP110;
		break;
	case 0x6c9038be:
		game = new MarioKart118;
		break;
	case 0x533f1a71:
		game = new SonicAllStarsRacing;
		break;
	case 0x2c8b0265:
		game = new LGI3D;
		break;
	case 0xd400a3f5:
		game = new LGI;
		break;
	case 0x80900efd:
		game = new VirtuaTennis4;
		break;
	case 0x92b5b16b:
		game = new InitialD8;
		break;
	case 0x4fd57346:
		game = new InitialD7;
		break;
	case 0x08d4bace:
		game = new InitialD6Update; // v1.2
		break;
	case 0x715aaebf:
		game = new InitialD6; // v1.0
		break;
	case 0x1b61779e:
		game = new GTIClubSuperminiFesta;
		break;
	case 0x6844eee1:
		game = new ChaseHQ2;
		break;
	case 0x47641574:
		game = new SegaRacingClassic;
		break;
	case 0xb6e0de95:
		game = new DaytonaChampionshipUSANSE;
		break;
	case 0x5a468d9e:
		game = new DaytonaChampionshipUSA;
		break;
	case 0xbafaca7b:
		game = new BattleGear4Tuned;
		break;
	case 0x97994382:
		game = new M2Emulator;
		break;
	case 0xE7BC4D6B:
		game = new AliensExtermination;
		break;
	case 0xdc693790:
	case 0x7dcef927:
	case 0x8073dbb9:
		game = new Transformers;
		break;
	case 0xbd8c984d:
		game = new BattleGear4;
		break;
	case 0xed9b5740:
		game = new H2Overdrive;
		break;
	case 0xfac8a714:
	case 0x01a76797:
		game = new Cars;
		break;
	case 0x8456EEC1:
		game = new DirtyDrivin;
		break;
	case 0xc484002f:
		game = new SRG;
		break;
	case 0x08f14845:
		game = new SR3;
		break;
	case 0xc68bcd2f:
		game = new InitialD0V131;
		break;
	case 0x89da99ee:
		game = new InitialD0V211;
		break;
	case 0xe75a6a44:
		game = new WMMT5;
		break;
	case 0xDD61E0BA:
		game = new WMMT5DX;
		break;
	case 0x1BB6F051:
		game = new WMMT5DXPlus;
		break;
	case 0x0761cc11:
		game = new WMMT6;
		break;
	case 0xa447f2ef:
		game = new WMMT6R;
		break;
	case 0xbfa0c985:
		game = new GRID;
		break;
	case 0xdb7c9b6e:
		game = new FNFDrift;
		break;
	 case 0x259812d7:
	 	game = new FNFSupercars;
		break;
	//WIP
	//case 0x648e6f7b: 
	//	game = new FNF;
	//	break;
	case 0x790b4172:
		game = new CrazyRide;
		break;
	case 0xc205c6Ac:
		game = new ArcticThunder;
		break;
	case 0xf3d3f699:
		//battlepod launcher we dont care about
		return 0;
		break;
	case 0x8505c794:
		game = new BattlePod;
		break;
	case 0xB818B0BD:
		game = new Batman;
		break;
	case 0x55f66578:
		game = new TransformersShadowsRising;
		break;
	case 0x84d7854b:
		game = new HarleyDavidson;
		break;
	case 0xFE7AFFF4:
		game = new SuperBikes2;
		break;
	default:
		break;
	}

	if (game != 0) //Load PC Based Arcade Game
	{
#ifdef _DEBUG
		OutputDebugStringA("Game Found");
		OutputDebugStringA(std::to_string(newCrcResult).c_str());
#endif
		game->OutputsGameLoop();
		Sleep(16);
	}
	else
	{
		if (ReadWithoutCrashing((uint32_t*)0x804CA44) == 0x82EED98)
		{
			game = new AfterburnerClimax;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x804CA44) == 0x454825FF)
		{
			game = new GhostSquadEvo;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x804CA44) == 0x62726F76)
		{
			game = new WalkingDead;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x804B850) == 0x82642C8)
		{
			game = new Outrun2SP;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x804B840) == 0x0002A68)
		{
			game = new MotoGP;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x804B840) == 0x0000012)
		{
			game = new DeadHeat;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x804A908) == 0x12EE)
		{
			game = new SRTV;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x804CF84) == 0x1B09)
		{
			game = new InitialD4;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x804D258) == 0x1C5F)
		{
			game = new InitialD5;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x0804E8F8) == 0x08479718)
		{
			game = new RTuned;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x0832572E) == 0xAAAA03C7) // Ver A
		{
			game = new HOTD4VerA;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x08320C69) == 0xAAAA03C7) // Ver C
		{
			game = new HOTD4VerC;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x8320C69) == 0xC70000A4)
		{
			game = new CruisnBlast;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x8320C69) == 0x000004B8)
		{
			game = new JurassicPark;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x8320C69) == (0x81DB3153))
		{
			game = new HummerExtreme;
		}
		else if (ReadWithoutCrashing((uint32_t*)0x8320C69) == (0x9AB3BC0))
		{
			game = new Hummer;
		}
		

		if (game != 0) //Load Lindbergh Game 
		{

			game->OutputsGameLoop();
			Sleep(16);
		}
	}
	if (game == 0)
	{
#ifdef _DEBUG
		static char test[256];
		memset(test, 0, 256);
		sprintf(test, "New CRC: %08x not implemented", newCrcResult);
		OutputDebugStringA(test);
#endif
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
		Outputs->SetValue(OutputLampStart, 0x00);
		Outputs->SetValue(OutputLampView1, 0x00);
		Outputs->SetValue(OutputLampView2, 0x00);
		Outputs->SetValue(OutputLampView3, 0x00);
		Outputs->SetValue(OutputLampView4, 0x00);
		Outputs->SetValue(OutputLampLeader, 0x00);
		Outputs->~COutputs();
		OutputsRunning = false;
		break;
	}
	return TRUE;
}
