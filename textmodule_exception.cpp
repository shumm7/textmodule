#include <exception>
#include <iostream>

void throw_invalid_argument() {
	throw std::invalid_argument("textmodule: invalid argument");
}