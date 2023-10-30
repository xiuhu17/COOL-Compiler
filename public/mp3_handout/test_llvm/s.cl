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
    test1(aa : Bool, kk: Int) : Bool {
        false
    };
    test2(aa : Bool, kk: Int) : Int {
        0
    };
    test3(aa : Bool, kk: Int) : Int {
        test2(false, 0)
    };
    
};
----------------------------------------------------------
class C inherits B{
    d : Object;
    test1(aa : Bool, kk: Int) : Bool {
        {   
            b <- 2;
            true;
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
    test9(aa : Bool, kk: Int, t : F) : SELF_TYPE {
        self
    };

    test10(aa : Bool, kk: Int, t : F) : String {
        x
    };
};


class G inherits IO{

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