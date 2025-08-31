#include "Includes.h"

uintptr_t BASE_MODULE_ADDRESS = 0x400000;
uintptr_t CASH_ADDRESS = 0x051CF90; // ➡️ Endereço do primeiro ponteiro a ser resolvido, que aponta para o endereço do dinheiro no jogo.
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

void FunctionCash(HANDLE hProcess)
{
	DWORD FinalAddress = ResolverPointerChain(hProcess, BASE_MODULE_ADDRESS + CASH_ADDRESS, CASH_OFFSET, sizeof(CASH_OFFSET) / sizeof(CASH_OFFSET[0])); // ➡️ Resolve o endereço final do dinheiro no jogo

	while (true)
    {
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		std::wcout << R"(
_________             ______  
__  ____/_____ __________  /_ 
_  /    _  __ `/_  ___/_  __ \
/ /___  / /_/ /_(__  )_  / / /
\____/  \__,_/ /____/ /_/ /_/  )";

        unsigned int currentMoney = 0; 

		if (!ReadProcessMemory(hProcess, (LPCVOID)FinalAddress, &currentMoney, sizeof(currentMoney), nullptr))
		{
			std::wcout << L"\n\n[!] Failed to read memory at address";
			Sleep(1500);
			break;
		}

		std::wcout << L"\n\n[!] Current Money: " << currentMoney;
		std::wcout << L"\n[?] Enter a new value or press ESC to return: ";
		std::wstring input;

		while (true)
		{
			wchar_t ch = _getwch();

			if (ch == 27) return; // ➡️ ESC          
			if (ch == 13) break; // ➡️ ENTER      
			if (ch == L'\b' && !input.empty()) 
			{
				input.pop_back(); // ➡️ Se o usuário pressionar BACKSPACE e a entrada não estiver vazia, remove o último caractere da entrada
				std::wcout << L"\b \b"; 
			}
			else if (iswdigit(ch)) 
			{
				input += ch;
				std::wcout << ch;
			}
		}

		if (input.empty()) 
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			std::wcout << L"\n[!] No value entered\n";
			Sleep(1500);
			continue; 
		}

		int NewMoney = 0;
		try 
		{
			NewMoney = std::stoi(input);
		}
		catch (...) 
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
			std::wcout << L"\n[!] Invalid value\n";			
			Sleep(1500);
			continue; 
		}

		if (WriteProcessMemory(hProcess, (LPVOID)FinalAddress, &NewMoney, sizeof(NewMoney), nullptr))  
		{
			std::wcout << L"\n[*] Money changed to: " << NewMoney << L"\n";
		}

		std::wcout << L"\n[!] Press any KEY to enter anoother value or ESC to return to the main menu...\n";
		wchar_t ch = _getwch();
		if (ch == 27) return;
	}
}

    
