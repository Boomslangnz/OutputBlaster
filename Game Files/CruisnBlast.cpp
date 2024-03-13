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

#include "CruisnBlast.h"
#include <iostream>
#include <fstream>

static int WindowsLoop()
{
	INT_PTR StartLamp = helpers->ReadIntPtr(0xA05C0DC, false);
	INT_PTR OutputLampStart = helpers->ReadInt32(0x8AC3038, false);
	
	INT_PTR KeypadLamp = helpers->ReadInt32(0x8AC3044, false);
	INT_PTR View1Lamp = helpers->ReadInt32(0x8AC3048, false);
	INT_PTR View2Lamp = helpers->ReadInt32(0x8AC304C, false);
	INT_PTR View3Lamp = helpers->ReadInt32(0x8AC3050, false);
	INT_PTR TunesLamp = helpers->ReadInt32(0x8AC3054, false);
	INT_PTR TopSpeakerLamp = helpers->ReadInt32(0x8AC3058, false);
	INT_PTR TopRedLamp = helpers->ReadInt32(0x8AC305C, false);
	INT_PTR TopWhiteLamp = helpers->ReadInt32(0x8AC3060, false);
	INT_PTR TopBlueLamp = helpers->ReadInt32(0x8AC3064, false);
	INT_PTR LeaderLamp = helpers->ReadInt32(0x8AC3068, false);
	INT_PTR SeatSidesLamp = helpers->ReadInt32(0x8AC306C, false);
	INT_PTR SeatBackLamp = helpers->ReadInt32(0x8AC3070, false);
	INT_PTR DashRedLamp = helpers->ReadInt32(0x8AC3074, false);
	INT_PTR DashOrangeLamp = helpers->ReadInt32(0x8AC3078, false);
	INT_PTR DashBlueLamp = helpers->ReadInt32(0x8AC307C, false);
	INT_PTR PedestalOuterLamp = helpers->ReadInt32(0x8AC3080, false);
	INT_PTR PedestalInnerLamp = helpers->ReadInt32(0x8AC3084, false);


	//Coming Soon
	

	return 0;
}

static DWORD WINAPI OutputsAreGo(LPVOID lpParam)
{
	while (true)
	{
		WindowsLoop();
		Sleep(SleepA);
	}
}

void CruisnBlast::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "CruisnBlast";
		Outputs->SetGame(m_game);
		Outputs->Initialize();
		Outputs->Attached();
		CreateThread(NULL, 0, OutputsAreGo, NULL, 0, NULL);
		while (GetMessage(&Msg1, NULL, NULL, 0))
		{
			TranslateMessage(&Msg1);
			DispatchMessage(&Msg1);
		}
		init = true;
	}
}