#include "pch.h"
#include "Solution.h"


Solution::Solution(char* fileOutput, char* nameFileAdditionalInformation)
	:output{fileOutput}, AdditionalInformation{ nameFileAdditionalInformation }
{
	fileSolution.open(output);
	fileAdditionalInformation.open(AdditionalInformation);
}


Solution::~Solution()
{
	fileSolution.close();
	fileAdditionalInformation.close();
}
