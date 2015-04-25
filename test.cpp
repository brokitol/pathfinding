#include <cstdlib>
#include <iostream>

int main()
{
	std::srand(10);
	for (int i = 0; i < 10 ; i++)
	{
		std::cout << std::rand() << std::endl;
	}
}
