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

static int WindowsLoop()
{
	DWORD StartLamp = helpers->ReadInt32(0x08AC3040, true);
	DWORD KeypadLamp = helpers->ReadInt32(0x08AC3044, true);
	DWORD View1Lamp = helpers->ReadInt32(0x08AC3048, true);
	DWORD View2Lamp = helpers->ReadInt32(0x08AC304C, true);
	DWORD View3Lamp = helpers->ReadInt32(0x08AC3050, true);
	DWORD TunesLamp = helpers->ReadInt32(0x08AC3054, true);
	DWORD TopSpeakerLamp = helpers->ReadInt32(0x08AC3058, true);
	DWORD TopRedLamp = helpers->ReadInt32(0x08AC305C, true);
	DWORD TopWhiteLamp = helpers->ReadInt32(0x08AC3060, true);
	DWORD TopBlueLamp = helpers->ReadInt32(0x08AC3064, true);
	DWORD LeaderLamp = helpers->ReadInt32(0x08AC3068, true);
	DWORD SeatSidesLamp = helpers->ReadInt32(0x08AC306C, true);
	DWORD SeatBackLamp = helpers->ReadInt32(0x08AC3070, true);
	DWORD DashRedLamp = helpers->ReadInt32(0x08AC3074, true);
	DWORD DashOrangeLamp = helpers->ReadInt32(0x08AC3078, true);
	DWORD DashBlueLamp = helpers->ReadInt32(0x08AC307C, true);
	DWORD PedestalOuterLamp = helpers->ReadInt32(0x08AC3080, true);
	DWORD PedestalInnerLamp = helpers->ReadInt32(0x08AC3084, true);

	Outputs->SetValue(OutputLampStart, StartLamp > 0);
	Outputs->SetValue(OutputLampView1, View1Lamp > 0);
	Outputs->SetValue(OutputLampView2, View2Lamp > 0);
	Outputs->SetValue(OutputLampView3, View3Lamp > 0);
	Outputs->SetValue(OutputLampView4, TunesLamp > 0);
	Outputs->SetValue(OutputLampLeader, LeaderLamp > 0);
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