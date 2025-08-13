#include "Includes.h"

/*
* NFSMW - NK Cheats
*
* |---------------------------------------------------------------------| 
* | [!] Status/Aviso: --------------------------------------------------|
* | [*] Aplicado: ------------------------------------------------------|
* | [~] Esperando: -----------------------------------------------------|
* | [?] Entrada: -------------------------------------------------------|
* |---------------------------------------------------------------------|
*
* [!] Este programa é um software livre: você pode redistribuí-lo e/ou modificá-lo como quiser.
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
    std::wcout << L"║ 2  ➡️  Infinite Nitrous             ║\n";
    std::wcout << L"║ 3  ➡️  Infinite Speedbreaker        ║\n";
    std::wcout << L"║ 4  ➡️  Never Busted                 ║\n";
    std::wcout << L"║ 5  ➡️  Unlock All Things            ║\n";
    std::wcout << L"║ 6  ➡️  *                            ║\n";
    std::wcout << L"║ 7  ➡️  *                            ║\n";
    std::wcout << L"║ 8  ➡️  *                            ║\n";
    std::wcout << L"║ 9  ➡️  *                            ║\n";
    std::wcout << L"║ z  ➡️  Exit                         ║\n";
    std::wcout << L"╚═════════════════════════════════════╝\n";
}

DWORD GetProcessIdByName(const std::wstring& processName)
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

int main()
{
	setlocale(LC_ALL, "PT_BR.UTF-8"); // ➡️ Template para UTF-8
    SetConsoleOutputCP(CP_UTF8); // ➡️ Força a saída UTF-8 (emojis ou caracteres especiais)
    SetConsoleTitleA("NFSMW - NK Cheats");

    DWORD PID = 0;

    while (PID == 0) // ➡️ Enquanto o PID for zero, ou seja, enquanto o processo speed.exe não tiver sido encontrado, continua repetindo o código dentro de 'while' = loop 
    {
        system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::wcout << L"[~] Waiting for speed.exe";
        for (int i = 0; i < 6; i++)
        {
            std::wcout << L".";
            Sleep(600);
        }

        PID = GetProcessIdByName(L"speed.exe");
		if (PID != 0) // ➡️ Se o PID for diferente de zero, ou seja, se o processo speed.exe for encontrado, sai do loop
            break;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
    BOOL running = TRUE;

    while (running)
    {
        ShowMenu(); 

        std::wcout << L"\n[!] ProcessID: " << PID << std::endl;
        std::wcout << L"[?] Enter your option (0-9): ";
        std::wstring input;

        while (true)
        {
            wchar_t ch = _getwch();

            if (ch == 13) break; // 
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
            Sleep(1000);
			continue; // ➡️ Continua o loop se a entrada for vazia
        }
        else if (input.length() > 1)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
            std::wcout << L"\n[!] Invalid option. Please enter a single digit or 'z' to exit\n";
            Sleep(1000);
			continue; // ➡️ Continua o loop se a entrada for inválida
        }
        
		wchar_t option = input[0]; 

		switch (option) // ➡️ Switch para verificar a opção escolhida pelo usuário
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
        case 'z':
            system("cls");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
            std::wcout << L"[!] Closing the program";
            for (int i = 0; i < 6; i++)
            {
                std::wcout << L".";
                Sleep(600);
            }
            Sleep(1000);
			running = FALSE; // ➡️ Define running como FALSE para sair do loop e encerrar o programa
            break;
        }
    }
    CloseHandle(hProcess);
}