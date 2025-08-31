#include "Includes.h"

/*
* NFSMW - NK Cheats / NFSMW - Console Basic Cheat
*
* |---------------------| 
* | [!] Status/Aviso    |
* | [*] Aplicado        |
* | [~] Esperando       |
* |---------------------|
*
* [!] Este programa é um software livre, você pode redistribuí-lo e/ou modificá-lo como quiser. '-'
*/

void ShowMenu() 
{
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::wcout << R"(
_____   _______________________  _____       __              _________                         ______          ________              _____           ______________             _____ 
___  | / /__  ____/_  ___/__   |/  /_ |     / /              __  ____/____________________________  /____      ___  __ )_____ __________(_)______    __  ____/__  /____________ __  /_
__   |/ /__  /_   _____ \__  /|_/ /__ | /| / /  ________     _  /    _  __ \_  __ \_  ___/  __ \_  /_  _ \     __  __  |  __ `/_  ___/_  /_  ___/    _  /    __  __ \  _ \  __ `/  __/
_  /|  / _  __/   ____/ /_  /  / / __ |/ |/ /   _/_____/     / /___  / /_/ /  / / /(__  )/ /_/ /  / /  __/     _  /_/ // /_/ /_(__  )_  / / /__      / /___  _  / / /  __/ /_/ // /_  
/_/ |_/  /_/      /____/ /_/  /_/  ____/|__/                 \____/  \____//_/ /_//____/ \____//_/  \___/      /_____/ \__,_/ /____/ /_/  \___/      \____/  /_/ /_/\___/\__,_/ \__/   )";

    std::wcout << "\n\n";
    std::wcout << "                                                                                                                                                                          By: Nerostav Kuznetsov\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    std::wcout << "Steam:    https://steamcommunity.com/profiles/76561198304587027   \n";
    std::wcout << "Insta:    https://instagram.com/nrstv_kuznetsov                    \n";
    std::wcout << "Github:   https://github.com/NerostavKuznetsov                      \n";
    std::wcout << "Youtub:   https://youtube.com/@Kuzntsv-666                           \n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::wcout << L" \n";
    std::wcout << L"╔═════════════════════════════════════╗\n";
    std::wcout << L"║              MAIN MENU              ║\n";
    std::wcout << L"╠═════════════════════════════════════╣\n";
    std::wcout << L"║ 1  ➡️  Cash                         ║\n";
    std::wcout << L"║ 2  ➡️  Infinite Nitrous             ║\n"; // OK
    std::wcout << L"║ 3  ➡️  Infinite Speedbreaker        ║\n"; // OK
    std::wcout << L"║ 4  ➡️  Never Busted                 ║\n"; // OK
    std::wcout << L"║ 5  ➡️  Unlock All Things            ║\n"; // 
    std::wcout << L"║ 6  ➡️  *                            ║\n";
    std::wcout << L"║ 7  ➡️  *                            ║\n";
    std::wcout << L"║ 8  ➡️  *                            ║\n";
    std::wcout << L"║ 9  ➡️  *                            ║\n";
    std::wcout << L"║ z  ➡️  Exit                         ║\n";
    std::wcout << L"╠═════════════════════════════════════╣\n";
    std::wcout << L"║  Need For Speed Most Wanted (2005)  ║\n";
    std::wcout << L"╚═════════════════════════════════════╝\n";
}

DWORD GetProcessIdByName(const std::wstring& processName) // ➡️ Pegar o ID do processo (PID) = (PROCESS ID) pelo nome do processo 
{
    DWORD processID = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    
    if(hSnapshot != INVALID_HANDLE_VALUE)
    {
		PROCESSENTRY32 PE32;
        PE32.dwSize = sizeof(PROCESSENTRY32);

        if (Process32FirstW(hSnapshot, &PE32))
        {
            do
            {
                if (processName == PE32.szExeFile)
                {
					processID = PE32.th32ProcessID;
                    break;
                }
            } while (Process32NextW(hSnapshot, &PE32));
		}  
        CloseHandle(hSnapshot);
		return processID;
    }
}

DWORD GetModuleBaseAddress(DWORD ProcID, const wchar_t* modBaseName) // ➡️ Pegar o endereço base do processo <speed.exe> (PID)
{
    DWORD baseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcID);

    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32W modBaseEntry;
        modBaseEntry.dwSize = sizeof(modBaseEntry);
        if (Module32FirstW(hSnapshot, &modBaseEntry))
        {
            do
            {
                if (!_wcsicmp(modBaseEntry.szModule, modBaseName))
                {
                    baseAddress = (DWORD)(modBaseEntry.modBaseAddr);
                    break;
                }
            } while (Module32NextW(hSnapshot, &modBaseEntry));
        }
    }
    CloseHandle(hSnapshot);
    return baseAddress;
}

int main()
{
    _tsetlocale(LC_ALL, _T("PORTUGUESE")); // Posso usar -> setlocale(LC_ALL, "PT_BR.UTF-8"); 
	setlocale(LC_ALL, "PT_BR.UTF-8"); // ➡️ Português do Brasil com UTF-8. Isso garante que acentos, caracteres especiais e algumas formatações de texto funcionem corretamente.
    SetConsoleOutputCP(CP_UTF8); // ➡️ Configura o Console do Windows para UTF-8, permitindo que emojis e outros caracteres Unicode apareçam corretamente na tela.
    SetConsoleTitleA("NFSMW - NK Cheats");

    DWORD PID = GetProcessIdByName(L"speed.exe");
     
    while (PID == 0) // ➡️ Enquanto o PID for igual zero, ou seja, enquanto o processo speed.exe não tiver sido encontrado, continua repetindo o código dentro de 'while' = loop   >> if (PID != 0) // break removido, while ja quebra quando o processo é encontrado
    {
        system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        std::wcout << L"[~] waiting for speed.exe";
        for (int i = 0; i < 6; i++)
        {
            std::wcout << L".";
            Sleep(666);
        }
        PID = GetProcessIdByName(L"speed.exe");

    }

    uintptr_t modBaseAddr = GetModuleBaseAddress(PID, L"speed.exe");

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
    BOOL running = TRUE;

    while (running)
    {
        ShowMenu();
        std::wcout << L"\n[!] Base address 0x" << std::hex << modBaseAddr << L"\n";
        std::wcout << L"[!] ProcessID: " << std::dec << PID << L"\n";
        std::wcout << L"[?] Enter your option (0-9): ";
        std::wstring input;

        while (true)
        {
            wchar_t ch = _getwch();

            if (ch == 13) break;  
            if (ch == L'\b' && !input.empty())
            {
                input.pop_back(); 
                std::wcout << L"\b \b";
            }
            else if (iswdigit(ch) || ch == L'z') // aceita z também
            {
                input += ch;
                std::wcout << ch;
            }
        }

        if (input.empty())
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
            std::wcout << L"\n[!] Empty option\n";
            Sleep(1666);
			continue; // ➡️ Continua o loop se a entrada for vazia
        }
        else if (input.length() > 1)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
            std::wcout << L"\n[!] Invalid option. Please enter a single digit or 'z' to exit\n";
            Sleep(1666);
			continue; // ➡️ Continua o loop se a entrada for inválida
        }
        
		wchar_t option = input[0]; 

		switch (option) 
        {
        case '1':
			system("cls");
            FunctionCash(hProcess);
            break;
        case '2':  
            system("cls");
			FunctionInfiniteNitrous(hProcess);
            break;
        case '3':
            system("cls");
            FunctionInfiniteSpeedbreaker(hProcess);
            break;
        case '4':
            system("cls");
			FunctionNeverBusted(hProcess);
            break;
        case '5':
			system("cls");
            FunctionUnlockAllThings(hProcess);
            break;
        case 'z':
            system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
            std::wcout << L"[!] Closing the program";
            for (int i = 0; i < 6; i++)
            {
                std::wcout << L".";
                Sleep(666);
            }
            Sleep(1666);
			running = FALSE; // ➡️ Define running como FALSE para sair do loop e encerrar o programa
            break;
        }
    }
    CloseHandle(hProcess);
}