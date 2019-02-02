#pragma once
#include "string"

#ifdef MULTICHARTSDLL_EXPORTS
	#define MULTICHARTSMACRO __declspec(dllexport)
#else
	#define MULTICHARTSMACRO __declspec(dllimport)
#endif

template class MULTICHARTSMACRO std::basic_string<char>;

extern "C" class MULTICHARTSMACRO MultiCharts
{
	int intNumber;
	double doubleNumber;
	std::string stringData;
	double* doubleArray;
	public:
		MultiCharts();
		~MultiCharts();
		void SetIntNumber(int intNumber);
		int GetIntNumber();
		void SetDoubleNumber(double doubleNumber);
		double GetDoubleNumber();
		void SetStringData(std::string stringData);
		std::string GetStringData();
		void InitDoubleArray(int size);
		void SetDoubleArray(double* doubleArray);
		double* GetDoubleArray();
};

extern "C" MultiCharts* CreateMultiCharts();

extern "C" void DisposeMultiCharts(MultiCharts* multiCharts);

extern "C" void SetIntNumber(MultiCharts* multiCharts, int intNumber);

extern "C" int GetIntNumber(MultiCharts* multiCharts);

extern "C" void SetDoubleNumber(MultiCharts* multiCharts, double doubleNumber);

extern "C" void SetStringData(MultiCharts* multiCharts, std::string stringData);

std::string GetStringData(MultiCharts* multiCharts);

extern "C" void SetDoubleArray(MultiCharts* multiCharts, double* doubleArray);

extern "C" double* GetDoubleArray(MultiCharts* multiCharts);

extern "C" void InitDoubleArray(MultiCharts* multiCharts, int size);
