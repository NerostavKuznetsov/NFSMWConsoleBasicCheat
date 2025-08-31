#include "Includes.h"

void FunctionInfiniteSpeedbreaker(HANDLE hProcess)
{
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::wcout << R"( 
________      ____________       __________           ________                 ______________                    ______
____  _/_________  __/__(_)_________(_)_  /_____      __  ___/_______________________  /__  /___________________ ___  /______________
 __  / __  __ \_  /_ __  /__  __ \_  /_  __/  _ \     _____ \___  __ \  _ \  _ \  __  /__  __ \_  ___/  _ \  __ `/_  //_/  _ \_  ___/
__/ /  _  / / /  __/ _  / _  / / /  / / /_ /  __/     ____/ /__  /_/ /  __/  __/ /_/ / _  /_/ /  /   /  __/ /_/ /_  ,<  /  __/  /    
/___/  /_/ /_//_/    /_/  /_/ /_//_/  \__/ \___/      /____/ _  .___/\___/\___/\__,_/  /_.___//_/    \___/\__,_/ /_/|_| \___//_/     
                                                                 /_/                                                                    )";
    uintptr_t Address = 0x400000 + 0x2EDDB9;
    BYTE bytes_ON[] = { 0xEB, 0x51 }; // ➡️ JMP 
    BYTE bytes_OFF[] = { 0x75, 0x51 }; // ➡️ JNE → Original bytes
    BYTE currentValue[2] = { 0 }; // ➡️ Valor atual que se encontra quando o jogo abre! → { 0x75, 0x51 } → Original bytes

    if (!ReadProcessMemory(hProcess, (LPCVOID)Address, currentValue, sizeof(currentValue), nullptr)) // ➡️ Não precisa de &currentValue em array de bytes
    {
        std::wcout << L"\n[!] Failed to read memory at address";
        Sleep(1666);
        return;
    }

    bool Status = currentValue[0] == bytes_OFF[0] && currentValue[1] == bytes_OFF[1]; 

    std::wcout << L"\n\n[!] Infinite Speedbreaker is " << (Status ? L"disabled\n" : L"enabled\n");
    std::wcout << L"[!] Press INSERT to enable/disable Infinite Speedbreaker or ESC to return to the main menu...\n";

    while (true)
    {
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            if (Status) // ➡️ Se estiver bytes_OFF(disabled), aplicaremos o bytes_ON(enabled)
            {
                WriteProcessMemory(hProcess, (LPVOID)Address, bytes_ON, sizeof(bytes_ON), nullptr);
                std::wcout << L"[!] Speedbreaker has been successfully enabled\n";
            }
            else // ➡️ Se estiver bytes_ON(enabled), aplicaremos o bytes_OFF(disabled)
            {
                WriteProcessMemory(hProcess, (LPVOID)Address, bytes_OFF, sizeof(bytes_OFF), nullptr);
                std::wcout << L"[!] Speedbreaker has been successfully disabled\n";
            }
            Status = !Status;
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 1)
        {
            return;
        }
    }
}

/* Note:
* 
* Variável simples "BYTE CurrentValue = "  precisa de &.
*
* Array  "BYTE CurrentValue[2] = " já vira ponteiro automaticamente, então não precisa de &
* 
* //////////////////////////////////////////////////////////////////////////////////////////////////////////
* 
* bool Status = (currentValue[0] == bytes_ON[0] && currentValue[1] == bytes_ON[1]);
* 
* ➡️ currentValue[0] == 0xEB && currentValue[1] == 0x51 → enabled // Status == true
* ➡️ currentValue[0] == 0x75 && currentValue[1] == 0x51 → disabled → Os bytes não batem com bytes_ON // Status == false
* 
* //////////////////////////////////////////////////////////////////////////////////////////////////////////
* 
* bool Status = (currentValue[0] == bytes_OFF[0] && currentValue[1] == bytes_OFF[1]);
*
* // ➡️ currentValue[0] == 0x75 && currentValue[1] == 0x51 → disabled // Status == true
* // ➡️ currentValue[0] == 0xEB && currentValue[1] == 0x51 → enabled  → Os bytes não batem com bytes_OFF // Status == false
*
* //////////////////////////////////////////////////////////////////////////////////////////////////////////
*
* bool Status = (currentValue[0] == bytes_OFF[0] && currentValue[1] == bytes_OFF[1]);
* 
* Aqui a pergunta mudou: “O que está na memória é igual aos bytes de OFF?”
* 
* Se sim → Status = true → isso significa que o cheat está desligado.
* Se não → Status = false → isso significa que o cheat já está ligado.
* 
* //////////////////////////////////////////////////////////////////////////////////////////////////////////
*
* bool Status = (currentValue[0] == bytes_ON[0] && currentValue[1] == bytes_ON[1]);
* 
* Aqui a pergunta é: “O que está na memória é igual aos bytes de ON?”
*
* Se sim → Status = true → isso significa que o cheat já está ligado.
* Se não → Status = false → isso significa que o cheat está desligado.
* 
*/