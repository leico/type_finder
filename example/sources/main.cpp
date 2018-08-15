//
//  main.cpp
//  07_variadic
//  Copyright (c) 2018 leico
//  
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//

#include <iostream>
#include <type_traits>
#include "type_finder.h" 

struct A {  };
struct B {  };
struct C {  };

struct AA : public A {  };
struct AB : public A {  };

int main(int argc, const char * argv[]) {

  // same returned not_found
  std :: cout << typeid( type_finder :: same< A, B, C > :: type ).name() << std :: endl ;

  // same returned type B
  std :: cout << typeid( type_finder :: same< B, A, int, double, char, B > :: type ).name() << std :: endl;

  // same_base returned type A
  std :: cout << typeid( type_finder :: same_base< A, B, C, AA > :: type ).name() << std :: endl;

  // same_base returned not_found
  std :: cout << typeid( type_finder :: same_base< AA, int, char, AB, C, B > :: type ).name() << std :: endl;

  // is_same returned false
  std :: cout << std :: boolalpha << type_finder :: is_same< A, B, C > :: value << std :: endl; 
  
  // is_same returned true
  std :: cout << std :: boolalpha << type_finder :: is_same< int, long, double, int > :: value << std :: endl; 

  // is_same_base returned true
  std :: cout << std :: boolalpha << type_finder :: is_same_base< A, B, C, AA > :: value << std :: endl; 

  // is_same_base returned false
  std :: cout << std :: boolalpha << type_finder :: is_same_base< A, int, B, C> :: value << std :: endl; 

  return 0;
}





