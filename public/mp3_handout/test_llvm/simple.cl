class Main inherits IO{
    c : Int;
    main() : Int {
        {   
            let x : Int in x <- 3;
            let x : Int in x.type_name();
            --c <- new Int;
            0;
        } 
    };
        mainn(a: Int, b: Main, c: Int, d : Int) : Int {
        {   
            --let x : Int in x <- 3;
            --let x : Int in x.type_name();
            -- c <- new Int;
            0;
        } 
    };
};

class B{
    z : B;
    y : SELF_TYPE;
};
class C{
  a : Int;
  b : B;
  c : SELF_TYPE;
};

class D inherits C{
  d : Int;
  e : B;
  k : C;
  f : SELF_TYPE;
  j : Bool;
};
