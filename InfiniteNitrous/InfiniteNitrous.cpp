#include "includes.h"

void FunctionInfiniteNitrous(HANDLE hProcess)
{
	system("cls");
	std::wcout << R"(
________      ____________       __________           _____   ___________                            
____  _/_________  __/__(_)_________(_)_  /_____      ___  | / /__(_)_  /_________________  _________
 __  / __  __ \_  /_ __  /__  __ \_  /_  __/  _ \     __   |/ /__  /_  __/_  ___/  __ \  / / /_  ___/
__/ /  _  / / /  __/ _  / _  / / /  / / /_ /  __/     _  /|  / _  / / /_ _  /   / /_/ / /_/ /_(__  ) 
/___/  /_/ /_//_/    /_/  /_/ /_//_/  \__/ \___/      /_/ |_/  /_/  \__/ /_/    \____/\__,_/ /____/   )";

	uintptr_t Instruction_Address = 0x00692B01;
	BYTE Original_Bytes[] = { 0xD8, 0x64, 0x24, 0x2C };
	BYTE NOP_Bytes[4];
    BYTE currentValue[4] = { 0 };

    if (!ReadProcessMemory(hProcess, (LPCVOID)Instruction_Address, currentValue, sizeof(currentValue), nullptr))
    {
        std::wcout << L"\n\n[!] Failed to read memory at address!";
        Sleep(1666);
        return;
    }

    bool Status = currentValue[0] == Original_Bytes[0] && currentValue[1] == Original_Bytes[1] && currentValue[2] == Original_Bytes[2] && currentValue[3] == Original_Bytes[3];

	std::fill(std::begin(NOP_Bytes), std::end(NOP_Bytes), 0x90);
    std::wcout << L"\n\n[!] Infinite Nitrous is " << (Status ? L"disabled\n" : L"enabled\n");
	std::wcout << L"[!] Press INSERT to enable/disable Infinite Nitrous or ESC to return to the main menu...\n";

    while (true)
    {
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            if (Status)
            {
                WriteProcessMemory(hProcess, (LPVOID)Instruction_Address, NOP_Bytes, sizeof(NOP_Bytes), nullptr);
                std::wcout << L"[+] InfiniteNitrous has been successfully enabled\n";
            }
            else
            {
                WriteProcessMemory(hProcess, (LPVOID)Instruction_Address, Original_Bytes, sizeof(Original_Bytes), nullptr);
                std::wcout << L"[-] InfiniteNitrous has been successfullY disabled\n";
            }
            Status = !Status;
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 1)
        {
            return;
        }
    }
}