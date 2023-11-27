#ifndef _EDIT_LIST_BASE_H_
#define _EDIT_LIST_BASE_H_
#include <string>
#include "interfaceBase.h"

using namespace std;

constexpr int FIRST_LINE = 3;
constexpr int NAME_LINE = 3;
constexpr int CONFIRM_LINE = 4;
constexpr int ARROW_OFFSET = 2;
constexpr int INPUT_OFFSET = 16;
constexpr int PROMPT_OFFSET = 12;

class CEditListBase : public CInterfaceBase
{
private:
	void addCsv();
public:
	CEditListBase();
	virtual void up();
	virtual void down() {}
	virtual void enter(int &, int &) {}
protected:
	int line;
	string name;
	void moveCursor(int);
	void setName();
	void confirm(int &, int &, bool);
};
#endif // !_EDIT_LIST_BASE_H_
