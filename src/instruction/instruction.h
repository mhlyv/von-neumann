#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "memory/memory.h"

namespace instruction {

class Instruction : public MemoryElement {
private:
public:
	virtual ~Instruction();
};

}

#endif // __INSTRUCTION_H__
