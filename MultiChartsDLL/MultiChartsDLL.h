#pragma once

#ifdef MULTICHARTSDLL_EXPORTS
	#define MULTICHARTSMACRO __declspec(dllexport)
#else
	#define MULTICHARTSMACRO __declspec(dllimport)
#endif

constexpr auto DATE_SIZE = 20;

extern "C" class MULTICHARTSMACRO MultiCharts
{
	double* trainingData;
	int trainingDataSize;

	char (*dateArray)[DATE_SIZE];
	int dateArraySize;
	
	long* volumeArray;
	int volumeArraySize;
	
	char* fileName;
	int fileNameSize;
	
	double learningRate;
	int epochs;
	long scale;

	public:

		MultiCharts();
		~MultiCharts();
	
		void InitTrainingData(int size);
		void SetTrainingData(double* trainingData);
	
		void InitDateArray(int size);
		void SetDateArray(char (*dateArray)[DATE_SIZE]);
	
		void InitVolumeArray(int size);
		void SetVolumeArray(long* volume);

		void InitFileName(int size);
		void SetFileName(char* fileName);

};

extern "C" MultiCharts* CreateMultiCharts();
extern "C" void DisposeMultiCharts(MultiCharts* multiCharts);

extern "C" void SetTrainingData(MultiCharts* multicharts, double* trainingData);