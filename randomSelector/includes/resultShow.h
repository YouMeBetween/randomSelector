#ifndef _RESULT_SHOW_H_
#define _RESULT_SHOW_H_
#include "interfaceBase.h"

using namespace std;

class CResultShow : public CInterfaceBase
{
private:
	void show();
public:
	CResultShow();
	virtual void up() {}
	virtual void down() {}
	virtual int enter();
};
#endif // !_RESULT_SHOW_H_
