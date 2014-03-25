/**
Helpful utilities. OS file helper functions etc
*/
#include "main.h"
#include <fstream>
#include <streambuf>

class Util
{
public:
	static std::string readTextFile(const std::string relativePath);
private:
};