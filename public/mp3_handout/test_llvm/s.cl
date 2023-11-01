class B {
    a : String;
    b : Int <- 0;
    main() : String {
        {
            let x : Int <- 1 in x.type_name(); 
            let x : Int in x.type_name(); 
            let x : Object in 0; 
            let x : IO in new IO;
            --let x : Int in x.abort();
            --let x : Int in abort();
            let x : Object <- new Object in x.type_name();
        }
    };
    test1(aa : Bool, kk: Int) : SELF_TYPE {
        self
    };
    test2(aa : Bool, kk: Int) : Int {
        0
    };
    test3(aa : Bool, kk: Int, ee : B) : Int {
        test2(false, 0)
    };
    
};
----------------------------------------------------------
class C inherits B{
    d : Object;
    test1(aa : Bool, k: Int) : SELF_TYPE {
        {   
            self;
        }
    };
    test4(aa : Bool, kk: Int) : Bool {
        true
    };
};

class D inherits C{
       y : SELF_TYPE;
    test5(aa : Bool, kk: Int) : Bool {
        true
    };

    test6(aa : Bool, kk: Int) : SELF_TYPE {
        self
    };

    test7(aa : Bool, kk: Int) : D {
        self
    };
};

class E inherits D{

    z : Int;
    test8(aa : Bool, kk: Int) : SELF_TYPE {
        self
    };

};

----------------------------------------------------------

class F inherits E{
    x : String;
    w : E;
    k : Int;
    p : C;
    test9(aa : Bool, kk: Int, t : F) : SELF_TYPE {
        self
    };

    test10(aa : Bool, kk: Int, t : F) : String {
        x
    };

    test11(aa : Bool, kk: Int, t : F) : Int {
        {
        --let x : Int in x.type_name();
        --let x : Int <- 3 in x + 2;
        --let x : Int in x + 2;
        let x : Int <- 3 in x;
        0;
        }
    };

        test12(aa : Bool, kk: Int, t : F) : Int {
        {
        --let x : Int in x.type_name();
        --let x : Int <- 3 in x + 2;
        --let x : Int in x + 2;
        --w.test5(false, 1);
        --w.test6(false, 1);
        --w.test7(false, 1);
        let x : Int <- 3 in x.type_name();
        0;
        }
    };

    test13() : Int {
        let b : B in w.test3(false, 1, b)
    };

    test14() : B {
        self
    };
    test15() : Int {
        test2(false, 1)
    };

    test16() : Int {
        p.test2(false, 1)
    };
};


class G inherits IO{

};

class AA {
    a : Int;
    test1() :Int{
        if true then let x : Int in 3 + 2 else 3 fi
    };
};

class BB inherits AA {
    b : Int; 
    c : Int <- 2; -- first store 0, then store 2
    d : Int <- new Int;
};

class CC {
    a : AA; -- first do default initilization, then do the initialization
    b : BB <- let b : BB in b; -- first do default initilization, then do the initialization
    bb : BB <- new BB;
    c : Int <- if true then 2 else 3 fi;
};

class Main inherits IO{
    c: C;
    main() : Int {
        {   
            let x : Int in x <- 3;
            let x : Int in x.type_name();
            c <- new C;
            --let y : C in y <- new C;
            --let x : C in x <- c;
            --let x : C in x.test2(false, 0);
            0;
        } 
    };
};