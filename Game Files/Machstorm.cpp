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

#include "Machstorm.h"

static int WindowsLoop()
{
	UINT8 VibrationData = helpers->ReadByte(0x6390E9, true);
	UINT8 PowerData = helpers->ReadByte(0x639109, true);
	UINT8 LEDRearCoverData1 = helpers->ReadByte(0x6390EB, true);
	UINT8 LEDRearCoverData2 = helpers->ReadByte(0x6390EC, true);
	UINT8 LEDRearCoverData3 = helpers->ReadByte(0x6390ED, true);
	UINT8 ColourRed = helpers->ReadByte(0x639108, true);
	UINT8 ColourGreenBlue = helpers->ReadByte(0x63910B, true);

	Outputs->SetValue(OutputVibration, !!(VibrationData & 0x01));
	Outputs->SetValue(OutputRearCover, !!((LEDRearCoverData1 & LEDRearCoverData2 & LEDRearCoverData3) & 0x01));
	Outputs->SetValue(OutputLampRed, ColourRed);

	if (PowerData > 244)
	{
		Outputs->SetValue(OutputPower, PowerData - 245);
	}
	else
	{
		Outputs->SetValue(OutputPower, PowerData - 101);
	}

	if (ColourGreenBlue == 0)
	{
		Outputs->SetValue(OutputLampGreen, 0);
		Outputs->SetValue(OutputLampBlue, 0);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 0) && (ColourGreenBlue < 16))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue);
		Outputs->SetValue(OutputLampBlue, 0);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 15) && (ColourGreenBlue < 32))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 16);
		Outputs->SetValue(OutputLampBlue, 1);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 31) && (ColourGreenBlue < 48))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 32);
		Outputs->SetValue(OutputLampBlue, 2);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 47) && (ColourGreenBlue < 64))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 48);
		Outputs->SetValue(OutputLampBlue, 3);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 63) && (ColourGreenBlue < 80))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 64);
		Outputs->SetValue(OutputLampBlue, 4);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 79) && (ColourGreenBlue < 96))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 80);
		Outputs->SetValue(OutputLampBlue, 5);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 95) && (ColourGreenBlue < 112))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 96);
		Outputs->SetValue(OutputLampBlue, 6);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 111) && (ColourGreenBlue < 128))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 112);
		Outputs->SetValue(OutputLampBlue, 7);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 127) && (ColourGreenBlue < 144))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 128);
		Outputs->SetValue(OutputLampBlue, 8);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 143) && (ColourGreenBlue < 160))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 144);
		Outputs->SetValue(OutputLampBlue, 9);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 159) && (ColourGreenBlue < 176))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 160);
		Outputs->SetValue(OutputLampBlue, 10);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 175) && (ColourGreenBlue < 192))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 176);
		Outputs->SetValue(OutputLampBlue, 11);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 191) && (ColourGreenBlue < 208))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 192);
		Outputs->SetValue(OutputLampBlue, 12);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 207) && (ColourGreenBlue < 224))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 208);
		Outputs->SetValue(OutputLampBlue, 13);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if ((ColourGreenBlue > 223) && (ColourGreenBlue < 240))
	{
		Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 224);
		Outputs->SetValue(OutputLampBlue, 14);
		Outputs->SetValue(OutputLampWhite, 0);
	}
	else if (ColourGreenBlue > 239)
	{
		if ((ColourGreenBlue == 255) && (ColourRed == 15))
		{
			Outputs->SetValue(OutputLampWhite, 1);
		}
		else
		{
			Outputs->SetValue(OutputLampGreen, ColourGreenBlue - 240);
			Outputs->SetValue(OutputLampBlue, 15);
			Outputs->SetValue(OutputLampWhite, 0);
		}
	}
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

void Machstorm::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Machstorm";
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