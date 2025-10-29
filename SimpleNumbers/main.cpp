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
		for (size_t i = 2; i < 5; ++i)
			if (ModExp(i, num - 1, num) != 1)
				return false;
		return true;
	}
	else
	{
		for (size_t i = 2; i < 12; ++i)
			if (ModExp(i, num - 1, num) != 1)
				return false;
		return true;
	}
}

bool IsSimpleRabinMillerAlgorithm(unsigned long long num, int iterations = 5)
{
	if (num < 2) return false;
	if (num == 2) return true;
	if (num % 2 == 0) return false;

	unsigned long long u = num - 1;
	size_t t = 0;
	while ((u & 1) == 0)
	{
		u >>= 1;
		t++;
	}

	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<unsigned long long> dis(2, num - 2);

	for (int iter = 0; iter < iterations; ++iter)
	{
		unsigned long long a = dis(gen);
		unsigned long long x = ModExp(a, u, num);

		if (x == 1) continue;

		bool found_minus_one = false;
		for (size_t i = 0; i < t; ++i)
		{
			if (x == num - 1)
			{
				found_minus_one = true;
				break;
			}
			if (x == 1) return false;

			x = ModExp(x, 2, num);
		}

		if (!found_minus_one) return false;
	}

	return true;
}

int main()
{
	//Алгоритм перебором
	//std::ifstream infile("SimpleNumbersFromTenTillMillion.txt");
	//std::ofstream outfile("SimpleNumbersFromTenTillMillionExhaustiveSearchAlgorithm.txt");
	//std::ifstream infile("SimpleNumbersFromMillionTillBillion.txt");
	//std::ofstream outfile("SimpleNumbersFromMillionTillBillionExhaustiveSearchAlgorithm.txt");
	//std::ifstream infile("SimpleNumbersFromBillionTillSixtilion.txt");
	//std::ofstream outfile("SimpleNumbersFromBillionTillSixtilionExhaustiveSearchAlgorithm.txt");
	// Алгоритм Ферма
	//std::ifstream infile("SimpleNumbersFromTenTillMillion.txt");
	//std::ofstream outfile("SimpleNumbersFromTenTillMillionFermaAlgorithm.txt");
	//std::ifstream infile("SimpleNumbersFromMillionTillBillion.txt");
	//std::ofstream outfile("SimpleNumbersFromMillionTillBillionFermaAlgorithm.txt");
	//std::ifstream infile("SimpleNumbersFromBillionTillSixtilion.txt");
	//std::ofstream outfile("SimpleNumbersFromBillionTillSixtilionFermaAlgorithm.txt");
	//Алгоритм Рабина-Миллера
	//std::ifstream infile("SimpleNumbersFromTenTillMillion.txt");
	//std::ofstream outfile("SimpleNumbersFromTenTillMillionRabinMillerAlgorithm.txt");
	//std::ifstream infile("SimpleNumbersFromMillionTillBillion.txt");
	//std::ofstream outfile("SimpleNumbersFromMillionTillBillionRabinMillerAlgorithm.txt");
	std::ifstream infile("SimpleNumbersFromBillionTillSixtilion.txt");
	std::ofstream outfile("SimpleNumbersFromBillionTillSixtilionRabinMillerAlgorithm.txt");
	if (infile.is_open() && outfile.is_open())
	{
		for (size_t i = 0; i < 100; ++i)
		{
			unsigned long long num;
			infile >> num;
			auto start = std::chrono::high_resolution_clock::now();
			//IsSimpleExhaustiveSearchAlgorithm(num);
			//IsSimpleFermaAlgorithm(num);
			IsSimpleRabinMillerAlgorithm(num);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = end - start;
			double seconds = elapsed.count();
			if (!IsSimpleExhaustiveSearchAlgorithm(num))
				outfile << "Warning ";
			//outfile<<num<<' ' << IsSimpleExhaustiveSearchAlgorithm(num) << ' ';
			//outfile << std::fixed << std::setprecision(15)<< (seconds) << std::endl;
			//outfile << num << ' ' << IsSimpleFermaAlgorithm(num) << ' ';
			//outfile << std::fixed << std::setprecision(15) << (seconds) << std::endl;
			outfile << num << ' ' << IsSimpleRabinMillerAlgorithm(num) << ' ';
			outfile << std::fixed << std::setprecision(15) << (seconds) << std::endl;
		}
	}
}

/*
int main()
{
	std::ofstream outfile("SimpleNumbersFromBillionTillSixtilion.txt");
	int k = 0;
	int m = 9;

	for (unsigned long long i = 1000000000;m<19;++i)
		if (IsSimpleExhaustiveSearchAlgorithm(i))
		{
			outfile << i << '\n';
			std::cout << i<<'\n';
			k++;
			if (k > 10)
			{
				m++;
				i = std::pow(10,m);
				k = 0;
			}
			else
				i += 1;
		}
}*/