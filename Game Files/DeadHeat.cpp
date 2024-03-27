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

#include "DeadHeat.h"

static bool dHstartLampOn = false;
static bool dHnitrousOn = false;
static bool dHringTopOn = false;
static bool dHringCenterOn = false;
static bool dHringBottomOn = false;
static bool dHkeypadOn = false;
static bool dHseatOn = false;

static int WindowsLoop()
{

	Outputs->SetValue(OutputLampStart, dHstartLampOn );
	Outputs->SetValue(OutputLampView1, dHnitrousOn );
	Outputs->SetValue(OutputBillboardLamp, dHringTopOn);
	Outputs->SetValue(OutputDash, dHringCenterOn);
	Outputs->SetValue(OutputBase, dHringBottomOn);
	Outputs->SetValue(OutputKeypad, dHkeypadOn);
	Outputs->SetValue(OutputSeat1Lamp, dHseatOn);
	
	//setting default lamps to off
	Outputs->SetValue(OutputLampView2, false);
	Outputs->SetValue(OutputLampView3, false);
	Outputs->SetValue(OutputLampView4, false);

	dHstartLampOn = false;
	dHnitrousOn = false;
	dHringTopOn = false;
	dHringCenterOn = false;
	dHringBottomOn = false;
	dHkeypadOn = false;
	dHseatOn = false;
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
static void(__cdecl* CBLampSetOri)(int param_1, int param_2);
static void __cdecl CBLampSet(int param_1, int param_2)
{
	if (param_2 == 2) {
		dHstartLampOn = true;
	}
	if (param_2 == 4)
	{
		dHnitrousOn = true;
	}
	if (param_2 == 128)
	{
		dHringTopOn = true;
	}
	if (param_2 == 64)
	{
		dHringCenterOn = true;
	}
	if (param_2 == 32)
	{
		dHringBottomOn = true;
	}
	if (param_2 == 16)
	{
		dHkeypadOn = true;
	}
	if (param_2 == 8)
	{
		dHseatOn = true;
	}
	return CBLampSetOri(param_1, param_2);
}

void DeadHeat::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Dead Heat";
		Outputs->SetGame(m_game);
		Outputs->Initialize();
		Outputs->Attached();
		CreateThread(NULL, 0, OutputsAreGo, NULL, 0, NULL);

		MH_Initialize();
		MH_CreateHook((LPVOID)(0x80a0050), CBLampSet, (LPVOID*)&CBLampSetOri);
		MH_EnableHook(MH_ALL_HOOKS);
		
		while (GetMessage(&Msg1, NULL, NULL, 0))
		{
			TranslateMessage(&Msg1);
			DispatchMessage(&Msg1);
		}
		init = true;
	}
}