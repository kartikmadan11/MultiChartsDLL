// MultiChartsDLL.cpp : Defines the exported functions for the DLL application.
//

#include "Python.h"
#include "stdafx.h"
#include "MultiChartsDLL.h"
#include "pyhelper.hpp"
#include "string"

MultiCharts::MultiCharts() { }

MultiCharts::~MultiCharts() { }

/*

		--Member Functions--

*/

void MultiCharts::DisposeMultiCharts()
{
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

void MultiCharts::SetTrainingData(double* trainingData)
{
	this->trainingData = trainingData;
}

void MultiCharts::InitDateArray(int size)
{
	this->dateArraySize = size;
	this->dateArray = new char[size][DATE_SIZE];
}

void MultiCharts::SetDateArray(char *dateArray)
{
	for (int i = 0, k = 0; i < dateArraySize; i++, k+=DATE_SIZE - 1)
	{
		for (int j = 0; j < DATE_SIZE - 1; j++)
		{
			this->dateArray[i][j] = dateArray[j+k];
		}
		this->dateArray[i][DATE_SIZE - 1] = '\0';
	}
}

void MultiCharts::InitVolumeArray(int size)
{
	this->volumeArray = new long[size];
}

void MultiCharts::SetVolumeArray(long* volume)
{
	this->volumeArray = volume;
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

double MultiCharts::TrainModel()
{
	// Creating a Python Instance
	CPyInstance pyInstance;

	//PyThreadState *_save;
	//_save = PyEval_SaveThread();
	//PyEval_RestoreThread(_save);

	// Importing the .py module
	CPyObject pModule = PyImport_ImportModule("build");

	if (pModule)
	{
		// Importing the Train Function
		CPyObject pFunc = PyObject_GetAttrString(pModule, "train");

		if (pFunc && PyCallable_Check(pFunc))
		{
			// Creating PyObjects Parameters for Train Function

			//Python Lists for Training Data Values and Dates
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

				PyList_Append(pTrainingData, PyFloat_FromDouble(trainingData[i]));
				PyList_Append(pDate, PyUnicode_FromFormat("%s", c));
			}

			std::string fileNameString(fileName, fileNameSize);
			const char* d = fileNameString.c_str();

			CPyObject pLearningRate = PyFloat_FromDouble(learningRate);
			CPyObject pScale = Py_BuildValue("i", scale);
			CPyObject pEpochs = Py_BuildValue("i", epochs);
			CPyObject pMomentum = Py_BuildValue("i", momentum);
			CPyObject pOptimizer = Py_BuildValue("i", optimizer);
			CPyObject pFileName = PyUnicode_FromFormat("%s", d);

			if (pTrainingData && pDate)
			{
				// Receiving return value from the Train Function
				CPyObject pValue = PyObject_CallFunctionObjArgs(pFunc, pTrainingData, pDate, pLearningRate, pScale, pEpochs, pMomentum, pOptimizer, pFileName, NULL);

				// Releasing Function and Parameter Objects
				pFunc.Release();
				pTrainingData.Release();
				pDate.Release();
				pLearningRate.Release();
				pScale.Release();
				pEpochs.Release();
				pMomentum.Release();
				pOptimizer.Release();
				pFileName.Release();

				if (pValue)
				{
					return PyFloat_AsDouble(pValue);
				}
				else
				{
					return 1.01;
				}
			}
			else
			{
				return 2.01;
			}
		}
		else
		{
			return 3.01;
		}
	}
	else
	{
		return 4.01;
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
		multiCharts->InitTrainingData(size);
	}
}

void SetDateArray(MultiCharts* multiCharts, char *dateArray)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetDateArray(dateArray);
	}
}

void InitVolumeArray(MultiCharts* multiCharts, int size)
{
	if (multiCharts != NULL)
	{
		multiCharts->InitTrainingData(size);
	}
}

void SetVolumeArray(MultiCharts* multiCharts, long * volumeArray)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetVolumeArray(volumeArray);
	}
}

void InitFileName(MultiCharts * multiCharts, int size)
{
	if (multiCharts != NULL)
	{
		multiCharts->InitTrainingData(size);
	}
}

void SetFileName(MultiCharts* multiCharts, char * fileName)
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
	return multiCharts->TrainModel();
}