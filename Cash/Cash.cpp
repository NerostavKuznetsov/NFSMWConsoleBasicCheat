#include "Includes.h" // ➡️ Inclui o arquivo de cabeçalho com todas as bibliotecas e definições necessárias

uintptr_t BASE_MODULE_ADDRESS = 0x400000; // ➡️ Endereço base do módulo (speed.exe), geralmente é 0x400000 para executáveis do Windows
uintptr_t CASH_ADDRESS = 0x051CF90; // ➡️ Endereço do primeiro ponteiro a ser resolvido, que aponta para o endereço do dinheiro no jogo
uintptr_t CASH_OFFSET[] = { 0x10, 0xB4 }; // ➡️ Offsets para resolver o ponteiro do dinheiro no jogo.

DWORD ResolverPointerChain(HANDLE hProcess, DWORD BMA_PLUS_CA, unsigned int offsets[], int size) // ➡️ Função para resolver uma cadeia de ponteiros
{
	DWORD FinalAddress = BMA_PLUS_CA; // ➡️ BMA_PLUS_CA  = BASE_MODULE_ADDRESS + CASH_ADDRESS = 0x400000 + 0x51CF90 = Valor dinâmico do primeiro ponteiro a ser resolvido  
	for (int i = 0; i < size; i++) // ➡️ Itera sobre os offsets para resolver o ponteiro
    {
		DWORD temp = 0; // ➡️ Variável temporária para armazenar o valor lido da memória(Evita lixo na memória, protege contra falhas de leitura e melhor visibilidade do código)
		ReadProcessMemory(hProcess, (LPCVOID)FinalAddress, &temp, sizeof(temp), nullptr); // ➡️  Lê o valor do endereço FinalAddress na memória do processo hProcess e armazena em temp
		FinalAddress = temp + offsets[i]; // ➡️ Atualiza FinalAddress para o próximo endereço na cadeia de ponteiros, adicionando o offset atual
    } 
	return FinalAddress; // ➡️ Retorna o endereço final resolvido
}

void FunctionCash(HANDLE hProcess) // ➡️ Função principal para manipular o dinheiro no jogo
{
	DWORD FinalAddress = ResolverPointerChain(hProcess, BASE_MODULE_ADDRESS + CASH_ADDRESS, CASH_OFFSET, sizeof(CASH_OFFSET) / sizeof(CASH_OFFSET[0])); // ➡️ Resolve o endereço final do dinheiro no jogo

	while (true) // ➡️ Loop infinito para permitir múltiplas alterações de dinheiro
    {
		system("cls"); // ➡️ Limpa a tela do console
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para verde brilhante

		std::wcout << R"( 
_________             ______  
__  ____/_____ __________  /_ 
_  /    _  __ `/_  ___/_  __ \
/ /___  / /_/ /_(__  )_  / / /
\____/  \__,_/ /____/ /_/ /_/  )"; // ➡️ Fim da arte ASCII

		unsigned int currentMoney = 0; // ➡️ Variável para armazenar o valor atual do dinheiro

		if (!ReadProcessMemory(hProcess, (LPCVOID)FinalAddress, &currentMoney, sizeof(currentMoney), nullptr)) // ➡️ Lê o valor atual do dinheiro na memória do processo
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para vermelho brilhante
			std::wcout << L"\n\n[!] Failed to read memory at address!"; // ➡️ Mensagem de erro se a leitura falhar
			Sleep(1666); // ➡️ Pausa para permitir que o usuário veja a mensagem de erro
			break; // ➡️ Sai do loop se a leitura falhar
		}

		std::wcout << L"\n\n[!] Current Money: " << currentMoney; // ➡️ Exibe o valor atual do dinheiro lido da memória do processo.
		std::wcout << L"\n[?] Enter a new value or press ESC to return: "; // ➡️ Solicita ao usuário que insira um novo valor de dinheiro ou pressione ESC para sair
		std::wstring input; // ➡️ Usado para armazenar a entrada do usuário

		while (true) // ➡️ Loop para capturar a entrada do usuário
		{
			wchar_t ch = _getwch(); // ➡️ Captura um caractere da entrada do usuário sem exibir no console

			if (ch == 27) return; // ➡️ ESC          
			if (ch == 13) break; // ➡️ ENTER      
			if (ch == L'\b' && !input.empty()) // ➡️ BACKSPACE
			{
				input.pop_back(); // ➡️ Se o usuário pressionar BACKSPACE e a entrada não estiver vazia, remove o último caractere da entrada
				std::wcout << L"\b \b"; // ➡️ Move o cursor para trás, imprime um espaço em branco para apagar o caractere e move o cursor de volta
			}
			 if (iswdigit(ch)) // ➡️ Aceita apenas dígitos
			{
				input += ch; // ➡️ Adiciona o caractere digitado à entrada
				std::wcout << ch; // ➡️ Exibe o caractere digitado no console
			}
		}

		if (input.empty()) // ➡️ Verifica se a entrada está vazia
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para vermelho brilhante
			std::wcout << L"\n[!] No value entered\n"; // ➡️ Mensagem de erro para entrada vazia
			Sleep(1666); // ➡️ Pausa para permitir que o usuário veja a mensagem de erro
			continue; // ➡️ Continua o loop se a entrada for vazia
		}

		int NewMoney = 0; // ➡️ Variável para armazenar o novo valor de dinheiro
		try 
		{
			NewMoney = std::stoi(input); // ➡️ Converte a entrada para um inteiro
		}
		catch (...) // ➡️ Captura qualquer exceção que possa ocorrer durante a conversão
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para vermelho brilhante
			std::wcout << L"\n[!] Invalid value\n"; // ➡️ Mensagem de erro para valor inválido		
			Sleep(1666); // ➡️ Pausa para permitir que o usuário veja a mensagem de erro
			continue; // ➡️ Continua o loop se a conversão falhar
		}

		if (WriteProcessMemory(hProcess, (LPVOID)FinalAddress, &NewMoney, sizeof(NewMoney), nullptr))  // ➡️ Escreve o novo valor de dinheiro na memória do processo
		{
			std::wcout << L"\n[*] Money changed to: " << NewMoney << L"\n"; // ➡️ Confirmação de que o valor foi alterado com sucesso
		}

		std::wcout << L"\n[!] Press any KEY to enter anoother value or ESC to return to the main menu...\n"; // ➡️ Instruções para o usuário
		wchar_t ch = _getwch(); // ➡️ Espera o usuário pressionar uma tecla
		if (ch == 27) return; // ➡️ Se a tecla pressionada for ESC, retorna ao menu principal
	}
}

    
