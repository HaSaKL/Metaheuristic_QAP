#ifndef QAPSwapNeighbor_H
#define QAPSwapNeighbor_H

#include <QAP.h>
#include <neighborhood/moNeighbor.h>

// A very basic Neighbor for the QAP_Problem, just consiting of a single
// switch of to Solution Elements, which are represented
// by a std::pair 

class QAPSwapNeighbor: public moNeighbor<QAP_Problem, typename QAP_Problem::Fitness> {
	
private:
	// A pair which represents the desired SwapOperation
	// which makes up the Neighbor
	std::pair<unsigned int, unsigned int> indices;
	
public:
	// realise the move
	void move(QAP_Problem & _solution) {
		//FIXME: Can this be realized using std::swap?
		std::swap(_solution[indices.first], _solution[indices.second]);
		_solution.invalidate();
	}
	
	void setIndices(unsigned int _first, unsigned int _second) {
		indices.first = _first;
		indices.second = _second;
	}
	
	void getIndicies(unsigned int & _first, unsigned int & _second) {
		_first = indices.first;
		_second = indices.second;
	}
	
	bool equals(QAPSwapNeighbor & _neighbor) {
		unsigned first, second;
		_neighbor.getIndicies(first, second);
		
		bool res;
		res = ( ((indices.first == first) && (indices.second == second)) || ((indices.first == second) && (indices.second == first)) );
		
		return res;
	}
	
	void print() {
		std::cout << "[" << indices.first << ", " << indices.second << "]" << std::endl;
	}
};

#endif
