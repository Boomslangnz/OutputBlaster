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

#include "TheWalkingDead.h"


static int WindowsLoop()
{
	UINT8 Start = helpers->ReadByte(0x90F6760, false);
	UINT8 RightStart = helpers->ReadByte(0x90F6764, false);
	UINT8 Posts = helpers->ReadByte(0x90F6768, false);
	UINT8 RearRed = helpers->ReadByte(0x90F676C, false);
	UINT8 WalkerCeiling = helpers->ReadByte(0x90F6770, false);
	UINT8 WalkerEyes = helpers->ReadByte(0x90F6774, false);
	UINT8 WalkerAmbientBlue = helpers->ReadByte(0x90F67BC, false);
	UINT8 WalkerAmbientGreen = helpers->ReadByte(0x90F67B8, false);
	UINT8 WalkerAmbientRed = helpers->ReadByte(0x90F67B4, false);
	UINT8 LeftGunMount = helpers->ReadByte(0x90F6790, false);
	UINT8 RightGunMount = helpers->ReadByte(0x90F67C0, false);
	UINT8 DashboardLeftGreen = helpers->ReadByte(0x90F6788, false);
	UINT8 DashboardRightBlue = helpers->ReadByte(0x90F678C, false);
	UINT8 RoofRed = helpers->ReadByte(0x90F6794, false);
	UINT8 RoofGreen = helpers->ReadByte(0x90F6798, false);
	UINT8 RoofBlue = helpers->ReadByte(0x90F679C, false);
	UINT8 SquareMarquee = helpers->ReadByte(0x90F67B0, false);
	UINT8 LeftCrossbowTop = helpers->ReadByte(0x8AC2188, false);
	UINT8 RightCrossbowTop = helpers->ReadByte(0x8AC218C, false);

	UINT8 Player1Ammo = helpers->ReadByte(0x901010C, false);
	UINT8 Player2Ammo = helpers->ReadByte(0x90102E0, false);
	Outputs->SetValue(OutputLampStart, !!(Start));
	Outputs->SetValue(Output2pLampStart, !!(RightStart));
	Outputs->SetValue(OutputBillboardLamp, !!(Posts));
	Outputs->SetValue(OutputBrakeLamp1p, !!(RearRed));
	Outputs->SetValue(OutputBrakeLamp2p, !!(WalkerCeiling));
	Outputs->SetValue(OutputThrottle1, !!(WalkerEyes));
	Outputs->SetValue(OutputRearBlue, !!(WalkerAmbientBlue));
	Outputs->SetValue(OutputRearGreen, !!(WalkerAmbientGreen));
	Outputs->SetValue(OutputRearRed, !!(WalkerAmbientRed));
	Outputs->SetValue(Output1pHolderLamp, !!(LeftGunMount));
	Outputs->SetValue(Output2pHolderLamp, !!(RightGunMount));
	Outputs->SetValue(OutputLampGreen, !!(DashboardLeftGreen));
	Outputs->SetValue(OutputLampBlue, !!(DashboardRightBlue));
	Outputs->SetValue(OutputLampRed2, !!(RoofRed));
	Outputs->SetValue(OutputLampGreen2, !!(RoofGreen));
	Outputs->SetValue(OutputLampBlue2, !!(RoofBlue));
	Outputs->SetValue(OutputLampWhite, !!(SquareMarquee));
	Outputs->SetValue(OutputLampView1, !!(LeftCrossbowTop));
	Outputs->SetValue(OutputLampView2, !!(RightCrossbowTop));
	
	Outputs->SetValue(OutputAmmo1pA, Player1Ammo);
	Outputs->SetValue(OutputAmmo2pA, Player2Ammo);

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

void WalkingDead::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "The Walking Dead";
		Outputs->SetGame(m_game);
		Outputs->Initialize();
		Outputs->Attached();
		OutputDebugStringA("The Walking Dead Outputs Initialized");
		CreateThread(NULL, 0, OutputsAreGo, NULL, 0, NULL);
		while (GetMessage(&Msg1, NULL, NULL, 0))
		{
			TranslateMessage(&Msg1);
			DispatchMessage(&Msg1);
		}
		init = true;
	}
}