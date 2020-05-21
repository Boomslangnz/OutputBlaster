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

#include "LGI.h"

static int WindowsLoop()
{
	INT_PTR outputBase = helpers->ReadIntPtr(0x63BF5C, true);
	UINT8 outputData = helpers->ReadByte(outputBase + 0x44, false);

	Outputs->SetValue(OutputLampStart, !!(outputData & 0x80));
	Outputs->SetValue(Output1pKnock, !!(outputData & 0x20));
	Outputs->SetValue(Output1pMotor, !!(outputData & 0x40));
	Outputs->SetValue(Output2pKnock, !!(outputData & 0x04));
	Outputs->SetValue(Output2pMotor, !!(outputData & 0x08));
	Outputs->SetValue(Output2pLampStart, !!(outputData & 0x10));
	Outputs->SetValue(OutputRawLamps, outputData);
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

void LGI::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Let's Go Island";
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