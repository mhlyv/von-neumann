#include <cctype>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "config.h"
#include "memory/memory.h"
#include "vector/vector.hpp"

namespace args {

static void ParseMemorySize(int argc, const char **argv) {
	std::size_t memory_size = 0;

	if (argc < 2) {
		throw std::invalid_argument("Number expected after --memory");
	}

	std::stringstream sstream(argv[1]);
	sstream >> memory_size;

	if (memory_size == 0) {
		throw std::invalid_argument("0 is an invalid memory size");
	} else {
		config::memory_size = memory_size;
	}
}

static void TryFileName(const char *filename) {
	std::ifstream file(filename);

	if (file.good()) {
		config::filename = filename;
	} else {
		throw std::invalid_argument("Invalid file name");
	}
}

static void ParseArgs(int argc, const char **argv) {
	for (int i = 1; i < argc; i++) {
		if (std::strcmp(argv[i], "--verbose") == 0) {
			config::verbose = true;
		} else if (std::strcmp(argv[i], "--memory") == 0) {
			ParseMemorySize(argc - i, argv + i);
			i++; // Skip the number
		} else if (config::filename == nullptr) {
			// This should be the last option after all other flags
			TryFileName(argv[i]);
		} else {
			// If the argument falls through, it's invalid
			if (config::verbose) {
				std::cerr << "Invalid argument: " << argv[i] << std::endl;
			}
			throw std::invalid_argument("Invalid argument");
		}
	}

	if (config::filename == nullptr) {
		throw std::invalid_argument("No file name provided");
	}
}

}

int main(const int argc, const char **argv) {
	args::ParseArgs(argc, argv);
	if (config::verbose) {
		config::PrintConfig();
	}

	return 0;
}
