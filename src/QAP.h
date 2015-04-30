/* The Class QAP_Problem defines the representation of a
 * Quadratic Assignment Problem (QAP), as a permutation of
 * integers from 1..n 
 * This is a MINIMIZATION problem.
 * The class also provides basic functions like:
 * 
 * - reading the Problem to set Problem Parameters
 * - getting Problem Parameters
 * - Evaluation of Problems' fitness value
 * - Random Initialization of solution
 * 
 * The fitness-setter and printing are inherited from EO-class
 * 
 */

#ifndef QAP_H
#define QAP_H

#include <eo>

class QAP_Problem : public EO<eoMinimizingFitness>
{
	// FIXME: Could be easier, if instead of array and pointers a standard container (array, vector) would be used
	// this would reduce the code for copying the Matrices for a copy or assignment significantly
private:
	// problem dimension respec. number of variables
	int n;
	
	// distance matrix A 
	// uses pointer since size is unknown before init
	int ** A;
	
	// intensity matrix B
	// uses pointer since size is unknown before init
	int ** B;		
	
	
public:
	
	// define a solution as array, which will hold assignment
	// as permutation of location number
	int* solution;
	
	// Constructor
	QAP_Problem(std::string & _fileData) {
		
		// read the Problem Data from a given File
		// Note: File sturucture from QAPLibs is:
		// 		 first line: matrix dimension n
		//		 second line: empty
		//       third line to n+3 th line: matirx A
		//		 n+4 th line: empty
		// 	     n+5 th to 2n+5 th line: matrix B
		
		// open file -> name in _fileData, mode: input operations
		std::fstream file(_fileData.c_str(), std::ios::in);
		
		// Check if opening file was successful
		if (!file) {
			std::string str = "QAP_Problem: Problems with file [" + _fileData + "]";
			throw std::runtime_error(str);
		}
		
		// read problem dimensions
		file >> n;
		
		// create empty, new solution vector
		solution = new int[n];
		
		// create matrices A and B according to problem size
		A = new int *[n];
		B = new int *[n];
		for (unsigned i=0; i < n; i++) {
			A[i] = new int [n];
			B[i] = new int [n];
		}
		
		// read matrix A
		for(unsigned i=0; i < n; i++)
		{
			//row-wise, create a new array for the row
			A[i] = new int[n];
			for(unsigned j = 0; j < n; j++)
			{
				// in each row: read each element
				file >> A[i][j];
			}
		}
		
		// read matrix B
		for(unsigned i=0; i < n; i++)
		{
			//row-wise, create a new array for the row
			B[i] = new int[n];
			for(unsigned j = 0; j < n; j++)
			{
				// in each row: read each element
				file >> B[i][j];
			}
		}
		
		// close file after reading
		file.close();
	}
	
	// copy constructor
	// if Problem class is called with existing class-object
	QAP_Problem(QAP_Problem & _problem) {

		// get problem size
		n = _problem.getProbSize();
		
		// copy solution
		solution = new int[n];
		for (int i = 0; i <n; i++) {
			solution[i] = _problem.solution[i];
		}
		
		/*
		// create and copy matrices A and B
		A = new int *[n];
		B = new int *[n];
		for (unsigned i=0; i < n; i++) {
			A[i] = new int [n];
			B[i] = new int [n];
			for (unsigned j=0; j < n; j++) {
				A[i][j] = _problem.getA()[i][j];
				B[i][j] = _problem.getB()[i][j];
			}
		}
		*/
		
		A = _problem.getA();
		B = _problem.getB();
		
		// if copied solution is valid; use corresponding fitness value
		if (!_problem.invalid()) {
			fitness(_problem.fitness());
		}
	}
	
	// destructor --> Burn after using
	~QAP_Problem() {
		delete[] solution;
		
		unsigned i;
		
		// delete matrix A
		if(A != NULL) {
			for(i=0; i < n; i++) {
				delete[] A[i];
			}
			delete[]A;
		}
		
		// delete matrix B
		if(B != NULL) {
			for(i=0; i < n; i++) {
				delete[] B[i];
			}
			delete[]B;
		}
	}
	
	// copy assignemnt Operator
	// if existing object is assigend to value of current object
	void operator= (QAP_Problem & _problem) {
		// delete old values
		delete[] solution;
		
		unsigned i;
		
		// delete matrix A
		if(A != NULL) {
			for(i=0; i < n; i++) {
				delete[] A[i];
			}
			delete[]A;
		}
		
		// delete matrix B
		if(B != NULL) {
			for(i=0; i < n; i++) {
				delete[] B[i];
			}
			delete[]B;
		}
		
		// and copy new values
		// get problem size
		n = _problem.getProbSize();
		
		// copy solution
		solution = new int[n];
		for (int i = 0; i <n; i++) {
			solution[i] = _problem.solution[i];
		}
		
		// create and copy matrices A and B
		A = new int *[n];
		B = new int *[n];
		for (unsigned i=0; i < n; i++) {
			A[i] = new int [n];
			B[i] = new int [n];
			for (unsigned j=0; j < n; j++) {
				A[i][j] = _problem.getA()[i][j];
				B[i][j] = _problem.getB()[i][j];
			}
		}
		
		// if copied solution is valid; use corresponding fitness value
		if (!_problem.invalid()) {
			fitness(_problem.fitness());
		}
	}
	
	// subscripting operator acesses solution array, needed to copy solution
	int& operator[] (unsigned i) {
		return solution[i];
	}
	
	// get the matrix A (distance matrix)
	int** getA() {
		return A;
	}
	
	// get the matrix B (intensity matrix)
	int** getB() {
		return B;
	}
	
	// get the problem dimension
	int getProbSize() {
		return n;
	}
	
	// Method to print Solution Array
	void printSolution() { 
		for (int i = 0; i < n; i++) {
			std::cout << solution[i] << "-";
		}
		std::cout << std::endl;
	}
	
	// full Evaluation of the problem for a given solution,
	// which is the purpose of the entire class
	void fullEvaluation() {
		int costs = 0;
		
		// calculate costs
		for (unsigned i = 0; i < n; i++) {
			for (unsigned j = 0; j < n; j++) {
				costs += A[i][j] * B[solution[i]][solution[j]];
			}
		}
		
		// set costs as fitness
		fitness(costs);
	}

	// randomly Initialize the solution array of the problem
	void RandomInit() {
		
		// create random solution
		int random, temp;
		
		// constuct solution
		for (unsigned int i = 0; i < n; i++) {
			solution[i] = i;
		}
		
		// randomize solution
		for (unsigned int i = 0; i < n; i++) {
			random = rng.rand() % (n-i) + i;
			std::swap(solution[i], solution[random]);
		}
		
		// evaluate the solution
		//fullEvaluation();
	}
};

#endif