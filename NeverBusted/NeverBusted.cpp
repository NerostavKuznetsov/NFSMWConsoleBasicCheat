#include "Includes.h"

void FunctionNeverBusted(HANDLE hProcess)
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::wcout << R"(
_____   __                            ________              _____     _________
___  | / /_______   ______________    ___  __ )___  __________  /___________  /
__   |/ /_  _ \_ | / /  _ \_  ___/    __  __  |  / / /_  ___/  __/  _ \  __  / 
_  /|  / /  __/_ |/ //  __/  /        _  /_/ // /_/ /_(__  )/ /_ /  __/ /_/ /  
/_/ |_/  \___/_____/ \___//_/         /_____/ \__,_/ /____/ \__/ \___/\__,_/   )";

	uintptr_t Address = 0x400000 + 0x43BB0;
	BYTE bytes_ON[] = { 0xEB, 0x39 };
	BYTE bytes_OFF[] = { 0x75, 0x39 };
	BYTE currentValue[2] = { 0 };

	if (!ReadProcessMemory(hProcess, (LPCVOID)Address, currentValue, sizeof(currentValue), nullptr))
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::wcout << L"\n\n[!] Failed to read memory at address!";
		Sleep(1666);
		return;
	}

	bool Status = currentValue[0] == bytes_OFF[0] && currentValue[1] == bytes_OFF[1];

	std::wcout << L"\n\n[!] Never Busted is " << (Status ? L"disabled\n" : L"enabled\n");
	std::wcout << L"[!] Press INSERT to enable/disable Never Busted or ESC to return to the main menu...\n";

	while (true)
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			if (Status)
			{
				WriteProcessMemory(hProcess, (LPVOID)Address, bytes_ON, sizeof(bytes_ON), nullptr);
				std::wcout << L"[!] Never Busted has been successfully enabled\n";
			}
			else
			{
				WriteProcessMemory(hProcess, (LPVOID)Address, bytes_OFF, sizeof(bytes_OFF), nullptr);
				std::wcout << L"[!] Never Busted has been successfully disabled\n";
			}
			Status = !Status;
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 1)
		{
			return;
		}
	}
}