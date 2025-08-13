#include "includes.h"

bool WriteByte(HANDLE hProcess, uintptr_t address, BYTE value) 
{
	SIZE_T bytesWritten; // ➡️ SIZE_T = É um tipo de dado usado para representar tamanhos de objetos em bytes, e é definido como um inteiro sem sinal. Ele é usado principalmente para operações de alocação de memória e manipulação de buffers.
    return WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(value), &bytesWritten) && bytesWritten == sizeof(value);
}

void FunctionMakeCustomProfileNames(HANDLE hProcess)
{
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::wcout << R"(
______  ___      ______            _________             _____                       ________             __________________          _____   __                              
___   |/  /_____ ___  /______      __  ____/___  __________  /_____________ ___      ___  __ \_______________  __/__(_)__  /____      ___  | / /_____ _______ ________________
__  /|_/ /_  __ `/_  //_/  _ \     _  /    _  / / /_  ___/  __/  __ \_  __ `__ \     __  /_/ /_  ___/  __ \_  /_ __  /__  /_  _ \     __   |/ /_  __ `/_  __ `__ \  _ \_  ___/
_  /  / / / /_/ /_  ,<  /  __/     / /___  / /_/ /_(__  )/ /_ / /_/ /  / / / / /     _  ____/_  /   / /_/ /  __/ _  / _  / /  __/     _  /|  / / /_/ /_  / / / / /  __/(__  ) 
/_/  /_/  \__,_/ /_/|_| \___/      \____/  \__,_/ /____/ \__/ \____//_/ /_/ /_/      /_/     /_/    \____//_/    /_/  /_/  \___/      /_/ |_/  \__,_/ /_/ /_/ /_/\___//____/  )";

    std::wcout << L"\n\n";

    BYTE InputLimit, AllowAnyChar, SaveListLength, IgnoreChar;

    if (
        !ReadProcessMemory(hProcess, (LPCVOID)0x527570, &InputLimit, sizeof(InputLimit), nullptr) ||
        !ReadProcessMemory(hProcess, (LPCVOID)0x52758E, &AllowAnyChar, sizeof(AllowAnyChar), nullptr) ||
        !ReadProcessMemory(hProcess, (LPCVOID)0x563A7A, &SaveListLength, sizeof(SaveListLength), nullptr) ||
        !ReadProcessMemory(hProcess, (LPCVOID)0x563A7E, &IgnoreChar, sizeof(IgnoreChar), nullptr)
        )
    {
        std::wcout << L"\n[!] Failed to read memory at address\n";
        Sleep(1000);
        return;
    }

    else
    {
        if (WriteByte(hProcess, 0x527570, 15) && WriteByte(hProcess, 0x52758E, 0) && WriteByte(hProcess, 0x563A7A, 16) && WriteByte(hProcess, 0x563A7E, '/'))
        {
            std::wcout << L"[!] MakeCustomProfileNames is activated!\n";
            std::wcout << L"[!] Note: When you create a custom profile, and when you open the game and the save does not appear, don't worry, just press (5) to activate it and it will appear in the list of saves.\n";
            std::wcout << L"[!] Press ESC to return to the main menu...\n";
        }
        else
        {
            std::wcout << L"[!] Failed to write memory during activation!\n";
        }
		while (!(GetAsyncKeyState(VK_ESCAPE) & 1)); // ➡️ Espera até que a tecla ESC seja pressionada
    }
}

