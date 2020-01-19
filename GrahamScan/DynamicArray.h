#pragma once
#include <string>
#include <iostream>
using namespace std;

template <class T>
class Dynamic_Array
{
	friend void GrahamScan(Graph* graph, Dynamic_Array<T>* PointsCopy);

	T* array;
	int maxSize;

	const int AUGMENTATION_FACTOR = 2;

public:
	int currentSize;
	T& operator[](int index) { return array[index];}
	Dynamic_Array()
	{
		currentSize = 0;
		maxSize = 1;
		array = new T[1];
	}

	~Dynamic_Array()
	{
		currentSize = maxSize = 0;
		delete[] array;
		//array = 0;
	}

	void addElement(T data)
	{
		if (currentSize < maxSize)
		{
			//cout << data << endl;
			array[currentSize] = data;
			currentSize++;
			//cout << array[currentSize-1] << endl;
			//getchar();
		}
		else
		{
			maxSize *= AUGMENTATION_FACTOR;

			T* extendedArray = new T[maxSize];

			for (int i = 0; i < currentSize; i++)
				extendedArray[i] = array[i];

			extendedArray[currentSize] = data;

			currentSize++;

			delete[] array;
			array = extendedArray;
		}
	}

	//returns true if the replacement completed or false if failed
	bool replaceData(int index, T data)
	{
		if (index >= 0 && index < currentSize)
		{
			array[index] = data;
			return true;
		}
		else
		{
			cout << "Replacement failed - index out of range" << endl;;
			return false;
		}

	}

	T getData(int index)
	{
		if (index >= 0 && index < currentSize)
		{
			return array[index];
		}
		else
		{
			cerr << "Retrieving failed - index out of range" << endl;
			return T();
		}
	}

	//full version
	string toString()
	{
		string outcome = "";

		outcome = "Number of array's elements: " + to_string(currentSize) + "\n";
		for (int i = 0; i < currentSize; i++)
		{
			outcome = outcome + to_string(array[i]) + " ";
		}

		outcome += "\n\n";

		return outcome;
	}

	//short version
	string toString(int numberOfElements)
	{
		string outcome = "";

		outcome = "Number of array's elements: " + to_string(currentSize) + "\n";
		for (int i = 0; i < numberOfElements; i++)
		{
			outcome = outcome + to_string(array[i]) + " ";
		}

		outcome += "\n\n";

		return outcome;
	}

	//char's version
	string toString(int numberOfElements, string(*elementToString)(T))
	{
		string outcome = "";

		outcome = "Number of array's elements: " + to_string(currentSize) + "\n";
		for (int i = 0; i < numberOfElements; i++)
		{
			outcome = outcome + elementToString(array[i]) + " ";
		}

		outcome += "\n\n";

		return outcome;
	}
	void Swap(int index1, int index2)
	{
		T temp = array[index1];
		array[index1] = array[index2];
		array[index2] = temp;
	}

	T* FindStartPoint()
	{
		if (currentSize == 0)
		{
			cout << "Dynamic_Array::FindStartPoint error: The list is empty!" << endl;
			return nullptr;
		}
		
		int IndexOfStartPoint = 0;

		for (int i = 1; i < currentSize; i++)
		{
			if (array[i].y < array[IndexOfStartPoint].y) IndexOfStartPoint = i;
			else if (array[i].y == array[IndexOfStartPoint].y)
			{
				if(array[i].x < array[IndexOfStartPoint].x) IndexOfStartPoint = i;
			}
		}
		return &(array[IndexOfStartPoint]);
	}
	void CopyWithout(Dynamic_Array<T>* Target, T Without)
	{
		for (int i = 0; i < currentSize; i++)
		{
			if ((array[i].x == Without.x) && (array[i].y == Without.y)) continue;

			Target->addElement(array[i]);
		}
	}

	void NewCoordinatesSystem(T StartPoint)
	{
		for (int i = 0; i < currentSize; i++)
		{
			array[i] = array[i] - StartPoint;
		}
	}
};

//genererate LINKER error
//string elementToString(char c)
//{
//	return string(1, c);
//}