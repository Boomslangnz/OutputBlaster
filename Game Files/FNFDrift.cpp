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

#include "FNFDrift.h"

static int WindowsLoop()
{

	DWORD Lamps = helpers->ReadInt32(0x41B86BC, true);

	//no lamps on 63488
	//all lamps on 16775168
	//ONLY view 1 on 8452096
	//ONLY view 2 on 4257792
	//ONLY view 3 on 2160640
	//ONLY START on 587776
	//ONLY MUSIC on 1112064



	//View 1
	Outputs->SetValue(OutputLampView1, !!(Lamps & 0x800000));
	//View 2
	Outputs->SetValue(OutputLampView2, !!(Lamps & 0x400000));
	//View 3
	Outputs->SetValue(OutputLampView3, !!(Lamps & 0x200000));
	//Music
	Outputs->SetValue(OutputLampView4, !!(Lamps & 0x100000));
	//start
	Outputs->SetValue(OutputLampStart, !!(Lamps & 0x90000));

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

void FNFDrift::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "FNF Drift";
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