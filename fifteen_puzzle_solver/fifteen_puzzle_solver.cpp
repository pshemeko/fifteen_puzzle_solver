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
    std::cout << "Hello World!\n"; 

	puzzleDataType tab[] = { 1,2,3,4 };
	std::vector<puzzleDataType> state(tab, tab + sizeof(tab) / sizeof(puzzleDataType));
	puzzleDataType x = 2;
	puzzleDataType y = 2;
	Puzzle puz(x, y, std::vector<puzzleDataType>{1, 2, 3, 0});


	std::cout<<(int)puz.IsOnFinishState() <<"\thash:" << puz.hasHFunction() <<"\t";

	Puzzle puz1(x, y, std::vector<puzzleDataType>{2, 1, 3, 0});
	std::cout << (int)puz1.IsOnFinishState() << "\thash:" << puz1.hasHFunction() << "\t";

	Puzzle puz2(3, 3, std::vector<puzzleDataType>{1, 2, 3, 4, 5, 6, 7, 8, 0});
	std::cout << (int)puz2.IsOnFinishState() << "\thash:" << puz2.hasHFunction() << "\t";

	for (auto el : state)
	{
		std::cout << (int)el << "\t";
	}

    std::cout << std::endl << std::endl;

    Puzzle puzee(4, 3, { 1,2,3,4,5,6, 0,7,8,9,10,11 });
    std::cout << puzee<< std::endl <<"Pozycja zera: " <<puzee.zeroPosition;

    std::cout << std::endl << "czy sie ruszylo:" << (int)puzee.MoveZero(Moves::Up);
    std::cout << puzee << std::endl << "Pozycja zera: " << puzee.zeroPosition;
    std::cout << std::endl << "czy sie ruszylo:" << (int)puzee.MoveZero(Moves::Up);
    std::cout << puzee << std::endl << "Pozycja zera: " << puzee.zeroPosition;
    std::cout << std::endl<<"czy sie ruszylo:"<< (int)puzee.MoveZero(Moves::Up);
    std::cout << puzee << std::endl << "Pozycja zera: " << puzee.zeroPosition;
    std::cout << std::endl;

    std::cout << "Parametry sa: " << argc <<" Postaci: " << argv[0] << std::endl  ;

	Contex conteks;
	//char * aa = "aa.txt";
	conteks.set(const_cast<char *>("4x4_02_00001.txt"));
	
		Puzzle ale = Puzzle(*conteks.GetStartPuzzle().get());

		std::cout <<"\ndrukuje puzla z contex\n" << ale;
   





	// ************************* od tad tak ma wygladac main: **********************************
        std::cout << "\n teraz dziala run::::::::::::::::::::::::";
		Contex con;
        //con.set(const_cast<char *>("4x4_02_00001.txt"));
		//Configuator conf(argc, argv,con);
        Configuator conf(con);
        conf.setTest();
        Methods *met = nullptr;
        met = conf.returnMethod();	// to wrzucic 
		met->run();
       
		system("pause");
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
