class Main inherits IO{
    c : Int;
    main() : Object {
        {   
            let x : Int in x <- 3;
            let x : Int in x.type_name();
            --c <- new Int;
            0;
        } 
    };
        mainn(a: Int, b: Main, c: Int, d : Int, f : Bool, j: Int, k : Int) : Int {
        {   
            --let x : Int in x <- 3;
            --let x : Int in x.type_name();
            -- c <- new Int;
            c + 2;
            c + 2;
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
    d : C;
    e : SELF_TYPE;
    f : D;
};
class E inherits D {
    g : B;
    h: C;
    i : D;
    j : E;
    k : SELF_TYPE;
};

(*
class  D inherits C{
    d : C <- new D;
    e : Object <- 1; -- Object <- i32
    g : Int <- new Int; -- i32 <- Int 
    f : Object <- new Int; -- Object <- Object
    x : Int <- 2;
    y : Int <- x + 2;

    gg: Bool <- new Bool;

    test(): Int{
        x + 2
    };
};

class F {
    test1():F{
        self
    };
    test2():Object{
        new Int
    };
    test3():Int{
        0
    };
    test4():Int{
        new Int
    };
    test5():Object{
        let x : Int in x.type_name()
    };
    test6():Object{
        let x : Int in x.copy()
    };
};
*)


-- llvm::Function* test; test.getType(); test.getFunctionType(); test.getname(); 