#include "main.h"

std::string Util::readTextFile(const std::string relativePath)
{
	// File input stream
	std::ifstream file(relativePath);

	// Use string constructor to read file into string
	std::string fileAsString((std::istreambuf_iterator<char>(file)),
							  std::istreambuf_iterator<char>());

	return fileAsString;
}