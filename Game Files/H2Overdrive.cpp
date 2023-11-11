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

static int Digit1;
static int Digit2;
static int Digit3;
static int Digit4;
static int PulseCount;
static int PulseCountSpeedo;
static int Speedo1Brightness;
static int Speedo2Brightness;
static int Speedo3Brightness;
static int Speedo4Brightness;
static int Speedo5Brightness;
static int Speedo6Brightness;
static int Speedo7Brightness;
static int Speedo8Brightness;
static int Speedo9Brightness;
static int Speedo10Brightness;
static int Speedo11Brightness;
static int Speedo12Brightness;
static int Speedo13Brightness;
static int Speedo14Brightness;
static int Speedo15Brightness;
static int Speedo16Brightness;
static int Speedo17Brightness;
static int Speedo18Brightness;
static int Speedo19Brightness;
static int Speedo20Brightness;
static int Speedo21Brightness;
static int Speedo22Brightness;
static int Speedo23Brightness;
static int Speedo24Brightness;
static int Boost1Brightness;
static int Boost2Brightness;
static int Boost3Brightness;
static int Boost4Brightness;
static int Boost5Brightness;
static int Boost6Brightness;
static int Boost7Brightness;
static int Boost8Brightness;
static int Boost9Brightness;
static int Boost10Brightness;
static int Boost11Brightness;
static int Boost12Brightness;
static int Boost13Brightness;
static int Boost14Brightness;
static int Boost15Brightness;
static int Boost16Brightness;
static int Boost17Brightness;
static int Boost18Brightness;
static int Boost19Brightness;
static int Boost20Brightness;
static int Boost21Brightness;
static int Boost22Brightness;
static int Boost23Brightness;
static int Boost24Brightness;
static char SpeedoChar[256];

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

	Outputs->SetValue(OutputIntakeLeft, IntakeLeft * (MaxScaleOutput * 1.0));
	Outputs->SetValue(OutputIntakeCenter, IntakeCenter * (MaxScaleOutput * 1.0));
	Outputs->SetValue(OutputIntakeRight, IntakeRight * (MaxScaleOutput * 1.0));
	Outputs->SetValue(OutputBase0Left, Base0Left * (MaxScaleOutput * 1.0));
	Outputs->SetValue(OutputBase1Left, Base1Left * (MaxScaleOutput * 1.0));
	Outputs->SetValue(OutputBase0Right, Base0Right * (MaxScaleOutput * 1.0));
	Outputs->SetValue(OutputBase1Right, Base1Right * (MaxScaleOutput * 1.0));
	Outputs->SetValue(OutputSeatLeft, SeatLeft * (MaxScaleOutput * 1.0));
	Outputs->SetValue(OutputSeatRight, SeatRight * (MaxScaleOutput * 1.0));
	Outputs->SetValue(OutputInfinity1, Infinity1 * (MaxScaleOutput * 1.0));
	Outputs->SetValue(OutputInfinity2, Infinity2 * (MaxScaleOutput * 1.0));
	Outputs->SetValue(OutputInfinity3, Infinity3 * (MaxScaleOutput * 1.0));
	Outputs->SetValue(OutputLampLeader, Leader * (MaxScaleOutput * 1.0));
	
	return 0;
}

static int SpeedoLoop()
{
	++PulseCount;

	if (PulseCount >= PulseRate / 16)
	{
		PulseCount = 0;

		UINT8 boost = helpers->ReadByte(0x74CB5C, false);
		UINT8 keypad = helpers->ReadByte(0x74CB60, false);
		UINT8 throttle1 = helpers->ReadByte(0x74CB64, false);
		UINT8 throttle2 = helpers->ReadByte(0x74CB68, false);
		UINT8 throttle3 = helpers->ReadByte(0x74CB6C, false);

		switch (boost)
		{
		case 0x00:
			Outputs->SetValue(OutputBoost, 1);
			break;
		case 0x01:
			Outputs->SetValue(OutputBoost, 0);
			break;
		case 0x02:
		case 0x03:
			if (Outputs->GetValue(OutputBoost))
				Outputs->SetValue(OutputBoost, 0);
			else
				Outputs->SetValue(OutputBoost, 1);
			break;
		}

		switch (keypad)
		{
		case 0x00:
			Outputs->SetValue(OutputKeypad, 1);
			break;
		case 0x01:
			Outputs->SetValue(OutputKeypad, 0);
			break;
		case 0x02:
		case 0x03:
			if (Outputs->GetValue(OutputKeypad))
				Outputs->SetValue(OutputKeypad, 0);
			else
				Outputs->SetValue(OutputKeypad, 1);
			break;
		}

		switch (throttle1)
		{
		case 0x00:
			Outputs->SetValue(OutputThrottle1, 1);
			break;
		case 0x01:
			Outputs->SetValue(OutputThrottle1, 0);
			break;
		case 0x02:
		case 0x03:
			if (Outputs->GetValue(OutputThrottle1))
				Outputs->SetValue(OutputThrottle1, 0);
			else
				Outputs->SetValue(OutputThrottle1, 1);
			break;
		}

		switch (throttle2)
		{
		case 0x00:
			Outputs->SetValue(OutputThrottle2, 1);
			break;
		case 0x01:
			Outputs->SetValue(OutputThrottle2, 0);
			break;
		case 0x02:
		case 0x03:
			if (Outputs->GetValue(OutputThrottle2))
				Outputs->SetValue(OutputThrottle2, 0);
			else
				Outputs->SetValue(OutputThrottle2, 1);
			break;
		}

		switch (throttle3)
		{
		case 0x00:
			Outputs->SetValue(OutputThrottle3, 1);
			break;
		case 0x01:
			Outputs->SetValue(OutputThrottle3, 0);
			break;
		case 0x02:
		case 0x03:
			if (Outputs->GetValue(OutputThrottle3))
				Outputs->SetValue(OutputThrottle3, 0);
			else
				Outputs->SetValue(OutputThrottle3, 1);
			break;
		}
	}

	UINT8 digit1speedoA = helpers->ReadByte(0x78C4DC, false);
	UINT8 digit1speedoB = helpers->ReadByte(0x78C4DD, false);
	UINT8 digit1speedoC = helpers->ReadByte(0x78C4DE, false);
	UINT8 digit1speedoD = helpers->ReadByte(0x78C4DF, false);
	UINT8 digit1speedoE = helpers->ReadByte(0x78C4E0, false);
	UINT8 digit1speedoF = helpers->ReadByte(0x78C4E1, false);
	UINT8 digit1speedoG = helpers->ReadByte(0x78C4E2, false);

	UINT8 digit2speedoA = helpers->ReadByte(0x78C4E4, false);
	UINT8 digit2speedoB = helpers->ReadByte(0x78C4E5, false);
	UINT8 digit2speedoC = helpers->ReadByte(0x78C4E6, false);
	UINT8 digit2speedoD = helpers->ReadByte(0x78C4E7, false);
	UINT8 digit2speedoE = helpers->ReadByte(0x78C4E8, false);
	UINT8 digit2speedoF = helpers->ReadByte(0x78C4E9, false);
	UINT8 digit2speedoG = helpers->ReadByte(0x78C4EA, false);

	UINT8 digit3speedoA = helpers->ReadByte(0x78C4EC, false);
	UINT8 digit3speedoB = helpers->ReadByte(0x78C4ED, false);
	UINT8 digit3speedoC = helpers->ReadByte(0x78C4EE, false);
	UINT8 digit3speedoD = helpers->ReadByte(0x78C4EF, false);
	UINT8 digit3speedoE = helpers->ReadByte(0x78C4F0, false);
	UINT8 digit3speedoF = helpers->ReadByte(0x78C4F1, false);
	UINT8 digit3speedoG = helpers->ReadByte(0x78C4F2, false);

	UINT8 digit4speedoA = helpers->ReadByte(0x78C4F4, false);
	UINT8 digit4speedoB = helpers->ReadByte(0x78C4F5, false);
	UINT8 digit4speedoC = helpers->ReadByte(0x78C4F6, false);
	UINT8 digit4speedoD = helpers->ReadByte(0x78C4F7, false);
	UINT8 digit4speedoE = helpers->ReadByte(0x78C4F8, false);
	UINT8 digit4speedoF = helpers->ReadByte(0x78C4F9, false);
	UINT8 digit4speedoG = helpers->ReadByte(0x78C4FA, false);

	UINT8 speedometerled1 = helpers->ReadByte(0x78C4FC, false);
	UINT8 speedometerled2 = helpers->ReadByte(0x78C4FD, false);
	UINT8 speedometerled3 = helpers->ReadByte(0x78C4FE, false);
	UINT8 speedometerled4 = helpers->ReadByte(0x78C4FF, false);
	UINT8 speedometerled5 = helpers->ReadByte(0x78C500, false);
	UINT8 speedometerled6 = helpers->ReadByte(0x78C501, false);
	UINT8 speedometerled7 = helpers->ReadByte(0x78C502, false);
	UINT8 speedometerled8 = helpers->ReadByte(0x78C503, false);
	UINT8 speedometerled9 = helpers->ReadByte(0x78C504, false);
	UINT8 speedometerled10 = helpers->ReadByte(0x78C505, false);
	UINT8 speedometerled11 = helpers->ReadByte(0x78C506, false);
	UINT8 speedometerled12 = helpers->ReadByte(0x78C507, false);
	UINT8 speedometerled13 = helpers->ReadByte(0x78C508, false);
	UINT8 speedometerled14 = helpers->ReadByte(0x78C509, false);
	UINT8 speedometerled15 = helpers->ReadByte(0x78C50A, false);
	UINT8 speedometerled16 = helpers->ReadByte(0x78C50B, false);
	UINT8 speedometerled17 = helpers->ReadByte(0x78C50C, false);
	UINT8 speedometerled18 = helpers->ReadByte(0x78C50D, false);
	UINT8 speedometerled19 = helpers->ReadByte(0x78C50E, false);
	UINT8 speedometerled20 = helpers->ReadByte(0x78C50F, false);
	UINT8 speedometerled21 = helpers->ReadByte(0x78C510, false);
	UINT8 speedometerled22 = helpers->ReadByte(0x78C511, false);
	UINT8 speedometerled23 = helpers->ReadByte(0x78C512, false);
	UINT8 speedometerled24 = helpers->ReadByte(0x78C513, false);

	UINT8 boostmeterled1 = helpers->ReadByte(0x78C514, false);
	UINT8 boostmeterled2 = helpers->ReadByte(0x78C515, false);
	UINT8 boostmeterled3 = helpers->ReadByte(0x78C516, false);
	UINT8 boostmeterled4 = helpers->ReadByte(0x78C517, false);
	UINT8 boostmeterled5 = helpers->ReadByte(0x78C518, false);
	UINT8 boostmeterled6 = helpers->ReadByte(0x78C519, false);
	UINT8 boostmeterled7 = helpers->ReadByte(0x78C51A, false);
	UINT8 boostmeterled8 = helpers->ReadByte(0x78C51B, false);
	UINT8 boostmeterled9 = helpers->ReadByte(0x78C51C, false);
	UINT8 boostmeterled10 = helpers->ReadByte(0x78C51D, false);
	UINT8 boostmeterled11 = helpers->ReadByte(0x78C51E, false);
	UINT8 boostmeterled12 = helpers->ReadByte(0x78C51F, false);
	UINT8 boostmeterled13 = helpers->ReadByte(0x78C520, false);
	UINT8 boostmeterled14 = helpers->ReadByte(0x78C521, false);
	UINT8 boostmeterled15 = helpers->ReadByte(0x78C522, false);
	UINT8 boostmeterled16 = helpers->ReadByte(0x78C523, false);
	UINT8 boostmeterled17 = helpers->ReadByte(0x78C524, false);
	UINT8 boostmeterled18 = helpers->ReadByte(0x78C525, false);
	UINT8 boostmeterled19 = helpers->ReadByte(0x78C526, false);
	UINT8 boostmeterled20 = helpers->ReadByte(0x78C527, false);
	UINT8 boostmeterled21 = helpers->ReadByte(0x78C528, false);
	UINT8 boostmeterled22 = helpers->ReadByte(0x78C529, false);
	UINT8 boostmeterled23 = helpers->ReadByte(0x78C52A, false);
	UINT8 boostmeterled24 = helpers->ReadByte(0x78C52B, false);

	if (!digit1speedoA && !digit1speedoB && !digit1speedoC && !digit1speedoD && !digit1speedoE && !digit1speedoF && !digit1speedoG)
		Digit1 = 0;
	else if (digit1speedoA && digit1speedoB && digit1speedoC && digit1speedoD && digit1speedoE && digit1speedoF && !digit1speedoG)
		Digit1 = 0;
	else if (!digit1speedoA && digit1speedoB && digit1speedoC && !digit1speedoD && !digit1speedoE && !digit1speedoF && !digit1speedoG)
		Digit1 = 1;
	else if (digit1speedoA && digit1speedoB && !digit1speedoC && digit1speedoD && digit1speedoE && !digit1speedoF && digit1speedoG)
		Digit1 = 2;
	else if (digit1speedoA && digit1speedoB && digit1speedoC && digit1speedoD && !digit1speedoE && !digit1speedoF && digit1speedoG)
		Digit1 = 3;
	else if (!digit1speedoA && digit1speedoB && digit1speedoC && !digit1speedoD && !digit1speedoE && digit1speedoF && digit1speedoG)
		Digit1 = 4;
	else if (digit1speedoA && !digit1speedoB && digit1speedoC && digit1speedoD && !digit1speedoE && digit1speedoF && digit1speedoG)
		Digit1 = 5;
	else if (digit1speedoA && !digit1speedoB && digit1speedoC && digit1speedoD && digit1speedoE && digit1speedoF && digit1speedoG)
		Digit1 = 6;
	else if (digit1speedoA && digit1speedoB && digit1speedoC && !digit1speedoD && !digit1speedoE && !digit1speedoF && !digit1speedoG)
		Digit1 = 7;
	else if (digit1speedoA && digit1speedoB && digit1speedoC && digit1speedoD && digit1speedoE && digit1speedoF && digit1speedoG)
		Digit1 = 8;
	else if (digit1speedoA && digit1speedoB && digit1speedoC && digit1speedoD && !digit1speedoE && digit1speedoF && digit1speedoG)
		Digit1 = 9;
	else if (!digit1speedoA && digit1speedoB && digit1speedoC && !digit1speedoD && digit1speedoE && digit1speedoF && digit1speedoG)
		Digit1 = 0x48; // H
	else if (digit1speedoA && !digit1speedoB && !digit1speedoC && !digit1speedoD && digit1speedoE && digit1speedoF && digit1speedoG)
		Digit1 = 0x46; // F
	else if (!digit1speedoA && digit1speedoB && digit1speedoC && digit1speedoD && digit1speedoE && digit1speedoF && !digit1speedoG)
		Digit1 = 0x55; // U
	else if (!digit1speedoA && !digit1speedoB && digit1speedoC && !digit1speedoD && digit1speedoE && !digit1speedoF && digit1speedoG)
		Digit1 = 0x4E; // n
	else if (!digit1speedoA && !digit1speedoB && !digit1speedoC && !digit1speedoD && digit1speedoE && !digit1speedoF && digit1speedoG)
		Digit1 = 0x52; // r
	else if (digit1speedoA && digit1speedoB && digit1speedoC && !digit1speedoD && digit1speedoE && digit1speedoF && digit1speedoG)
		Digit1 = 0x41; // A
	else if (digit1speedoA && !digit1speedoB && !digit1speedoC && digit1speedoD && digit1speedoE && digit1speedoF && !digit1speedoG)
		Digit1 = 0x43; // C
	else if (digit1speedoA && !digit1speedoB && !digit1speedoC && digit1speedoD && digit1speedoE && digit1speedoF && digit1speedoG)
		Digit1 = 0x45; // E
	else if (!digit1speedoA && digit1speedoB && digit1speedoC && digit1speedoD && !digit1speedoE && digit1speedoF && digit1speedoG)
		Digit1 = 0x59; // Y
	else if (digit1speedoA && digit1speedoB && !digit1speedoC && !digit1speedoD && digit1speedoE && digit1speedoF && digit1speedoG)
		Digit1 = 0x50; // P
	else if (!digit1speedoA && !digit1speedoB && !digit1speedoC && digit1speedoD && digit1speedoE && digit1speedoF && !digit1speedoG)
		Digit1 = 0x4C; // L
	else if (!digit1speedoA && !digit1speedoB && digit1speedoC && digit1speedoD && digit1speedoE && digit1speedoF && digit1speedoG)
		Digit1 = 0x42; // b
	else if (!digit1speedoA && !digit1speedoB && digit1speedoC && digit1speedoD && digit1speedoE && !digit1speedoF && digit1speedoG)
		Digit1 = 0x4F; // o
	else if (!digit1speedoA && !digit1speedoB && !digit1speedoC && digit1speedoD && digit1speedoE && digit1speedoF && digit1speedoG)
		Digit1 = 0x54; // t
	

	if (!digit2speedoA && !digit2speedoB && !digit2speedoC && !digit2speedoD && !digit2speedoE && !digit2speedoF && !digit2speedoG)
		Digit2 = 0;
	else if (digit2speedoA && digit2speedoB && digit2speedoC && digit2speedoD && digit2speedoE && digit2speedoF && !digit2speedoG)
		Digit2 = 0;
	else if (!digit2speedoA && digit2speedoB && digit2speedoC && !digit2speedoD && !digit2speedoE && !digit2speedoF && !digit2speedoG)
		Digit2 = 1;
	else if (digit2speedoA && digit2speedoB && !digit2speedoC && digit2speedoD && digit2speedoE && !digit2speedoF && digit2speedoG)
		Digit2 = 2;
	else if (digit2speedoA && digit2speedoB && digit2speedoC && digit2speedoD && !digit2speedoE && !digit2speedoF && digit2speedoG)
		Digit2 = 3;
	else if (!digit2speedoA && digit2speedoB && digit2speedoC && !digit2speedoD && !digit2speedoE && digit2speedoF && digit2speedoG)
		Digit2 = 4;
	else if (digit2speedoA && !digit2speedoB && digit2speedoC && digit2speedoD && !digit2speedoE && digit2speedoF && digit2speedoG)
		Digit2 = 5;
	else if (digit2speedoA && !digit2speedoB && digit2speedoC && digit2speedoD && digit2speedoE && digit2speedoF && digit2speedoG)
		Digit2 = 6;
	else if (digit2speedoA && digit2speedoB && digit2speedoC && !digit2speedoD && !digit2speedoE && !digit2speedoF && !digit2speedoG)
		Digit2 = 7;
	else if (digit2speedoA && digit2speedoB && digit2speedoC && digit2speedoD && digit2speedoE && digit2speedoF && digit2speedoG)
		Digit2 = 8;
	else if (digit2speedoA && digit2speedoB && digit2speedoC && digit2speedoD && !digit2speedoE && digit2speedoF && digit2speedoG)
		Digit2 = 9;
	else if (!digit2speedoA && digit2speedoB && digit2speedoC && !digit2speedoD && digit2speedoE && digit2speedoF && digit2speedoG)
		Digit2 = 0x48; // H
	else if (digit2speedoA && !digit2speedoB && !digit2speedoC && !digit2speedoD && digit2speedoE && digit2speedoF && digit2speedoG)
		Digit2 = 0x46; // F
	else if (!digit2speedoA && digit2speedoB && digit2speedoC && digit2speedoD && digit2speedoE && digit2speedoF && !digit2speedoG)
		Digit2 = 0x55; // U
	else if (!digit2speedoA && !digit2speedoB && digit2speedoC && !digit2speedoD && digit2speedoE && !digit2speedoF && digit2speedoG)
		Digit2 = 0x4E; // n
	else if (!digit2speedoA && !digit2speedoB && !digit2speedoC && !digit2speedoD && digit2speedoE && !digit2speedoF && digit2speedoG)
		Digit2 = 0x52; // r
	else if (digit2speedoA && digit2speedoB && digit2speedoC && !digit2speedoD && digit2speedoE && digit2speedoF && digit2speedoG)
		Digit2 = 0x41; // A
	else if (digit2speedoA && !digit2speedoB && !digit2speedoC && digit2speedoD && digit2speedoE && digit2speedoF && !digit2speedoG)
		Digit2 = 0x43; // C
	else if (digit2speedoA && !digit2speedoB && !digit2speedoC && digit2speedoD && digit2speedoE && digit2speedoF && digit2speedoG)
		Digit2 = 0x45; // E
	else if (!digit2speedoA && digit2speedoB && digit2speedoC && digit2speedoD && !digit2speedoE && digit2speedoF && digit2speedoG)
		Digit2 = 0x59; // Y
	else if (digit2speedoA && digit2speedoB && !digit2speedoC && !digit2speedoD && digit2speedoE && digit2speedoF && digit2speedoG)
		Digit2 = 0x50; // P
	else if (!digit2speedoA && !digit2speedoB && !digit2speedoC && digit2speedoD && digit2speedoE && digit2speedoF && !digit2speedoG)
		Digit2 = 0x4C; // L
	else if (!digit2speedoA && !digit2speedoB && digit2speedoC && digit2speedoD && digit2speedoE && digit2speedoF && digit2speedoG)
		Digit2 = 0x42; // b
	else if (!digit2speedoA && !digit2speedoB && digit2speedoC && digit2speedoD && digit2speedoE && !digit2speedoF && digit2speedoG)
		Digit2 = 0x4F; // o
	else if (!digit2speedoA && !digit2speedoB && !digit2speedoC && digit2speedoD && digit2speedoE && digit2speedoF && digit2speedoG)
		Digit2 = 0x54; // t

	if (!digit3speedoA && !digit3speedoB && !digit3speedoC && !digit3speedoD && !digit3speedoE && !digit3speedoF && !digit3speedoG)
		Digit3 = 0;
	else if (digit3speedoA && digit3speedoB && digit3speedoC && digit3speedoD && digit3speedoE && digit3speedoF && !digit3speedoG)
		Digit3 = 0;
	else if (!digit3speedoA && digit3speedoB && digit3speedoC && !digit3speedoD && !digit3speedoE && !digit3speedoF && !digit3speedoG)
		Digit3 = 1;
	else if (digit3speedoA && digit3speedoB && !digit3speedoC && digit3speedoD && digit3speedoE && !digit3speedoF && digit3speedoG)
		Digit3 = 2;
	else if (digit3speedoA && digit3speedoB && digit3speedoC && digit3speedoD && !digit3speedoE && !digit3speedoF && digit3speedoG)
		Digit3 = 3;
	else if (!digit3speedoA && digit3speedoB && digit3speedoC && !digit3speedoD && !digit3speedoE && digit3speedoF && digit3speedoG)
		Digit3 = 4;
	else if (digit3speedoA && !digit3speedoB && digit3speedoC && digit3speedoD && !digit3speedoE && digit3speedoF && digit3speedoG)
		Digit3 = 5;
	else if (digit3speedoA && !digit3speedoB && digit3speedoC && digit3speedoD && digit3speedoE && digit3speedoF && digit3speedoG)
		Digit3 = 6;
	else if (digit3speedoA && digit3speedoB && digit3speedoC && !digit3speedoD && !digit3speedoE && !digit3speedoF && !digit3speedoG)
		Digit3 = 7;
	else if (digit3speedoA && digit3speedoB && digit3speedoC && digit3speedoD && digit3speedoE && digit3speedoF && digit3speedoG)
		Digit3 = 8;
	else if (digit3speedoA && digit3speedoB && digit3speedoC && digit3speedoD && !digit3speedoE && digit3speedoF && digit3speedoG)
		Digit3 = 9;
	else if (!digit3speedoA && digit3speedoB && digit3speedoC && !digit3speedoD && digit3speedoE && digit3speedoF && digit3speedoG)
		Digit3 = 0x48; // H
	else if (digit3speedoA && !digit3speedoB && !digit3speedoC && !digit3speedoD && digit3speedoE && digit3speedoF && digit3speedoG)
		Digit3 = 0x46; // F
	else if (!digit3speedoA && digit3speedoB && digit3speedoC && digit3speedoD && digit3speedoE && digit3speedoF && !digit3speedoG)
		Digit3 = 0x55; // U
	else if (!digit3speedoA && !digit3speedoB && digit3speedoC && !digit3speedoD && digit3speedoE && !digit3speedoF && digit3speedoG)
		Digit3 = 0x4E; // n
	else if (!digit3speedoA && !digit3speedoB && !digit3speedoC && !digit3speedoD && digit3speedoE && !digit3speedoF && digit3speedoG)
		Digit3 = 0x52; // r
	else if (digit3speedoA && digit3speedoB && digit3speedoC && !digit3speedoD && digit3speedoE && digit3speedoF && digit3speedoG)
		Digit3 = 0x41; // A
	else if (digit3speedoA && !digit3speedoB && !digit3speedoC && digit3speedoD && digit3speedoE && digit3speedoF && !digit3speedoG)
		Digit3 = 0x43; // C
	else if (digit3speedoA && !digit3speedoB && !digit3speedoC && digit3speedoD && digit3speedoE && digit3speedoF && digit3speedoG)
		Digit3 = 0x45; // E
	else if (!digit3speedoA && digit3speedoB && digit3speedoC && digit3speedoD && !digit3speedoE && digit3speedoF && digit3speedoG)
		Digit3 = 0x59; // Y
	else if (digit3speedoA && digit3speedoB && !digit3speedoC && !digit3speedoD && digit3speedoE && digit3speedoF && digit3speedoG)
		Digit3 = 0x50; // P
	else if (!digit3speedoA && !digit3speedoB && !digit3speedoC && digit3speedoD && digit3speedoE && digit3speedoF && !digit3speedoG)
		Digit3 = 0x4C; // L
	else if (!digit3speedoA && !digit3speedoB && digit3speedoC && digit3speedoD && digit3speedoE && digit3speedoF && digit3speedoG)
		Digit3 = 0x42; // b
	else if (!digit3speedoA && !digit3speedoB && digit3speedoC && digit3speedoD && digit3speedoE && !digit3speedoF && digit3speedoG)
		Digit3 = 0x4F; // o
	else if (!digit3speedoA && !digit3speedoB && !digit3speedoC && digit3speedoD && digit3speedoE && digit3speedoF && digit3speedoG)
		Digit3 = 0x54; // t

	if (!digit4speedoA && !digit4speedoB && !digit4speedoC && !digit4speedoD && !digit4speedoE && !digit4speedoF && !digit4speedoG)
		Digit4 = 0;
	else if (digit4speedoA && digit4speedoB && digit4speedoC && digit4speedoD && digit4speedoE && digit4speedoF && !digit4speedoG)
		Digit4 = 0;
	else if (!digit4speedoA && digit4speedoB && digit4speedoC && !digit4speedoD && !digit4speedoE && !digit4speedoF && !digit4speedoG)
		Digit4 = 1;
	else if (digit4speedoA && digit4speedoB && !digit4speedoC && digit4speedoD && digit4speedoE && !digit4speedoF && digit4speedoG)
		Digit4 = 2;
	else if (digit4speedoA && digit4speedoB && digit4speedoC && digit4speedoD && !digit4speedoE && !digit4speedoF && digit4speedoG)
		Digit4 = 3;
	else if (!digit4speedoA && digit4speedoB && digit4speedoC && !digit4speedoD && !digit4speedoE && digit4speedoF && digit4speedoG)
		Digit4 = 4;
	else if (digit4speedoA && !digit4speedoB && digit4speedoC && digit4speedoD && !digit4speedoE && digit4speedoF && digit4speedoG)
		Digit4 = 5;
	else if (digit4speedoA && !digit4speedoB && digit4speedoC && digit4speedoD && digit4speedoE && digit4speedoF && digit4speedoG)
		Digit4 = 6;
	else if (digit4speedoA && digit4speedoB && digit4speedoC && !digit4speedoD && !digit4speedoE && !digit4speedoF && !digit4speedoG)
		Digit4 = 7;
	else if (digit4speedoA && digit4speedoB && digit4speedoC && digit4speedoD && digit4speedoE && digit4speedoF && digit4speedoG)
		Digit4 = 8;
	else if (digit4speedoA && digit4speedoB && digit4speedoC && digit4speedoD && !digit4speedoE && digit4speedoF && digit4speedoG)
		Digit4 = 9;
	else if (!digit4speedoA && digit4speedoB && digit4speedoC && !digit4speedoD && digit4speedoE && digit4speedoF && digit4speedoG)
		Digit4 = 0x48; // H
	else if (digit4speedoA && !digit4speedoB && !digit4speedoC && !digit4speedoD && digit4speedoE && digit4speedoF && digit4speedoG)
		Digit4 = 0x46; // F
	else if (!digit4speedoA && digit4speedoB && digit4speedoC && digit4speedoD && digit4speedoE && digit4speedoF && !digit4speedoG)
		Digit4 = 0x55; // U
	else if (!digit4speedoA && !digit4speedoB && digit4speedoC && !digit4speedoD && digit4speedoE && !digit4speedoF && digit4speedoG)
		Digit4 = 0x4E; // n
	else if (!digit4speedoA && !digit4speedoB && !digit4speedoC && !digit4speedoD && digit4speedoE && !digit4speedoF && digit4speedoG)
		Digit4 = 0x52; // r
	else if (digit4speedoA && digit4speedoB && digit4speedoC && !digit4speedoD && digit4speedoE && digit4speedoF && digit4speedoG)
		Digit4 = 0x41; // A
	else if (digit4speedoA && !digit4speedoB && !digit4speedoC && digit4speedoD && digit4speedoE && digit4speedoF && !digit4speedoG)
		Digit4 = 0x43; // C
	else if (digit4speedoA && !digit4speedoB && !digit4speedoC && digit4speedoD && digit4speedoE && digit4speedoF && digit4speedoG)
		Digit4 = 0x45; // E
	else if (!digit4speedoA && digit4speedoB && digit4speedoC && digit4speedoD && !digit4speedoE && digit4speedoF && digit4speedoG)
		Digit4 = 0x59; // Y
	else if (digit4speedoA && digit4speedoB && !digit4speedoC && !digit4speedoD && digit4speedoE && digit4speedoF && digit4speedoG)
		Digit4 = 0x50; // P
	else if (!digit4speedoA && !digit4speedoB && !digit4speedoC && digit4speedoD && digit4speedoE && digit4speedoF && !digit4speedoG)
		Digit4 = 0x4C; // L
	else if (!digit4speedoA && !digit4speedoB && digit4speedoC && digit4speedoD && digit4speedoE && digit4speedoF && digit4speedoG)
		Digit4 = 0x42; // b
	else if (!digit4speedoA && !digit4speedoB && digit4speedoC && digit4speedoD && digit4speedoE && !digit4speedoF && digit4speedoG)
		Digit4 = 0x4F; // o
	else if (!digit4speedoA && !digit4speedoB && !digit4speedoC && digit4speedoD && digit4speedoE && digit4speedoF && digit4speedoG)
		Digit4 = 0x54; // t

	sprintf(SpeedoChar, "%d%d%d.%d", Digit1, Digit2, Digit3, Digit4);

	int SpeedoInt = atoi(SpeedoChar);

	if ((!Digit1 && !Digit2 && !Digit3 && !Digit4) || (Digit1 > 10 || Digit2 > 10 || Digit3 > 10 || Digit4 > 10))
		SpeedoInt = 0;

	Speedo1Brightness = speedometerled1 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo2Brightness = speedometerled2 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo3Brightness = speedometerled3 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo4Brightness = speedometerled4 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo5Brightness = speedometerled5 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo6Brightness = speedometerled6 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo7Brightness = speedometerled7 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo8Brightness = speedometerled8 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo9Brightness = speedometerled9 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo10Brightness = speedometerled10 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo11Brightness = speedometerled11 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo12Brightness = speedometerled12 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo13Brightness = speedometerled13 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo14Brightness = speedometerled14 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo15Brightness = speedometerled15 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo16Brightness = speedometerled16 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo17Brightness = speedometerled17 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo18Brightness = speedometerled18 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo19Brightness = speedometerled19 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo20Brightness = speedometerled20 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo21Brightness = speedometerled21 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo22Brightness = speedometerled22 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo23Brightness = speedometerled23 / 10.0 * (MaxScaleOutput * 1.0);
	Speedo24Brightness = speedometerled24 / 10.0 * (MaxScaleOutput * 1.0);

	Boost1Brightness = boostmeterled1 / 10.0 * (MaxScaleOutput * 1.0);
	Boost2Brightness = boostmeterled2 / 10.0 * (MaxScaleOutput * 1.0);
	Boost3Brightness = boostmeterled3 / 10.0 * (MaxScaleOutput * 1.0);
	Boost4Brightness = boostmeterled4 / 10.0 * (MaxScaleOutput * 1.0);
	Boost5Brightness = boostmeterled5 / 10.0 * (MaxScaleOutput * 1.0);
	Boost6Brightness = boostmeterled6 / 10.0 * (MaxScaleOutput * 1.0);
	Boost7Brightness = boostmeterled7 / 10.0 * (MaxScaleOutput * 1.0);
	Boost8Brightness = boostmeterled8 / 10.0 * (MaxScaleOutput * 1.0);
	Boost9Brightness = boostmeterled9 / 10.0 * (MaxScaleOutput * 1.0);
	Boost10Brightness = boostmeterled10 / 10.0 * (MaxScaleOutput * 1.0);
	Boost11Brightness = boostmeterled11 / 10.0 * (MaxScaleOutput * 1.0);
	Boost12Brightness = boostmeterled12 / 10.0 * (MaxScaleOutput * 1.0);
	Boost13Brightness = boostmeterled13 / 10.0 * (MaxScaleOutput * 1.0);
	Boost14Brightness = boostmeterled14 / 10.0 * (MaxScaleOutput * 1.0);
	Boost15Brightness = boostmeterled15 / 10.0 * (MaxScaleOutput * 1.0);
	Boost16Brightness = boostmeterled16 / 10.0 * (MaxScaleOutput * 1.0);
	Boost17Brightness = boostmeterled17 / 10.0 * (MaxScaleOutput * 1.0);
	Boost18Brightness = boostmeterled18 / 10.0 * (MaxScaleOutput * 1.0);
	Boost19Brightness = boostmeterled19 / 10.0 * (MaxScaleOutput * 1.0);
	Boost20Brightness = boostmeterled20 / 10.0 * (MaxScaleOutput * 1.0);
	Boost21Brightness = boostmeterled21 / 10.0 * (MaxScaleOutput * 1.0);
	Boost22Brightness = boostmeterled22 / 10.0 * (MaxScaleOutput * 1.0);
	Boost23Brightness = boostmeterled23 / 10.0 * (MaxScaleOutput * 1.0);
	Boost24Brightness = boostmeterled24 / 10.0 * (MaxScaleOutput * 1.0);

	++PulseCountSpeedo;

	if (PulseCountSpeedo >= SleepA / 16)
	{
		PulseCountSpeedo = 0;

		Outputs->SetValue(OutputDigit1Speedo, Digit1);
		Outputs->SetValue(OutputDigit2Speedo, Digit2);
		Outputs->SetValue(OutputDigit3Speedo, Digit3);
		Outputs->SetValue(OutputDigit4Speedo, Digit4);
		Outputs->SetValue(OutputSpeedo, SpeedoInt);
		Outputs->SetValue(OutputSpeedo1Brightness, Speedo1Brightness);
		Outputs->SetValue(OutputSpeedo2Brightness, Speedo2Brightness);
		Outputs->SetValue(OutputSpeedo3Brightness, Speedo3Brightness);
		Outputs->SetValue(OutputSpeedo4Brightness, Speedo4Brightness);
		Outputs->SetValue(OutputSpeedo5Brightness, Speedo5Brightness);
		Outputs->SetValue(OutputSpeedo6Brightness, Speedo6Brightness);
		Outputs->SetValue(OutputSpeedo7Brightness, Speedo7Brightness);
		Outputs->SetValue(OutputSpeedo8Brightness, Speedo8Brightness);
		Outputs->SetValue(OutputSpeedo9Brightness, Speedo9Brightness);
		Outputs->SetValue(OutputSpeedo10Brightness, Speedo10Brightness);
		Outputs->SetValue(OutputSpeedo11Brightness, Speedo11Brightness);
		Outputs->SetValue(OutputSpeedo12Brightness, Speedo12Brightness);
		Outputs->SetValue(OutputSpeedo13Brightness, Speedo13Brightness);
		Outputs->SetValue(OutputSpeedo14Brightness, Speedo14Brightness);
		Outputs->SetValue(OutputSpeedo15Brightness, Speedo15Brightness);
		Outputs->SetValue(OutputSpeedo16Brightness, Speedo16Brightness);
		Outputs->SetValue(OutputSpeedo17Brightness, Speedo17Brightness);
		Outputs->SetValue(OutputSpeedo18Brightness, Speedo18Brightness);
		Outputs->SetValue(OutputSpeedo19Brightness, Speedo19Brightness);
		Outputs->SetValue(OutputSpeedo20Brightness, Speedo20Brightness);
		Outputs->SetValue(OutputSpeedo21Brightness, Speedo21Brightness);
		Outputs->SetValue(OutputSpeedo22Brightness, Speedo22Brightness);
		Outputs->SetValue(OutputSpeedo23Brightness, Speedo23Brightness);
		Outputs->SetValue(OutputSpeedo24Brightness, Speedo24Brightness);
		Outputs->SetValue(OutputBoost1Brightness, Boost1Brightness);
		Outputs->SetValue(OutputBoost2Brightness, Boost2Brightness);
		Outputs->SetValue(OutputBoost3Brightness, Boost3Brightness);
		Outputs->SetValue(OutputBoost4Brightness, Boost4Brightness);
		Outputs->SetValue(OutputBoost5Brightness, Boost5Brightness);
		Outputs->SetValue(OutputBoost6Brightness, Boost6Brightness);
		Outputs->SetValue(OutputBoost7Brightness, Boost7Brightness);
		Outputs->SetValue(OutputBoost8Brightness, Boost8Brightness);
		Outputs->SetValue(OutputBoost9Brightness, Boost9Brightness);
		Outputs->SetValue(OutputBoost10Brightness, Boost10Brightness);
		Outputs->SetValue(OutputBoost11Brightness, Boost11Brightness);
		Outputs->SetValue(OutputBoost12Brightness, Boost12Brightness);
		Outputs->SetValue(OutputBoost13Brightness, Boost13Brightness);
		Outputs->SetValue(OutputBoost14Brightness, Boost14Brightness);
		Outputs->SetValue(OutputBoost15Brightness, Boost15Brightness);
		Outputs->SetValue(OutputBoost16Brightness, Boost16Brightness);
		Outputs->SetValue(OutputBoost17Brightness, Boost17Brightness);
		Outputs->SetValue(OutputBoost18Brightness, Boost18Brightness);
		Outputs->SetValue(OutputBoost19Brightness, Boost19Brightness);
		Outputs->SetValue(OutputBoost20Brightness, Boost20Brightness);
		Outputs->SetValue(OutputBoost21Brightness, Boost21Brightness);
		Outputs->SetValue(OutputBoost22Brightness, Boost22Brightness);
		Outputs->SetValue(OutputBoost23Brightness, Boost23Brightness);
		Outputs->SetValue(OutputBoost24Brightness, Boost24Brightness);
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

static DWORD WINAPI OutputsAreGo2(LPVOID lpParam)
{
	while (true)
	{
		SpeedoLoop();
		Sleep(16);
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
		CreateThread(NULL, 0, OutputsAreGo2, NULL, 0, NULL);
		while (GetMessage(&Msg1, NULL, NULL, 0))
		{
			TranslateMessage(&Msg1);
			DispatchMessage(&Msg1);
		}
		init = true;
	}
}