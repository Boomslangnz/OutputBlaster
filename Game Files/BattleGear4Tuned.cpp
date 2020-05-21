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

#include "BattleGear4Tuned.h"

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
	int keyvaluelamp = 0;
	int redvaluelamp = 0;
	int greenvaluelamp = 0;
	int bluevaluelamp = 0;
	UINT8 startoutput = helpers->ReadByte(0x82D95C, false);
	UINT8 viewoutput = helpers->ReadByte(0x82D956, false);
	UINT8 hazardoutput = helpers->ReadByte(0x82D958, false);
	UINT8 keyoutput = helpers->ReadByte(0x82D95A, false);
	UINT8 onlineoutput = helpers->ReadByte(0x82D966, false);
	UINT8 overrevoutput = helpers->ReadByte(0x82D967, false);
	UINT8 redoutput = helpers->ReadByte(0x82D95E, false);
	UINT8 greenoutput = helpers->ReadByte(0x82D960, false);
	UINT8 blueoutput = helpers->ReadByte(0x82D962, false);
	startvaluelamp = OutputValue(startoutput);
	viewvaluelamp = OutputValue(viewoutput);
	hazardvaluelamp = OutputValue(hazardoutput);
	keyvaluelamp = OutputValue(keyoutput);
	redvaluelamp = OutputValue(redoutput);
	greenvaluelamp = OutputValue(greenoutput);
	bluevaluelamp = OutputValue(blueoutput);

	//Max Value 100 on everything except Online & OverRev
	Outputs->SetValue(OutputLampStart, (startvaluelamp / 8.0) * 100.0);
	Outputs->SetValue(OutputLampView1, (viewvaluelamp / 8.0) * 100.0);
	Outputs->SetValue(OutputLampHazard, (hazardvaluelamp / 8.0) * 100.0);
	Outputs->SetValue(OutputLampKey, (keyvaluelamp / 8.0) * 100.0);
	Outputs->SetValue(OutputLampOnline, !!(onlineoutput & 0x01));
	Outputs->SetValue(OutputLampOverrev, !!(overrevoutput & 0x01));
	Outputs->SetValue(OutputLampRed, (redvaluelamp / 8.0) * 100.0);
	Outputs->SetValue(OutputLampGreen, (greenvaluelamp / 8.0) * 100.0);
	Outputs->SetValue(OutputLampBlue, (bluevaluelamp / 8.0) * 100.0);
	Outputs->SetValue(OutputLampYellow, ((redvaluelamp & greenvaluelamp) / 8.0) * 100.0);
	Outputs->SetValue(OutputLampCyan, ((greenvaluelamp & bluevaluelamp) / 8.0) * 100.0);
	Outputs->SetValue(OutputLampMagneta, ((bluevaluelamp & redvaluelamp) / 8.0) * 100.0);
	Outputs->SetValue(OutputLampWhite, ((bluevaluelamp & greenvaluelamp & redvaluelamp) / 8.0) * 100.0);
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

void BattleGear4Tuned::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Battle Gear 4 Tuned";
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