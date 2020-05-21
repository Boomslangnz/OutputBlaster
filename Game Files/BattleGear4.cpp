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

#include "BattleGear4.h"

static int OutputValue(int output) {
	switch (output) {
	case 0x20:
		return 8;
	case 0x1C:
		return 7;
	case 0x18:
		return 6;
	case 0x14:
		return 5;
	case 0x10:
		return 4;
	case 0x0C:
		return 3;
	case 0x08:
		return 2;
	case 0x04:
		return 1;
	default:
		return 0;
	}
}

static int WindowsLoop()
{
	int startvaluelamp = 0;
	int viewvaluelamp = 0;
	int hazardvaluelamp = 0;

	UINT8 startoutput = helpers->ReadByte(0x7CE8D8, false);
	UINT8 viewoutput = helpers->ReadByte(0x7CE8D2, false);
	UINT8 hazardoutput = helpers->ReadByte(0x7CE8D4, false);
	UINT8 overrevoutput = helpers->ReadByte(0x7CE8E3, false);
	startvaluelamp = OutputValue(startoutput);
	viewvaluelamp = OutputValue(viewoutput);
	hazardvaluelamp = OutputValue(hazardoutput);

	//Max Value 100 on everything except OverRev
	Outputs->SetValue(OutputLampStart, (startvaluelamp / 8.0) * 100.0);
	Outputs->SetValue(OutputLampView1, (viewvaluelamp / 8.0) * 100.0);
	Outputs->SetValue(OutputLampHazard, (hazardvaluelamp / 8.0) * 100.0);
	Outputs->SetValue(OutputLampOverrev, !!(overrevoutput & 0x01));

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

void BattleGear4::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Battle Gear 4";
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