-- Equality test

class Main inherits IO
{
  func():Bool {2=5};
  main():Object {{ 
	if func() then out_string("ok") else out_string("not ok") fi;
	self; 
  }};
};
