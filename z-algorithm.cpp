/* Copyright 2017 Carlos Roberto Martinez Ojeda <carlos.1424@live.com.mx>
   Topic: Z-algorithm
   References: http://web.cs.ucdavis.edu/~gusfield/cs122f10/videolist.html
               http://codeforces.com/blog/entry/3107
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> Zfuntion(string s)
{
  int n = s.length(), L = 0, R = 0, K;
  vector<int> z(n);

  for(int i = 1; i < n; i++){
    if(i > R){
      L = R = i;
      while(R < n && s[R-L] == s[R]) R++;
      z[i] = R-L; R--;
    }
    else{
      K = i - L;
      if(z[K] < R-i+1) z[i] = z[K];
      else{
        L = i;
        while(R < n && s[R-L] == s[R]) R++;
        z[i] = R-L; R--;
      }
    }
  }

  return z;

}

int main()
{
  string s = "aabxaabxcaabxaabxay";
  for(auto z : Zfuntion(s))
    cout << z << " ";
  cout << endl;
  return 0;
}