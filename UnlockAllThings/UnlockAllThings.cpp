#include "Includes.h"

void FunctionUnlockAllThings(HANDLE hProcess)
{
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::wcout << R"(
_____  __      ______           ______      __________________   _____________ _____                       
__  / / /_________  /______________  /__    ___    |__  /__  /   ___  __/__  /____(_)_____________ ________
_  / / /__  __ \_  /_  __ \  ___/_  //_/    __  /| |_  /__  /    __  /  __  __ \_  /__  __ \_  __ `/_  ___/
/ /_/ / _  / / /  / / /_/ / /__ _  ,<       _  ___ |  / _  /     _  /   _  / / /  / _  / / /  /_/ /_(__  ) 
\____/  /_/ /_//_/  \____/\___/ /_/|_|      /_/  |_/_/  /_/      /_/    /_/ /_//_/  /_/ /_/_\__, / /____/  
                                                                                           /____/           )";
    uintptr_t Address = 0x926124;
    BYTE bytes_ON[] = { 1 };
    BYTE bytes_OFF[] = { 0 };
    BYTE currentValue[1] = { 0 };

    if (!ReadProcessMemory(hProcess, (LPCVOID)0x926124, currentValue, sizeof(currentValue), nullptr)) 
    {
        std::wcout << L"\n\n[!] Failed to read memory at address\n";
        Sleep(1666);
        return;
    }

    bool Status = currentValue[0] == bytes_OFF[0];

    std::wcout << L"\n\n[!] UnlockAllThings is " << (Status ? L"disabled\n" : L"enabled\n");
    std::wcout << L"[!] Press INSERT to enable/disable or ESC to return to the main menu...\n";

    while (true)
    {
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            if (Status)
            {
                WriteProcessMemory(hProcess, (LPVOID)Address, bytes_ON, sizeof(bytes_ON), nullptr);
                std::wcout << L"[!] UnlockAllThings has been successfully enabled\n";
            }
            else
            {
                WriteProcessMemory(hProcess, (LPVOID)Address, bytes_OFF, sizeof(bytes_OFF), nullptr);
                std::wcout << L"[!] UnlockAllThings has been successfully disabled\n";
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 1)
        {
            return; 
        }
    }
}










	