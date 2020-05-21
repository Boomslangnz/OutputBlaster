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
#include "Outputs.h"

const char *COutputs::s_outputNames[] =
{
	"pause",
	"LampStart",
	"LampView1",
	"LampView2",
	"LampView3",
	"LampView4",
	"LampLeader",
	"RawDrive",
	"RawLamps",
	"LampAction",
	"LampSelectUp",
	"LampSelectDown",
	"LampSelectLeft",
	"LampSelectRight",
	"LampHazard",
	"LampKey",
	"LampOnline",
	"LampOverrev",
	"LampRed",
	"LampGreen",
	"LampBlue",
	"LampYellow",
	"LampCyan",
	"LampMagneta",
	"LampWhite",
	"LampPatoButtonR",
	"LampPatoButtonB",
	"LampPato",
	"WooferLEDRed",
	"WooferLEDGreen",
	"WooferLEDBlue",
	"RearLEDRed",
	"RearLEDGreen",
	"RearLEDBlue",
	"SideLEDRed",
	"SideLEDGreen",
	"SideLEDBlue",
	"ItemLEDRed",
	"ItemLEDGreen",
	"ItemLEDBlue",
	"LampDriverLeft",
	"LampDriverRight",
	"1pKnock",
	"1pMotor",
	"2pKnock",
	"2pMotor",
	"2pLampStart",
	"VisualChange2D/3D",
	"1pAirFront",
	"1pAirRear",
	"2pAirFront",
	"2pAirRear",
	"LampInterruptionButton",
	"LampSide",
	"Vibration",
	"Power",
	"LEDRearCover",
	"PanelLamp",
	"SlotLamp1",
	"SlotLamp2",
	"SlotLamp3",
	"SeatLamp1",
	"SeatLamp2",
	"SeatLamp3",
	"SeatLamp4",
	"SeatLamp5",
	"SeatLamp6",
	"SeatLamp7",
	"Billboard Red",
	"Billboard Green",
	"Billboard Blue",
	"Billboard White",
	"Item Button",
	"Mario Button",
	"SideLEDWhite",
	"1pRecoil",
	"1pHolderLamp",
	"2pRecoil",
	"2pHolderLamp",
	"BillboardLamp",
	"Boost Lamp",
	"Boost Lamp Red",
	"Boost Lamp Green",
	"Boost Lamp Blue",
	"LampRed2",
	"LampGreen2",
	"LampBlue2",
	"FFB",
	"FFB1",
	"FFB2",
	"FFB3",
	"FFB4",
	"Ammo1pA",
	"Ammo1pB",
	"Ammo2pA",
	"Ammo2pB",
	"Flame1pBool",
	"Flame2pBool",
	"Health1pBool",
	"Health2pBool",
	"Shoot1p",
	"Shoot2p",
	"1p Controller Lamp",
	"2p Controller Lamp",
	"1p Brake Lamp",
	"2p Brake Lamp",
	"Emblem Lamp Red",
	"Emblem Lamp Green",
	"Emblem Lamp Blue",
	"Intake Left",
	"Intake Center",
	"Intake Right",
	"Base0 Left",
	"Base1 Left",
	"Base0 Right",
	"Base1 Right",
	"Seat Left",
	"Seat Right",
	"Infinity 1",
	"Infinity 2",
	"Infinity 3",
};

const char *COutputs::GetOutputName(EOutputs output)
{
	int idx = (int)output;
	if (idx < 0 || idx >= NUM_OUTPUTS)
		return NULL;
	return s_outputNames[idx];
}

EOutputs COutputs::GetOutputByName(const char *name)
{
	for (unsigned i = 0; i < NUM_OUTPUTS; i++)
	{
		if (_stricmp(name, s_outputNames[i]) == 0)
			return (EOutputs)i;
	}
	return OutputUnknown;
}

COutputs::COutputs()
{
	memset(m_first, true, sizeof(m_first));
	memset(m_values, 0, sizeof(m_values));
}

COutputs::~COutputs()
{
	//
}

const GameOutput &COutputs::GetGame() const
{
	return m_game;
}

void COutputs::SetGame(const GameOutput &game)
{
	m_game = game;
}

UINT8 COutputs::GetValue(EOutputs output) const
{
	int idx = (unsigned)output;
	if (idx < 0 || idx >= NUM_OUTPUTS)
		return 0;
	return m_values[idx];
}

void COutputs::SetValue(EOutputs output, UINT8 value)
{
	int idx = (unsigned)output;
	if (idx < 0 || idx >= NUM_OUTPUTS)
		return;
	bool firstSet = m_first[idx];
	UINT8 prevValue = m_values[idx];
	m_first[idx] = false;
	m_values[idx] = value;
	if (firstSet || value != prevValue)
		SendOutput(output, prevValue, value);
}

bool COutputs::HasValue(EOutputs output) 
{
	int idx = (unsigned)output;
	if (idx < 0 || idx >= NUM_OUTPUTS)
		return false;
	return !m_first[output]; 
}

