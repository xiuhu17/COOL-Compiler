-- Equality test

class A{};
class Main inherits IO
{ 
  test1 : String <- "test";
  test2 : A <- new A;
  test3 : Main;
  func():Bool {2=5};
  main():Object {{ 
	if isvoid test3 then out_string(test1) else out_string("fail") fi;
	self; 
  }};
};
