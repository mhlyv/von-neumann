#include <stddef.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "machine/machine.h"

// read a number from command line args
static size_t get_size(int argc, const char **argv) {
	size_t size = 0;

	if (argc < 2) {
		throw std::invalid_argument("number expected after switch");
	}

	std::stringstream sstream(argv[1]);
	sstream >> size;

	if (size == 0) {
		throw std::invalid_argument("0 is an invalid number size");
	}

	return size;
}

int main(const int argc, const char **argv) {
	size_t memory_size = 1000;
	size_t n_registers = 10;
	const char *filename = nullptr;
	int exit_code = 0;

	// parse args
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--memory") == 0) {
			memory_size = get_size(argc - i, argv + i);
			i++; // Skip the number
		} else if (strcmp(argv[i], "--registers") == 0) {
			n_registers = get_size(argc - i, argv + i);
			i++; // Skip the number
		} else if (filename == nullptr) {
			// This should be the last option after all other flags
			std::ifstream file(argv[i]);
			if (file.good()) {
				filename = argv[i];
			} else {
				throw std::invalid_argument("Invalid file name");
			}
		} else {
			throw std::invalid_argument("Invalid argument");
		}
	}

	if (filename == nullptr) {
		throw std::invalid_argument("No file name provided");
	}

	try {
		// run program from file with parameters
		machine::Machine machine(memory_size, n_registers);
		machine.run(filename);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		exit_code = 1;
	}

	return exit_code;
}
