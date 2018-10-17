// ChangeRefreshRate.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

DISPLAY_DEVICE GetPrimaryDevice()
{
	int index = 0;
	DISPLAY_DEVICE dd;
	dd.cb = sizeof(DISPLAY_DEVICE);

	while (EnumDisplayDevices(NULL, index++, &dd, 0))
	{
		if (dd.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) return dd;
	}
	return dd;
}

int main()
{
	DISPLAY_DEVICE dd = GetPrimaryDevice();
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(dm));
	dm.dmSize = sizeof(DEVMODE);
	if (!EnumDisplaySettings(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm))
	{
		printf("EnumDisplaySettings failed:%d\n", GetLastError());
		return FALSE;
	}
	cout << "Choose refresh rate: 60 or 144?" << endl;
	cout << "Write the number only and press [ENTER]." << endl;
	cout << "To close program without making changes, use the [Close] button." << endl;

	int userInput;
	int refreshRate60 = 60;
	int refreshRate144 = 144;

	cin >> userInput;

	if (userInput == refreshRate60)
	{
		dm.dmDisplayFrequency = refreshRate60;
	}
	else if (userInput == refreshRate144)
	{
		dm.dmDisplayFrequency = refreshRate144;
	}
	else
	{
		return false;
		system("exit");
	}

	dm.dmFields = (DM_DISPLAYFREQUENCY);
	if (ChangeDisplaySettings(&dm, CDS_TEST) != DISP_CHANGE_SUCCESSFUL)
	{
		printf("\nIllegal graphics mode: %d\n", GetLastError());
		return FALSE;
	}

	return (ChangeDisplaySettings(&dm, 0) == DISP_CHANGE_SUCCESSFUL);
}


