class A {};
class B inherits A{};
class C inherits A{};


class Main inherits IO{
    a : Int;
    b : Object;
    c : Bool <- new Bool;
    d : A;
    main() : Int {
        {   
           --a + 2;
            --a + 2;
            --a + 2;
            --a <- new Int;
            --c <- new Bool;
            --a <- (b <- 1);
            --let x : SELF_TYPE, x : Main in 0;
            --let a : Int , a : Main, a : Bool, a : Int <- 2, a : Bool in if a then 2 else 3 fi;
           -- let a : Int , a : Main, a : Bool, a : Int <- 2 in if a = 2 then 2 else 3 fi;
            --if new Bool then 2 else 3 fi;
            --a <- if true then 1 else new Int fi ;
            --a <- if true then a <- new Int else new Int fi ;
            --b <- if true then 1 else new Int fi ;
           -- b <- if true then new Int else new Int fi ;
            --d <- if true then new C else new B fi ;
            --let x : Int in 2;
            --if true then b <- new Int else b <- new Int fi;
            --if true then false else false fi;
            --if true then new Bool else new Bool fi;
            --if true then false else new B fi;
             --if b <- false then 2 else 3 fi;
              --while true loop 3 pool;
            -- new Int;
             --if isvoid c then 3 else 4 fi;
            -- a <- 2 + 3;

             --2 + 89;
            --0;
            --2 * 3;
           -- 2 / 3;
            --2 / (3 + 2);
            --3.type_name();
            -- let x : Int <- new Int in 0;
            --new B = new C;
            --1 = new Int;
            --new Int = new Int;
            --if 2 = 2 then 2 else 3 fi;
            --if not new Bool then 2 else 3 fi;
            isvoid true;
            0;
        } 
    };
};
