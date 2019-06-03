// MultiChartsDLL.cpp : Defines the exported functions for the DLL application.
//

#include "Python.h"
#include "stdafx.h"
#include "MultiChartsDLL.h"
#include "pyhelper.hpp"
#include "string"

using namespace std;
// Creating a Python Instance
CPyInstance pyInstance;

MultiCharts::MultiCharts() { }

MultiCharts::~MultiCharts() { }

/*

		--Member Functions--

*/

void MultiCharts::DisposeMultiCharts()
{
	if ((bool)Py_IsInitialized)
	{
		int _ = Py_FinalizeEx();
		Py_Finalize();
	}

	if (trainingData != NULL)
	{
		delete[] trainingData;
		trainingData = NULL;
	}

	if (dateArray != NULL)
	{
		delete[] dateArray;
		dateArray = NULL;
	}

	if (testingData != NULL)
	{
		delete[] testingData;
		testingData = NULL;
	}

	if (testDateArray != NULL)
	{
		delete[] testDateArray;
		testDateArray = NULL;
	}

	if (fileName != NULL)
	{
		delete[] fileName;
		fileName = NULL;
	}

	if (volumeArray != NULL)
	{
		delete[] volumeArray;
		volumeArray = NULL;
	}

	if (this != NULL)
	{
		delete this;
	}
}

void MultiCharts::InitTrainingData(int size)
{
	this->trainingDataSize = size;
	this->trainingData = new double[size];
}

void MultiCharts::SetTrainingData(double *trainingData)
{
	//this->trainingData = trainingData;
	for (int i = 0; i < trainingDataSize; i++)
	{
		this->trainingData[i] = trainingData[i];
	}
	//delete trainingData;
	trainingData = NULL;
}

void MultiCharts::InitTestingData(int size)
{
	this->testingDataSize = size;
	this->testingData = new double[size];
}

void MultiCharts::SetTestingData(double *testingData)
{	
	for (int i = 0; i < testingDataSize; i++)
	{
		this->testingData[i] = testingData[i];
	}
	//delete testingData;
	testingData = NULL;
}

void MultiCharts::InitDateArray(int size)
{
	this->dateArraySize = size;
	this->dateArray = new char[size][DATE_SIZE];
}

void MultiCharts::SetDateArray(char *dateArray)
{
	for (int i = 0, k = 0; i < dateArraySize; i++, k += DATE_SIZE - 1)
	{
		for (int j = 0; j < DATE_SIZE - 1; j++)
		{
			this->dateArray[i][j] = dateArray[j + k];
		}
		this->dateArray[i][DATE_SIZE - 1] = '\0';
	}
	//delete dateArray;
	dateArray = NULL;
}

void MultiCharts::InitTestDateArray(int size)
{
	this->testDateArraySize = size;
	this->testDateArray = new char[size][DATE_SIZE];
}

void MultiCharts::SetTestDateArray(char *testDateArray)
{
	for (int i = 0, k = 0; i < testDateArraySize; i++, k += DATE_SIZE - 1)
	{
		for (int j = 0; j < DATE_SIZE - 1; j++)
		{
			this->testDateArray[i][j] = testDateArray[j + k];
		}
		this->testDateArray[i][DATE_SIZE - 1] = '\0';
	}
	//delete testDateArray;
	testDateArray = NULL;
}

void MultiCharts::InitVolumeArray(int size)
{
	this->volumeArraySize = size;
	this->volumeArray = new long[size];
}

void MultiCharts::SetVolumeArray(long* volume)
{
	this->volumeArray = volume;
	//delete[] volume;
	//volume = NULL;
}

void MultiCharts::InitFileName(int size)
{
	this->fileNameSize = size;
	this->fileName = new char[size];
}

void MultiCharts::SetFileName(char* fileName)
{
	for (int i = 0; i < fileNameSize; i++)
	{
		this->fileName[i] = fileName[i];
	}
	fileName[fileNameSize] = '\0';
}

void MultiCharts::SetLearningRate(double learningRate)
{
	this->learningRate = learningRate;
}

void MultiCharts::SetEpochs(int epochs)
{
	this->epochs = epochs;
}

void MultiCharts::SetScale(int scale)
{
	this->scale = scale;
}

void MultiCharts::SetOptimizer(int optimizer)
{
	this->optimizer = optimizer;
}

void MultiCharts::SetMomentum(int momentum)
{
	this->momentum = momentum;
}

void MultiCharts::SetTestingPart(double testingPart)
{
	this->testingPart = testingPart;
}

void MultiCharts::SetTestingWeight(double testingWeight)
{
	this->testingWeight = testingWeight;
}

double MultiCharts::TrainModel()
{	
	// Importing the .py module
	CPyObject pModule = PyImport_ImportModule("build");

	PyGILState_STATE gstate = PyGILState_Ensure();
	
	if (pModule)
	{
		// Importing the Train Function
		CPyObject pFunc = PyObject_GetAttrString(pModule, "train");

		if (pFunc && PyCallable_Check(pFunc))
		{
			// Creating PyObjects Parameters for Train Function

			// Python Lists for Training Data Values and Dates
			CPyObject pTrainingData = PyList_New(0);
			CPyObject pDate = PyList_New(0);

			for (int i = 0; i < trainingDataSize; i++)
			{
				char* dateAtPosI = new char[DATE_SIZE];
				for (int j = 0; j < DATE_SIZE - 1; j++)
				{
					dateAtPosI[j] = dateArray[i][j];
				}
				dateAtPosI[DATE_SIZE - 1] = '\0';
				std::string date(dateAtPosI);
				const char* c = date.c_str();
				delete[] dateAtPosI;

				CPyObject pTrainEle = PyFloat_FromDouble(trainingData[i]);
				CPyObject pDateEle = PyUnicode_FromFormat("%s", c);

				PyList_Append(pTrainingData, pTrainEle);
				PyList_Append(pDate, pDateEle);
			}

			std::string fileNameString(fileName, fileNameSize);
			const char* d = fileNameString.c_str();

			CPyObject pLearningRate = PyFloat_FromDouble(learningRate);
			CPyObject pScale = Py_BuildValue("i", scale);
			CPyObject pEpochs = Py_BuildValue("i", epochs);
			CPyObject pMomentum = Py_BuildValue("i", momentum);
			CPyObject pOptimizer = Py_BuildValue("i", optimizer);
			CPyObject pFileName = PyUnicode_FromFormat("%s", d);

			if (pTrainingData && pDate && pLearningRate && pScale && pEpochs && pMomentum && pOptimizer && pFileName)
			{
				// Receiving return value from the Train Function
				CPyObject pValue = PyObject_CallFunctionObjArgs(pFunc, pTrainingData, pDate, pLearningRate, pScale, pEpochs, pMomentum, pOptimizer, pFileName, NULL);

				if (pValue)
				{
					double returnVal = PyFloat_AsDouble(pValue);
					PyGILState_Release(gstate);
					return returnVal;
				}
				else
				{
					PyGILState_Release(gstate);
					return 1.01;
				}
			}
			else
			{
				PyGILState_Release(gstate);
				return 2.01;
			}
		}
		else
		{
			PyGILState_Release(gstate);
			return 3.01;
		}
	}
	else
	{
		PyGILState_Release(gstate);
		return 4.01;
	}
}

double MultiCharts::TestModel()
{
	// Importing the .py module
 	CPyObject pModule = PyImport_ImportModule("build");

	PyGILState_STATE gstate = PyGILState_Ensure();
	
	if (pModule)
	{
		// Importing the Test Function
		CPyObject pFunc = PyObject_GetAttrString(pModule, "test");

		if (pFunc && PyCallable_Check(pFunc))
		{
			// Creating PyObjects Parameters for Test Function

			//Python Lists for Test Data Values and Dates
			CPyObject pTestingData = PyList_New(0);
			CPyObject pDate = PyList_New(0);

			for (int i = 0; i < testingDataSize; i++)
			{
				char* dateAtPosI = new char[DATE_SIZE];
				for (int j = 0; j < DATE_SIZE - 1; j++)
				{
					dateAtPosI[j] = testDateArray[i][j];
				}
				dateAtPosI[DATE_SIZE - 1] = '\0';
				std::string date(dateAtPosI);
				const char* c = date.c_str();
				delete[] dateAtPosI;

				CPyObject pTestEle = PyFloat_FromDouble(testingData[i]);
				CPyObject pDateEle = PyUnicode_FromFormat("%s", c);

				PyList_Append(pTestingData, pTestEle);
				PyList_Append(pDate, pDateEle);
			}

			std::string fileNameString(fileName, fileNameSize);
			const char* d = fileNameString.c_str();

			CPyObject pTestingWeight = PyFloat_FromDouble(testingWeight);
			CPyObject pFileName = PyUnicode_FromFormat("%s", d);

			if (pTestingData && pDate && pTestingWeight && pFileName)
			{
				// Receiving return value from the Test Function
				CPyObject pValue = PyObject_CallFunctionObjArgs(pFunc, pTestingData, pDate, pTestingWeight, pFileName, NULL);

				if (pValue)
				{
					double returnVal = PyFloat_AsDouble(pValue);
					PyGILState_Release(gstate);
					return returnVal;
				}
				else
				{
					PyGILState_Release(gstate);
					return 0.01;
				}
			}
			else
			{
				PyGILState_Release(gstate);
				return 0.02;
			}
		}
		else
		{
			PyGILState_Release(gstate);
			return 0.03;
		}
	}
	else
	{
		PyGILState_Release(gstate);
		return 0.04;
	}
}

double* MultiCharts::Predict(int ticks)
{
	// Importing the .py module
	CPyObject pModule = PyImport_ImportModule("build");

	PyGILState_STATE gstate = PyGILState_Ensure();

	if (pModule)
	{
		// Importing the Predict Function
		CPyObject pFunc = PyObject_GetAttrString(pModule, "predict");

		if (pFunc && PyCallable_Check(pFunc))
		{
			// Creating PyObjects Parameters for Predict Function

			std::string fileNameString(fileName, fileNameSize);
			const char* d = fileNameString.c_str();

			CPyObject pFileName = PyUnicode_FromFormat("%s", d);
			CPyObject pTicks = Py_BuildValue("i", ticks);

			if (pFileName && pTicks)
			{
				// Receiving return value from the Predict Function
				CPyObject pValue = PyObject_CallFunctionObjArgs(pFunc, pFileName, pTicks, NULL);

				if (pValue)
				{
					if (PyList_Check(pValue))
					{
						int count = (int)PyList_Size(pValue);

						double* predictions = new double[count];
						CPyObject pTemp;

						for (int i = 0; i < count; i++)
						{
							pTemp = PyList_GetItem(pValue, i);
							predictions[i] = PyFloat_AsDouble(pTemp);
						}

						PyGILState_Release(gstate);
						
						//double* predictions = new double[ticks]{ 1.1, 2.01, 3.22, 4.1, 5.09 };
						return predictions;
					}
					else
					{
						return NULL;
					}
				}
				else
				{
					return NULL;
				}
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

/*

		-- Exported Functions --

*/

MultiCharts* CreateMultiCharts()
{
	return new MultiCharts();
}

void DisposeMultiCharts(MultiCharts* multiCharts)
{
	if (multiCharts != NULL)
	{
		multiCharts->DisposeMultiCharts();
		multiCharts = NULL;
	}
}

void InitTrainingData(MultiCharts* multiCharts, int size)
{
	if (multiCharts != NULL)
	{
		multiCharts->InitTrainingData(size);
	}
}

void SetTrainingData(MultiCharts* multiCharts, double* trainingData)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetTrainingData(trainingData);
	}
}

void InitDateArray(MultiCharts* multiCharts, int size)
{
	if (multiCharts != NULL)
	{
		multiCharts->InitDateArray(size);
	}
}

void SetDateArray(MultiCharts* multiCharts, char* dateArray)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetDateArray(dateArray);
	}
}

void InitTestingData(MultiCharts* multiCharts, int size)
{
	if (multiCharts != NULL)
	{
		multiCharts->InitTestingData(size);
	}
}

void SetTestingData(MultiCharts* multiCharts, double* testingData)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetTestingData(testingData);
	}
}

void InitTestDateArray(MultiCharts* multiCharts, int size)
{
	if (multiCharts != NULL)
	{
		multiCharts->InitTestDateArray(size);
	}
}

void SetTestDateArray(MultiCharts* multiCharts, char* testDateArray)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetTestDateArray(testDateArray);
	}
}

void InitVolumeArray(MultiCharts* multiCharts, int size)
{
	if (multiCharts != NULL)
	{
		multiCharts->InitVolumeArray(size);
	}
}

void SetVolumeArray(MultiCharts* multiCharts, long* volumeArray)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetVolumeArray(volumeArray);
	}
}

void InitFileName(MultiCharts* multiCharts, int size)
{
	if (multiCharts != NULL)
	{
		multiCharts->InitFileName(size);
	}
}

void SetFileName(MultiCharts* multiCharts, char* fileName)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetFileName(fileName);
	}
}

void SetLearningRate(MultiCharts* multiCharts, double learningRate)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetLearningRate(learningRate);
	}
}

void SetEpochs(MultiCharts* multiCharts, int epochs)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetEpochs(epochs);
	}
}

void SetScale(MultiCharts* multiCharts, int scale)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetScale(scale);
	}
}

void SetOptimizer(MultiCharts* multiCharts, int optimizer)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetOptimizer(optimizer);
	}
}

void SetMomentum(MultiCharts* multiCharts, int momentum)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetMomentum(momentum);
	}
}

double TrainModel(MultiCharts* multiCharts)
{
	if (multiCharts != NULL)
	{
		return multiCharts->TrainModel();
	}
	return 10.1;
}

double TestModel(MultiCharts* multiCharts)
{
	if (multiCharts != NULL)
	{
		return multiCharts->TestModel();
	}
	return 10.2;
}

double* Predict(MultiCharts* multiCharts, int ticks)
{
	if (multiCharts != NULL)
	{
		return multiCharts->Predict(ticks);
	}
	return NULL;
}