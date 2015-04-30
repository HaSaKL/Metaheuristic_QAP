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
		
		
		// load problem
		QAP_Problem p(PROBLEM_FILE);
		// defini evaluation functions
		QAPEval<QAP_Problem> problem_eval;
		// initialize problem randomly
		p.RandomInit();
		// evaluate random solution
		problem_eval(p);
		
		p.printSolution();
		std::cout << "Initial Fitness: " << p.fitness() << std::endl << std::endl;
		
		
		// define Neighborhood and a Neighbor
		QAPSwapNeighbor n1;
		QAPSwapNeighborhood nh;
		
		// initialize neighborhood
		nh.init(p, n1);
		
		std::cout << "First possible Swap: ";
		n1.print();
		
		
		// initialize Incremental Evaluation
		QAPSwapIncrEval neighbor_eval(p);
		
		// calculate new fitness with incremental evaluation
		neighbor_eval(p, n1);
		std::cout << "New Fitness should be: " << n1 << std::endl << std::endl;
		
		
		std::cout << "Performing Swap ........" << std::endl;
		// do the swap
		n1.move(p);
	
		// calculate doing full Evla
		problem_eval(p);
		p.printSolution();
		std::cout << "New Fitness is: " << p.fitness() << std::endl << std::endl;
		
		
        make_help(parser);
	}
	
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}