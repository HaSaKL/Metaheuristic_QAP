#ifndef QAPSwapNeighborhood_H
#define QAPSwapNeighborhood_H

#include <mo>
#include <QAP.h>
#include <QAPSwapNeighbor.h>
#include <neighborhood/moNeighborhood.h>

class QAPSwapNeighborhood : public moNeighborhood<QAPSwapNeighbor>{
private:
	// A pair which represents a Swap-Operation
	std::pair<unsigned int, unsigned int> indices;
	
public:

	bool hasNeighbor(QAP_Problem & _solution) {
		// Swap is always possible, if there are more then two locations
		return (_solution.getProbSize() > 1);
	}
	
	void init(QAP_Problem & _solution, QAPSwapNeighbor & _current) {
		indices.first = 0;
		indices.second = 1;
		_current.setIndices(0, 1);
	}

	void next(QAP_Problem & _solution, QAPSwapNeighbor & _current) {
		if (indices.second == _solution.getProbSize()-1){
			indices.first++;
			indices.second = indices.first+1;
		}
		else {
			indices.second++;
		}	
		_current.setIndices(indices.first, indices.second);
	}

	bool cont(QAP_Problem & _solution) {
		return !((indices.first == (_solution.getProbSize()-2)) && (indices.second == (_solution.getProbSize()-1)));
	}

	std::string className() const {
		return "QAPSwapNeighborhood";
	}
};

#endif