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

#include "CrazyRide.h"

static uintptr_t usbBase;
static bool startOn = false;
static bool brakeOn = false;
static bool stopOn = false;
static int WindowsLoop()
{

	UINT8 Brake = helpers->ReadInt32(usbBase + 0x22638, false);
	UINT8 Start = helpers->ReadInt32(usbBase + 0x22630, false);
	UINT8 StopLamp = helpers->ReadInt32(usbBase + 0x22634, false);

	if (Start == 1) {
		Outputs->SetValue(OutputLampStart, true);
	}
	else if (Start == 2)
	{
		if (startOn)
		{
			startOn = false;
		}
		else
		{
			startOn = true;
		}
		Outputs->SetValue(OutputLampStart, startOn);
	}
	else
	{
		Outputs->SetValue(OutputLampStart, false);
	}

	//brake
	
	if (Brake == 1)
	{
		Outputs->SetValue(OutputLampView1, true);
	}
	else if (Brake == 2)
	{
		if (brakeOn)
		{
			brakeOn = false;
		}
		else
		{
			brakeOn = true;
		}
		Outputs->SetValue(OutputLampView1, brakeOn);
	}	
	else
	{
		Outputs->SetValue(OutputLampView1, false);
	}

	//stop lamp

	if (StopLamp == 1)
	{
		Outputs->SetValue(OutputLampView2, true);
	}
	else if (StopLamp == 2)
	{
		if (stopOn)
		{
			stopOn = false;
		}
		else
		{
			stopOn = true;
		}
		Outputs->SetValue(OutputLampView2, stopOn);
	}
	else
	{
		Outputs->SetValue(OutputLampView2, false);
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


void CrazyRide::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		usbBase = (uintptr_t)GetModuleHandleA("UsbPluginsDll_R.dll");
		m_game.name = "Crazy Ride";
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