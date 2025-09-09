#include <Includes.h> // ➡️ Inclui o arquivo de cabeçalho com todas as bibliotecas e definições necessárias

/*
* Selectable Marker Count =                 0x7B3D7D; -> Exact count Address = 2
* Selectable Marker Count 2 =               0x7B3E19; -> Visual = 2
* Selections remaining =                    0x7A7A3C; -> Visual = 2
* You can now select X markers from Y =     0x7A7ABE; -> Visual = 2 
*/

void FunctionMarkers(HANDLE hProcess) // ➡️ Função principal para manipular os marcadores no jogo
{
	system("cls"); // ➡️ Limpa a tela do console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para verde brilhante
    std::wcout << R"(   
______  ___             ______                     
___   |/  /_____ __________  /_____________________
__  /|_/ /_  __ `/_  ___/_  //_/  _ \_  ___/_  ___/
_  /  / / / /_/ /_  /   _  ,<  /  __/  /   _(__  ) 
/_/  /_/  \__,_/ /_/    /_/|_| \___//_/    /____/   )"; // ➡️ Fim da arte ASCII 

	uintptr_t MarkersAddresses[] = { 0x7B3D7D, 0x7B3E19, 0x7A7A3C, 0x7A7ABE }; // ➡️ Array com os endereços dos valores dos marcadores
	BYTE CurrentValue[4] = { 0 }; // ➡️ Array para armazenar os valores atuais lidos da memória
	BYTE MaxMarkersValue = 6; // Valor máximo que queremos definir para os marcadores
	BYTE DefaultMarkersValue = 2; // Valor padrão que queremos definir para os marcadores
    
	for (int i = 0; i < 4; i++) // ➡️ Lê os valores atuais dos marcadores da memória do processo
    {
		if (!ReadProcessMemory(hProcess, (LPCVOID)MarkersAddresses[i], &CurrentValue[i], sizeof(CurrentValue[i]), nullptr)) // ➡️ Lê o valor atual do marcador na memória do processo
        {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // ➡️ Define a cor do texto para vermelho brilhante
			Sleep(1666); // ➡️ Pausa para permitir que o usuário veja a mensagem de erro
			return; // ➡️ Sai da função se a leitura falhar
        }
    }

    // ➡️ Define Status com base nos valores iniciais
	bool Status = CurrentValue[0] == DefaultMarkersValue && CurrentValue[1] == DefaultMarkersValue && CurrentValue[2] == DefaultMarkersValue && CurrentValue[3] == DefaultMarkersValue; // ➡️ Se os valores atuais forem iguais aos valores padrão(2), Status será true, indicando que o cheat está desligado. Se forem diferentes, Status será false, indicando que o cheat está ligado :)

	std::wcout << L"\n\nCurrent values: "; // ➡️ Exibe os valores atuais dos marcadores lidos da memória do processo
	std::wcout << L"\nSelectable Marker Count ---------------> " << CurrentValue[0]; // ➡️ Exibe o valor do primeiro marcador
	std::wcout << L"\nSelectable Marker Count 2 -------------> " << CurrentValue[1]; // ➡️ Exibe o valor do segundo marcador
	std::wcout << L"\nSelections remaining ------------------> " << CurrentValue[2]; // ➡️ Exibe o valor do terceiro marcador
	std::wcout << L"\nYou can now select X markers from Y ---> " << CurrentValue[3] << L"\n"; // ➡️ Exibe o valor do quarto marcador
	std::wcout << L"\n[!] Markers Cheat is currently " << (Status ? L"OFF (Default Values)" : L"ON (Max Values)") << L"\n"; // ➡️ Exibe o status atual do cheat
    // ➡️ Status == true → escreve MaxMarkersValue(6). O cheat está desligado e ao pressionar INSERT ele ativa o cheat, escrevendo os valores máximos.
    // ➡️ Status == false → escreve DefaultMarkersValue(2).
	std::wcout << L"[!] Press INSERT to max/default markers or ESC to return to the main menu...\n"; // ➡️ Instruções para o usuário

	while (true) // ➡️ Loop infinito para permitir múltiplas alterações
    {
		if (GetAsyncKeyState(VK_INSERT) & 1) // ➡️ Se a tecla INSERT for pressionada
        {
			BYTE newValue = Status ? MaxMarkersValue : DefaultMarkersValue; // ➡️ Se Status for true (default), define newValue como MaxMarkersValue, caso contrário, define como DefaultMarkersValue

			for (int i = 0; i < 4; i++) // ➡️ Loop para escrever o novo valor em todos os endereços
            {
				WriteProcessMemory(hProcess, (LPVOID)MarkersAddresses[i], &newValue, sizeof(newValue), nullptr); // Escreve o novo valor em cada um dos endereços
            }

			std::wcout << L"[!] Markers values have been successfully set to " << newValue << L"\n"; // ➡️ Mensagem de sucesso

			Status = !Status; // ➡️ Inverte o status <-- Aqui ele inverte para preparar para a próxima vez) 
        }

		if (GetAsyncKeyState(VK_ESCAPE) & 1) // ➡️ Se a tecla ESC for pressionada
        {
			return; // ➡️ Sai da função e retorna ao menu principal
        }
    }
}

/*
* %%% true → cheat desligado (valores padrão, DefaultMarkersValue = 2).
*
* %%% false → cheat ligado (valores máximos, MaxMarkersValue = 6).
* 
* //////////////////////////////////////////////////////////////////////////////////////////////////////
* 
* Explicação do funcionamento do cheat Markers:
* 
* No começo, Status indica o estado do cheat:
*
* true → cheat desligado (valores padrão, DefaultMarkersValue = 2).
*
* false → cheat ligado (valores máximos, MaxMarkersValue = 6).
* 
* Quando você pressiona INSERT:
*
* Se o cheat estava desligado (Status == true), ele:
*
* Escreve os valores máximos (6).
*
* Depois inverte Status para false.
*
* Se o cheat estava ligado (Status == false), ele:
*
* Escreve os valores padrão (2).
*
* Depois inverte Status para true.
* 
* /////////////////////////////////////////////////////////////////////////////////////////////////////
* 
* Primeira vez que aperta INSERT
*
* Status == true
*
* newValue = MaxMarkersValue (6)
*
* Cheat liga → escreve 6.
*
* Status vira false.
*
* Segunda vez que aperta INSERT
*
* Status == false
*
* newValue = DefaultMarkersValue (2)
*
* Cheat desliga → escreve 2.
*
* Status vira true.
*
*/