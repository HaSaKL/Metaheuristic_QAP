#ifndef QAPSwapIncrEval_H
#define QAPSwapIncrEval_H


#include <eval/moEval.h>
#include <QAP.h>
#include <QAPSwapNeighbor.h>

// This is also already realized in mo/problems/eval/moQAPIncrEval.h, copy to better understand what is happening
class QAPSwapIncrEval: public moEval<QAPSwapNeighbor> {
private:
	// values / pointers from Problem class
	int n;
	int ** A;
	int ** B;
	
public:
	typedef typename QAPSwapNeighbor::EOT EOT;
	//typedef typename Neighbor::EOT EOT;

	// default constructor -> get Problem values for Evaluation
	QAPSwapIncrEval(QAP_Problem & _problem) {
		n = _problem.getProbSize();
		A = _problem.getA();
		B = _problem.getB();
	}
	
	void operator() (EOT & _solution, QAPSwapNeighbor & _neighbor) {
		
		int delta;
		unsigned int k;
		
		unsigned int i;
		unsigned int j;
		
		_neighbor.getIndicies(i,j);
		
		delta = (A[i][i]-A[j][j])*(B[_solution[j]][_solution[j]]-B[_solution[i]][_solution[i]]) 
				+ (A[i][j]-A[j][i])*(B[_solution[j]][_solution[i]]-B[_solution[i]][_solution[j]]);
		
		for (k = 0; k < n; k++) {
			if (k != i && k != j) {
				delta = delta + 
						(A[k][i]-A[k][j])*(B[_solution[k]][_solution[j]]-B[_solution[k]][_solution[i]]) 
						+ (A[i][k]-A[j][k])*(B[_solution[j]][_solution[k]]-B[_solution[i]][_solution[k]]);
			}
		}
		
		_neighbor.fitness(_solution.fitness() + delta);
	}
};

#endif