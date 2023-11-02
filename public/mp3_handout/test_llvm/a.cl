-- Equality test

class A{};
Class B inherits A{};

class Main inherits IO
{     
  test1 : String <- "test";
  test2 : A <- new B;
  test3 : Main;
  y : B;
  x : Int;
  z : Int <- x + 2;
  func():Bool {2=5};
  main():Object {{ 
		let x : A <- new B in out_string("test"); 
	self; 
  }};


  let3(): Object {
    {
      let x : Int <- 0 in 2 +  x;
      self;

    }
  };

    let4(): Object {
    {
      let x : Int <- new Int in 2 +  x;
      self;

    }
  };

    let5(): Int {
    {
      let x : Int <- 5, y : Object in y <- x;
    }
  };

    let2(): Object {
    {
      let x : Int in 2 +  x;
    }
  };
      let22(): Object {
    {
      let x : Int in 2 +  x;
      self;
    }
  };
  let6() : Object {
    {
      let x : Int in {x.type_name(); }; 
    }
  };
  let7() : Object {
    {
      let x : Int in {x.type_name(); x + 2;}; 
    }
  };
    let0(): Object {
    {
      let x : Int, y : Object in y <- x;
    }
  };
    let1(): Object {
    {
      let x : Int, y : Object in y <- x;
      self;
    }
  };
  let11(): Int {
    { 
      y;
      x;
    }
  };
  let33(x : Int, y : B): Int {
    {
      x + 2;
    }
  };
    let34(): Int {
    {
      x + 2;
    }
  };
};

class C{
  a : Int;
  b : B;
  c : SELF_TYPE;
};

class D inherits C{
  d : Int;
  e : B;
  f : SELF_TYPE;
};

  --test1 : String <- "test";
  --test2 : A <- new B;
  --test3 : Main;
  --y : B;
  --x : Int;
  --z : Int <- x + 2;