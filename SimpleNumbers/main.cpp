#include <iostream>
#include <limits>
#include <fstream>
#include <chrono>

bool IsSimpleExhaustiveSearchAlgorithm(unsigned long long num)
{
	unsigned long long i = 2;
	while (i * i <= num)
	{
		if (num % i == 0)
			return false;
		i += 2;
	}
	return true;
}

int main()
{
	unsigned long long y = 1000;
	//std::ifstream infile("SimpleNumbersFromMillionTillBillion.txt");
	//std::ofstream outfile("SimpleNumbersFromMillionTillBillionExhaustiveSearchAlgorithm.txt");
	std::ifstream infile("SimpleNumbersFromTenTillMillion.txt");
	std::ofstream outfile("SimpleNumbersFromTenTillMillionExhaustiveSearchAlgorithm.txt");
	if (infile.is_open() && outfile.is_open())
	{
		for (size_t i = 0; i < 100; ++i)
		{
			unsigned long long num;
			infile >> num;
			auto start = std::chrono::high_resolution_clock::now();
			IsSimpleExhaustiveSearchAlgorithm(num);
			auto end = std::chrono::high_resolution_clock::now();    
			std::chrono::duration<double> duration = end - start;
			outfile.precision(7);
			outfile << std::fixed;
			outfile << duration.count() << std::endl;
		}
	}
}