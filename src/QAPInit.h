#ifndef QAPINIT_h
#define QAPINIT_h
 
#include <QAP.h>
#include <eoInt.h>
 
// define initialization class, derive from eoInit
class QAPInit : public eoInit<QAP_Problem>
{
public:
	void operator() (QAP_Problem & _problem) {
		_problem.RandomInit();
	}
};
 
 
 #endif
