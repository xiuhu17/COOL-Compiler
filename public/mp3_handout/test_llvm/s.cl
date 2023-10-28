class B {
    a : String;
    b : Int <- 0;
    main() : String {
        {
            let x : Int <- 1 in x.type_name();
            let x : Int in x.type_name();
            let x : Object in 0;
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
        0
    };
};

class C inherits B{
    d : Object;
    test1(aa : Bool, kk: Int) : Object {
        true
    };
};

class Main {
    c: C;
    main() : String {
        {   
            let x : Int in x <- 3;
            let x : Int in x.type_name();
            --let y : C in y <- new C;
            --let x : C in x <- c;
            --let x : C in x.test2(false, 0);
            --0;
        } 
    };
};