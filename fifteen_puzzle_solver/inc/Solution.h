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

	int length_of_the_solution_found;	// d³ugoœæ znaezionego rozwiazania
	size_t number_of_visited_states;		//liczba stanów odwiedzonych
	size_t number_of_processed_states;		//liczba stanów przetworzonych
	int maximum_depth_of_recursion_achieved;	//maksymalna osi¹gniêta g³êbokoœæ rekursji

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

