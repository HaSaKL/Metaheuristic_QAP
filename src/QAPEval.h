#ifndef QAPEVAL_H
#define QAPEVAL_H

#include <QAP.h>
#include <eoEvalFunc.h>

// use template for Problem type (EOT), so other 
// objectives besides minimization are also possible
class QAPEval : public eoEvalFunc <QAP_Problem>
{
		
public:
	void operator() (QAP_Problem & _problem)
	{
		_problem.fullEvaluation();
	}
};

#endif