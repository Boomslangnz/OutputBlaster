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

#include "H2Overdrive.h"

static int WindowsLoop()
{
	float IntakeLeft = helpers->ReadFloat32(0x78C650, false);
	float IntakeCenter = helpers->ReadFloat32(0x78C690, false);
	float IntakeRight = helpers->ReadFloat32(0x78C6D0, false);
	float Base0Left = helpers->ReadFloat32(0x78C750, false);
	float Base1Left = helpers->ReadFloat32(0x78C790, false);
	float Base0Right = helpers->ReadFloat32(0x78C810, false);
	float Base1Right = helpers->ReadFloat32(0x78C7D0, false);
	float SeatLeft = helpers->ReadFloat32(0x78C8D0, false);
	float SeatRight = helpers->ReadFloat32(0x78C910, false);
	float Infinity1 = helpers->ReadFloat32(0x78C950, false);
	float Infinity2 = helpers->ReadFloat32(0x78C990, false);
	float Infinity3 = helpers->ReadFloat32(0x78C9D0, false);
	float Leader = helpers->ReadFloat32(0x78C710, false);

	Outputs->SetValue(OutputIntakeLeft, IntakeLeft * 100.0);
	Outputs->SetValue(OutputIntakeCenter, IntakeCenter * 100.0);
	Outputs->SetValue(OutputIntakeRight, IntakeRight * 100.0);
	Outputs->SetValue(OutputBase0Left, Base0Left * 100.0);
	Outputs->SetValue(OutputBase1Left, Base1Left * 100.0);
	Outputs->SetValue(OutputBase0Right, Base0Right * 100.0);
	Outputs->SetValue(OutputBase1Right, Base1Right * 100.0);
	Outputs->SetValue(OutputSeatLeft, SeatLeft * 100.0);
	Outputs->SetValue(OutputSeatRight, SeatRight * 100.0);
	Outputs->SetValue(OutputInfinity1, Infinity1 * 100.0);
	Outputs->SetValue(OutputInfinity2, Infinity2 * 100.0);
	Outputs->SetValue(OutputInfinity3, Infinity3 * 100.0);
	Outputs->SetValue(OutputLampLeader, Leader * 100.0);

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

void H2Overdrive::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "H2Overdrive";
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