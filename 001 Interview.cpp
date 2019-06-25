#include <iostream>
#include <vector>
using namespace std;

/*
 * You have two sorted arrays, where each element is an interval.
 * Now, merge the two array, overlapping intervals can be merged as a single one.
 *
 * I/P :
 * List 1 [1,2] , [3,9]
 * List 2 [4,5], [8, 10], [11,12]
 *
 * O/P [1,2], [3,10], [11,12]
 */

struct Interval{
  double min;
  double max;
};

int main() {
  Interval array1 [] = {Interval{1, 2}, Interval{3, 9}};
  Interval array2 [] = {Interval{4, 5}, Interval{8, 10}, Interval{11, 12}};
  int size1 = sizeof(array1) / sizeof(*array1);
  int size2 = sizeof(array2) / sizeof(*array2);

  // sort arrays into one vector according to their minimal value
  vector<Interval> sortedVector;
  int indexArray1 = 0, indexArray2 = 0;
  while(indexArray1 < size1 && indexArray2 < size2){
    if(array1[indexArray1].min <= array2[indexArray2].min){
      sortedVector.push_back(array1[indexArray1]);
      indexArray1++;
    }
    else{
      sortedVector.push_back(array2[indexArray2]);
      indexArray2++;
    }
  }
  while(indexArray1 != size1){
    sortedVector.push_back(array1[indexArray1]);
    indexArray1++;
  }
  while(indexArray2 != size2){
    sortedVector.push_back(array2[indexArray2]);
    indexArray2++;
  }

  // merge intervals in sortedVector into vector
  vector<Interval> mergedIntervals;
  Interval mergedInterval = sortedVector.at(0);
  int currentIndex = 1;
  while(currentIndex < size1 + size2){
    // case [1,4] and [5,6] -> doesn't merge
    if(mergedInterval.max < sortedVector.at(currentIndex).min) {
      // push last merged interval into the vector and assign mergedInterval to the current sortedVector element
      mergedIntervals.push_back(mergedInterval);
      mergedInterval = sortedVector.at(currentIndex);
    }
    // can be merged, case [1,4] and [3,7] -> [1,7]
    else if(mergedInterval.max < sortedVector.at(currentIndex).max)
      mergedInterval.max = sortedVector.at(currentIndex).max;
    // can be merged, case [1,4] and [2,3] -> [1,4], merged interval won't change
    currentIndex++;
  }
  // push last merged interval into the vector
  mergedIntervals.push_back(mergedInterval);

  // print merged intervals
  cout << "Merged Intervals" << endl;
  for(int i = 0; i < mergedIntervals.size(); i++)
    cout << "[" << mergedIntervals.at(i).min << "," << mergedIntervals.at(i).max << "] ";

  return 0;
}