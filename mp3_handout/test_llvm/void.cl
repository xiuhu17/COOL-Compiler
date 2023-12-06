class Main inherits IO
{     
  test1 : String;

  func():Bool {2=5};
  main():Object {{ 
		if isvoid test1 then out_string("isvoid") else out_string("notvoid") fi;  
    self;
  }};
};