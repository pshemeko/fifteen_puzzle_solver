// fifteen_puzzle_solver.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include "Puzzle.h"
#include "Contex.h"
#include "Configuator.h"

int main(int argc, char** argv)
{
    //std::cout << "Hello World!\n\n"; 

	//std::cout << "Liczba parametrow : " << argc << std::endl;
	//std::cout << "Nazwa programu : " << argv[0] << std::endl;
	//for (int i = 1; i < argc; ++i)
	//	std::cout << "Parametr nr " << i << ": " << argv[i] << std::endl;




	// ************************* od tad tak ma wygladac main: **********************************
    //    std::cout << "\n teraz dziala run::::::::::::::::::::::::";
		Contex con;
//		std::cout<<"jeden";
        //con.set(const_cast<char *>("4x4_02_00001.txt"));
		Configuator conf(argc, argv,con);
        //Configuator conf(con);
		
        //conf.setTest();
		conf.set();
        Methods *met = nullptr;
        met = conf.returnMethod();	// to wrzucic 
		
		//Solution solu(const_cast<char *>("jeden.txt"), const_cast<char *>("dwa.txt"));
		//Solution solu(argv[4], argv[5]);
        Solution solu(argv[3], argv[4], argv[5]);
		met->run(solu);
       
	//	system("pause");
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
