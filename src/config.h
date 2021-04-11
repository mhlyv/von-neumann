#ifndef CONFIG_H
#define CONFIG_H

#include <cctype>
#include <iostream>

namespace config {

bool verbose = false;
const char *filename = nullptr;
std::size_t memory_size(10000);

void PrintConfig() {
	std::cout << "Verbose: " << (verbose ? "true" : "false") << std::endl;
	std::cout << "Filename: " << filename << std::endl;
	std::cout << "Memory size: " << memory_size << std::endl;
}

}

#endif // CONFIG_H
