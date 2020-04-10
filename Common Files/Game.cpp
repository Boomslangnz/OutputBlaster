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

#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

typedef unsigned char U8;

Helpers * helpers = new Helpers();

int configOutputsSystem = GetPrivateProfileInt(TEXT("Settings"), TEXT("OutputsSystem"), 0, settingsFilename);
int configNetOutputsWithLF = GetPrivateProfileInt(TEXT("Settings"), TEXT("NetOutputsWithLF"), 0, settingsFilename);
int configNetOutputsTCPPort = GetPrivateProfileInt(TEXT("Settings"), TEXT("NetOutputsTCPPort"), 8000, settingsFilename);
int configNetOutputsUDPBroadcastPort = GetPrivateProfileInt(TEXT("Settings"), TEXT("NetOutputsUDPBroadcastPort"), 8001, settingsFilename);

bool Helpers::fileExists(char *filename)
{
	std::ifstream ifile(filename);
	return !ifile.fail();
}

void Helpers::log(char *msg) {
	if (enableLogging == 0) { return; }
	std::ofstream ofs("FFBlog.txt", std::ofstream::app);
	ofs << msg << std::endl;
	ofs.close();
}

void Helpers::logInt(int value) {
	std::string njs = std::to_string(value);
	log((char *)njs.c_str());
}

void Helpers::logInit(char *msg) {
	if (enableLogging == 0) { return; }
	std::ofstream ofs("FFBlog.txt", std::ofstream::out);
	ofs << msg << std::endl;
	ofs.close();
}

// reading memory
LPVOID Helpers::GetTranslatedOffset(INT_PTR offset)
{
	return reinterpret_cast<LPVOID>((INT_PTR)GetModuleHandle(NULL) + offset);
}

UINT8 Helpers::ReadByte(INT_PTR offset, bool isRelativeOffset)
{
	UINT8 val = 0;
	SIZE_T read;
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	ReadProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(UINT8), &read);
	return val;
}

float Helpers::WriteFloat32(INT_PTR offset, float val, bool isRelativeOffset)
{
	//val = 0.0f;
	SIZE_T written;
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	WriteProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(float), &written);
	return val;
}

UINT8 Helpers::WriteByte(INT_PTR offset, UINT8 val, bool isRelativeOffset)
{
	SIZE_T written;
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	WriteProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(UINT8), &written);
	return val;
}

INT_PTR Helpers::WriteIntPtr(INT_PTR offset, INT_PTR val, bool isRelativeOffset)
{
	SIZE_T written;
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	WriteProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(INT_PTR), &written);
	return val;
}

UINT8 Helpers::WriteNop(INT_PTR offset, bool isRelativeOffset)
{
	U8 nop = 0x90;
	SIZE_T written;
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	WriteProcessMemory(GetCurrentProcess(), trueOffset, &nop, 1, &written);
	return nop;
}

int Helpers::ReadInt32(INT_PTR offset, bool isRelativeOffset)
{
	int val = 0;
	SIZE_T read;
	//log("going to try to RPM");
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	ReadProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(int), &read);
	//log("RPM");
	//char text[256];
	//sprintf_s(text, "%16X / %16X\n", offset, trueOffset);
	//log(text);
	return val;
}

INT_PTR Helpers::ReadIntPtr(INT_PTR offset, bool isRelativeOffset)
{
	SIZE_T read;
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	INT_PTR val;
	ReadProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(INT_PTR), &read);
	return val;
}

float Helpers::ReadFloat32(INT_PTR offset, bool isRelativeOffset)
{
		
		float val = 0.0f;
		SIZE_T read;
		//log("going to try to RPM");
		LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
		ReadProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(float), &read);
		//char text[256];
		//sprintf_s(text, "%16X / %16X\n", offset, trueOffset);
		//log(text);
		//log("RPM");
		return val;
		
}

void Game::OutputsGameLoop()
{
	return;
}

COutputs* Game::CreateOutputsFromConfig()
{
	switch (configOutputsSystem) {
		case 1: {
			auto outputs = new CNetOutputs();
			// TCP and UDP port from .ini
			outputs->TcpPort = configNetOutputsTCPPort;
			outputs->UdpBroadcastPort = configNetOutputsUDPBroadcastPort;
			if (configNetOutputsWithLF==1) {
				outputs->FrameEnding = std::string("\r\n");
			}
			return (COutputs*)outputs;
		} break;
		case 0:
		default:
			return new CWinOutputs();
			break;
	}
}
