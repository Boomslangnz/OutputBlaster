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

#include "GhostSquadEvo.h"

static int WindowsLoop()
{
	DWORD LampsOut = helpers->ReadInt32(0x8656358, false);
	Outputs->SetValue(OutputLampStart, !!(LampsOut & 128)); //Start 1
	Outputs->SetValue(Output2pLampStart, !!(LampsOut & 16)); //Start 2
	Outputs->SetValue(Output1pHolderLamp, !!(LampsOut & 32)); //Holder Lamp 1
	Outputs->SetValue(Output2pHolderLamp, !!(LampsOut & 4)); //Holder Lamp 2
	Outputs->SetValue(Output1pRecoil, !!(LampsOut & 64)); //Gun Reaction 1
	Outputs->SetValue(Output2pRecoil, !!(LampsOut & 8)); //Gun Reaction 2

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


void GhostSquadEvo::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Ghost Squad Evo";
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