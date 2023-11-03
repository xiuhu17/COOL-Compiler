class A {};
class B inherits A{};
class C inherits A{};


class Main inherits IO{
    a : Int;
    b : Object;
    c : Bool;
    d : A;
    main() : Object {
        {   
            --a + 2;
            a + 2;
            a + 2;
            -- a <- new Int;
            -- c <- new Bool;
            a <- (b <- 1);
             let x : SELF_TYPE, x : Main in 0;
            let a : Int , a : Main, a : Bool, a : Int <- 2, a : Bool in if a then 2 else 3 fi;
            let a : Int , a : Main, a : Bool, a : Int <- 2 in if a = 2 then 2 else 3 fi;
            --if new Bool then 2 else 3 fi;
            --a <- if true then 1 else new Int fi ;
            --a <- if true then a <- new Int else new Int fi ;
            --b <- if true then 1 else new Int fi ;
            -- b <- if true then new Int else new Int fi ;
            -- d <- if true then new C else new B fi ;
            let x : Int in 2;
            -- if true then b <- new Int else b <- new Int fi;
            -- if true then 3 else false fi;
            --if true then new Bool else new Bool fi;
            --if true then false else new B fi;

            0;
        } 
    };
};
