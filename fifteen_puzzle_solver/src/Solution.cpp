#include "pch.h"
#include "Solution.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <time.h>


Solution::Solution(char* fileOutput, char* nameFileAdditionalInformation)
	:output{fileOutput}, AdditionalInformation{ nameFileAdditionalInformation }
{
	//fileSolution.open(output, std::ios::out);
	//fileAdditionalInformation.open(AdditionalInformation, std::ios::out);
	length_of_the_solution_found = 0;
	number_of_visited_states = 0;
	number_of_processed_states = 0;
	maximum_depth_of_recursion_achieved = 0;
	time_duration_of_process = std::chrono::milliseconds::zero();
}


Solution::Solution(char * fileInput, char * fileOutput, char * nameFileAdditionalInformation)
    :output{ fileOutput }, AdditionalInformation{ nameFileAdditionalInformation }, fileInput{ fileInput }
{
    //fileSolution.open(output, std::ios::out);
    //fileAdditionalInformation.open(AdditionalInformation, std::ios::out);
    length_of_the_solution_found = 0;
    number_of_visited_states = 0;
    number_of_processed_states = 0;
    maximum_depth_of_recursion_achieved = 0;
    time_duration_of_process = std::chrono::milliseconds::zero();
}


void Solution::open(void)
{
	fileSolution.open(output, std::ios::out);
	fileAdditionalInformation.open(AdditionalInformation, std::ios::out);
}


void Solution::close()
{
	fileSolution.close();
	fileAdditionalInformation.close();
}


Solution::~Solution()
{
	//fileSolution.close();
	//fileAdditionalInformation.close();
}

void Solution::save()
{
	
	if (fileSolution.is_open())
	{
		fileSolution << length_of_the_solution_found ;
		if (length_of_the_solution_found >= 0)
		{
			fileSolution << std::endl;
			fileSolution << solution;
		}
	}

	if (fileAdditionalInformation.is_open())
	{
		fileAdditionalInformation << length_of_the_solution_found << std::endl;
		fileAdditionalInformation << number_of_visited_states << std::endl;
		fileAdditionalInformation << number_of_processed_states << std::endl;
		fileAdditionalInformation << maximum_depth_of_recursion_achieved << std::endl;
		// teraz podaje w sekoundach bo przeliczam mili na sekundy
		//double czas = time_duration_of_process.count();
		//czas /= 1000.0;
		fileAdditionalInformation << std::setprecision(3) << std::fixed << time_duration_of_process.count(); // 1000.0 << std::endl;	// TODO czy tak czy zmieniac by bylo do 3 mejsc po przecinku jak w tresci
		fileAdditionalInformation << std::endl;

		//fileAdditionalInformation << std::chrono::duration_cast<std::chrono::seconds>(time_duration_of_process).count();

	}
	else throw "blad otwarcia";


}


