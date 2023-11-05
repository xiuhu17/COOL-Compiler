-- Test of isvoid

class Base inherits IO {
    test() : Object {
        {
            out_string("Base");
            self;
        }
    }; 
};
class Child1 inherits Base {
    test() : Object {
        {
            out_string("Child1");
            self;
        }
    }; 
};
class Child2 inherits Base {
    test() : Object {
        {
            out_string("Child2");
            self;
        }
    }; 
};
class A {
    func(c : Base) : Int{
        {
            c.test();
            0;
        }
    };
};
class Main inherits IO
{
  x:Main;
  func() : Bool {isvoid x};
  main() : Object {{
	let test : Base <- new Child1, a : A <- new A in a.func(test);
        self;
  }};
};
