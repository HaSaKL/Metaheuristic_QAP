#include <eo>
#include <QAP.h>
#include <QAPEval.h>
#include <QAPInit.h>
#include <QAPSwapNeighbor.h>
#include <QAPSwapNeighborhood.h>

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
		// defini evaluation function
		QAPEval problem_eval;
		// initialize problem randomly
		p.RandomInit();
		// evaluate random solution
		problem_eval(p);
		
		p.printSolution();
		std::cout << "Initial Fitness: " << p.fitness() << std::endl << std::endl;
		
		
		// define Neighborhood and a Neighbor
		QAPSwapNeighbor<QAP_Problem> n1;
		QAPSwapNeighborhood<QAP_Problem> nh;
		
		// initialize neighborhood
		nh.init(p, n1);
		
		std::cout << "First possible Swap: ";
		n1.print();
		
		
		// do the swap
		n1.move(p);
		//FIXME: Now define an incremental evaluator!
		// this way not all swps need to be made before evaluation
		// if nothing els works use FullEvalCopy...
		
		problem_eval(p);
		p.printSolution();
		std::cout << "New Fitness : " << p.fitness() << std::endl << std::endl;
		
		nh.next(p,n1);
		std::cout << "Next possible Swap: ";
		n1.print();
		
		n1.move(p);
		problem_eval(p);
		p.printSolution();
		std::cout << "New Fitness : " << p.fitness() << std::endl << std::endl;
		
		// After all parameters are read, offer help if needed
        make_help(parser);
	}
	
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}