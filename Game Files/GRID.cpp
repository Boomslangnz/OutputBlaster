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

#include "GRID.h"

static float RPMValue;

static int WindowsLoop()
{
	Outputs->SetValue(OutputRPM, static_cast<int>(RPMValue / 100.0));
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

static int(__fastcall* RPMHookOri)(int a1);
static int __fastcall RPMHook(int a1)
{
	RPMValue = *((float*)a1 + 11);

	return RPMHookOri(a1);
}

void GRID::OutputsGameLoop()
{
	if (!init)
	{
		DWORD ImageBase = (DWORD)GetModuleHandleA(0);
		Outputs = CreateOutputsFromConfig();
		m_game.name = "GRID";
		Outputs->SetGame(m_game);
		Outputs->Initialize();
		Outputs->Attached();
		CreateThread(NULL, 0, OutputsAreGo, NULL, 0, NULL);

		MH_Initialize();
		MH_CreateHook((void*)(ImageBase + 0x51C720), RPMHook, (void**)&RPMHookOri);
		MH_EnableHook(MH_ALL_HOOKS);

		while (GetMessage(&Msg1, NULL, NULL, 0))
		{
			TranslateMessage(&Msg1);
			DispatchMessage(&Msg1);
		}
		init = true;
	}
}