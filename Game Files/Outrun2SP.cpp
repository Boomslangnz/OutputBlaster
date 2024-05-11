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

#include "Outrun2SP.h"

static bool raceLeaderOn = false;

static int WindowsLoop()
{
	UINT8 outputdata = helpers->ReadByte(0x8670E08, false);
	UINT8 raceLeader = helpers->ReadByte(0x830430C, false);
	float RPMfloat = helpers->ReadFloat32(0x827A174, false);
	DWORD RPM = floor(RPMfloat + 0.5);
	

	
	Outputs->SetValue(OutputLampLeader, !!(raceLeader & 0x01));
	//little hack for oeople with two machines, but only one connected to lamps. Basically if the current machine is losing, light up a new LampLeader2 lamp.
	//proper way to do this is grab the position of each player in the race, but this is a quick fix for this specific use case.
	Outputs->SetValue(OutputLampLeader2, !!(raceLeader & 0x00));
	Outputs->SetValue(OutputLampStart, !!(outputdata & 0x80));
	Outputs->SetValue(OutputLampView1, !!(outputdata & 0x08));
	Outputs->SetValue(OutputDriverLampL, !!(outputdata & 0x20));
	Outputs->SetValue(OutputDriverLampR, !!(outputdata & 0x04));
	Outputs->SetValue(OutputRPM, RPM / 10.0);
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

void Outrun2SP::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Outrun 2 Special Tours";
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