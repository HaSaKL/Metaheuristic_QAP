#ifndef QAPEVAL_H
#define QAPEVAL_H

#include <QAP.h>
#include <eoEvalFunc.h>

// use template for Problem type (EOT), so other 
// objectives besides minimization are also possible
template< class EOT>
class QAPEval : public eoEvalFunc <EOT>
{
		
public:
	void operator() (EOT & _problem)
	{
		_problem.fullEvaluation();
	}
};

#endif