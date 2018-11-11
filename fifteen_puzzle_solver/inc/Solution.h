#pragma once
#include <fstream>
class Solution
{
	char * output;
	char* AdditionalInformation;
public:

	std::fstream fileSolution; // plik z rozwiazaniem
	std::fstream fileAdditionalInformation;
	Solution(char* fileOut, char* nameFileAdditionalInformation);
	~Solution();
};

