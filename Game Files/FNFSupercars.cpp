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

#include "FNFSupercars.h"

static int WindowsLoop()
{
	DWORD Start = helpers->ReadInt32( 0x731970, false);
	DWORD View1 = helpers->ReadInt32( 0x731990, false);
	DWORD View2 = helpers->ReadInt32( 0x7319B0, false);
	DWORD View3 = helpers->ReadInt32( 0x7319D0, false);
	DWORD Music = helpers->ReadInt32( 0x7319F0, false);
	//DWORD RaceLeader = helpers->ReadByte( + 0x45271F4, false);

	Outputs->SetValue(OutputLampStart, !!(Start >= 1166012416));
	Outputs->SetValue(OutputLampView1, !!(View1 >= 1166012416));
	Outputs->SetValue(OutputLampView2, !!(View2 >= 1166012416));
	Outputs->SetValue(OutputLampView3, !!(View3 >= 1166012416));
	Outputs->SetValue(OutputLampView4, !!(Music >= 1166012416));
	//Outputs->SetValue(OutputLampLeader, !!(RaceLeader & 0xFF));

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




void FNFSupercars::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "FNF Supercars";
		Outputs->SetGame(m_game);
		Outputs->Initialize();
		Outputs->Attached();
		MH_EnableHook(MH_ALL_HOOKS);
		CreateThread(NULL, 0, OutputsAreGo, NULL, 0, NULL);
		while (GetMessage(&Msg1, NULL, NULL, 0))
		{
			TranslateMessage(&Msg1);
			DispatchMessage(&Msg1);
		}
		init = true;
	}
}