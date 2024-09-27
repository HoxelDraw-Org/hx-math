#include "main.h"

int main()
{
	if (!testVector())
	{
		std::printf("Vector tests failed!------------------------\n\n");
	}

	if (!testMatrix())
	{
		std::printf("Matrix tests failed!------------------------\n\n");
	}

	if (!testAABB())
	{
		std::printf("AABB tests failed!--------------------------\n\n");
	}

	if (!testRay())
	{
		std::printf("Ray tests failed!--------------------------\n\n");
	}
	
	if (!testMath())
	{
		std::printf("Math tests failed!--------------------------\n\n");
	}

	return 0;
}
