#pragma once

#ifdef MULTICHARTSDLL_EXPORTS
	#define MULTICHARTSMACRO __declspec(dllexport)
#else
	#define MULTICHARTSMACRO __declspec(dllimport)
#endif

extern "C" class MULTICHARTSMACRO MultiCharts
{
	int intNumber;
	double doubleNumber;
	char* stringData;
	double* doubleArray;
	char* pythonStringData;
public:
	MultiCharts();
	~MultiCharts();
	void SetIntNumber(int intNumber);
	int GetIntNumber();
	void SetDoubleNumber(double doubleNumber);
	double GetDoubleNumber();
	void InitStringData(int size);
	void SetStringData(char* stringData);
	char* GetStringData();
	void InitDoubleArray(int size);
	void SetDoubleArray(double* doubleArray);
	double* GetDoubleArray();
	void InitPythonStringData(int size);
	void SetPythonStringData(char* pythonStringData);
	char* GetPythonStringData();
};

extern "C" MultiCharts* CreateMultiCharts();

extern "C" void DisposeMultiCharts(MultiCharts* multiCharts);

extern "C" void SetIntNumber(MultiCharts* multiCharts, int intNumber);

extern "C" int GetIntNumber(MultiCharts* multiCharts);

extern "C" void SetDoubleNumber(MultiCharts* multiCharts, double doubleNumber);

extern "C" void SetStringData(MultiCharts* multiCharts, char* stringData);

extern "C" char* GetStringData(MultiCharts* multiCharts);

extern "C" void InitStringData(MultiCharts* multiCharts, int size);

extern "C" void SetDoubleArray(MultiCharts* multiCharts, double* doubleArray);

extern "C" double* GetDoubleArray(MultiCharts* multiCharts);

extern "C" void InitDoubleArray(MultiCharts* multiCharts, int size);

extern "C" void InitPythonStringData(MultiCharts* multiCharts, int size);

extern "C" void SetPythonStringData(MultiCharts* multiCharts, char* pythonStringData);

extern "C" char* GetPythonStringData(MultiCharts* multiCharts);