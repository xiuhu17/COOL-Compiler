class Z{
    test2() : SELF_TYPE {
        {
            0;
            self;
        }
    };};
class B inherits Z{
    
};
----------------------------------------------------------
class C inherits B{
    d : Object;
};


class F inherits C{
    p : C;
    ----------------------------------------------------------------------
    test16() : Int {
        {
            test2(); 
            0;
        }
    };
        test17() : Int {
        {
            p.test2();
            0;
        }
    };

    
    test18() : Int {
        {
            p@B.test2();
            0;
        }
    }; 


        test19() : Int {
        {
            3.type_name();
            0;
        }
    };
    ----------------------------------------------------------------------
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
            --let x : C in x.test2();
            0;
        } 
    };
};