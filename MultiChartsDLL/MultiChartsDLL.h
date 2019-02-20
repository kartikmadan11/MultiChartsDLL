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
	
	/*
	DEPLOY
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
	int scale;
	*/

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
	
		/*
		void InitTrainingData(int size);
		void SetTrainingData(double* trainingData);

		void InitDateArray(int size);
		void SetDateArray(char(*dateArray)[DATE_SIZE]);

		void InitVolumeArray(int size);
		void SetVolumeArray(long* volume);

		void InitFileName(int size);
		void SetFileName(char* fileName);

		void SetLearningRate(double learningRate);
		void SetEpochs(int epochs);
		void SetScale(int scale);
		*/
	
};

extern "C" MultiCharts* CreateMultiCharts();
extern "C" void DisposeMultiCharts(MultiCharts* multiCharts);

extern "C" void SetIntNumber(MultiCharts* multiCharts, int intNumber);
extern "C" int GetIntNumber(MultiCharts* multiCharts);

extern "C" double GetDoubleNumber(MultiCharts* multiCharts);
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

/*
extern "C" void InitTrainingData(MultiCharts* multiCharts, int size);
extern "C" void SetTrainingData(MultiCharts* multiCharts, double* trainingData);

extern "C" void InitDateArray(MultiCharts* multiCharts, int size);
extern "C" void SetDateArray(MultiCharts* multiCharts, char(*dateArray)[DATE_SIZE]);

extern "C" void InitVolumeArray(MultiCharts* multiCharts, int size);
extern "C" void SetVolumeArray(MultiCharts* multiCharts, long* volumeArray);

extern "C" void InitFileName(MultiCharts* multiCharts, int size);
extern "C" void SetFileName(MultiCharts* multiCharts, char* fileName);

extern "C" void SetLearningRate(MultiCharts* multiCharts, double learningRate);
extern "C" void SetEpochs(MultiCharts* multiCharts, short epochs);
extern "C" void SetScale(MultiCharts* multiCharts, int scale);
extern "C" void SetOptimizer(MultiCharts* multiCharts, short optimizer);
*/