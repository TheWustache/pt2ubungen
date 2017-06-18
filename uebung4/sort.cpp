#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>

// function template for printing contents of containers to std::cout
template<class T>
void printContainer(T& container)
{
	std::cout << "{";
	for (auto element : container)
		std::cout << element << " ";
	std::cout << "}" << std::endl;
}

// Todo 4.4 - Merge the given lists [leftIt..midIt) and [midIt..rightIt)
template<class T>
void merge(T leftIt, T midIt, T rightIt)
{
	//remember start, middle
	T startIt = leftIt, midIt2 = midIt;
	assert(leftIt <= midIt && midIt <= rightIt);
	std::vector<T::value_type> mergedValues;
	//insert the smaller of 2 segments into mergedValues
	while (leftIt != midIt && midIt2 != rightIt) {
		if (*leftIt <= *midIt2) {
			mergedValues.push_back(*leftIt);
			leftIt++;
		}
		else {
			mergedValues.push_back(*midIt2);
			midIt2++;
		}
	}
	//add rest of the remaining segment
	while (leftIt!= midIt) {
		mergedValues.push_back(*leftIt);
		leftIt++;
	}
	while(midIt2 !=rightIt){
		mergedValues.push_back(*midIt2);
		midIt2++;
	}
	//copy sorted values back to original values
	leftIt = mergedValues.begin();
	rightIt = mergedValues.end();
	while (leftIt != rightIt) {		
		*startIt++ = *leftIt++;
	}
}

// Todo 4.4 - Sort the given container using merge sort.
template<class T>
void mergeSort(T leftIt, T rightIt)
{
	if (leftIt + 1 == rightIt) {
		return;
	}
	assert(leftIt < rightIt);
	T middleIt = leftIt + std::distance(leftIt, rightIt)/2;
	mergeSort(leftIt, middleIt);
	mergeSort(middleIt, rightIt);
	merge(leftIt, middleIt, rightIt);
}

int main(int argc, char** argv)
{
	// define sample data
	std::vector<int> sampleDataInt = { 10, 1, 12, 33, 24, 5, 6, -7, -2, 19 };
	std::vector<std::string> sampleDataString = { "Die", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung" };

	// test for integer vector
	printContainer(sampleDataInt);
	mergeSort(sampleDataInt.begin(), sampleDataInt.end());
	printContainer(sampleDataInt);

	// test for string vector
	printContainer(sampleDataString);
	mergeSort(sampleDataString.begin(), sampleDataString.end());
	printContainer(sampleDataString);

	return 0;
}
