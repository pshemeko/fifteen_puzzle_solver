#pragma once
#include "Methods.h"
class MethodDFS : public Methods
{
public:
    std::vector<Moves> order; // np. LRUD, LURD kolejnosc przeszukian

    MethodDFS(Contex contex, char* fileOutputSolution, char* fileAdditionalInformation, std::vector<Moves> orderEnum);
    virtual ~MethodDFS();
    auto run(Solution &sol) -> void;
};

