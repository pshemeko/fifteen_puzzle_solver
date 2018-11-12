#include "pch.h"
#include "Solution.h"


Solution::Solution(char* fileOutput, char* nameFileAdditionalInformation)
	:output{fileOutput}, AdditionalInformation{ nameFileAdditionalInformation }
{
	fileSolution.open(output);
	fileAdditionalInformation.open(AdditionalInformation);
	length_of_the_solution_found = 0;
	number_of_visited_states = 0;
	number_of_processed_states = 0;
	maximum_depth_of_recursion_achieved = 0;
	time_duration_of_process = std::chrono::milliseconds::zero();
}


Solution::~Solution()
{
	fileSolution.close();
	fileAdditionalInformation.close();
}
