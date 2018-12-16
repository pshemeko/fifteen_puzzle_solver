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
    char* fileInput;

	std::string solution; //ciag operatorow uzytych

	int length_of_the_solution_found;	// d�ugo�� znaezionego rozwiazania
	size_t number_of_visited_states;		//liczba stan�w odwiedzonych
	size_t number_of_processed_states;		//liczba stan�w przetworzonych
	int maximum_depth_of_recursion_achieved;	//maksymalna osi�gni�ta g��boko�� rekursji

	std::chrono::duration<double, std::milli> time_duration_of_process;	// czas trwania procesu oliczeniowego

	std::fstream fileSolution; // plik z rozwiazaniem
	std::fstream fileAdditionalInformation;
	Solution(char* fileOut, char* nameFileAdditionalInformation);
    Solution(char* fileInput, char* fileOut, char* nameFileAdditionalInformation);
	~Solution();

	void save();
	void open(void);
	void close();

};

