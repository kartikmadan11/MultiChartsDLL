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
	char* dateArrayHelper;
	int dateArraySize;

	long* volumeArray;
	int volumeArraySize;
	
	char* fileName;
	int fileNameSize;
	
	double learningRate;
	short epochs;
	int scale;
	short optimizer;

	public:
  
		MultiCharts();
		~MultiCharts();
	
		void InitTrainingData(int size);
		void SetTrainingData(double* trainingData);

		void InitDateArray(int size);
		void SetDateArray(char *dateArray);
	
		void InitVolumeArray(int size);
		void SetVolumeArray(long* volume);

		void InitFileName(int size);
		void SetFileName(char* fileName);

		void SetLearningRate(double learningRate);
		void SetEpochs(short epochs);
		void SetScale(int scale);
		void SetOptimizer(short optimizer);

		double TrainModel();
};

/*
		-- Exported Functions
*/

extern "C" MultiCharts* CreateMultiCharts();
extern "C" void DisposeMultiCharts(MultiCharts* multiCharts);

extern "C" void InitTrainingData(MultiCharts* multiCharts, int size);
extern "C" void SetTrainingData(MultiCharts* multiCharts, double* trainingData);

extern "C" void InitDateArray(MultiCharts* multiCharts, int size);
extern "C" void SetDateArray(MultiCharts* multiCharts, char *dateArray);

extern "C" void InitVolumeArray(MultiCharts* multiCharts, int size);
extern "C" void SetVolumeArray(MultiCharts* multiCharts, long* volumeArray);

extern "C" void InitFileName(MultiCharts* multiCharts, int size);
extern "C" void SetFileName(MultiCharts* multiCharts, char* fileName);

extern "C" void SetLearningRate(MultiCharts* multiCharts, double learningRate);
extern "C" void SetEpochs(MultiCharts* multiCharts, short epochs);
extern "C" void SetScale(MultiCharts* multiCharts, int scale);
extern "C" void SetOptimizer(MultiCharts* multiCharts, short optimizer);

extern "C" double TrainModel(MultiCharts* multiCharts);