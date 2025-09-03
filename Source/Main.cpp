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

void ShowMenu() // ➡️ Função para exibir o menu principal
{
	system("cls"); // ➡️ Limpa a tela do console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Define a cor do texto para verde brilhante
    std::wcout << R"(
_____   _______________________  _____       __              _________                         ______          ________              _____           ______________             _____ 
___  | / /__  ____/_  ___/__   |/  /_ |     / /              __  ____/____________________________  /____      ___  __ )_____ __________(_)______    __  ____/__  /____________ __  /_
__   |/ /__  /_   _____ \__  /|_/ /__ | /| / /  ________     _  /    _  __ \_  __ \_  ___/  __ \_  /_  _ \     __  __  |  __ `/_  ___/_  /_  ___/    _  /    __  __ \  _ \  __ `/  __/
_  /|  / _  __/   ____/ /_  /  / / __ |/ |/ /   _/_____/     / /___  / /_/ /  / / /(__  )/ /_/ /  / /  __/     _  /_/ // /_/ /_(__  )_  / / /__      / /___  _  / / /  __/ /_/ // /_  
/_/ |_/  /_/      /____/ /_/  /_/  ____/|__/                 \____/  \____//_/ /_//____/ \____//_/  \___/      /_____/ \__,_/ /____/ /_/  \___/      \____/  /_/ /_/\___/\__,_/ \__/   )"; 

    std::wcout << "\n\n";
    std::wcout << "                                                                                                                                                                          By: Nerostav Kuznetsov\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para roxo brilhante
    std::wcout << "Steam:    https://steamcommunity.com/profiles/76561198304587027   \n";
    std::wcout << "Insta:    https://instagram.com/nrstv_kuznetsov                    \n";
    std::wcout << "Github:   https://github.com/NerostavKuznetsov                      \n";
    std::wcout << "Youtub:   https://youtube.com/@Kuzntsv-666                           \n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY); // ➡️
    std::wcout << L" \n";
    std::wcout << L"╔═════════════════════════════════════╗\n";
    std::wcout << L"║              MAIN MENU              ║\n";
    std::wcout << L"╠═════════════════════════════════════╣\n";
    std::wcout << L"║ 1  ➡️  Cash                         ║\n"; // OK
    std::wcout << L"║ 2  ➡️  Infinite Nitrous             ║\n"; // OK
    std::wcout << L"║ 3  ➡️  Infinite Speedbreaker        ║\n"; // OK
    std::wcout << L"║ 4  ➡️  Never Busted                 ║\n"; // OK
    std::wcout << L"║ 5  ➡️  Unlock All Things            ║\n"; // OK
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
	DWORD processID = 0; // ➡️ Inicializa o ID do processo como 0
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // ➡️ Cria um snapshot de todos os processos em execução no sistema
    
	if (hSnapshot != INVALID_HANDLE_VALUE) // ➡️ Verifica se o snapshot foi criado com sucesso
    {
		PROCESSENTRY32 PE32; // ➡️ Estrutura para armazenar informações sobre o processo
		PE32.dwSize = sizeof(PROCESSENTRY32); // ➡️ Define o tamanho da estrutura

		if (Process32FirstW(hSnapshot, &PE32)) // ➡️ Obtém informações sobre o primeiro processo no snapshot
        {
			do // ➡️ Loop através dos processos no snapshot
            {
				if (processName == PE32.szExeFile) // ➡️ Compara o nome do processo com o nome fornecido
                {
					processID = PE32.th32ProcessID; // ➡️ Se encontrar uma correspondência, armazena o ID do processo
					break; // ➡️ Sai do loop se o processo for encontrado
                }
			} while (Process32NextW(hSnapshot, &PE32)); // ➡️ Move para o próximo processo no snapshot
		}  
		CloseHandle(hSnapshot); // ➡️ Fecha o handle do snapshot para liberar recursos
		return processID; // ➡️ Retorna o ID do processo (ou 0 se não encontrado)
    }
}

DWORD GetModuleBaseAddress(DWORD ProcID, const wchar_t* modBaseName) // ➡️ Pegar o endereço base do processo .exe (PID)
{
    DWORD baseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcID); // ➡️ Cria um snapshot dos módulos (DLLs e o próprio .exe) carregados no processo especificado por ProcID
	// TH32CS_SNAPMODULE32 é necessário para capturar módulos de 32 bits em um processo de 64 bits

	if (hSnapshot != INVALID_HANDLE_VALUE) // ➡️ Verifica se o snapshot foi criado com sucesso
    {
		MODULEENTRY32W modBaseEntry; // ➡️ Estrutura para armazenar informações sobre o módulo
		modBaseEntry.dwSize = sizeof(modBaseEntry); // ➡️ Define o tamanho da estrutura
		if (Module32FirstW(hSnapshot, &modBaseEntry)) // ➡️ Obtém informações sobre o primeiro módulo no snapshot
        {
			do // ➡️ Loop através dos módulos no snapshot
            { 
				if (!_wcsicmp(modBaseEntry.szModule, modBaseName)) // ➡️ Compara o nome do módulo com o nome fornecido (case-insensitive)
                {
					baseAddress = (DWORD)(modBaseEntry.modBaseAddr); // ➡️ Se encontrar uma correspondência, armazena o endereço base do módulo
					break; // ➡️ Sai do loop se o módulo for encontrado
                }
			} while (Module32NextW(hSnapshot, &modBaseEntry)); // ➡️ Move para o próximo módulo no snapshot
        }
    }
	CloseHandle(hSnapshot); // ➡️ Fecha o handle do snapshot para liberar recursos
	return baseAddress; // ➡️ Retorna o endereço base do módulo (ou 0 se não encontrado)
}

int main()
{
    _tsetlocale(LC_ALL, _T("PORTUGUESE")); // Posso usar -> setlocale(LC_ALL, "PT_BR.UTF-8"); 
	setlocale(LC_ALL, "PT_BR.UTF-8"); // ➡️ Português do Brasil com UTF-8. Isso garante que acentos, caracteres especiais e algumas formatações de texto funcionem corretamente
    SetConsoleOutputCP(CP_UTF8); // ➡️ Configura o Console do Windows para UTF-8, permitindo que emojis e outros caracteres Unicode apareçam corretamente na tela
	SetConsoleTitleA("NFSMW - NK Cheats"); // ➡️ Define o título da janela do console

	DWORD PID = GetProcessIdByName(L"speed.exe"); // ➡️ Pega o PID do processo speed.exe
     
    while (PID == 0) // ➡️ Enquanto o PID for igual zero, ou seja, enquanto o processo speed.exe não tiver sido encontrado, continua repetindo o código dentro de 'while' = loop   >> if (PID != 0) // break removido, while ja quebra quando o processo é encontrado
    {
		system("cls"); // ➡️ Limpa a tela do console
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para verde brilhante

		std::wcout << L"[~] waiting for speed.exe"; // ➡️ Mensagem de espera
		for (int i = 0; i < 6; i++) // ➡️ Animação de pontos
        {
			std::wcout << L"."; // ➡️ Imprime um ponto
			Sleep(666); // ➡️ Pausa por 666 milissegundos
        }
		PID = GetProcessIdByName(L"speed.exe"); // ➡️ Atualiza o PID a cada iteração do loop

    }

	uintptr_t modBaseAddr = GetModuleBaseAddress(PID, L"speed.exe"); // ➡️ Pega o endereço base do módulo speed.exe

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID); // ➡️ Abre o processo com todas as permissões
	BOOL running = TRUE; // ➡️ Variável para controlar o loop do menu principal

	while (running) // ➡️ Loop principal do menu
    {
		ShowMenu(); // ➡️ Exibe o menu principal
		std::wcout << L"\n[!] Base address 0x" << std::hex << modBaseAddr << L"\n"; // ➡️ Exibe o endereço base do módulo em hexadecimal
		std::wcout << L"[!] ProcessID: " << std::dec << PID << L"\n"; // ➡️ Exibe o PID do processo em decimal
		std::wcout << L"[?] Enter your option (0-9): "; // ➡️ Solicita ao usuário que insira uma opção
		std::wstring input; // ➡️ Usado para armazenar a entrada do usuário

		while (true) // ➡️ Loop para capturar a entrada do usuário
        {
            wchar_t ch = _getwch();

			if (ch == 13) break; // ➡️ ENTER 
			if (ch == L'\b' && !input.empty()) // ➡️ BACKSPACE
            {
				input.pop_back(); // ➡️ Se o usuário pressionar BACKSPACE e a entrada não estiver vazia, remove o último caractere da entrada
				std::wcout << L"\b \b"; // ➡️ Move o cursor para trás, imprime um espaço em branco para apagar o caractere e move o cursor de volta
            }
			else if (iswdigit(ch) || ch == L'z') // ➡️ Aceita apenas dígitos ou 'z' para sair
            {
				input += ch; // ➡️ Adiciona o caractere à entrada
				std::wcout << ch; // ➡️ Exibe o caractere digitado
            }
        }

		if (input.empty()) // ➡️ Verifica se a entrada está vazia
        {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para vermelho brilhante
			std::wcout << L"\n[!] Empty option\n"; // ➡️ Mensagem de erro se a entrada estiver vazia
            Sleep(1666);
			continue; // ➡️ Continua o loop se a entrada for vazia
        }
		else if (input.length() > 1) // ➡️ Verifica se a entrada tem mais de um caractere
        {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para vermelho brilhante
            std::wcout << L"\n[!] Invalid option. Please enter a single digit or 'z' to exit\n";
            Sleep(1666);
			continue; // ➡️ Continua o loop se a entrada for inválida
        }
        
		wchar_t option = input[0]; // ➡️ Pega o primeiro caractere da entrada como a opção selecionada

		switch (option) // ➡️ Switch para selecionar a função com base na opção do usuário
        {
        case '1':
			system("cls");
			FunctionCash(hProcess); // ➡️ Chama a função para adicionar dinheiro
			break; // ➡️ Sai do switch
        case '2':  
            system("cls");
			FunctionInfiniteNitrous(hProcess); // ➡️ Chama a função para Nitrous Infinito
			break;
        case '3':
            system("cls");
			FunctionInfiniteSpeedbreaker(hProcess); // ➡️ Chama a função para Speedbreaker Infinito
            break;
        case '4':
            system("cls");
			FunctionNeverBusted(hProcess); // ➡️ Chama a função para Never Busted
            break;
        case '5':
			system("cls");
			FunctionUnlockAllThings(hProcess); // ➡️ Chama a função para Desbloquear Tudo
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