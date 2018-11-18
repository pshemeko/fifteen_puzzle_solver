#pragma once
#include <fstream>
#include <time.h>
#include <chrono>
#include <string>

class Solution
{
public:
	char * output;
	char* AdditionalInformation;

	std::string solution; //ciag operatorow uzytych
	//parameter needed for program output

	size_t length_of_the_solution_found;	// d�ugo�� znaezionego rozwiazania
	size_t number_of_visited_states;		//liczba stan�w odwiedzonych
	size_t number_of_processed_states;		//liczba stan�w przetworzonych
	int maximum_depth_of_recursion_achieved;	//maksymalna osi�gni�ta g��boko�� rekursji

	std::chrono::milliseconds time_duration_of_process;	// czas trwania procesu oliczeniowego

	std::fstream fileSolution; // plik z rozwiazaniem
	std::fstream fileAdditionalInformation;
	Solution(char* fileOut, char* nameFileAdditionalInformation);
	~Solution();

	void save();	//TODO napisac zapisywanie tych danych do pliku
};

