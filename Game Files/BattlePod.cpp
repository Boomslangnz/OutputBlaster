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

#include "BattlePod.h"
#include <TlHelp32.h>

DWORD GetProcessIDByName(const std::wstring& processName) {
	DWORD processID = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hSnapshot, &pe)) {
			do {
				if (pe.szExeFile == processName) {
					processID = pe.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnapshot, &pe));
		}
		CloseHandle(hSnapshot);
	}
	return processID;
}
static UINT64 baseAddress = 0x00007ff758ac0000;
static HANDLE hProcess;

static int WindowsLoop()
{
	int air = 0;
	int vibration = 0;
	int view = 0;
	int ledRearPanelA = 0;
	int ledRearPanelB = 0;
	int ledRearPanelC = 0;
	int ledRearWindowsRGB = 0;
	int ledRearCoverRGB = 0;

	uintptr_t targetAddress = baseAddress + 0x1EE7A48;
	ReadProcessMemory(hProcess, (LPCVOID)targetAddress, &air, sizeof(air), NULL);

	targetAddress = baseAddress + 0x1EE7A3C;
	ReadProcessMemory(hProcess, (LPCVOID)targetAddress, &vibration, sizeof(vibration), NULL);

	targetAddress = baseAddress + 0x1EE7A64;
	ReadProcessMemory(hProcess, (LPCVOID)targetAddress, &view, sizeof(view), NULL);

	targetAddress = baseAddress + 0x1EE7A58;
	ReadProcessMemory(hProcess, (LPCVOID)targetAddress, &ledRearPanelA, sizeof(ledRearPanelA), NULL);

	targetAddress = baseAddress + 0x1EE7A5C;
	ReadProcessMemory(hProcess, (LPCVOID)targetAddress, &ledRearPanelB, sizeof(ledRearPanelB), NULL);

	targetAddress = baseAddress + 0x1EE7A60;
	ReadProcessMemory(hProcess, (LPCVOID)targetAddress, &ledRearPanelC, sizeof(ledRearPanelC), NULL);

	targetAddress = baseAddress + 0x1EE7A54;
	ReadProcessMemory(hProcess, (LPCVOID)targetAddress, &ledRearWindowsRGB, sizeof(ledRearWindowsRGB), NULL);

	targetAddress = baseAddress + 0x1EE7A50;
	ReadProcessMemory(hProcess, (LPCVOID)targetAddress, &ledRearCoverRGB, sizeof(ledRearCoverRGB), NULL);

	int ledRearWindowsRed = (ledRearWindowsRGB >> 8) & 0xF;
	int ledRearWindowsGreen = (ledRearWindowsRGB >> 4) & 0xF;
	int ledRearWindowsBlue = ledRearWindowsRGB & 0xF;

	int ledRearCoverRed = (ledRearCoverRGB >> 8) & 0xF;
	int ledRearCoverGreen = (ledRearCoverRGB >> 4) & 0xF;
	int ledRearCoverBlue = ledRearCoverRGB & 0xF;

	Outputs->SetValue(Output1pAirFront, !!(air & 1));
	Outputs->SetValue(OutputLampView1, !!(view & 1));
	Outputs->SetValue(OutputLampView2, !!(ledRearPanelA & 1));
	Outputs->SetValue(OutputLampView3, !!(ledRearPanelB & 1));
	Outputs->SetValue(OutputLampView4, !!(ledRearPanelC & 1));
	Outputs->SetValue(OutputLampRed, ledRearWindowsRed);
	Outputs->SetValue(OutputLampGreen, ledRearWindowsGreen);
	Outputs->SetValue(OutputLampBlue, ledRearWindowsBlue);
	Outputs->SetValue(OutputLampRed2, ledRearCoverRed);
	Outputs->SetValue(OutputLampGreen2, ledRearCoverGreen);
	Outputs->SetValue(OutputLampBlue2, ledRearCoverBlue);
	Outputs->SetValue(OutputFFB, (vibration / 16) * 100);
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

void BattlePod::OutputsGameLoop()
{
	if (!init)
	{
		std::wstring exeName = L"SWArcGame-Win64-Shipping.exe";
		DWORD processID = GetProcessIDByName(exeName);
		if (processID == 0) return;

		hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processID);
		if (hProcess == NULL) {
			return;
		}

		Outputs = CreateOutputsFromConfig();
		m_game.name = "BattlePod";
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
