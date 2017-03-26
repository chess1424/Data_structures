/* Copyright 2017 Carlos Roberto Martinez Ojeda <carlos.1424@@live.com.mx>
   Topic: Suffix array
   Complexity O(n log^2 n ) */

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct suffix{
  int index;
  int rank[2];
}suffix;

bool mySort(suffix a, suffix b)
{
  if(a.rank[0] != b.rank[0]) return a.rank[0] < b.rank[0];
  else return a.rank[1] < b.rank[1];
}

int* constructSA(string &str)
{
  int n = str.length();
  int *SA = new int[n];
  suffix suffixes[n];

  //first get all inital suffixes
  for(int i = 0; i < n; i++)
  {
    suffixes[i].index = i;
    suffixes[i].rank[0] = str[i] - 'a';
    suffixes[i].rank[1] = (i + 1 < n) ? str[i+1] - 'a' : -1;
  }

  sort(suffixes, suffixes + n, mySort);

  //sort by 4, 8... 2^k elements
  for(int k = 2; k < 2*n; k*=2)
  {
    int indexes[n];

    //assign first rank
    suffix prevSuffix = suffixes[0];
    suffixes[0].rank[0] = 0;
    indexes[suffixes[0].index] = 0;

    for(int i = 1; i < n; i++)
    {
      if(suffixes[i].rank[0] == prevSuffix.rank[0] && suffixes[i].rank[1] ==
         prevSuffix.rank[1])
        suffixes[i].rank[0] = suffixes[i-1].rank[0];
      else
      {
        prevSuffix = suffixes[i];
        suffixes[i].rank[0] = suffixes[i-1].rank[0] + 1;
      }
      indexes[suffixes[i].index] = i;
    }

    //assign second rank
    for(int i = 0; i < n; i++)
    {
      int nextIndex = suffixes[i].index + k;

      if(nextIndex >= n) suffixes[i].rank[1] = -1;
      else suffixes[i].rank[1] = suffixes[indexes[nextIndex]].rank[0];
    }

    sort(suffixes, suffixes + n, mySort);
  }

  //Storing final state of sorting suffixes
  for(int i = 0; i < n; i++)
  {
    SA[i] = suffixes[i].index;
  }

  return SA;
}

int main()
{
  vector <string> v = {"banana", "attcatg", "mississippi"};

  for(auto str : v)
  {
    int *SA = constructSA(str);

    for(int i = 0; i < str.length(); i++)
      cout << SA[i] << " ";
    cout << endl;
  }

  return 0;
}