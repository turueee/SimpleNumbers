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

unsigned long long ModMul(unsigned long long a, unsigned long long b, unsigned long long mod)
{
	if (b == 0)
		return 0;
	if (b == 1)
		return a % mod;
	if ((b & 1) == 0)
		return (2 * ModMul(a, b / 2, mod)) % mod;
	else
		return (ModMul(a, b - 1, mod) + a) % mod;
}

unsigned long long ModExp(unsigned long long os, unsigned long long pow, unsigned long long divide)
{
	if (pow == 0)
		return static_cast<unsigned long long>(1);
	unsigned long long z = ModExp(os, pow / 2, divide);
	if ((pow & 1) == 0)
		return ModMul(z, z, divide);
	else
		return ModMul(ModMul(os, z, divide), z, divide);
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

bool IsSimpleRabinMillerAlgorithm(unsigned long long num)
{
	if (num < 2) return false;
	if (num == 2) return true;
	if (num % 2 == 0) return false;
	if (num == 3) return true;

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
	unsigned long long a = dis(gen);

	unsigned long long x = ModExp(a, u, num);

	if (x == 1 || x == num - 1)
	{
		return true;
	}

	for (size_t i = 1; i < t; ++i)
	{
		x = ModExp(x, 2, num);

		if (x == num - 1)
		{
			return true;
		}
		if (x == 1)
		{
			return false;
		}
	}

	return false;
}

int main()
{
	//Алгоритм перебором
	std::ifstream infile0("SimpleNumbersFromTenTillMillion.txt");
	std::ofstream outfile0("SimpleNumbersFromTenTillMillionExhaustiveSearchAlgorithm.txt");
	if (infile0.is_open() && outfile0.is_open())
	{
		for (size_t i = 0; i < 100; ++i)
		{
			unsigned long long num;
			infile0 >> num;
			auto start = std::chrono::high_resolution_clock::now();
			IsSimpleExhaustiveSearchAlgorithm(num);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = end - start;
			double seconds = elapsed.count();
			outfile0<<num<<' ' << IsSimpleExhaustiveSearchAlgorithm(num) << ' ';
			outfile0 << std::fixed << std::setprecision(15)<< (seconds) << std::endl;
		}
	}


	std::ifstream infile1("SimpleNumbersFromMillionTillBillion.txt");
	std::ofstream outfile1("SimpleNumbersFromMillionTillBillionExhaustiveSearchAlgorithm.txt");
	if (infile1.is_open() && outfile1.is_open())
	{
		for (size_t i = 0; i < 100; ++i)
		{
			unsigned long long num;
			infile1 >> num;
			auto start = std::chrono::high_resolution_clock::now();
			IsSimpleExhaustiveSearchAlgorithm(num);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = end - start;
			double seconds = elapsed.count();
			outfile1 << num << ' ' << IsSimpleExhaustiveSearchAlgorithm(num) << ' ';
			outfile1 << std::fixed << std::setprecision(15) << (seconds) << std::endl;
		}
	}


	std::ifstream infile2("SimpleNumbersFromBillionTillSixtilion.txt");
	std::ofstream outfile2("SimpleNumbersFromBillionTillSixtilionExhaustiveSearchAlgorithm.txt");
	if (infile2.is_open() && outfile2.is_open())
	{
		for (size_t i = 0; i < 100; ++i)
		{
			unsigned long long num;
			infile2 >> num;
			auto start = std::chrono::high_resolution_clock::now();
			IsSimpleExhaustiveSearchAlgorithm(num);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = end - start;
			double seconds = elapsed.count();
			outfile2 << num << ' ' << IsSimpleExhaustiveSearchAlgorithm(num) << ' ';
			outfile2 << std::fixed << std::setprecision(15) << (seconds) << std::endl;
		}
	}
	// Алгоритм Ферма
	std::ifstream infile3("SimpleNumbersFromTenTillMillion.txt");
	std::ofstream outfile3("SimpleNumbersFromTenTillMillionFermaAlgorithm.txt");
	if (infile3.is_open() && outfile3.is_open())
	{
		for (size_t i = 0; i < 100; ++i)
		{
			unsigned long long num;
			infile3 >> num;
			auto start = std::chrono::high_resolution_clock::now();
			IsSimpleFermaAlgorithm(num);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = end - start;
			double seconds = elapsed.count();
			outfile3 << num << ' ' << IsSimpleFermaAlgorithm(num) << ' ';
			outfile3 << std::fixed << std::setprecision(15) << (seconds) << std::endl;
		}
	}


	std::ifstream infile4("SimpleNumbersFromMillionTillBillion.txt");
	std::ofstream outfile4("SimpleNumbersFromMillionTillBillionFermaAlgorithm.txt");
	if (infile4.is_open() && outfile4.is_open())
	{
		for (size_t i = 0; i < 100; ++i)
		{
			unsigned long long num;
			infile4 >> num;
			auto start = std::chrono::high_resolution_clock::now();
			IsSimpleFermaAlgorithm(num);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = end - start;
			double seconds = elapsed.count();
			outfile4 << num << ' ' << IsSimpleFermaAlgorithm(num) << ' ';
			outfile4 << std::fixed << std::setprecision(15) << (seconds) << std::endl;
		}
	}


	std::ifstream infile5("SimpleNumbersFromBillionTillSixtilion.txt");
	std::ofstream outfile5("SimpleNumbersFromBillionTillSixtilionFermaAlgorithm.txt");
	if (infile5.is_open() && outfile5.is_open())
	{
		for (size_t i = 0; i < 100; ++i)
		{
			unsigned long long num;
			infile5 >> num;
			auto start = std::chrono::high_resolution_clock::now();
			IsSimpleFermaAlgorithm(num);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = end - start;
			double seconds = elapsed.count();
			outfile5 << num << ' ' << IsSimpleFermaAlgorithm(num) << ' ';
			outfile5 << std::fixed << std::setprecision(15) << (seconds) << std::endl;
		}
	}
	//Алгоритм Рабина-Миллера
	std::ifstream infile6("SimpleNumbersFromTenTillMillion.txt");
	std::ofstream outfile6("SimpleNumbersFromTenTillMillionRabinMillerAlgorithm.txt");
	if (infile6.is_open() && outfile6.is_open())
	{
		for (size_t i = 0; i < 100; ++i)
		{
			unsigned long long num;
			infile6 >> num;
			auto start = std::chrono::high_resolution_clock::now();
			IsSimpleRabinMillerAlgorithm(num);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = end - start;
			double seconds = elapsed.count();
			outfile6 << num << ' ' << IsSimpleRabinMillerAlgorithm(num) << ' ';
			outfile6 << std::fixed << std::setprecision(15) << (seconds) << std::endl;
		}
	}


	std::ifstream infile7("SimpleNumbersFromMillionTillBillion.txt");
	std::ofstream outfile7("SimpleNumbersFromMillionTillBillionRabinMillerAlgorithm.txt");
	if (infile7.is_open() && outfile7.is_open())
	{
		for (size_t i = 0; i < 100; ++i)
		{
			unsigned long long num;
			infile7 >> num;
			auto start = std::chrono::high_resolution_clock::now();
			IsSimpleRabinMillerAlgorithm(num);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = end - start;
			double seconds = elapsed.count();
			outfile7 << num << ' ' << IsSimpleRabinMillerAlgorithm(num) << ' ';
			outfile7 << std::fixed << std::setprecision(15) << (seconds) << std::endl;
		}
	}


	std::ifstream infile8("SimpleNumbersFromBillionTillSixtilion.txt");
	std::ofstream outfile8("SimpleNumbersFromBillionTillSixtilionRabinMillerAlgorithm.txt");
	if (infile8.is_open() && outfile8.is_open())
	{
		for (size_t i = 0; i < 100; ++i)
		{
			unsigned long long num;
			infile8 >> num;
			auto start = std::chrono::high_resolution_clock::now();
			IsSimpleRabinMillerAlgorithm(num);
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = end - start;
			double seconds = elapsed.count();
			outfile8 << num << ' ' << IsSimpleRabinMillerAlgorithm(num) << ' ';
			outfile8 << std::fixed << std::setprecision(15) << (seconds) << std::endl;
		}
	}
}
