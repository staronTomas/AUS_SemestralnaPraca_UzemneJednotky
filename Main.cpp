
#include <iostream>

#include "HlavnyProgram.h"
#include "structures/heap_monitor.h"

int main()
{
	initHeapMonitor();

	HlavnyProgam* program = new HlavnyProgam();

	program->spustiProgram();

	delete program;
	return 0;
}
