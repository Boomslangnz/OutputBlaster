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

#include "DirtyDrivin.h"

static int WindowsLoop()
{
	DWORD LeftIndicator1 = helpers->ReadInt32(0x5A205C, true);
	DWORD LeftIndicator2 = helpers->ReadInt32(0x5A2058, true);
	DWORD LeftIndicator3 = helpers->ReadInt32(0x5A2054, true);
	DWORD LeftIndicator4 = helpers->ReadInt32(0x5A2050, true);
	DWORD RightIndicator1 = helpers->ReadInt32(0x5A206C, true);
	DWORD RightIndicator2 = helpers->ReadInt32(0x5A2068, true);
	DWORD RightIndicator3 = helpers->ReadInt32(0x5A2064, true);
	DWORD RightIndicator4 = helpers->ReadInt32(0x5A2060, true);
	DWORD FogLight1 = helpers->ReadInt32(0x5A208C, true);
	DWORD FogLight2 = helpers->ReadInt32(0x5A2074, true);
	DWORD FogLight3 = helpers->ReadInt32(0x5A2070, true);
	DWORD FogLight4 = helpers->ReadInt32(0x5A2088, true);
	DWORD Speaker1 = helpers->ReadInt32(0x5A2078, true);
	DWORD Speaker2 = helpers->ReadInt32(0x5A207C, true);
	DWORD Speaker3 = helpers->ReadInt32(0x5A2080, true);
	DWORD LargeDials = helpers->ReadInt32(0x5A2084, true);
	UINT8 RestOutputs = helpers->ReadByte(0x5A2000, true);

	Outputs->SetValue(OutputLeftIndicator1, (LeftIndicator1 / 4095.0) * 100.0);
	Outputs->SetValue(OutputLeftIndicator2, (LeftIndicator2 / 4095.0) * 100.0);
	Outputs->SetValue(OutputLeftIndicator3, (LeftIndicator3 / 4095.0) * 100.0);
	Outputs->SetValue(OutputLeftIndicator4, (LeftIndicator4 / 4095.0) * 100.0);
	Outputs->SetValue(OutputRightIndicator1, (RightIndicator1 / 4095.0) * 100.0);
	Outputs->SetValue(OutputRightIndicator2, (RightIndicator2 / 4095.0) * 100.0);
	Outputs->SetValue(OutputRightIndicator3, (RightIndicator3 / 4095.0) * 100.0);
	Outputs->SetValue(OutputRightIndicator4, (RightIndicator4 / 4095.0) * 100.0);
	Outputs->SetValue(OutputFogLight1, (FogLight1 / 4095.0) * 100.0);
	Outputs->SetValue(OutputFogLight2, (FogLight2 / 4095.0) * 100.0);
	Outputs->SetValue(OutputFogLight3, (FogLight3 / 4095.0) * 100.0);
	Outputs->SetValue(OutputFogLight4, (FogLight4 / 4095.0) * 100.0);
	Outputs->SetValue(OutputSpeaker1, (Speaker1 / 4095.0) * 100.0);
	Outputs->SetValue(OutputSpeaker2, (Speaker2 / 4095.0) * 100.0);
	Outputs->SetValue(OutputSpeaker3, (Speaker3 / 4095.0) * 100.0);
	Outputs->SetValue(OutputLargeDials, (LargeDials / 4095.0) * 100.0);
	Outputs->SetValue(OutputSmallDialLeft, !!(RestOutputs & 0x40));
	Outputs->SetValue(OutputSmallDialRight, !!(RestOutputs & 0x08));
	Outputs->SetValue(OutputBase, !!(RestOutputs & 0x20));
	Outputs->SetValue(OutputLampView1, !!(RestOutputs & 0x80));
	Outputs->SetValue(OutputExtra, !!(RestOutputs & 0x10));

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

void DirtyDrivin::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Dirty Drivin";
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