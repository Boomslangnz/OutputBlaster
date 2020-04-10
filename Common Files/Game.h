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

#pragma once
#include "../Output Files/WinOutputs.h"
#include "../Output Files/NetOutputs.h"
#include <Windows.h>

static GameOutput m_game;
static COutputs* Outputs;
static uintptr_t imageBase;
static MSG Msg1;

// From .ini
extern int configGameId;
extern int configOutputsSystem;
extern int configNetOutputsWithLF;
extern int configNetOutputsTCPPort;
extern int configNetOutputsUDPBroadcastPort;

static bool init = false;
static wchar_t* settingsFilename = TEXT(".\\OutputBlaster.ini");
static int SleepA = GetPrivateProfileInt(TEXT("Settings"), TEXT("Sleep"), 16, settingsFilename);

class Helpers {
public:
	int enableLogging = 0;
	// helper functions
	bool fileExists(char *filename);
	// logging
	void log(char *msg);
	void logInt(int value);
	void logInit(char *msg);
	// reading memory
	LPVOID GetTranslatedOffset(INT_PTR offset);
	int ReadInt32(INT_PTR offset, bool isRelativeOffset);
	UINT8 ReadByte(INT_PTR offset, bool isRelativeOffset);
	float WriteFloat32(INT_PTR offset, float val, bool isRelativeOffset);
	UINT8 WriteByte(INT_PTR offset, UINT8 val, bool isRelativeOffset);
	INT_PTR WriteIntPtr(INT_PTR offset, INT_PTR val, bool isRelativeOffset);
	UINT8 WriteNop(INT_PTR offset, bool isRelativeOffset);
	INT_PTR ReadIntPtr(INT_PTR offset, bool isRelativeOffset);
	float ReadFloat32(INT_PTR offset, bool isRelativeOffset);
};

extern Helpers* helpers;

class Game {
public:
	
	COutputs * CreateOutputsFromConfig();

	virtual void OutputsGameLoop();
};