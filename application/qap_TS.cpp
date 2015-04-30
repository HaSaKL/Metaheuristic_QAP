#include <eo>
#include <QAP.h>
#include <QAPEval.h>
#include <QAPInit.h>
#include <QAPSwapNeighbor.h>
#include <QAPSwapNeighborhood.h>
#include <QAPSwapIncrEval.h>

//checks for help demand and writes the status file and make_help
void make_help(eoParser & _parser);


//Main Program
int main(int argc, char* argv[])
{
	try 
	{
		std::cout << "Metaheuristic for QAP compiled at " << __DATE__ << " " << __TIME__ << std::endl; 
		
		// Read and set user parameters
		// Initialize parser
		eoParser parser(argc, argv);
		
		// define parsed objects --> What parameters can be parsed? List of Parameters here
		std::string PROBLEM_FILE = parser.createParam(
				std::string("chr12a.dat"),
				"ProblemFile",
				"Path of the problem file",
				'p',
				"Param"
			).value();
			
		std::cout << "Using problem definition from: " << PROBLEM_FILE << std::endl;
		std::cout << " - - - - - - - - - - - - - - - - - - - "<< std::endl << std::endl;
		
		
		// DEFINE PROBLEM AND NEIGHBORHOOD
		// load problem
		QAP_Problem p(PROBLEM_FILE);
		
		// definie full evaluation function
		QAPEval problem_FullEval;
		
		// definie problem Initilizer
		QAPInit problem_Init;
		
		// initialize problem randomly and evaluate
		problem_Init(p);
		problem_FullEval(p);
		
		// define Swap Neighborhood with Neighbors and IncrEval
		QAPSwapNeighbor n1;
		QAPSwapNeighborhood nh;
		QAPSwapIncrEval problem_IncrEval(p);
		
		
		
		
		// Print Initial Solution
		p.printSolution();
		std::cout << "Initial Fitness: " << p.fitness() << std::endl << std::endl;
		
	
		// TABU SEARCH DEFINITION
		int TabuListSize = 20;
		int TimeLimit = 1;
		
		
		
		moTS <QAPSwapNeighbor> TabuSearch(nh, 
										  problem_FullEval, 
										  problem_IncrEval, 
										  TimeLimit,
										  TabuListSize);
		
		
		// do Tabu Search
		std::cout << "Performing Tabu Search .........." << std::endl << std::endl;
		
		TabuSearch(p);
		
		p.printSolution();
		std::cout << "Final Solution: " << p.fitness() << std::endl;
		
		
        make_help(parser);
	}
	
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}