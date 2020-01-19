#pragma once
#include "DynamicArray.h"
#include <iostream>
#include <cmath>

template <class T>
class BinaryHeap
{
	//maximum
	Dynamic_Array<T>* dynamicArray;
	Linked_List<T>* linkedList;
	T* array;
	int arrayMaxSize;
	int arrayCurrentSize;
	bool isDynamic;
	bool isList;
	bool directionOfRepair;
	bool willBeDeleted;

	int GetParentIndex(int index) { if (index > 0) return floor((index - 1) / 2); }
	int GetLeftChildIndex(int index) { return (2 * index + 1); }
	int GetRightChildIndex(int index) { return (2 * index + 2); }
	bool isLeaf(int index) {

		if (isDynamic)
		{
			if (2 * index + 2 > dynamicArray->currentSize)
				return true;
			else
				return false;
		}
		else if (isList)
		{
			if (2 * index + 2 > arrayCurrentSize)
				return true;
			else
				return false;
		}
		else
		{
			if (2 * index + 2 > arrayCurrentSize)
				return true;
			else
				return false;
		}

	}
	void HipUp(int index)
	{
		if (isDynamic)
		{
			while ((dynamicArray->getData(index) > dynamicArray->getData(GetParentIndex(index))) && index > 1)
			{
				dynamicArray->Swap(index, GetParentIndex(index));
				index = GetParentIndex(index);
			}
		}
		else if (isList)
		{
			while ((linkedList->GetDataOfElement(index) > linkedList->GetDataOfElement(GetParentIndex(index))) && index > 1)
			{
				linkedList->Swap(index, GetParentIndex(index));
				index = GetParentIndex(index);
			}
		}
		else
		{
			while (index >= 1 && array[index] > array[GetParentIndex(index)])
			{
				//dynamicArray->Swap(index, GetParentIndex(index));
				T temp;
				temp = array[index];
				array[index] = array[GetParentIndex(index)];
				array[GetParentIndex(index)] = temp;

				index = GetParentIndex(index);
			}
		}

	}
	void HipDown(int index)
	{
		int greater;

		if (isDynamic)
		{
			while (!isLeaf(index))
			{
				T left = dynamicArray->getData(GetLeftChildIndex(index));
				T right = dynamicArray->getData(GetRightChildIndex(index));

				if (left.label != -1 && right.label != -1)
				{
					if (Compare(left, right) == 1)
					//if (left >right )
						greater = GetLeftChildIndex(index);
					else
						greater = GetRightChildIndex(index);

					if (Compare(dynamicArray->getData(greater), dynamicArray->getData(index)) == 1)
					//if (dynamicArray->getData(greater) > dynamicArray->getData(index))
						dynamicArray->Swap(greater, index);

					index = greater;
				}
				else if(right.label == -1)
				{
					greater = GetLeftChildIndex(index);

					if (Compare(dynamicArray->getData(greater), dynamicArray->getData(index)) == 1)
					//if (dynamicArray->getData(greater) > dynamicArray->getData(index))
						dynamicArray->Swap(greater, index);

					index = greater;
				}
				
			}

		}
		else if (isList)
		{
			while (!isLeaf(index))
			{
				if (Compare(linkedList->GetDataOfElement(GetRightChildIndex(index)), linkedList->GetDataOfElement(GetLeftChildIndex(index))) == 1)
					greater = GetLeftChildIndex(index);
				else
					greater = GetRightChildIndex(index);

				if (Compare(linkedList->GetDataOfElement(index), linkedList->GetDataOfElement(greater)) == 1)
					linkedList->Swap(index, greater);

				index = greater;
			}
		}
		else
		{
			while (!isLeaf(index))
			{
				if ((GetLeftChildIndex(index) <= arrayCurrentSize - 1) && (GetRightChildIndex(index) <= arrayCurrentSize - 1))
				{
					if (array[GetLeftChildIndex(index)] > array[GetRightChildIndex(index)] && (GetLeftChildIndex(index) <= arrayCurrentSize - 1))
						greater = GetLeftChildIndex(index);
					else
						greater = GetRightChildIndex(index);
				}
				else if ((GetLeftChildIndex(index) <= arrayCurrentSize - 1))
					greater = GetLeftChildIndex(index);
				else if ((GetRightChildIndex(index) <= arrayCurrentSize - 1))
					greater = GetRightChildIndex(index);




				if (array[greater] > array[index])
				{
					//dynamicArray->Swap(index, greater);

					T temp;
					temp = array[index];
					array[index] = array[greater];
					array[greater] = temp;
				}


				index = greater;
			}
		}

	}
public:
	BinaryHeap() { isDynamic = true; dynamicArray = new Dynamic_Array<T>; }
	//linked list
	BinaryHeap(Linked_List<T> * ll, bool toDelete, bool directionOfRepair)
	{
		isDynamic = false;
		isList = true;
		willBeDeleted = toDelete;

		this->directionOfRepair = directionOfRepair;
		linkedList = ll;
		arrayMaxSize = arrayCurrentSize = ll->size;

		//array repairing
		//if true top-down; false - bottom-up
		if (directionOfRepair)
		{
			for (int i = 0; i < arrayCurrentSize; i++) {
				HipUp(i);
				//cout<<this->ToString()<<endl;
			}
		}
		else
		{
			for (int i = arrayCurrentSize - 1; i >= 0; i--)
			{
				HipDown(i);
				//cout<<this->ToString()<<endl;
			}

		}
	}
	BinaryHeap(Dynamic_Array<T> * array, bool toDelete, bool directionOfRepair)
	{
		isDynamic = true;
		willBeDeleted = toDelete;

		this->directionOfRepair = directionOfRepair;
		dynamicArray = array;
		arrayMaxSize = arrayCurrentSize = array->currentSize;

		/*for (int i = 0; i < dynamicArray->currentSize; i++)
			cout <<"array index: "<< i<<"Point index"<< dynamicArray->getData(i).label << ": " << dynamicArray->getData(i).x << ", " << dynamicArray->getData(i).y << endl;*/

			//array repairing
			//if true top-down; false - bottom-up
		if (directionOfRepair)
		{
			for (int i = 0; i < arrayCurrentSize; i++) {
				HipUp(i);
				//cout<<this->ToString()<<endl;
			}
		}
		else
		{
			for (int i = arrayCurrentSize - 1; i >= 0; i--)
			{
				HipDown(i);
				//cout<<this->ToString()<<endl;
			}

		}
	}
	BinaryHeap(T * array, int size, bool directionOfRepair)
	{
		isDynamic = false;

		this->directionOfRepair = directionOfRepair;
		this->array = array;
		arrayMaxSize = arrayCurrentSize = size;

		//array repairing
		//if true top-down; false - bottom-up
		if (directionOfRepair)
		{
			for (int i = 0; i < arrayCurrentSize; i++) {
				HipUp(i);
				//cout<<this->ToString()<<endl;
			}
		}
		else
		{
			for (int i = arrayCurrentSize - 1; i >= 0; i--)
			{
				HipDown(i);
				//cout<<this->ToString()<<endl;
			}

		}
	}
	//only for DynamicArray
	~BinaryHeap()
	{
		if (isDynamic && willBeDeleted) dynamicArray->~Dynamic_Array();
		if (isList && willBeDeleted) linkedList->~Linked_List();
	}
	//only for DynamicArray
	void Push(T data)
	{
		dynamicArray->addElement(data);

		HipUp((dynamicArray->currentSize) - 1);
	}
	//only for DynamicArray
	T Pop()
	{
		if ((dynamicArray->currentSize) > 0)
		{
			T temp = dynamicArray->getData(0);
			dynamicArray->Swap(0, (dynamicArray->currentSize) - 1);
			dynamicArray->currentSize = (dynamicArray->currentSize) - 1;

			HipDown(0);

			return temp;
		}
	}

	void HeapSort()
	{
		if (isDynamic)
		{
			for (int i = arrayCurrentSize - 1; i >= 0; i--)
			{
				/*cout << (*dynamicArray)[0] << endl;
				getchar();*/

				dynamicArray->Swap(0, i);

				dynamicArray->currentSize--;
				arrayCurrentSize--;
				HipDown(0);
			}
			dynamicArray->currentSize = arrayCurrentSize = arrayMaxSize;
		}
		else if (isList)
		{
			for (int i = arrayCurrentSize - 1; i >= 0; i--)
			{
				/*cout << (*dynamicArray)[0] << endl;
				getchar();*/

				linkedList->Swap(0, i);

				linkedList->size--;
				arrayCurrentSize--;
				HipDown(0);
			}
			linkedList->size = arrayCurrentSize = arrayMaxSize;
		}
		else
		{
			for (int i = arrayCurrentSize - 1; i >= 0; i--)
			{
				//cout << array[0] << endl;
				T temp;
				temp = array[0];
				array[0] = array[i];
				array[i] = temp;
				//cout <<"\t"<< this->ToString() << endl;

				arrayCurrentSize--;

				HipDown(0);
				//cout<<this->ToString()<<endl;
			}
			arrayCurrentSize = arrayMaxSize;
		}
	}

	string ToString() {

		if (isDynamic)
			return dynamicArray->toString();
		else
		{
			string outcome = "";

			for (int i = 0; i < arrayCurrentSize; i++)
				outcome = outcome + to_string(array[i]) + " ";

			return outcome;
		}
	}
	string ToString(int numberOfElements)
	{
		if (isDynamic)
			return dynamicArray->toString(numberOfElements);
		else
		{
			string outcome = "";

			for (int i = 0; i < numberOfElements; i++)
				outcome = outcome + array[i] + " ";

			return outcome;
		}
	}
};

int Compare(Point p1, Point p2)
{
	double CrossProduct = p1.y * p2.x - p2.y * p1.x;
	if (CrossProduct > 0.0) return 1;
	if (CrossProduct < 0.0)return -1;
	return 0;
}