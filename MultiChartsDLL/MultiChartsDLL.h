#pragma once

#ifdef MULTICHARTSDLL_EXPORTS
	#define MULTICHARTSMACRO __declspec(dllexport)
#else
	#define MULTICHARTSMACRO __declspec(dllimport)
#endif

constexpr auto DATE_SIZE = 21;

extern "C" class MULTICHARTSMACRO MultiCharts
{
	double* trainingData;
	int trainingDataSize;

	double* testingData;
	int testingDataSize;

	char (*dateArray)[DATE_SIZE];
	int dateArraySize;

	char (*testDateArray)[DATE_SIZE];
	int testDateArraySize;

	long* volumeArray;
	int volumeArraySize;
	
	char* fileName;
	int fileNameSize;

	double learningRate;
	int epochs;
	int scale;
	int optimizer;
	int momentum;
	double testingPart;
	double testingWeight;

	public:

		MultiCharts();
		~MultiCharts();
		void DisposeMultiCharts();

		void InitTrainingData(int size);
		void SetTrainingData(double* trainingData);

		void InitTestingData(int size);
		void SetTestingData(double* testingData);

		void InitDateArray(int size);
		void SetDateArray(char *dateArray);

		void InitTestDateArray(int size);
		void SetTestDateArray(char *testDateArray);

		void InitVolumeArray(int size);
		void SetVolumeArray(long* volume);

		void InitFileName(int size);
		void SetFileName(char* fileName);

		void SetLearningRate(double learningRate);
		void SetEpochs(int epochs);
		void SetScale(int scale);
		void SetOptimizer(int optimizer);
		void SetMomentum(int momentum);
		void SetTestingPart(double testingPart);
		void SetTestingWeight(double testingWeight);

		double TrainModel();
		double TestModel();
		double* Predict();
};

/*
		-- Exported Functions
*/

extern "C" MultiCharts* CreateMultiCharts();
extern "C" void DisposeMultiCharts(MultiCharts* multiCharts);

extern "C" void InitTrainingData(MultiCharts* multiCharts, int size);
extern "C" void SetTrainingData(MultiCharts* multiCharts, double* trainingData);

extern "C" void InitDateArray(MultiCharts* multiCharts, int size);
extern "C" void SetDateArray(MultiCharts* multiCharts, char* dateArray);

extern "C" void InitTestingData(MultiCharts* multiCharts, int size);
extern "C" void SetTestingData(MultiCharts* multiCharts, double* testingData);

extern "C" void InitTestDateArray(MultiCharts* multiCharts, int size);
extern "C" void SetTestDateArray(MultiCharts* multiCharts, char* testDateArray);

extern "C" void InitVolumeArray(MultiCharts* multiCharts, int size);
extern "C" void SetVolumeArray(MultiCharts* multiCharts, long* volumeArray);

extern "C" void InitFileName(MultiCharts* multiCharts, int size);
extern "C" void SetFileName(MultiCharts* multiCharts, char* fileName);

extern "C" void SetLearningRate(MultiCharts* multiCharts, double learningRate);
extern "C" void SetEpochs(MultiCharts* multiCharts, int epochs);
extern "C" void SetScale(MultiCharts* multiCharts, int scale);
extern "C" void SetOptimizer(MultiCharts* multiCharts, int optimizer);
extern "C" void SetMomentum(MultiCharts* multiCharts, int momentum);

extern "C" double TrainModel(MultiCharts* multiCharts);
extern "C" double TestModel(MultiCharts* multiCharts);
extern "C" double* Predict(MultiCharts* multiCharts);