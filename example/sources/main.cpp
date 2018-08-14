//
//  main.cpp
//  07_variadic
//
//  Created by leico_studio on 2018/08/02.
//  Copyright © 2018年 leico_studio. All rights reserved.
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





