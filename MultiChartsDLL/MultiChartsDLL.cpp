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

	if (dateArray)
	{
		delete[] dateArray;
		dateArray = NULL;
	}

	if (fileName)
	{
		delete[] fileName;
		fileName = NULL;
	}

	if (volumeArray)
	{
		delete[] volumeArray;
		volumeArray = NULL;
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
	this->fileName = new char[size];
}

void MultiCharts::SetFileName(char* fileName)
{
	this->fileName = fileName;
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

double MultiCharts::TrainModel()
{
	
	CPyInstance pyInstance;
	//PyThreadState *_save; 
	//_save = PyEval_SaveThread();
	//PyEval_RestoreThread(_save);
	CPyObject pModule = PyImport_ImportModule("build");
	
	if (pModule)
	{
		CPyObject pFunc = PyObject_GetAttrString(pModule, "train");
		if (pFunc && PyCallable_Check(pFunc))
		{
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
				PyList_Append(pTrainingData, PyFloat_FromDouble(trainingData[i]));
				PyList_Append(pDate, PyUnicode_FromFormat("%s", c));
			}
			CPyObject pLearningRate = PyUnicode_FromFormat("%.2f", learningRate);
			CPyObject pScale = PyUnicode_FromFormat("%d", scale);
			CPyObject pEpochs = PyUnicode_FromFormat("%d", epochs);

			if (pTrainingData && pDate)
			{
				CPyObject pValue = PyObject_CallFunctionObjArgs(pFunc, pTrainingData, pDate, pLearningRate, pScale, pEpochs, NULL);
				pFunc.Release();
				pTrainingData.Release();
				pDate.Release();
				pLearningRate.Release();
				pScale.Release();
				pEpochs.Release();
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

        -- Helpers

*/

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

void SetEpochs(MultiCharts* multiCharts, short epochs)
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

void SetOptimizer(MultiCharts* multiCharts, short optimizer)
{
	if (multiCharts != NULL)
	{
		multiCharts->SetOptimizer(optimizer);
	}
}

double TrainModel(MultiCharts* multiCharts)
{
	return multiCharts->TrainModel();
}
