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

static int WindowsLoop()
{
	int air = 0;
	int vibration = 0;
	int view = 0;
	int ledRearPanelA = 0;
	int ledRearPanelB = 0;
	int ledRearPanelC = 0;
	int ledRearWindowsRGB = 0;
	int ledRearCoverRGB = 0;

	air = helpers->ReadInt32( 0x1EE7A48, true);
	vibration = helpers->ReadInt32( 0x1EE7A3C, true);
	view = helpers->ReadInt32( 0x1EE7A64, true);
	ledRearPanelA = helpers->ReadInt32( 0x1EE7A58, true);
	ledRearPanelB = helpers->ReadInt32( 0x1EE7A5C, true);
	ledRearPanelC = helpers->ReadInt32( 0x1EE7A60, true);
	ledRearWindowsRGB = helpers->ReadInt32( 0x1EE7A54, true);
	ledRearCoverRGB = helpers->ReadInt32( 0x1EE7A50, true);



	int ledRearWindowsRed = (ledRearWindowsRGB >> 8) & 0xF;
	int ledRearWindowsGreen = (ledRearWindowsRGB >> 4) & 0xF;
	int ledRearWindowsBlue = ledRearWindowsRGB & 0xF;

	int ledRearCoverRed = (ledRearCoverRGB >> 8) & 0xF;
	int ledRearCoverGreen = (ledRearCoverRGB >> 4) & 0xF;
	int ledRearCoverBlue = ledRearCoverRGB & 0xF;

	Outputs->SetValue(Output1pAirFront, !!(air & 1));
	Outputs->SetValue(OutputLampView1, !!(view & 1));
	Outputs->SetValue(OutputLampView2, !!(ledRearPanelA & 1));
	Outputs->SetValue(OutputLampView3, !!(ledRearPanelB & 1));
	Outputs->SetValue(OutputLampView4, !!(ledRearPanelC & 1));
	Outputs->SetValue(OutputLampRed, ledRearWindowsRed);
	Outputs->SetValue(OutputLampGreen, ledRearWindowsGreen);
	Outputs->SetValue(OutputLampBlue, ledRearWindowsBlue);
	Outputs->SetValue(OutputLampRed2, ledRearCoverRed);
	Outputs->SetValue(OutputLampGreen2, ledRearCoverGreen);
	Outputs->SetValue(OutputLampBlue2, ledRearCoverBlue);
	Outputs->SetValue(OutputFFB, (vibration / 16) * 100);
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
