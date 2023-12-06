
class Main {
    main() : Int {
        {
        let x: Int <- 3 in let y : Int in x + y;
        let x: Int <- 3 in let x : Bool in let x : Int <- 5 in let y : Int in 5;
        let x : Int in let x : Int <- 5 in let x : Bool in let x : Int in let x : Bool <- true in let y : Int in let x : Int <- 3  in y + x; 
        let x : Int, x : Int <- 5 , x : Bool in let x : Int, x : Bool <- true, y : Int in let x : Int <- 3  in y + x; 
        let z : Int <- let x : Int, x : Int <- 5 , x : Bool in let x : Int, x : Bool <- true, y : Int in let x : Int <- 3  in y + x in z + 99;
        }
    };
};
