#include <iostream>
#include <vector>
#include "myvector.h"

using std::cout;    using std::endl;
using std::string;

int main() {
  //    std::vector<string> myV(5);
  MyVector<string> v(5);



  v.push_back("hello");
  v.push_back("world");

  MyVector<string> copyV = v;
  for(size_t i = 0; i < copyV.size(); ++i) {
      cout << copyV[i] << endl;
    }

  // does bounds checking
  //    cout << v.at(50) << endl;

  /*
       * This doesn't swork because we have not specified
       * const versions of our accessor methods.
       *
       *
       */
  //    const MyVector<string> constV(10, "iamconst");
  //    cout << constV[0] << endl;

  return 0;
}
