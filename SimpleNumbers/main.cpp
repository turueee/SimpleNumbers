#include <iostream>
#include <limits>
#include <fstream>
#include <chrono>
#include <iomanip>

#include <cstdint>

#if defined(_MSC_VER)
#include <intrin.h>
#pragma intrinsic(__rdtsc)
#define rdtsc __rdtsc
#else
#include <x86intrin.h>
#define rdtsc __rdtsc
#endif


#include <random>
#include <vector>
#include <unordered_set>

std::vector<unsigned long long> GenerateUniqueReservoir(unsigned long long n) {
	unsigned long long k = 20;
	if (n < k) k = n;

	std::vector<unsigned long long> reservoir(k);
	std::random_device rd;
	std::mt19937_64 gen(rd());

	for (unsigned long long i = 0; i < k; ++i) {
		reservoir[i] = i + 1;
	}

	for (unsigned long long i = k + 1; i <= n; ++i) {
		std::uniform_int_distribution<unsigned long long> dist(0, i - 1);
		unsigned long long j = dist(gen);
		if (j < k) {
			reservoir[j] = i;
		}
	}

	return reservoir;
}

bool IsSimpleExhaustiveSearchAlgorithm(unsigned long long num)
{
	unsigned long long i = 2;
	while (i * i <= num)
	{
		if (num % i == 0)
			return false;
		++i;
	}
	return true;
}

unsigned long long ModExp(unsigned long long os, unsigned long long pow, unsigned long long divide)
{
	if (pow == 0)
		return static_cast<unsigned long long>(1);
	unsigned long long z = ModExp(os, pow / 2, divide);
	if ((pow & 1) == 0)
		return (z*z)%divide;
	else
		return (os * z * z) % divide;
}

bool IsSimpleFermaAlgorithm(unsigned long long num)
{
	if (num < 21)
	{
		for (size_t i = 2; i < num; ++i)
			if (ModExp(i, num - 1, num) != 1)
				return false;
		return true;
	}
	else
	{
		for (size_t i = 2; i < 30; ++i)
			if (ModExp(i, num - 1, num) != 1)
				return false;
		return true;
	}
}

int main()
{
	std::cout << IsSimpleFermaAlgorithm(3828001);
	/*
	unsigned long long y = 1000;
	std::ifstream infile("SimpleNumbersFromMillionTillBillion.txt");
	std::ofstream outfile("SimpleNumbersFromMillionTillBillionExhaustiveSearchAlgorithm.txt");
	//std::ifstream infile("SimpleNumbersFromTenTillMillion.txt");
	//std::ofstream outfile("SimpleNumbersFromTenTillMillionExhaustiveSearchAlgorithm.txt");
	if (infile.is_open() && outfile.is_open())
	{
		for (size_t i = 0; i < 100; ++i)
		{
			unsigned long long num;
			infile >> num;
			auto start = std::chrono::high_resolution_clock::now();
			IsSimpleExhaustiveSearchAlgorithm(num);
			auto end = std::chrono::high_resolution_clock::now();
			std::cout << num << std::endl;
			std::chrono::duration<double> elapsed = end - start;
			double seconds = elapsed.count();
			if (!IsSimpleExhaustiveSearchAlgorithm(num))
				outfile << "Warning ";
			outfile<<num<<' ' << IsSimpleExhaustiveSearchAlgorithm(num) << ' ';
			outfile << std::fixed << std::setprecision(6)<< (seconds) << std::endl;
		}
	}
	*/
}