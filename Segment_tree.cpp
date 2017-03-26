/* Copyright 2017 Carlos Roberto Martinez Ojeda <carlos.1424@@live.com.mx>
   Topic: Segment tree
   Queries complexity O(m log n), m = queries, n = number of elements */
#include <iostream>
#include <math.h>
#include <climits>

using namespace std;

int minQuery(const int*segmentTree, int qlow, int qhigh, int low, int high, int pos)
{

  //complete overlap
  if(low >= qlow && high <= qhigh)
    return segmentTree[pos];

  //no overlap
  if(qlow > high || qhigh < low)
    return INT_MAX;

  //partial overlap
  int left, right, mid = (low + high) / 2;
  left  = minQuery(segmentTree, qlow, qhigh, low, mid, pos*2+1);
  right = minQuery(segmentTree, qlow, qhigh, mid+1, high, pos*2+2);
  return min(left, right);
}

int maxQuery(const int*segmentTree, int qlow, int qhigh, int low, int high, int pos)
{
  //complete overlap
  if(low >= qlow && high <= qhigh)
    return segmentTree[pos];

  //no overlap
  if(qlow > high || qhigh < low)
    return INT_MIN;

  //partial overlap
  int left, right, mid = (low + high) / 2;
  left = maxQuery(segmentTree, qlow, qhigh, low, mid, pos*2+1);
  right = maxQuery(segmentTree, qlow, qhigh, mid+1, high, pos*2+2);
  return max(left, right);
}

void constructMinSegmentTree(const int *arr, int *segmentTree, int low, int high, int pos)
{
  if(low == high)
  {
    segmentTree[pos] = arr[low];
    return;
  }

  int mid = (low + high) / 2;
  constructMinSegmentTree(arr, segmentTree, low, mid, pos*2+1);
  constructMinSegmentTree(arr, segmentTree, mid+1, high, pos*2+2);
  segmentTree[pos] = min(segmentTree[pos*2+1], segmentTree[pos*2+2]);
}

void constructMaxSegmentTree(const int* arr, int *segmentTree, int low, int high, int pos)
{
  if(low == high)
  {
    segmentTree[pos] = arr[low];
    return;
  }

  int mid = (low + high) / 2;
  constructMaxSegmentTree(arr, segmentTree, low, mid, pos*2+1);
  constructMaxSegmentTree(arr, segmentTree, mid+1, high, pos*2+2);
  segmentTree[pos] = max(segmentTree[pos*2+1], segmentTree[pos*2+2]);
}

int *constructSegmentTree(const int* arr, const int size, const  bool min = false)
{
  int *segmentTree = new int[size * 2];

  if(min)
    constructMinSegmentTree(arr, segmentTree, 0, size-1, 0);
  else
    constructMaxSegmentTree(arr, segmentTree, 0, size-1, 0);

  return segmentTree;
}

int main()
{
  int arr[] = {-1, 3, 4, 0, 2, 1};
  int size  = sizeof(arr) / sizeof(arr[0]);

  int *minSegmentTree = constructSegmentTree(arr, size, true);

  //compute min queries
  cout << minQuery(minSegmentTree, 0, 5, 0, 5, 0) << endl;
  cout << minQuery(minSegmentTree, 1, 5, 0, 5, 0) << endl;
  cout << minQuery(minSegmentTree, 1, 2, 0, 5, 0) << endl;
  cout << minQuery(minSegmentTree, 4, 5, 0, 5, 0) << endl;

  int *maxSegmentTree = constructSegmentTree(arr, size);
  //compute max queries
  cout << maxQuery(maxSegmentTree, 0, 5, 0, 5, 0) << endl;
  cout << maxQuery(maxSegmentTree, 1, 5, 0, 5, 0) << endl;
  cout << maxQuery(maxSegmentTree, 1, 2, 0, 5, 0) << endl;
  cout << maxQuery(maxSegmentTree, 4, 5, 0, 5, 0) << endl;

  return 0;
}