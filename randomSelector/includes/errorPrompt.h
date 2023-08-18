#ifndef _ERROR_PROMPT_H_
#define _ERROR_PROMPT_H_
#include <string>

using namespace std;

class CErrorPrompt
{
private:
	void gotoxy(int, int);
	void show();
public:
	CErrorPrompt(string);
};
#endif // !_ERROR_PROMPT_H_
