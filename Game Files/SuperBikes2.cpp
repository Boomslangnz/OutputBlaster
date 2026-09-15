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

#include "SuperBikes2.h"


bool sb2LampStart = false;
bool sb2LampView = false;
bool sb2LampMusic = false;
bool sb2Plate = false;
bool sb2Leader = false;
bool sb2Top = false;
bool sb2Dash = false;
bool sbSubWoofer = false;

static void* (__cdecl* SetControlOrLampOrig)(unsigned int param_1, unsigned int param_2);
static void* __cdecl SetControlOrLamp(unsigned int param_1, unsigned int param_2) {
	void* result = SetControlOrLampOrig(param_1, param_2);
	if (param_1 == 0x1004a) {

		unsigned int lampId = (param_2 >> 16) & 0xFF;
		unsigned int lampState = param_2 & 0xFFF;

		bool lampOn = (lampState != 0);
		if (lampId == 0) sb2LampStart = lampOn;
		if (lampId == 2) sb2LampView = lampOn;
		if (lampId == 4) sb2Plate = lampOn;
		if (lampId == 5) sb2LampMusic = lampOn;
		if (lampId == 6) sb2Leader = lampOn;
		if (lampId == 7) sb2Top = lampOn;
		if (lampId == 10) sb2Dash = lampOn;
		if (lampId == 11) sbSubWoofer = lampOn;

	}
	return result;
}

static void(__cdecl* HardwareDispatchOrig)(unsigned int param_1, unsigned int param_2);
static void __cdecl HardwareDispatch(unsigned int param_1, unsigned int param_2) {
	return;
}

static int(__cdecl* SerialInitOrig)();
static int __cdecl SerialInit() {
	return 1;
}

static int(__cdecl* LedDisplayUpdateOrig)();
static int __cdecl LedDisplayUpdate() {
	return 1;
}

static int(__cdecl* HidWriteOrig)(LPCVOID param_1);
static int __cdecl HidWrite(LPCVOID param_1) {
	return 0;
}

static int(__cdecl* UsbWriteOrig)();
static int __cdecl UsbWrite() {
	return 0;
}

static int(__cdecl* HidDeviceScanOrig)();
static int __cdecl HidDeviceScan() {
	return 0;
}

static int(__cdecl* InitUsbDeviceOrig)();
static int __cdecl InitUsbDeviceHook() {
	return 0;
}

static int WindowsLoop()
{
	Outputs->SetValue(OutputLampStart, sb2LampStart);
	Outputs->SetValue(OutputLampView1, sb2LampView);
	Outputs->SetValue(OutputLampView2, sb2LampMusic);
	Outputs->SetValue(OutputLampLeader, sb2Leader);
	Outputs->SetValue(OutputFogLight1, sb2Top);
	Outputs->SetValue(OutputRearCover, sb2Plate);
	Outputs->SetValue(OutputDash, sb2Dash);
	Outputs->SetValue(OutputWooferBlue, sbSubWoofer);
	return 0;
}

static DWORD WINAPI OutputsAreGo(LPVOID lpParam)
{
	MH_Initialize();
	MH_CreateHook((LPVOID)0x04bbc10, SetControlOrLamp, (LPVOID*)&SetControlOrLampOrig);
	MH_CreateHook((LPVOID)0x04018d0, HardwareDispatch, (LPVOID*)&HardwareDispatchOrig);
	MH_CreateHook((LPVOID)0x04ee430, SerialInit, (LPVOID*)&SerialInitOrig);
	MH_CreateHook((LPVOID)0x04ee890, LedDisplayUpdate, (LPVOID*)&LedDisplayUpdateOrig);

	MH_CreateHook((LPVOID)0x0405800, HidWrite, (LPVOID*)&HidWriteOrig);
	MH_CreateHook((LPVOID)0x0402bc0, UsbWrite, (LPVOID*)&UsbWriteOrig);

	MH_CreateHook((LPVOID)0x0405930, HidDeviceScan, (LPVOID*)&HidDeviceScanOrig);
	MH_CreateHook((LPVOID)0x0405c80, InitUsbDeviceHook, (LPVOID*)&InitUsbDeviceOrig);

	MH_EnableHook(MH_ALL_HOOKS);


	*(int*)0x089dfc40 = 1;

	DWORD* hidDev = *(DWORD**)0x0894b4c8;
	if (hidDev != nullptr) {
		HANDLE hRead = (HANDLE)hidDev[0];
		HANDLE hWrite = (HANDLE)hidDev[1];
		if (hWrite) { CancelIo(hWrite); CloseHandle(hWrite); hidDev[1] = 0; }
		if (hRead) { CancelIo(hRead); CloseHandle(hRead); hidDev[0] = 0; }
	}
	*(DWORD**)0x0894b4c8 = nullptr;

	helpers->WriteNopBytes(0x0046d363, 2, false);
	helpers->WriteNopBytes(0x00408f99, 6, false);

	while (true)
	{
		WindowsLoop();
		Sleep(SleepA);
	}
}

void SuperBikes2::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = CreateOutputsFromConfig();
		m_game.name = "Super Bikes 2";
		Outputs->SetGame(m_game);
		Outputs->Initialize();
		Outputs->Attached();
		OutputDebugStringA("Super Bikes 2 Outputs Initialized");
		CreateThread(NULL, 0, OutputsAreGo, NULL, 0, NULL);
		while (GetMessage(&Msg1, NULL, NULL, 0))
		{
			TranslateMessage(&Msg1);
			DispatchMessage(&Msg1);
		}
		init = true;
	}
}