#include <fstream>
#include <iostream>

#include "aStar.hpp"
#include "Graph.hpp"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        throw std::invalid_argument("Two input files expected!\n");
    }

    std::ifstream isCost(argv[1]);
    std::ifstream isHeuristic(argv[2]);

    if(isCost.good() && isHeuristic.good())
    {
		srand(time(nullptr));
		
        IA::Graph G;
        G.read(isCost, isHeuristic);

        isCost.close();
        isHeuristic.close();

        IA::aStar A(G);
        int startNode, goalNode;

        std::cout << "\tA-Star Search Algorithm\n";
        std::cout << "Choose initial Node: ";
        std::cin >> startNode;
        std::cout << "Choose final Node: ";
        std::cin >> goalNode;

        if(startNode <= 0 || startNode > G.vertex() || goalNode <= 0 || goalNode > G.vertex())
        {
            throw std::invalid_argument("Invalid Node ID!");
        }
        
		A.search(startNode - 1, goalNode - 1);
		std::cout << std::endl << A << std::endl;
    }
    else
    {
        throw std::invalid_argument("Unable to open files!\n");
    }

    return 0;
}
