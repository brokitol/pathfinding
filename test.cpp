#include <cstdlib>
#include <iostream>
#include <random>

int main()
{
	std::minstd_rand0 g1 (10);

	for (int i = 0; i < 10 ; i++)
	{
		std::cout << g1() << std::endl;
	}
}
