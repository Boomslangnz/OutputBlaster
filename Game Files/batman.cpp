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

#include "batman.h"

static bool lightsEnabled = false;

static int WindowsLoop()
{
	if (lightsEnabled) {

		bool StartButton = helpers->ReadByte(0x1BEF942, false) > 0;
		bool FireButtons = helpers->ReadByte(0x1BEF946, false) > 0;
		bool BatLogo = helpers->ReadByte(0x1BEF952, false) > 0;
		bool Marquee = helpers->ReadByte(0x1BEF97E, false) > 0;
		bool SpeakersRed = helpers->ReadByte(0x1BEF962, false) > 0;
		bool SpeakersOrange = helpers->ReadByte(0x1BEF966, false) > 0;
		bool SpeakersYellow = helpers->ReadByte(0x1BEF96A, false) > 0;
		bool CenterDashPanel = helpers->ReadByte(0x1BEF94E, false) > 0;
		bool RightDashPanel = helpers->ReadByte(0x1BEF94A, false) > 0;
		bool KeypadRed = helpers->ReadByte(0x1BEF96E, false) > 0;
		bool KeypadGreen = helpers->ReadByte(0x1BEF972, false) > 0;
		bool KeypadBlue = helpers->ReadByte(0x1BEF976, false) > 0;
		bool Kickplates = helpers->ReadByte(0x1BEF97A, false) > 0;

		Outputs->SetValue(OutputLampStart, StartButton);
		Outputs->SetValue(OutputShoot1p, FireButtons);
		Outputs->SetValue(OutputBillboardWhite, BatLogo);
		Outputs->SetValue(OutputBillboardLamp, Marquee);
		Outputs->SetValue(OutputSpeaker1, SpeakersRed);
		Outputs->SetValue(OutputSpeaker2, SpeakersOrange);
		Outputs->SetValue(OutputSpeaker3, SpeakersYellow);
		Outputs->SetValue(OutputDash, CenterDashPanel);
		Outputs->SetValue(OutputSeatRight, RightDashPanel);
		Outputs->SetValue(OutputLampRed, KeypadRed);
		Outputs->SetValue(OutputLampGreen, KeypadGreen);
		Outputs->SetValue(OutputLampBlue, KeypadBlue);
		Outputs->SetValue(OutputBase, Kickplates);

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

static DWORD(__fastcall* TurnOnIOORig)(int* param_1);
static DWORD __fastcall TurnOnIO(int* param_1)
{

	lightsEnabled = true;
	return 1;
}

void Batman::OutputsGameLoop()
{
	if (!init)
	{

		MH_Initialize();
		MH_CreateHook((void*)0x12f9440, &TurnOnIO, reinterpret_cast<LPVOID*>(&TurnOnIOORig));
		MH_EnableHook(MH_ALL_HOOKS);
		init = true;

		Outputs = CreateOutputsFromConfig();
		m_game.name = "Batman";
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