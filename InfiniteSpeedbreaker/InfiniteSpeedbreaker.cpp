#include "Includes.h" // ➡️ Inclui o arquivo de cabeçalho com todas as bibliotecas e definições necessárias

void FunctionInfiniteSpeedbreaker(HANDLE hProcess) // ➡️ Função principal para manipular o Speedbreaker infinito no jogo
{
	system("cls"); // ➡️ Limpa a tela do console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para verde brilhante
    std::wcout << R"( 
________      ____________       __________           ________                 ______________                    ______
____  _/_________  __/__(_)_________(_)_  /_____      __  ___/_______________________  /__  /___________________ ___  /______________
 __  / __  __ \_  /_ __  /__  __ \_  /_  __/  _ \     _____ \___  __ \  _ \  _ \  __  /__  __ \_  ___/  _ \  __ `/_  //_/  _ \_  ___/
__/ /  _  / / /  __/ _  / _  / / /  / / /_ /  __/     ____/ /__  /_/ /  __/  __/ /_/ / _  /_/ /  /   /  __/ /_/ /_  ,<  /  __/  /    
/___/  /_/ /_//_/    /_/  /_/ /_//_/  \__/ \___/      /____/ _  .___/\___/\___/\__,_/  /_.___//_/    \___/\__,_/ /_/|_| \___//_/     
                                                                 /_/                                                                    )"; // ➡️ Fim da arte ASCII
	uintptr_t Address = 0x400000 + 0x2EDDB9; // ➡️ Endereço da instrução que queremos modificar
    BYTE bytes_ON[] = { 0xEB, 0x51 }; // ➡️ JMP 
    BYTE bytes_OFF[] = { 0x75, 0x51 }; // ➡️ JNE → Original bytes
    BYTE currentValue[2] = { 0 }; // ➡️ Valor atual que se encontra quando o jogo abre! → { 0x75, 0x51 } → Original bytes

    if (!ReadProcessMemory(hProcess, (LPCVOID)Address, currentValue, sizeof(currentValue), nullptr)) // ➡️ Não precisa de &currentValue em array de bytes
    {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para vermelho brilhante
		std::wcout << L"\n[!] Failed to read memory at address!"; // ➡️ Mensagem de erro se a leitura falhar
		Sleep(1666); // ➡️ Pausa para permitir que o usuário veja a mensagem de erro
		return; // ➡️ Sai da função se a leitura falhar 
    }

	bool Status = (currentValue[0] == bytes_OFF[0] && currentValue[1] == bytes_OFF[1]); // ➡️ Se os bytes atuais forem iguais aos bytes_OFF(disabled), Status será true, indicando que o cheat está desligado. Se forem diferentes, Status será false, indicando que o cheat está ligado

	std::wcout << L"\n[!] Infinite Speedbreaker is " << (Status ? L"disabled\n" : L"enabled\n"); // ➡️ Exibe o status atual do cheat
	std::wcout << L"[!] Press INSERT to enable/disable Infinite Speedbreaker or ESC to return to the main menu...\n"; // ➡️ Instruções para o usuário

	while (true) // ➡️ Loop infinito para permitir múltiplas alterações
    {
		if (GetAsyncKeyState(VK_INSERT) & 1) // ➡️ Se a tecla INSERT for pressionada
        {
            if (Status) // ➡️ Se estiver bytes_OFF(disabled), aplicaremos o bytes_ON(enabled)
            {
				WriteProcessMemory(hProcess, (LPVOID)Address, bytes_ON, sizeof(bytes_ON), nullptr); // ➡️ Não precisa de &bytes_ON em array de bytes
				std::wcout << L"[!] Speedbreaker has been successfully enabled\n"; // ➡️ Mensagem de sucesso
            }
            else // ➡️ Se estiver bytes_ON(enabled), aplicaremos o bytes_OFF(disabled)
            {
				WriteProcessMemory(hProcess, (LPVOID)Address, bytes_OFF, sizeof(bytes_OFF), nullptr); // ➡️ Não precisa de &bytes_OFF em array de bytes
				std::wcout << L"[!] Speedbreaker has been successfully disabled\n"; // ➡️ Mensagem de sucesso
            }
			Status = !Status; // ➡️ Inverte o status
        }

		if (GetAsyncKeyState(VK_ESCAPE) & 1) // ➡️ Se a tecla ESC for pressionada
        {
			return; // ➡️ Sai da função e retorna ao menu principal
        }
    }
}

/* Note:
* 
* Variável simples "BYTE CurrentValue = "  precisa de &
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
* Se sim → Status = true → isso significa que o cheat está desligado
* Se não → Status = false → isso significa que o cheat já está ligado
* 
* //////////////////////////////////////////////////////////////////////////////////////////////////////////
*
* bool Status = (currentValue[0] == bytes_ON[0] && currentValue[1] == bytes_ON[1]);
* 
* Aqui a pergunta é: “O que está na memória é igual aos bytes de ON?”
*
* Se sim → Status = true → isso significa que o cheat já está ligado
* Se não → Status = false → isso significa que o cheat está desligado
* 
*/