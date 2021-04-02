#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <cctype>
#include <iostream>

namespace config {

bool verbose = false;
const char *filename = NULL;
std::size_t memory_size(10000);

void PrintConfig() {
	std::cout << "Verbose: " << (verbose ? "true" : "false") << std::endl;
	std::cout << "Filename: " << filename << std::endl;
	std::cout << "Memory size: " << memory_size << std::endl;
}

}

#endif // __CONFIG_H__
