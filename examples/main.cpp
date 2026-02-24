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

	if (!testEuler6())
	{
		std::printf("Euler6 tests failed!------------------------\n\n");
	}

	if (!testRotor())
	{
		std::printf("Rotor tests failed!-------------------------\n\n");
	}

	//TODO
	// Spherical-to-Cartesian conversion
	// Cartesian-to-Spherical conversion

	return 0;
}
