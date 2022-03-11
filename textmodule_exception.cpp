#include <exception>
#include <iostream>

void throw_invalid_argument() {
	throw std::invalid_argument("textmodule: invalid argument");
}

void throw_invalid_argument(const char* what) {
	throw std::invalid_argument(what);
}