#include "testAVLMap.h"

int main(void) {
	srand((unsigned int)time(NULL));
	testAVLMap testObj;
	testObj.comparePerformance();
	return(0);
}