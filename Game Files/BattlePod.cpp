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

#include "BattlePod.h"

uintptr_t gameAddress;

static int WindowsLoop()
{
	int fan = helpers->ReadInt32(gameAddress + 0x1EE7A48, false);
	int vibration = helpers->ReadInt32(gameAddress + 0x1EE7A3C, false);
	int view = helpers->ReadInt32(gameAddress + 0x1EE7A64, false);
	int ledRearPanelA = helpers->ReadInt32(gameAddress + 0x1EE7A58, false);
	int ledRearPanelB = helpers->ReadInt32(gameAddress + 0x1EE7A5C, false);
	int ledRearPanelC = helpers->ReadInt32(gameAddress + 0x1EE7A60, false);
	int ledRearWindowsRGB = helpers->ReadInt32(gameAddress + 0x1EE7A54, false);
	int ledRearCoverRGB = helpers->ReadInt32(gameAddress + 0x1EE7A50, false);

	int ledRearWindowsRed = (ledRearWindowsRGB >> 8) & 0xF;
	int ledRearWindowsGreen = (ledRearWindowsRGB >> 4) & 0xF;
	int ledRearWindowsBlue = ledRearWindowsRGB & 0xF;

	int ledRearCoverRed = (ledRearCoverRGB >> 8) & 0xF;
	int ledRearCoverGreen = (ledRearCoverRGB >> 4) & 0xF;
	int ledRearCoverBlue = ledRearCoverRGB & 0xF;

	Outputs->SetValue(Output1pAirFront, !!(fan != 0));
	Outputs->SetValue(OutputLampView1, !!(view != 0));
	Outputs->SetValue(OutputLampView2, !!(ledRearPanelA != 0));
	Outputs->SetValue(OutputLampView3, !!(ledRearPanelB != 0));
	Outputs->SetValue(OutputLampView4, !!(ledRearPanelC != 0));
	Outputs->SetValue(OutputLampRed, ledRearWindowsRed);
	Outputs->SetValue(OutputLampGreen, ledRearWindowsGreen);
	Outputs->SetValue(OutputLampBlue, ledRearWindowsBlue);
	Outputs->SetValue(OutputLampRed2, ledRearCoverRed);
	Outputs->SetValue(OutputLampGreen2, ledRearCoverGreen);
	Outputs->SetValue(OutputLampBlue2, ledRearCoverBlue);

	//vibration is converted to 0-100
	Outputs->SetValue(OutputFFB, vibration / 16 * 100);
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

void BattlePod::OutputsGameLoop()
{
	if (!init)
	{
		gameAddress = (uintptr_t)GetModuleHandleA("SWArcGame-Win64-Shipping.exe");
		Outputs = CreateOutputsFromConfig();
		m_game.name = "BattlePod";
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
