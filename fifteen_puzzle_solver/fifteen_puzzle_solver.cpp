
#include "pch.h"
#include <iostream>
#include <vector>
#include "Puzzle.h"
#include "Contex.h"
#include "Configuator.h"

int main(int argc, char** argv)
{

		Contex con;
		Configuator conf(argc, argv,con);
        //conf.setTest();
		conf.set();
        Methods *met = conf.returnMethod();	// tu wrzucic set()
		//Solution solu(argv[4], argv[5]);
        Solution solu(argv[3], argv[4], argv[5]);
		solu.open();
		met->run(solu);
		solu.close();

		//system("pause");
    return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
