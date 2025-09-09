#include "Includes.h" // ➡️ Inclui o arquivo de cabeçalho com todas as bibliotecas e definições necessárias

/*
* NFSMW - NK Cheats / NFSMW - Console Basic Cheat
*
* |---------------------| 
* | [!] Status/Aviso    |
* | [*] Aplicado        |
* | [~] Esperando       |
* |---------------------|
*
* [!] Este programa é um software livre, você pode redistribuí-lo e/ou modificá-lo como quiser. 
*/

void ShowMenu() // ➡️ Função para exibir o menu principal
{
	system("cls"); // ➡️ Limpa a tela do console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para verde brilhante
    std::wcout << R"(
_____   _______________________  _____       __              _________                         ______          ________              _____           ______________             _____ 
___  | / /__  ____/_  ___/__   |/  /_ |     / /              __  ____/____________________________  /____      ___  __ )_____ __________(_)______    __  ____/__  /____________ __  /_
__   |/ /__  /_   _____ \__  /|_/ /__ | /| / /  ________     _  /    _  __ \_  __ \_  ___/  __ \_  /_  _ \     __  __  |  __ `/_  ___/_  /_  ___/    _  /    __  __ \  _ \  __ `/  __/
_  /|  / _  __/   ____/ /_  /  / / __ |/ |/ /   _/_____/     / /___  / /_/ /  / / /(__  )/ /_/ /  / /  __/     _  /_/ // /_/ /_(__  )_  / / /__      / /___  _  / / /  __/ /_/ // /_  
/_/ |_/  /_/      /____/ /_/  /_/  ____/|__/                 \____/  \____//_/ /_//____/ \____//_/  \___/      /_____/ \__,_/ /____/ /_/  \___/      \____/  /_/ /_/\___/\__,_/ \__/   )"; // ➡️ Fim da arte ASCII 

	std::wcout << "\n\n"; // ➡️ Duas novas linhas para espaçamento
	std::wcout << "                                                                                                                                                                          By: Nerostav Kuznetsov\n"; // Typo: By -> BY 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para roxo brilhante
	std::wcout << "Steam:    https://steamcommunity.com/profiles/76561198304587027     \n"; // Typo: Steam -> STEAM
	std::wcout << "Insta:    https://instagram.com/nrstv_kuznetsov                      \n"; // Typo: Insta -> Instagram
	std::wcout << "Github:   https://github.com/NerostavKuznetsov/NFSMWConsoleBasicCheat \n"; // Typo: GitHub -> Github
	std::wcout << "Youtub:   https://youtube.com/@Kuzntsv-666                             \n"; // Typo: Youtub -> Youtube
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para verde brilhante
	std::wcout << L" \n"; // ➡️ Nova linha para espaçamento
    std::wcout << L"╔═════════════════════════════════════╗\n";
    std::wcout << L"║              MAIN MENU              ║\n";
    std::wcout << L"╠═════════════════════════════════════╣\n";
    std::wcout << L"║ 1  ➡️  Cash                         ║\n"; // OKAY
    std::wcout << L"║ 2  ➡️  Infinite Nitrous             ║\n"; // OKAY
    std::wcout << L"║ 3  ➡️  Infinite Speedbreaker        ║\n"; // OKAY
    std::wcout << L"║ 4  ➡️  Never Busted                 ║\n"; // OKAY
    std::wcout << L"║ 5  ➡️  Markers                      ║\n"; // OKAY
    std::wcout << L"║ 6  ➡️  Unlock All Things            ║\n"; // OKAY
    std::wcout << L"║ 7  ➡️  *                            ║\n"; // PENDING...
    std::wcout << L"║ 8  ➡️  *                            ║\n"; // PENDING...
    std::wcout << L"║ 9  ➡️  *                            ║\n"; // PENDING...
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

DWORD GetModuleBaseAddress(DWORD ProcessID, const wchar_t* modBaseName) // ➡️ Pegar o endereço base do processo .exe (PID)
{
	DWORD baseAddress = 0; // ➡️ Inicializa o endereço base como 0
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID); // ➡️ Cria um snapshot dos módulos (DLLs e o próprio .exe) carregados no processo especificado por ProcID
	// TH32CS_SNAPMODULE32 é necessário para capturar módulos de 32 bits em um processo de 64 bits

	if (hSnapshot != INVALID_HANDLE_VALUE) // ➡️ Verifica se o snapshot foi criado com sucesso
    {
		MODULEENTRY32W MEW32; // ➡️ Estrutura para armazenar informações sobre o módulo
		MEW32.dwSize = sizeof(MEW32); // ➡️ Define o tamanho da estrutura
		if (Module32FirstW(hSnapshot, &MEW32)) // ➡️ Obtém informações sobre o primeiro módulo no snapshot
        {
			do // ➡️ Loop através dos módulos no snapshot
            { 
				if (!_wcsicmp(MEW32.szModule, modBaseName)) // ➡️ Compara o nome do módulo com o nome fornecido (case-insensitive) - >   _wcsicmp → ignora maiúsculas/minúsculas (case-insensitive). = "Outlast2.exe" == "OUTLAST2.EXE"
                {
					baseAddress = (DWORD)(MEW32.modBaseAddr); // ➡️ Se encontrar uma correspondência, armazena o endereço base do módulo
					break; // ➡️ Sai do loop se o módulo for encontrado
                }
			} while (Module32NextW(hSnapshot, &MEW32)); // ➡️ Move para o próximo módulo no snapshot
        }
		CloseHandle(hSnapshot); // ➡️ Fecha o handle do snapshot para liberar recursos
		return baseAddress; // ➡️ Retorna o endereço base do módulo (ou 0 se não encontrado)
    }
}

int main() // ➡️ Função principal do programa
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
			wchar_t ch = _getwch(); // ➡️ Captura um caractere da entrada do usuário sem exibir no console

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
			Sleep(1666); // ➡️ Pausa para permitir que o usuário veja a mensagem de erro
			continue; // ➡️ Continua o loop se a entrada for vazia
        }
		else if (input.length() > 1) // ➡️ Verifica se a entrada tem mais de um caractere
        {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para vermelho brilhante
			std::wcout << L"\n[!] Invalid option. Please enter a single digit or 'z' to exit\n"; // ➡️ Mensagem de erro se a entrada tiver mais de um caractere
			Sleep(1666); // ➡️ Pausa para permitir que o usuário veja a mensagem de erro
			continue; // ➡️ Continua o loop se a entrada for inválida
        }
        
		wchar_t option = input[0]; // ➡️ Pega o primeiro caractere da entrada como a opção selecionada

		switch (option) // ➡️ Switch para selecionar a função com base na opção do usuário
        {
		case '1': // ➡️ Opção 1 para Cash
			system("cls"); // ➡️ Limpa a tela do console
			FunctionCash(hProcess); // ➡️ Chama a função para adicionar dinheiro
			break; // ➡️ Sai do switch
		case '2': // ➡️ Opção 2 para Infinite Nitrous
			system("cls"); // ➡️ Limpa a tela do console
			FunctionInfiniteNitrous(hProcess); // ➡️ Chama a função para Nitrous Infinito
			break; // ➡️ Sai do switch
		case '3': // ➡️ Opção 3 para Infinite Speedbreaker
			system("cls"); // ➡️ Limpa a tela do console
			FunctionInfiniteSpeedbreaker(hProcess); // ➡️ Chama a função para Speedbreaker Infinito
			break; // ➡️ Sai do switch
		case '4': // ➡️ Opção 4 para Never Busted
			system("cls"); // ➡️ Limpa a tela do console
			FunctionNeverBusted(hProcess); // ➡️ Chama a função para Never Busted
			break; // ➡️ Sai do switch
		case'5': // ➡️ Opção 5 para Markers
			system("cls"); // ➡️ Limpa a tela do console
            FunctionMarkers(hProcess); // ➡️ Chama a função para Markers
			break; // ➡️ Sai do switch
		case '6': // ➡️ Opção 6 para Unlock All Things
			system("cls"); // ➡️ Limpa a tela do console
			FunctionUnlockAllThings(hProcess); // ➡️ Chama a função para Desbloquear Tudo
			break; // ➡️ Sai do switch
		case 'z': // ➡️ Opção 'z' para sair
			system("cls"); // ➡️ Limpa a tela do console
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para vermelho brilhante
			std::wcout << L"[!] Closing the program"; // ➡️ Mensagem de encerramento
			for (int i = 0; i < 6; i++) // ➡️ Animação de pontos
            {
				std::wcout << L"."; // ➡️ Imprime um ponto
				Sleep(666); // ➡️ Pausa por 666 milissegundos
            }
			Sleep(1666); // ➡️ Pausa para permitir que o usuário veja a mensagem de encerramento
			running = FALSE; // ➡️ Define running como FALSE para sair do loop e encerrar o programa
			break; // ➡️ Sai do switch
        }
    }
	CloseHandle(hProcess); // ➡️ Fecha o handle do processo para liberar recursos
}