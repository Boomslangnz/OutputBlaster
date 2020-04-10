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

#include "ChaseHQ2.h"

int PatoLightOutput(int patolamp) {
	switch (patolamp) {
	case 0x100:
		return 6;
	case 0x08:
		return 5;
	case 0x80:
		return 4;
	case 0x200:
		return 3;
	case 0x400:
		return 2;
	case 0x10:
		return 1;
	default:
		return 0;
	}
}

static int WindowsLoop()
{
	int outputpatolamp = 0;
	imageBase = (uintptr_t)GetModuleHandleA(0);
	INT_PTR lampbase = *(INT_PTR*)(imageBase + 0x130B558);
	BYTE startlamp = *(BYTE*)(lampbase + 0x49);
	BYTE patolampR = *(BYTE*)(lampbase + 0x4F);
	BYTE patolampB = *(BYTE*)(lampbase + 0x4B);
	INT_PTR patolamp = *(INT_PTR*)(lampbase + 0x45);
	outputpatolamp = PatoLightOutput(patolamp - 16384);
	INT_PTR FFBBase = *(INT_PTR*)(imageBase + 0x130B558);
	BYTE FFB = *(BYTE*)FFBBase + 0x45;

	Outputs->SetValue(OutputLampStart, (startlamp / 255.0) * 100.0); //Modify value on mamehooker to show 0-100, with 100 being max 
	Outputs->SetValue(OutputLampPatoButtonR, (patolampR / 255.0) * 100.0);
	Outputs->SetValue(OutputLampPatoButtonB, (patolampB / 255.0) * 100.0);
	Outputs->SetValue(OutputLampPato, outputpatolamp);
	Outputs->SetValue(OutputFFB, FFB);
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

void ChaseHQ2::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "ChaseHQ2";
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